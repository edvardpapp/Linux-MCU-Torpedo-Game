/*
 * my_init.h
 *
 *  Created on: 28 May 2023
 *      Author: dominikpapp
 *  Provides initialisation code for components
 */

#ifndef MY_INIT_H_
#define MY_INIT_H_

#include <FreeRTOS.h>

#include <stdbool.h>
#include <stdio.h>

#include <em_gpio.h>
#include <em_cmu.h>
#include <em_usart.h>

#include <segmentLCD.h>

#include "pin_config.h"

#include "ships.h"
#include "segmentlcd_individual.h"

void init_lcd(void);
void init_vcom(void);
void init_uart0(void);
void init_map(SegmentLCD_LowerCharSegments_TypeDef MAP[SEGMENT_LCD_NUM_OF_LOWER_CHARS], unsigned level);

#endif /* MY_INIT_H_ */
