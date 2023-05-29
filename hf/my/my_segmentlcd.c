/*
 * my_segmentlcd.c
 *
 *  Created on: 28 May 2023
 *      Author: dominikpapp
 */
#include "my_segmentlcd.h"

// Constant for easier readability as sl_udelay_wait counts in microseconds
const unsigned one_milisec = 1000;

// Sets all ring segments
void SegmentLCD_ARingSet(bool set){
  for(int i = 0; i < 8; i ++)
      SegmentLCD_ARing(i, set);
}

// Turns on all rings in order with "delayMs" delay between each segment
void SegmentLCD_ARingOnDelay(uint16_t delayMs){
  for(int i = 0; i < 8; i ++){
      SegmentLCD_ARing(i, true);
      sl_udelay_wait(delayMs * one_milisec);
  }
}

// Makes ring segments blink. "start_state" if during the first cycle segments should be turned on or off.
// "cycles" defines the cycle count.  "delayMs" defines the delay between each blink in ms
void SegmentLCD_ARingBlink(uint8_t cycles, bool start_state, uint16_t delayMs){
  bool set = start_state;
  for(int i = 0; i < cycles; i ++){
    SegmentLCD_ARingSet(set);
    set = !set;
    sl_udelay_wait(delayMs * one_milisec);
  }
}
