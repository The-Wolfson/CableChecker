#ifndef _AUDIO_BOARD_DEFINITION_H_
#define _AUDIO_BOARD_DEFINITION_H_

// ES8388
///I2C
#define CCLK                2 //SCL
#define CDATA               3 //SDA
#define CE                  4
///I2S
#define MCLK                1
#define ASDOUT              10 //DOUT
#define LRCK                9 //WS
#define DSDIN               8 //DIN
#define SCLK                7 //BCLK

#define BUTTON_VOLUP_ID           -1     /* You need to define the GPIO pins of your board */
#define BUTTON_VOLDOWN_ID         -1     /* You need to define the GPIO pins of your board */
#define BUTTON_MUTE_ID            -1     /* You need to define the GPIO pins of your board */
#define BUTTON_SET_ID             -1     /* You need to define the GPIO pins of your board */
#define BUTTON_MODE_ID            -1     /* You need to define the GPIO pins of your board */
#define BUTTON_PLAY_ID            -1     /* You need to define the GPIO pins of your board */
#define PA_ENABLE_GPIO            -1     /* You need to define the GPIO pins of your board */
#define ADC_DETECT_GPIO           -1     /* You need to define the GPIO pins of your board */
#define BATTERY_DETECT_GPIO       -1     /* You need to define the GPIO pins of your board */
#define SDCARD_INTR_GPIO          -1     /* You need to define the GPIO pins of your board */

#define SDCARD_OPEN_FILE_NUM_MAX  -1

#define BOARD_PA_GAIN             (10) /* Power amplifier gain defined by board (dB) */

#define SDCARD_PWR_CTRL             -1
#define ESP_SD_PIN_CLK              -1
#define ESP_SD_PIN_CMD              -1
#define ESP_SD_PIN_D0               -1
#define ESP_SD_PIN_D1               -1
#define ESP_SD_PIN_D2               -1
#define ESP_SD_PIN_D3               -1
#define ESP_SD_PIN_D4               -1
#define ESP_SD_PIN_D5               -1
#define ESP_SD_PIN_D6               -1
#define ESP_SD_PIN_D7               -1
#define ESP_SD_PIN_CD               -1
#define ESP_SD_PIN_WP               -1

extern audio_hal_func_t AUDIO_NEW_CODEC_DEFAULT_HANDLE;

#define AUDIO_CODEC_DEFAULT_CONFIG(){                   \
        .adc_input  = AUDIO_HAL_ADC_INPUT_LINE1,        \
        .dac_output = AUDIO_HAL_DAC_OUTPUT_ALL,         \
        .codec_mode = AUDIO_HAL_CODEC_MODE_BOTH,        \
        .i2s_iface = {                                  \
            .mode = AUDIO_HAL_MODE_SLAVE,               \
            .fmt = AUDIO_HAL_I2S_NORMAL,                \
            .samples = AUDIO_HAL_48K_SAMPLES,           \
            .bits = AUDIO_HAL_BIT_LENGTH_16BITS,        \
        },                                              \
};

#define INPUT_KEY_NUM     0             /* You need to define the number of input buttons on your board */

#define INPUT_KEY_DEFAULT_INFO() {}

#endif
