/*
 * bsp_log.cpp
 *
 *  Created on: 09-Feb-2026
 *      Author: Sivaraj
 */

#if __cplusplus
extern "C"
{
#endif

#include <esp_log.h>

#if __cplusplus	
}
#endif

#include "bsp_log.hpp"

void bsp_log::info(const char* TAG, const char* msg) const
{
	ESP_LOGI(TAG, "%s", msg);
}

void bsp_log::warn(const char* TAG, const char* msg) const
{	
	ESP_LOGW(TAG, "%s", msg);
}

void bsp_log::error(const char* TAG, const char* msg) const
{	
	ESP_LOGE(TAG, "%s", msg);	
}