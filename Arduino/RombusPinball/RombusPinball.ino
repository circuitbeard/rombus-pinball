/* 
 *  Borrowed heavily from Pimoronis Picade sketch at https://github.com/pimoroni/Picade-Sketch/tree/master/Picade
 */

#include "RombusPinball.h"
#include "TimerOne.h"
#include <Keyboard.h>

#define DEBOUNCE_DELAY 25

const uint8_t rp_pins[] = { BTN_FLIPPER_LEFT, BTN_FLIPPER_RIGHT, BTN_MAGNA_SAVE_LEFT, BTN_MAGNA_SAVE_RIGHT, BTN_START, BTN_COIN, BTN_PLUNGER, BTN_BACK_LEFT_TOP, BTN_BACK_LEFT_BOTTOM, BTN_BACK_RIGHT_TOP, BTN_BACK_RIGHT_BOTTOM };
const uint8_t rp_keys[] = { KEY_LEFT_ARROW,   KEY_RIGHT_ARROW,   KEY_LEFT_CTRL,       KEY_RIGHT_CTRL,       '1',       '5',      KEY_RETURN,  'u',               'd',                  'q',                KEY_ESC               };

static button_state button_states[RP_BUTTON_COUNT] = {};

void setup() {
  Serial.begin(9600);
  //while(!Serial);
  Serial.setTimeout(100);

  // Setup pins as input with pullup resistor
  for ( uint8_t i = 0; i < RP_BUTTON_COUNT; i++ ) {
    if (rp_pins[i] == BTN_PLUNGER) {
        pinMode(rp_pins[i], INPUT);
    } else {
        pinMode(rp_pins[i], INPUT_PULLUP);
    }
  }

  Timer1.initialize(5000);
  Timer1.attachInterrupt(update);
  Timer1.start(); 
}

void update(void) {
  for (int i = 0; i < RP_BUTTON_COUNT; i++)
  {
    uint8_t state;
    state = !digitalRead(rp_pins[i]);
    if (state != button_states[i].state && (millis() - button_states[i].last_change) > DEBOUNCE_DELAY) // has this input changed state since the last time we checked?
    {
      button_states[i].state = state; // update our state map so we know what's happening with this key in future
      button_states[i].last_change = millis();
      handle_key(i, state);
    }
  }
}

bool handle_key(uint8_t i, uint8_t state) {
  uint8_t pin = rp_pins[i];
  uint8_t key = rp_keys[i];
  
  if (pin == BTN_PLUNGER) {
    state = state ? LOW : HIGH;
  }
  
  if (state) {
    Keyboard.press(key);
  } else {
    Keyboard.release(key);
  }
}

void loop() {
  // Do nothing...
}

