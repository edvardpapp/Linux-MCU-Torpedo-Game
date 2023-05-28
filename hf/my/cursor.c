/*
 * cursor.c
 *
 *  Created on: 28 May 2023
 *      Author: dominikpapp
 */
#include <my/cursor.h>

// Initialisation function to be called before and cursor manipulation! Default position is top left segment on LCD
void init_cursor(SegmentLCD_LowerCharSegments_TypeDef CURSOR_POS[SEGMENT_LCD_NUM_OF_LOWER_CHARS]){
  CURSOR_POS[0].a = true; // Top left segment set
}

// Returns on which position the cursor is. Possible values (0-7)
uint8_t getCursorPos(const SegmentLCD_LowerCharSegments_TypeDef CURSOR_POS[SEGMENT_LCD_NUM_OF_LOWER_CHARS]){
  for(int i = 0; i < SEGMENT_LCD_NUM_OF_LOWER_CHARS; i ++)
    if(CURSOR_POS[i].raw > 0)
      return i;
  return 0; // To avoid warning
}

// Moves the cursor upwards once. Confines to leftmost segment. Stepping up from the top segment doesn't go to botton segment.
// G and M segments are handled as one segment
void moveUp(SegmentLCD_LowerCharSegments_TypeDef CURSOR_POS[SEGMENT_LCD_NUM_OF_LOWER_CHARS]){
  uint8_t pos = getCursorPos(CURSOR_POS);
  switch (CURSOR_POS[pos].raw) {
      case bitA:
          break;
      case bitB:
        CURSOR_POS[pos].raw = bitA;
          break;
      case bitC:
        CURSOR_POS[pos].raw = bitM;
          break;
      case bitD:
        CURSOR_POS[pos].raw = bitE;
          break;
      case bitE:
        CURSOR_POS[pos].raw = bitG;
          break;
      case bitF:
        CURSOR_POS[pos].raw = bitA;
          break;
      case bitG:
        CURSOR_POS[pos].raw = bitF;
          break;
      case bitH:
        CURSOR_POS[pos].raw = bitA;
          break;
      case bitJ:
        CURSOR_POS[pos].raw = bitA;
          break;
      case bitK:
        CURSOR_POS[pos].raw = bitA;
          break;
      case bitM:
        CURSOR_POS[pos].raw = bitF;
          break;
      case bitN:
        CURSOR_POS[pos].raw = bitM;
          break;
      case bitP:
        CURSOR_POS[pos].raw = bitG;
          break;
      case bitQ:
        CURSOR_POS[pos].raw = bitG;
          break;
      default:
          break;
  }

}

// Moves the cursor downwards once. Confines to leftmost segment. Stepping down from the bottom segment doesn't go to top segment.
// G and M segments are handled as one segment
void moveDown(SegmentLCD_LowerCharSegments_TypeDef CURSOR_POS[SEGMENT_LCD_NUM_OF_LOWER_CHARS]){
  uint8_t pos = getCursorPos(CURSOR_POS);
  switch (CURSOR_POS[pos].raw) {
      case bitA:
        CURSOR_POS[pos].raw = bitF;
          break;
      case bitB:
        CURSOR_POS[pos].raw = bitM;
          break;
      case bitC:
        CURSOR_POS[pos].raw = bitD;
          break;
      case bitD:
          break;
      case bitE:
        CURSOR_POS[pos].raw = bitD;
          break;
      case bitF:
        CURSOR_POS[pos].raw = bitG;
          break;
      case bitG:
        CURSOR_POS[pos].raw = bitE;
          break;
      case bitH:
        CURSOR_POS[pos].raw = bitG;
          break;
      case bitJ:
        CURSOR_POS[pos].raw = bitG;
          break;
      case bitK:
        CURSOR_POS[pos].raw = bitG;
          break;
      case bitM:
        CURSOR_POS[pos].raw = bitE;
          break;
      case bitN:
        CURSOR_POS[pos].raw = bitD;
          break;
      case bitP:
        CURSOR_POS[pos].raw = bitD;
          break;
      case bitQ:
        CURSOR_POS[pos].raw = bitD;
          break;
      default:
          break;
  }

}

