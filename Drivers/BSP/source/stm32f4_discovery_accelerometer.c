/**
  ******************************************************************************
  * @file    stm32f4_discovery_accelerometer.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the
  *          MEMS accelerometers available on STM32F4-Discovery Kit.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery_accelerometer.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32F4_DISCOVERY
  * @{
  */

/** @defgroup STM32F4_DISCOVERY_ACCELEROMETER STM32F4 DISCOVERY ACCELEROMETER
  * @brief  This file includes the motion sensor driver for ACCELEROMETER motion sensor
  *         devices.
  * @{
  */

/** @defgroup STM32F4_DISCOVERY_ACCELEROMETER_Private_TypesDefinitions STM32F4 DISCOVERY ACCELEROMETER Private TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F4_DISCOVERY_ACCELEROMETER_Private_Defines STM32F4 DISCOVERY ACCELEROMETER Private Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F4_DISCOVERY_ACCELEROMETER_Private_Macros STM32F4 DISCOVERY ACCELEROMETER Private Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F4_DISCOVERY_ACCELEROMETER_Private_Variables STM32F4 DISCOVERY ACCELEROMETER Private Variables
  * @{
  */
static ACCELERO_DrvTypeDef *AcceleroDrv;
/**
  * @}
  */

/** @defgroup STM32F4_DISCOVERY_ACCELEROMETER_Private_FunctionPrototypes STM32F4 DISCOVERY ACCELEROMETER Private FunctionPrototypes
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F4_DISCOVERY_ACCELEROMETER_Private_Functions STM32F4 DISCOVERY ACCELEROMETER Private Functions
  * @{
  */

/**
  * @brief  Setx Accelerometer Initialization.
  * @retval ACCELERO_OK if no problem during initialization
  */
uint8_t BSP_ACCELERO_Init(void)
{
  uint8_t ret = ACCELERO_ERROR;
  uint16_t ctrl = 0x0000;
  LIS3DSH_InitTypeDef          l1s3dsh_InitStruct;


  if(Lis3dshDrv.ReadID() == I_AM_LIS3DSH)
  {
    /* Initialize the accelerometer driver structure */
    AcceleroDrv = &Lis3dshDrv;

    /* Set configuration of LIS3DSH MEMS Accelerometer **********************/
    l1s3dsh_InitStruct.Output_DataRate = LIS3DSH_DATARATE_100;
    l1s3dsh_InitStruct.Axes_Enable = LIS3DSH_XYZ_ENABLE;
    l1s3dsh_InitStruct.SPI_Wire = LIS3DSH_SERIALINTERFACE_4WIRE;
    l1s3dsh_InitStruct.Self_Test = LIS3DSH_SELFTEST_NORMAL;
    l1s3dsh_InitStruct.Full_Scale = LIS3DSH_FULLSCALE_2;
    l1s3dsh_InitStruct.Filter_BW = LIS3DSH_FILTER_BW_800;

    /* Configure MEMS: power mode(ODR) and axes enable */
    ctrl = (uint16_t) (l1s3dsh_InitStruct.Output_DataRate | \
                       l1s3dsh_InitStruct.Axes_Enable);

    /* Configure MEMS: full scale and self test */
    ctrl |= (uint16_t) ((l1s3dsh_InitStruct.SPI_Wire    | \
                         l1s3dsh_InitStruct.Self_Test   | \
                         l1s3dsh_InitStruct.Full_Scale  | \
                         l1s3dsh_InitStruct.Filter_BW) << 8);

    /* Configure the accelerometer main parameters */
    AcceleroDrv->Init(ctrl);

    ret = ACCELERO_OK;
  }
  else
  {
    ret = ACCELERO_ERROR;
  }
  return ret;
}

/**
  * @brief  Read ID of Accelerometer component.
  * @retval ID
  */
uint8_t BSP_ACCELERO_ReadID(void)
{
  uint8_t id = 0x00;

  if(AcceleroDrv->ReadID != NULL)
  {
    id = AcceleroDrv->ReadID();
  }
  return id;
}

/**
  * @brief  Reboot memory content of Accelerometer.
  */
void BSP_ACCELERO_Reset(void)
{
  if(AcceleroDrv->Reset != NULL)
  {
    AcceleroDrv->Reset();
  }
}

/**
  * @brief  Configure Accelerometer click IT.
  */
void BSP_ACCELERO_Click_ITConfig(void)
{
  if(AcceleroDrv->ConfigIT != NULL)
  {
    AcceleroDrv->ConfigIT();
  }
}

/**
  * @brief  Clear Accelerometer click IT.
  */
void BSP_ACCELERO_Click_ITClear(void)
{
  if(AcceleroDrv->ClearIT != NULL)
  {
    AcceleroDrv->ClearIT();
  }
}

/**
  * @brief  Get XYZ axes acceleration.
  * @param  pDataXYZ: Pointer to 3 angular acceleration axes.
  *                   pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis
  */
void BSP_ACCELERO_GetXYZ(int16_t *pDataXYZ)
{
  if(AcceleroDrv->GetXYZ != NULL)
  {
    AcceleroDrv->GetXYZ(pDataXYZ);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
