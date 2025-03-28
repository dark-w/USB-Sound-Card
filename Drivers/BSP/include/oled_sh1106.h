/*
 * oled_sh1106.h
 *
 *  Created on: Mar 27, 2025
 *      Author: Dark Wang
 */

#ifndef BSP_INCLUDE_OLED_SH1106_H_
#define BSP_INCLUDE_OLED_SH1106_H_

#include "main.h"

#define OLED_X_LEN 128

typedef enum
{
  OLED_SH1106_OK = 0U,
  OLED_SH1106_ERR = 1U
} OLED_SH1106_StatusTypeDef;

OLED_SH1106_StatusTypeDef OLED_SH1106_init();
OLED_SH1106_StatusTypeDef OLED_SH1106_show_chinese(uint8_t x,uint8_t y,uint8_t no);
OLED_SH1106_StatusTypeDef OLED_SH1106_clear();
OLED_SH1106_StatusTypeDef OLED_SH1106_buffer_display(uint8_t buffer_no);
OLED_SH1106_StatusTypeDef OLED_SH1106_buffer_display_dma_start(uint8_t buffer_no);
OLED_SH1106_StatusTypeDef spectrum_buffer_write(uint8_t omega_arr[OLED_X_LEN], uint8_t buffer_no);
#define DISPLAY_BUFFER_PAGE_NUM 8
#define DISPLAY_BUFFER_PAGE_PN 128
extern uint8_t display_buffer_1[DISPLAY_BUFFER_PAGE_NUM][DISPLAY_BUFFER_PAGE_PN];
extern uint8_t display_buffer_2[DISPLAY_BUFFER_PAGE_NUM][DISPLAY_BUFFER_PAGE_PN];

#endif /* BSP_INCLUDE_OLED_SH1106_H_ */
