#include "led_strip.h"
#include "button_gpio.h"
#include "esp_log.h"
#include "gpios.h"

#include "es8388_codec.h"
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"

led_strip_handle_t setup_led(const int gpio, const int count) {
    /// LED strip common configuration
    led_strip_config_t strip_config = {
        .strip_gpio_num = gpio, // The GPIO that connected to the LED strip's data line
        .max_leds = count, // The number of LEDs in the strip,
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
    led_strip_handle_t led_strip = NULL;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    return led_strip;
}

button_handle_t setup_button(const int gpio)  {
    const button_config_t btn_cfg = {0};
    const button_gpio_config_t btn_gpio_cfg = {
        .gpio_num = gpio,
        .active_level = 0,
    };
    button_handle_t button = NULL;
    ESP_ERROR_CHECK(iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &button));
    return button;
}

esp_codec_dev_handle_t setup_es8388_codec() {
    static const audio_codec_ctrl_if_t *ctrl_if_ = NULL;
    audio_codec_i2c_cfg_t i2c_cfg = {
        .port = 0, /*!< I2C port, this port need pre-installed by other modules */
        .addr = ES8388_CODEC_DEFAULT_ADDR, /*!< I2C address, default address can be gotten from codec head files */
        // .bus_handle = , /*!< I2C Master bus handle (for IDFv5.3 or higher version) */
    };
    ctrl_if_ = audio_codec_new_i2c_ctrl(&i2c_cfg);

    static const audio_codec_gpio_if_t *gpio_if_ = NULL;
    gpio_if_ = audio_codec_new_gpio();

    es8388_codec_cfg_t es8388_cfg = {
        .ctrl_if = ctrl_if_, /*!< Codec Control interface */
        .gpio_if = gpio_if_, /*!< Codec GPIO interface */
        .codec_mode = ESP_CODEC_DEV_WORK_MODE_BOTH, /*!< Codec work mode on ADC or DAC */
        .master_mode = false, /*!< Whether codec works as I2S master or not */
        .pa_pin = CE, /*!< PA chip power pin */
        .pa_reverted = false, /*!< false: enable PA when pin set to 1, true: enable PA when pin set to 0 */
        // .hw_gain = ,     /*!< Hardware gain */
    };

    static const audio_codec_data_if_t *data_if_ = NULL;
    audio_codec_i2s_cfg_t i2s_cfg = {
        .port = 0, /* I2S port, this port need pre-installed by other modules */
        // .rx_handle = /* I2S rx handle, need provide on IDF 5.x */
        // .tx_handle = /* I2S tx handle, need provide on IDF 5.x */
    };
    data_if_ = audio_codec_new_i2s_data(&i2s_cfg);

    const audio_codec_if_t *out_codec_if_ = es8388_codec_new(&es8388_cfg);
    esp_codec_dev_cfg_t dev_cfg = {
        .codec_if = out_codec_if_, // codec interface from es8388_codec_new
        .data_if = data_if_, // data interface from audio_codec_new_i2s_data
        .dev_type = ESP_CODEC_DEV_TYPE_IN_OUT, // codec supports both playback and record
    };

    esp_codec_dev_handle_t codec_dev = esp_codec_dev_new(&dev_cfg);

    return codec_dev;
}

void codec_play(esp_codec_dev_handle_t codec_dev) {
    // Below code shows how to play
    esp_codec_dev_set_out_vol(codec_dev, 60);
    esp_codec_dev_sample_info_t fs = {
        .sample_rate = 48000,
        .channel = 2,
        .bits_per_sample = 16,
    };
    esp_codec_dev_open(codec_dev, &fs);
    uint8_t data[256];
    esp_codec_dev_write(codec_dev, data, sizeof(data));
    // Below code shows how to record
    esp_codec_dev_set_in_gain(codec_dev, 30.0);
    esp_codec_dev_read(codec_dev, data, sizeof(data));
    esp_codec_dev_close(codec_dev);
}

void codec_record(esp_codec_dev_handle_t codec_dev) {

}

void app_main(void) {
    button_handle_t encoder_button = setup_button(ROTARY_SW);
    button_handle_t ring_shunt = setup_button(RSH);
    button_handle_t tip_shunt = setup_button(TSH);

    led_strip_handle_t led_strip = setup_led(LED_DIN, LED_COUNT);

    esp_codec_dev_handle_t codec_dev = setup_es8388_codec();

    while (true) {
        //1. play audio through XLR
        //2. record audio through XLR
        //3. play audio through headphone jack if inserted
        //4. update led strip
        //5. listen to rotary encoder
    }
}