// Moves the cursor left once. Stepping left from the leftmost segment doesn't go to rightmost (7th) right segment.
// G and M segments are handled as one segment
void moveLeft(SegmentLCD_LowerCharSegments_TypeDef CURSOR_POS[SEGMENT_LCD_NUM_OF_LOWER_CHARS]){
  uint8_t pos = getCursorPos(CURSOR_POS);
  switch (CURSOR_POS[pos].raw) {
      case bitA:
        if(pos == 0)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos - 1].raw = bitA;
          break;
      case bitB:
        CURSOR_POS[pos].raw = bitK;
          break;
      case bitC:
        CURSOR_POS[pos].raw = bitN;
          break;
      case bitD:
        if(pos == 0)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos - 1].raw = bitD;
          break;
      case bitE:
        if(pos == 0)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos - 1].raw = bitC;
          break;
      case bitF:
        if(pos == 0)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos - 1].raw = bitB;
          break;
      case bitG:
        if(pos == 0)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos - 1].raw = bitG;
          break;
      case bitH:
        CURSOR_POS[pos].raw = bitF;
          break;
      case bitJ:
        CURSOR_POS[pos].raw = bitH;
          break;
      case bitK:
        CURSOR_POS[pos].raw = bitJ;
          break;
      case bitM:
        if(pos == 0)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos - 1].raw = bitM;
          break;
      case bitN:
        CURSOR_POS[pos].raw = bitP;
          break;
      case bitP:
        CURSOR_POS[pos].raw = bitQ;
          break;
      case bitQ:
        CURSOR_POS[pos].raw = bitE;
          break;
      default:
          break;
  }

}

// Moves the cursor right once. Stepping right from the rightmost segment doesn't go to leftmost (0th) left segment.
// G and M segments are handled as one segment
void moveRight(SegmentLCD_LowerCharSegments_TypeDef CURSOR_POS[SEGMENT_LCD_NUM_OF_LOWER_CHARS]){
  uint8_t pos = getCursorPos(CURSOR_POS);
  switch (CURSOR_POS[pos].raw) {
      case bitA:
        if(pos == SEGMENT_LCD_NUM_OF_LOWER_CHARS - 1)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos + 1].raw = bitA;
          break;
      case bitB:
        if(pos == SEGMENT_LCD_NUM_OF_LOWER_CHARS - 1)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos + 1].raw = bitF;
          break;
      case bitC:
        if(pos == SEGMENT_LCD_NUM_OF_LOWER_CHARS - 1)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos + 1].raw = bitE;
          break;
      case bitD:
        if(pos == SEGMENT_LCD_NUM_OF_LOWER_CHARS - 1)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos + 1].raw = bitD;
          break;
      case bitE:
        CURSOR_POS[pos].raw = bitQ;
          break;
      case bitF:
        CURSOR_POS[pos].raw = bitH;
          break;
      case bitG:
        if(pos == SEGMENT_LCD_NUM_OF_LOWER_CHARS - 1)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos + 1].raw = bitG;
          break;
      case bitH:
        CURSOR_POS[pos].raw = bitJ;
          break;
      case bitJ:
        CURSOR_POS[pos].raw = bitK;
          break;
      case bitK:
        CURSOR_POS[pos].raw = bitB;
          break;
      case bitM:
        if(pos == SEGMENT_LCD_NUM_OF_LOWER_CHARS - 1)
          break;
        CURSOR_POS[pos].raw = 0;
        CURSOR_POS[pos + 1].raw = bitM;
          break;
      case bitN:
        CURSOR_POS[pos].raw = bitC;
          break;
      case bitP:
        CURSOR_POS[pos].raw = bitN;
          break;
      case bitQ:
        CURSOR_POS[pos].raw = bitP;
          break;
      default:
          break;
  }

}

