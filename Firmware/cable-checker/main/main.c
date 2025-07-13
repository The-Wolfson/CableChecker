#include "audio_pipeline.h"
#include "led_strip.h"
#include "button_gpio.h"
#include "es8388.h"
#include "es8388_codec.h"
#include "esp_audio.h"
#include "esp_log.h"
#include "gpios.h"
#include "i2s_stream.h"
#include "iot_button.h"
#include "led_strip_interface.h"
#include "driver/pulse_cnt.h"
#include "audio/short_test.h"

typedef enum {
    MODE_PLAY,
    MODE_RECORD,
    MODE_BOTH
} Mode;

//MARK: Global variables
Mode current_mode;
static bool headphone_inserted = false;
led_strip_handle_t led_strip;

//MARK: Init function
button_handle_t init_button(const int gpio, const int active_level) {
    const button_config_t btn_cfg = {.long_press_time = 3000};
    const button_gpio_config_t btn_gpio_cfg = {
        .gpio_num = gpio,
        .active_level = active_level,
    };
    button_handle_t button = NULL;
    ESP_ERROR_CHECK(iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &button));
    return button;
}

//Doing functions
void flash_leds() {
    for (int i = 1; i < LED_COUNT; i++) {
        led_strip_set_pixel(led_strip, i, 255, 255, 255); // RGB = white
    }
    led_strip_refresh(led_strip);

    vTaskDelay(pdMS_TO_TICKS(500));

    led_strip_clear(led_strip);
}
void play_test() {
    esp_audio_play(, AUDIO_CODEC_TYPE_DECODER, "file://main/audio/short_test.wav", 0);
}

//MARK: Callback functions
void select_mode_cb(void *arg, void *usr_data) {
    Mode new_mode = *(Mode *) usr_data;
    current_mode = new_mode;

    switch (current_mode) {
        case MODE_PLAY:
            led_strip_set_pixel(led_strip, MODE_LED_INDEX, 255, 0, 0);
            break;
        case MODE_RECORD:
            led_strip_set_pixel(led_strip, MODE_LED_INDEX, 0, 255, 0);
            break;
        default:
            led_strip_set_pixel(led_strip, MODE_LED_INDEX, 0, 0, 255);
            break;
    }
    led_strip_refresh(led_strip);
}

void headphone_insert_cb(void *arg, void *usr_data) {
    ESP_LOGI("Headphone", "Inserted");
    headphone_inserted = true;
    flash_leds();
}

void headphone_remove_cb(void *arg, void *usr_data) {
    ESP_LOGI("Headphone", "Removed");
    headphone_inserted = false;
    flash_leds();
}

void encoder_hold_cb(void *arg, void *usr_data) {
    ESP_LOGI("Encoder", "Hold");
    // Handle encoder hold event
    flash_leds();
    play_test();
}

void encoder_click_cb(void *arg, void *usr_data) {
    ESP_LOGI("Encoder", "Clicked");
    // Handle encoder click event
    flash_leds();
}

bool encoder_turned_cb(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx) {
    ESP_LOGI("Encoder", "Turned");
    // Handle encoder click event
    flash_leds();
    return true;
}

//Setup functions
void setup_led() {
    /// LED strip common configuration
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_DIN, // The GPIO that connected to the LED strip's data line
        .max_leds = LED_COUNT, // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812, // LED strip model, it determines the bit timing
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color component format is G-R-B
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };

    /// RMT backend specific configuration
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .resolution_hz = 10 * 1000 * 1000, // RMT counter clock frequency: 10MHz
        .mem_block_symbols = 64, // the memory size of each RMT channel, in words (4 bytes)
        .flags = {
            .with_dma = false, // DMA feature is available on chips like ESP32-S3/P4
        }
    };

    /// Create the LED strip object
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
}

void setup_SP3T() {
    button_handle_t switch_a = init_button(SP3T_A, 0);
    static Mode mode_play = MODE_PLAY;
    iot_button_register_cb(switch_a, BUTTON_ACTIVE, NULL, select_mode_cb, &mode_play);

    button_handle_t switch_b = init_button(SP3T_B, 0);
    static Mode mode_both = MODE_BOTH;
    iot_button_register_cb(switch_b, BUTTON_ACTIVE, NULL, select_mode_cb, &mode_both);

    button_handle_t switch_c = init_button(SP3T_C, 0);
    static Mode mode_record = MODE_RECORD;
    iot_button_register_cb(switch_c, BUTTON_ACTIVE, NULL, select_mode_cb, &mode_record);
}

void setup_ring_shunt() {
    button_handle_t ring_shunt = init_button(RSH, 1);
    iot_button_register_cb(ring_shunt, BUTTON_PRESS_DOWN, NULL, headphone_insert_cb, NULL);
    iot_button_register_cb(ring_shunt, BUTTON_PRESS_UP, NULL, headphone_remove_cb, NULL);
}

void setup_encoder_button() {
    button_handle_t encoder_button = init_button(ROTARY_SW, 0);
    iot_button_register_cb(encoder_button, BUTTON_LONG_PRESS_START, NULL, encoder_hold_cb, NULL);
    iot_button_register_cb(encoder_button, BUTTON_SINGLE_CLICK, NULL, encoder_click_cb, NULL);
}

void setup_rotary_encoder() {
    pcnt_unit_config_t unit_config = {
        .high_limit = 100,
        .low_limit = (-100),
    };
    pcnt_unit_handle_t pcnt_unit = NULL;
    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = ROTARY_CLK,
        .level_gpio_num = ROTARY_DT,
    };
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan_a));

    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = ROTARY_DT,
        .level_gpio_num = ROTARY_CLK,
    };
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_b_config, &pcnt_chan_b));

    pcnt_event_callbacks_t event_callbacks = {
        .on_reach = encoder_turned_cb,
    };
    pcnt_unit_register_event_callbacks(pcnt_unit, &event_callbacks, NULL);
}

//MARK: Main
void app_main(void) {
    setup_led();
    setup_ring_shunt();
    setup_encoder_button();
    setup_rotary_encoder();
    setup_SP3T();
}

/*
Flash leds when any input happens
Led show output
Reserve one led for mode

Input gain is managed by software

When headphones, use half led for output, half for Jack -> click to switch (half that changing flashes)

When headphones, start with volume low
In
Hold for 3 secs to start test
Display input
Flash green/yellow/red
Run for 5
Out
Hold for 3 secs to start test
Generate sine wave/white noise
Start with low volume, let user use encoder to turn up.
Hold for 3 secs to end
Both
Hold for 3 secs to start test
Run for 5
 */
