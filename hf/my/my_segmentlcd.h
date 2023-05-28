/*
 * my_segmentlcd.h
 *
 *  Created on: 28 May 2023
 *      Author: dominikpapp
 *
 *  Provides easier handling of LCD ring
 */

#ifndef MY_MY_SEGMENTLCD_H_
#define MY_MY_SEGMENTLCD_H_

#include <stdbool.h>
#include <stdint.h>
#include <sl_udelay.h>
#include <segmentlcd.h>

void SegmentLCD_ARingSet(bool set);
void SegmentLCD_ARingOnDelay(uint16_t delayMs);
void SegmentLCD_ARingBlink(uint8_t cycles, bool start_state, uint16_t delayMs);

#endif /* MY_MY_SEGMENTLCD_H_ */
