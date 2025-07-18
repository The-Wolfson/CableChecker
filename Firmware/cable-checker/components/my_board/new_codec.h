//
// Created by Joshua Wolfson on 14/7/2025.
//

#ifndef __NEW_CODEC_H__
#define __NEW_CODEC_H__

#include "audio_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize new_codec chip
 *
 * @param cfg configuration of new_codec
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t new_codec_init(audio_hal_codec_config_t *cfg);

/**
 * @brief Deinitialize new_codec chip
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t new_codec_deinit(void);

/**
 * The functions new_codec_ctrl_state and new_codec_config_i2s are not used by this driver.
 * They are kept here to maintain the uniformity and convenience of the interface
 * of the ADF project.
 * These settings for new_codec are burned in firmware and configuration files.
 * Default i2s configuration: 48000Hz, 16bit, Left-Right channels.
 * Use resampling to be compatible with different file types.
 *
 * @brief Control new_codec chip
 *
 * @param mode codec mode
 * @param ctrl_state start or stop decode or encode progress
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t new_codec_ctrl_state(audio_hal_codec_mode_t mode, audio_hal_ctrl_t ctrl_state);

/**
 * @brief Configure new_codec codec mode and I2S interface
 *
 * @param mode codec mode
 * @param iface I2S config
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t new_codec_config_i2s(audio_hal_codec_mode_t mode, audio_hal_codec_i2s_iface_t *iface);

/**
 * @brief mute or unmute the codec
 *
 * @param mute:  true, false
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t new_codec_set_voice_mute(bool mute);

/**
 * @brief  Set voice volume
 *
 * @param volume:  voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t new_codec_set_voice_volume(int volume);

/**
 * @brief Get voice volume
 *
 * @param[out] *volume:  voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t new_codec_get_voice_volume(int *volume);

#ifdef __cplusplus
}
#endif

#endif