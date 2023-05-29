/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

/***************************************************************************//**
 * FreeRTOS tasks.
 ******************************************************************************/
static void prvTaskHi(void *pvParam) {
  while (1) {
      printf("Task High\n");
      vTaskDelay(configTICK_RATE_HZ);
  }
}

static void prvTaskLo(void *pvParam) {
  while (1) {
      printf("Task Low\n");
      vTaskDelay(configTICK_RATE_HZ / 2);
  }
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  xTaskCreate(
      prvTaskHi,
      "",
      configMINIMAL_STACK_SIZE,
      NULL,
      tskIDLE_PRIORITY + 2,
      NULL
  );

  xTaskCreate(
      prvTaskLo,
      "",
      configMINIMAL_STACK_SIZE,
      NULL,
      tskIDLE_PRIORITY + 1,
      NULL
  );
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}


