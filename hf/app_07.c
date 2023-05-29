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
#include <semphr.h>

/***************************************************************************//**
 * FreeRTOS tasks.
 ******************************************************************************/
SemaphoreHandle_t  signal;

static void prvTaskSender(void *pvParam) {
  while (1) {
      vTaskDelay(configTICK_RATE_HZ);
      xSemaphoreGive(signal);
  }
}

static void prvTaskReceiver(void *pvParam) {
  while (1) {
      xSemaphoreTake(signal, portMAX_DELAY);
      printf("Signal received!\n");
  }
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  signal = xSemaphoreCreateBinary();

  xTaskCreate(
      prvTaskSender,
      "",
      configMINIMAL_STACK_SIZE,
      NULL,
      tskIDLE_PRIORITY + 2,
      NULL
  );

  xTaskCreate(
      prvTaskReceiver,
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


