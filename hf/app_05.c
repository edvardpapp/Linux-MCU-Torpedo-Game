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
#include <queue.h>

/***************************************************************************//**
 * FreeRTOS tasks.
 ******************************************************************************/
QueueHandle_t  q;

static void prvTaskSender(void *pvParam) {
  uint32_t cntr = 0;

  while (1) {
      vTaskDelay(configTICK_RATE_HZ);
      xQueueSend(q, &cntr, portMAX_DELAY);
      cntr++;
  }
}

static void prvTaskReceiver(void *pvParam) {
  uint32_t cntr;

  while (1) {
      xQueueReceive(q, &cntr, portMAX_DELAY);
      printf("Counter is: %lu\n", cntr);
  }
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  q = xQueueCreate(1, sizeof(uint32_t));

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


