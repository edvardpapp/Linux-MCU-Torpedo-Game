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

#include <sl_udelay.h>

SemaphoreHandle_t  guardian;

static void prvTaskH(void *pvParam)
{
  printf("|                         |                         |         Started         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|                         |                         |  Going to sleep (150ms) |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  vTaskDelay( (150 * configTICK_RATE_HZ) / 1000 );
  printf("|                         |                         |         Waked up        |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|                         |                         |   Acquiring semaphore   |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  xSemaphoreTake(guardian, portMAX_DELAY);
  printf("|                         |                         |    Semaphore acquired   |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|                         |                         |     Doing something     |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|                         |                         |        Job done         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|                         |                         |   Releasing semaphore   |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  xSemaphoreGive(guardian);

  printf("|                         |                         |         Exiting         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  vTaskDelete(NULL);
}

static void prvTaskM(void *pvParam)
{
  printf("|                         |        Started          |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|                         |  Going to sleep (250ms) |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  vTaskDelay( (250 * configTICK_RATE_HZ) / 1000 );
  printf("|                         |         Waked up        |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|                         |Doing something (1000 ms)|                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  // Wait about 1000 ms
  for (uint16_t ms = 0; ms < 10; ms++)
    {
      sl_udelay_wait(100000);

    }
  printf("|                         |       Job done          |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|                         |        Exiting          |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  vTaskDelete(NULL);
}

static void prvTaskL(void *pvParam)
{
  printf("|        Started          |                         |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|   Acquiring semaphore   |                         |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  xSemaphoreTake(guardian, portMAX_DELAY);
  printf("|   Semaphore acquired    |                         |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  // Wait about 400 ms
  for (uint16_t ms = 0; ms < 4; ms++)
    {
      printf("| Doing something (100ms) |                         |                         |\n");
      printf("--------------------------+-------------------------+--------------------------\n");
      sl_udelay_wait(100000);
    }
  printf("|       Job done          |                         |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");

  printf("|   Releasing semaphore   |                         |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  xSemaphoreGive(guardian);

  printf("|        Exiting          |                         |                         |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
  vTaskDelete(NULL);
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  guardian = xSemaphoreCreateMutex();
  //xSemaphoreGive(guardian);

  xTaskCreate
  (
      prvTaskH,
      "High",
      configMINIMAL_STACK_SIZE,
      NULL,
      tskIDLE_PRIORITY + 3,
      NULL
  );

  xTaskCreate
  (
      prvTaskM,
      "Medium",
      configMINIMAL_STACK_SIZE,
      NULL,
      tskIDLE_PRIORITY + 2,
      NULL
  );

  xTaskCreate
  (
      prvTaskL,
      "Low",
      configMINIMAL_STACK_SIZE,
      NULL,
      tskIDLE_PRIORITY + 1,
      NULL
  );

  printf("-------------------------------------------------------------------------------\n");
  printf("|    Low priority task    |  Medium priority task   |    High priority task   |\n");
  printf("--------------------------+-------------------------+--------------------------\n");
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}


