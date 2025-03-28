/*
 * oled_sh1106.c
 *
 *  Created on: Mar 27, 2025
 *      Author: Dark Wang
 */

#include "oled_sh1106.h"
#include "main.h"
#include "oledfont.h"
extern I2C_HandleTypeDef hi2c2;



#define ADDR_CMD 0b01111000
#define ADDR_DATA 0b01111010
const uint16_t oled_sh1106_addr_cmd = ADDR_CMD;
const uint16_t oled_sh1106_addr_data = ADDR_DATA;

OLED_SH1106_StatusTypeDef OLED_SH1106_set_pos(unsigned char x, unsigned char y);

uint8_t display_buffer_0[DISPLAY_BUFFER_PAGE_NUM][DISPLAY_BUFFER_PAGE_PN];
uint8_t display_buffer_1[DISPLAY_BUFFER_PAGE_NUM][DISPLAY_BUFFER_PAGE_PN];

static void send_cmd_write(uint8_t data)
{
  uint8_t data_array[2] = {0x00, data};
  if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c2, oled_sh1106_addr_cmd, data_array, 2, 10))
  {
    for (;;) {}
  }
}

static void send_data_write(uint8_t data)
{
  uint8_t data_array[2] = {0x40, data};
  if (HAL_OK != HAL_I2C_Master_Transmit(&hi2c2, oled_sh1106_addr_cmd, data_array, 2, 10))
  {
    for (;;) {}
  }
}

volatile uint8_t i2c_2_dma_flag = DISABLE;
static void send_data_write_dma(uint8_t page_no)
{
//  uint8_t data_array[2] = {0x40, data};
//  i2c_2_dma_flag = ENABLE;
//  if (HAL_OK != HAL_I2C_Master_Transmit_DMA(&hi2c2, oled_sh1106_addr_cmd, display_buffer[page_no], DISPLAY_BUFFER_PAGE_PN))
//  {
//    for (;;) {}
//  }
}

OLED_SH1106_StatusTypeDef OLED_SH1106_init()
{
//  HAL_I2C_Master_Transmit(&hi2c2, DevAddress, pData, Size, Timeout);
  send_cmd_write(0xAE);
  send_cmd_write(0x02);
  send_cmd_write(0x10);
  send_cmd_write(0x40);
  send_cmd_write(0xB0);
  send_cmd_write(0x81);
  send_cmd_write(0xFF);
  send_cmd_write(0xA1);
  send_cmd_write(0xA6);
  send_cmd_write(0xA8);
  send_cmd_write(0x3F);
  send_cmd_write(0xAD);
  send_cmd_write(0x8B);
  send_cmd_write(0x33);
  send_cmd_write(0xC8);
  send_cmd_write(0xD3);
  send_cmd_write(0x00);
  send_cmd_write(0xD5);
  send_cmd_write(0x80);
  send_cmd_write(0xD8);
  send_cmd_write(0x05);
  send_cmd_write(0xAE);
  send_cmd_write(0xD9);
  send_cmd_write(0x1F);
  send_cmd_write(0xDA);
  send_cmd_write(0x12);
  send_cmd_write(0xDB);
  send_cmd_write(0x40);
  send_cmd_write(0xAF);

  return OLED_SH1106_OK;
}

OLED_SH1106_StatusTypeDef OLED_SH1106_clear()
{
  uint8_t i, n;
  for(i = 0; i < 8; i++)
  {
    // 设置页地址 (0 ~ 7)
    send_cmd_write(0xb0 + i);
    send_cmd_write(0x02);
    send_cmd_write(0x10);

    for (n = 0; n < OLED_X_LEN; n++)
      send_data_write(0);
  }

  return OLED_SH1106_OK;
}


OLED_SH1106_StatusTypeDef OLED_SH1106_show_chinese(uint8_t x,uint8_t y,uint8_t no)
{
  uint8_t t, adder = 0;
  OLED_SH1106_set_pos(x, y);

  for (t = 0; t < 16; t++)
  {
    send_data_write(Hzk[2 * no][t]);
    adder += 1;
  }

  OLED_SH1106_set_pos(x, y + 1);
  for (t = 0; t < 16; t++)
  {
    send_data_write(Hzk[2 * no + 1][t]);
    adder += 1;
  }

  return OLED_SH1106_OK;
}

OLED_SH1106_StatusTypeDef OLED_SH1106_set_pos(unsigned char x, unsigned char y)
{
  send_cmd_write(0xb0 + y);
  send_cmd_write(((x & 0xf0) >> 4) | 0x10);
  send_cmd_write((x & 0x0f) | 0x01);

  return OLED_SH1106_OK;
}

OLED_SH1106_StatusTypeDef OLED_SH1106_buffer_display(uint8_t buffer_no)
{
  uint8_t i, n;
  for(i = 0; i < 8; i++)
  {
    // 设置页地址 (0 ~ 7)
    send_cmd_write(0xb0 + i);
    send_cmd_write(0x02);
    send_cmd_write(0x10);

    for (n = 0; n < OLED_X_LEN; n++)
    {
      if (1 == buffer_no)
        send_data_write(display_buffer_1[i][OLED_X_LEN - 1 - n]);
      else if (0 == buffer_no)
        send_data_write(display_buffer_0[i][OLED_X_LEN - 1 - n]);
    }
  }

  return OLED_SH1106_OK;
}

OLED_SH1106_StatusTypeDef OLED_SH1106_buffer_display_dma_start(uint8_t buffer_no)
{
  // 设置页地址 (0 ~ 7)
  send_cmd_write(0xb0 + buffer_no);
  send_cmd_write(0x02);
  send_cmd_write(0x10);
  send_data_write_dma(buffer_no);

  return OLED_SH1106_OK;
}

OLED_SH1106_StatusTypeDef spectrum_buffer_write(uint8_t omega_arr[OLED_X_LEN], uint8_t buffer_no)
{
  uint8_t (*pointer_to_buffer)[OLED_X_LEN];
  if (0 == buffer_no)
  {
    pointer_to_buffer = display_buffer_0;
  }
  else if (1 == buffer_no)
  {
    pointer_to_buffer = display_buffer_1;
  }

  for (int i = 0; i < OLED_X_LEN; i++)
  {
    uint8_t omega_amplitude = omega_arr[i];
    uint32_t data_column_low = 0;
    uint32_t data_column_high = 0;
    if (omega_amplitude < 31)
    {
      data_column_low = (1U << (omega_amplitude + 1)) - 1;
    }
    else if (32 == omega_amplitude)
    {
      data_column_low = 0xFFFFFFFF;
    }
    else if (omega_amplitude < 63)
    {
      data_column_high = (1U << (omega_amplitude - 31)) - 1;
      data_column_low = 0xFFFFFFFF;
    }
    else if (63 == omega_amplitude)
    {
      data_column_high = 0xFFFFFFFF;
      data_column_low = 0xFFFFFFFF;
    }

    pointer_to_buffer[0][i] = (uint8_t)(data_column_low);
    pointer_to_buffer[1][i] = (uint8_t)(data_column_low >> 8);
    pointer_to_buffer[2][i] = (uint8_t)(data_column_low >> 16);
    pointer_to_buffer[3][i] = (uint8_t)(data_column_low >> 24);

    pointer_to_buffer[4][i] = (uint8_t)(data_column_high);
    pointer_to_buffer[5][i] = (uint8_t)(data_column_high >> 8);
    pointer_to_buffer[6][i] = (uint8_t)(data_column_high >> 16);
    pointer_to_buffer[7][i] = (uint8_t)(data_column_high >> 24);
  }

    return OLED_SH1106_OK;
}


