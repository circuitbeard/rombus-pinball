#include <arduino.h>
#include <Keyboard.h>

#define RP_BUTTON_COUNT         11

#define BTN_FLIPPER_LEFT        11 // Green
#define BTN_FLIPPER_RIGHT        5 // Purple
#define BTN_MAGNA_SAVE_LEFT     12 // Yellow
#define BTN_MAGNA_SAVE_RIGHT     4 // Grey
#define BTN_START               10 // Blue
#define BTN_COIN                13 // Brown
#define BTN_PLUNGER              6 // White

// Back buttons labeled as if looking
// directly at them with the back of 
// the pinball machine facing you

#define BTN_BACK_LEFT_TOP       A0 // Blue
#define BTN_BACK_LEFT_BOTTOM    A1 // Orange
#define BTN_BACK_RIGHT_TOP      A3 // Yellow
#define BTN_BACK_RIGHT_BOTTOM   A4 // Green

typedef struct
{
  uint8_t state; // what state was the input last in ( HIGH/LOW )
  unsigned long last_change;
} button_state;
