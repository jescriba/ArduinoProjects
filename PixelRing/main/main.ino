#include "modes.h"

#define FALSE                0
#define TRUE                 1
#define POT_PIN              2
#define BUTTON               7
#define POT_MAX              625
#define DEFAULT_INTERVAL     30
#define HELD_INTERVAL        700
#define DEBOUNCE_INTERVAL    30
#define DOUBLE_TAP_INTERVAL  250

typedef enum e_Gesture {
  NONE,
  HELD,
  TAP,
  DOUBLE_TAP,
} Gesture;

/*
  Functions to read sensors
*/
float read_resistor_ratio();
void read_gesture(Gesture *previous_gesture);

/*
  Set Up
*/

void setup() {
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  initialize();
}

/*
  Main Loop
*/
void loop() {
  Gesture gesture = NONE;
  int current_mode_index = 0;
  long current_time;
  Mode mode = mode_0;
  while(true) {
    current_time = millis();
    read_gesture(&gesture);
    switch (gesture) {
      case NONE:
        //Serial.println("NONE");
        mode.execute(&mode);
        break;
      case HELD:
        //Serial.println("HELD");
        mode.initialized = 0;
        mode = mode_held;
        mode.execute(&mode);
        break;
      case TAP:
        //Serial.println("TAP");
        mode.initialized = 0;
        change_mode(&mode, &current_mode_index);
        mode.execute(&mode);                             
        break;
      case DOUBLE_TAP:
        //Serial.println("DOUBLE_TAP");
        mode.initialized = 0;
        mode = mode_off;
        mode.execute(&mode);
        break;
    }
  }
}

/*
  Read potentiometer value as a ratio of it's max value
*/
float read_pot() {
  return analogRead(POT_PIN) / (float)POT_MAX;
}

/*
  Read gesture - determine tap vs double tap vs held
*/
int button_state;
int last_button_state;
unsigned long last_tap_time;
unsigned long last_held_time;
unsigned long last_debounce_time;
void read_gesture(Gesture *previous_gesture) {
  int reading = digitalRead(BUTTON);

  if (reading != last_button_state) {
    last_debounce_time = millis();
  }

  unsigned long debounce_time_difference = (millis() - last_debounce_time);
  if (debounce_time_difference > DEBOUNCE_INTERVAL) {
    if (reading != button_state) {
      button_state = reading;

      unsigned long time_difference = millis() - last_tap_time;
      if (button_state == LOW) {
        last_tap_time = millis();

        if (time_difference < DOUBLE_TAP_INTERVAL) {
          (*previous_gesture) = DOUBLE_TAP;
          return;
        }

        (*previous_gesture) = TAP;
        return;
      }
    } else {
      if (button_state == HIGH && debounce_time_difference > HELD_INTERVAL) {
        (*previous_gesture) = HELD;
        return;
      }
    }
  }

  if ((*previous_gesture) == HELD && reading == HIGH) { 
    (*previous_gesture) = HELD;
    return;
  }

  last_button_state = reading;
  (*previous_gesture) = NONE;
}
