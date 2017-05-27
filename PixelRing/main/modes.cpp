#include <Adafruit_NeoPixel.h>
#include "modes.h"
//#include <stdarg.h>

int mode_index = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, LIGHT_PIN, NEO_GRB + NEO_KHZ800);

void set_color(int index, uint32_t rgb) {
  pixels.setPixelColor(index, rgb);
  pixels.show();
}

void fill(uint32_t rgb) {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    pixels.setPixelColor(i, rgb);
    pixels.show();
  }
}

void alternate_colors() {
  
}

uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t random_color(uint8_t r, uint8_t g, uint8_t b) {
  int red = random(r);
  int green = random(g);
  int blue = random(b);
  return color(red, green, blue);
}

void update_mode(Mode **mode) {
    switch (mode_index) {
    case 0:
      *mode = &mode_0;
      mode_index = 0;
      break;
    case 1:
      *mode = &mode_1;
      mode_index = 1;
      break;
    case 2:
      *mode = &mode_2;
      mode_index = 2;
      break;
    case 3:
      *mode = &mode_3;
      mode_index = 3;
      break;
    case 4:
      *mode = &mode_4;
      mode_index = 4;
      break;
    case 5:
      *mode = &mode_5;
      mode_index = 5;
      break;
    case 6:
      *mode = &mode_6;
      mode_index = 6;
      break;
    case 7:
      *mode = &mode_7;
      mode_index = 7;
      break;
    case 8:
      *mode = &mode_8;
      mode_index = 8;
      break; 
    case 9:
      *mode = &mode_9;
      mode_index = 9;
      break; 
    case 10:
      *mode = &mode_10;
      mode_index = 10;
      break;
    case 11:
      *mode = &mode_11;
      mode_index = 11;
      break;
  }
}

void change_mode(Mode **mode) {
  mode_index++;
  mode_index %= MODE_COUNT;

  update_mode(mode);
}

float knob_value() {
  return analogRead(KNOB_PIN);
}

void mode_off_execute(Mode *mode) {
  fill(color(0, 0, 0));
}

void mode_held_execute(Mode *mode) {
  int initialized = mode->initialized;
  if (!initialized) {
    mode->initialized = 1;
    fill(color(0, 0, 0));
  }

  int selected_mode = map(knob_value(), 0, KNOB_MAX, 0, MODE_COUNT - 1);

  unsigned long current_time = millis();
  unsigned long *previous_time = &(mode->events[0].previous_time);
  if (current_time - *previous_time >= 30) {
    for (int i = 0; i < PIXEL_COUNT ; i++) {
      if (i <= selected_mode) {
        set_color(i, color(2, 0, 4));
      } else {
        set_color(i, color(0, 0, 0));
      }
    }
    mode_index = selected_mode;
  }
}

void mode_0_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 1; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  int *index_1;
  index_1 = &mode->events[1].index;

  int *index_2;
  index_2 = &mode->events[2].index;
  
  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  unsigned long *previous_time_2;
  previous_time_2 = &(mode->events[2].previous_time);

  float knob_val = knob_value();

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 500);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, color(2, 0, 0));
    (*index_0)++;
    *index_0 %= PIXEL_COUNT;
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 1000);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, color(0, 0, 2));
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }

  int delay_2 = map(knob_val, 0, KNOB_MAX, 25, 2100);
  if (current_time - *previous_time_2 >= delay_2) {
    set_color(*index_2, color(0, 2, 0));
    (*index_2)++;
    *index_2 %= PIXEL_COUNT;
    *previous_time_2 = current_time;
  }
}

void mode_1_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 2; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  int *index_0;
  index_0 = &mode->events[0].index;
  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  float knob_val = knob_value();

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 300);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, color(2, 2, 2));
    (*index_0)++;
    *index_0 %= PIXEL_COUNT;
    *previous_time_0 = current_time;
  }
}

void mode_2_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 3; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  float knob_val = knob_value();

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 400);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color((int)random(PIXEL_COUNT), random_color(3, 2, 3));
    *previous_time_0 = current_time;
  }
}

void mode_3_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 4; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  int *index_1;
  index_1 = &mode->events[1].index;

  int *index_2;
  index_2 = &mode->events[2].index;
  
  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  unsigned long *previous_time_2;
  previous_time_2 = &(mode->events[2].previous_time);

  float knob_val = knob_value();

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 500);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, color(0, 1, 1));
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, color(1, 1, 0));
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }

  int delay_2 = map(knob_val, 0, KNOB_MAX, 25, 1500);
  if (current_time - *previous_time_2 >= delay_2) {
    set_color(*index_2, color(1, 0, 1));
    (*index_2)++;
    *index_2 %= PIXEL_COUNT;
    *previous_time_2 = current_time;
  }
}

void mode_4_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 5; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  int *index_1;
  index_1 = &mode->events[1].index;
  
  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  float knob_val = knob_value();

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 500);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, color(4, 1, 3));
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, color(2, 0, 0));
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }
}

void mode_5_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 6; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  int *index_1;
  index_1 = &mode->events[1].index;
  
  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  float knob_val = knob_value();
  
  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 500);
  if (current_time - *previous_time_0 >= delay_0) {
    if (*index_0 == *index_1) {
      set_color(*index_0 + 1, color(1, 0, 1));
    } else {
      set_color(*index_0, color(1, 0, 0));
      set_color(*index_0 + 1, color(0, 0, 0));
    }
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, color(0, 0, 1));
    set_color(*index_1 - 1, color(0, 0, 0));
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }
}

void mode_6_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 7; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  int *index_1;
  index_1 = &mode->events[1].index;
  
  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  float knob_val = knob_value();
  
  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 500);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, random_color(2, 0, 2));
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, color(2, 4, 0));
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }
}

void mode_7_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 8; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  int *index_1;
  index_1 = &mode->events[1].index;
  
  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  float knob_val = knob_value();
  
  int delay_0 = map(knob_val, 0, KNOB_MAX, 500, 1000);
  if (current_time - *previous_time_0 >= delay_0) {
    int rand_int = random(3);
    int previous_int = *index_0;
    if (rand_int == 2) {
      (*index_0)++;
    } else if (rand_int == 1) {
      (*index_0)--;
    } else {
      (*index_0) += 2;
    }
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    
    set_color(*index_0, random_color(2, 0, 2));
    set_color(previous_int, color(0, 0, 0));
    
    *previous_time_0 = current_time;
  }
} 

void mode_8_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 9; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index;
  index = &mode->events[0].index;

  unsigned long *previous_time;
  previous_time = &mode->events[0].previous_time;

  float knob_val = knob_value();
  
  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 500);
  if (current_time - *previous_time >= delay_0) {
    set_color(*index, random_color(2, 0, 2));
    (*index)--;
    *index %= PIXEL_COUNT;

    if (*index == 0) {
      *index = PIXEL_COUNT - 1;
    }
    *previous_time = current_time;
  }
} 

void mode_9_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 10; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();

  int *index_1;
  index_1 = &mode->events[1].index;
  
  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  float knob_val = knob_value();

  int rand_int = (int)random(100);
  
  int delay_0 = map(knob_val, 0, KNOB_MAX, 40000, 80000);
  if (current_time - *previous_time_0 >= delay_0) {
    fill(color(0, 0, 0));
    
    *previous_time_0 = current_time;
  }
  
  int delay_1 = map(knob_val, 0, KNOB_MAX, 200, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, random_color(2, 2, 2));
    int rand_int = random(3);
    if (rand_int == 2) {
      (*index_1)++;
    } else if (rand_int == 1) {
      (*index_1)--;
    }
    if (*index_1 == 0) {
      *index_1 = PIXEL_COUNT - 1;
    }
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }
} 
 
void mode_10_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 11; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  int *index_1;
  index_1 = &mode->events[1].index;

  int *index_2;
  index_2 = &mode->events[2].index;
  
  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  unsigned long *previous_time_2;
  previous_time_2 = &(mode->events[2].previous_time);

  float knob_val = knob_value();
  
  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 500);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, random_color(2, 0, 2));
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, random_color(2, 0, 4));
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }
} 

void mode_11_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= 12; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
  
  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  int *index_1;
  index_1 = &mode->events[1].index;

  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  float knob_val = knob_value();

  int semi_sort = 1;
  for (int i = 0; i < PIXEL_COUNT - 1; i++) {
      uint32_t color_1 = pixels.getPixelColor(i);
      uint32_t color_2 = pixels.getPixelColor(i + 1);
      if (color_1 > color_2) {
        semi_sort = 0;
      }
  }
  if (semi_sort) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
      set_color(i, random_color(3, 2, 2));
    }
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    for (int i = 0; i < PIXEL_COUNT - 1; i++) {
      uint32_t color_1 = pixels.getPixelColor(i);
      uint32_t color_2 = pixels.getPixelColor(i + 1);
      if (color_1 > color_2) {
        set_color(i + 1, color_1);
        set_color(i, color_2);
      }
    }
    *previous_time_1 = current_time;
  }
} 

Mode mode_off;
Mode mode_held;
Mode mode_0;
Mode mode_1;
Mode mode_2;
Mode mode_3;
Mode mode_4;
Mode mode_5;
Mode mode_6;
Mode mode_7;
Mode mode_8;
Mode mode_9;
Mode mode_10;
Mode mode_11;
void initialize() {
  pixels.begin(); // This initializes the NeoPixel library.
  
  unsigned long current_time = millis();
  Event *events_off = (Event*)malloc(sizeof(Event));
  events_off[0].index = 0;
  events_off[0].previous_time = current_time;
  mode_off = (Mode) {
    .initialized = 0, .events = events_off, .execute = mode_off_execute
  };

  Event *events_held = (Event*)malloc(sizeof(Event));
  events_held[0].index = 0;
  events_held[0].previous_time = current_time;
  mode_held = (Mode) {
    .initialized = 0, .events = events_held, .execute = mode_held_execute
  };

  Event *events_0 = (Event*)malloc(3 * sizeof(Event));
  events_0[0].index = 0;
  events_0[0].previous_time = current_time;
  events_0[1].index = 0;
  events_0[1].previous_time = current_time;
  events_0[2].index = 0;
  events_0[2].previous_time = current_time;
  mode_0 = (Mode) {
    .initialized = 0, .events = events_0, .execute = mode_0_execute
  };

  Event *events_1 = (Event*)malloc(sizeof(Event));
  events_1[0].index = 0;
  events_1[0].previous_time = current_time;
  mode_1 = (Mode) {
    .initialized = 0, .events = events_1, .execute = mode_1_execute
  };

  Event *events_2 = (Event*)malloc(sizeof(Event));
  events_2[0].index = 0;
  events_2[1].previous_time = current_time;
  mode_2 = (Mode) {
    .initialized = 0, .events = events_2, .execute = mode_2_execute
  };

  Event *events_3 = (Event*)malloc(3 * sizeof(Event));
  events_3[0].index = PIXEL_COUNT;
  events_3[0].previous_time = current_time;
  events_3[1].index = 0;
  events_3[1].previous_time = current_time;
  events_3[2].index = 0;
  events_3[2].previous_time = current_time;
  mode_3 = (Mode) {
    .initialized = 0, .events = events_3, .execute = mode_3_execute
  };

  Event *events_4 = (Event*)malloc(2 * sizeof(Event));
  events_4[0].index = PIXEL_COUNT;
  events_4[0].previous_time = current_time;
  events_4[1].index = 0;
  events_4[1].previous_time = current_time;
  mode_4 = (Mode) {
    .initialized = 0, .events = events_4, .execute = mode_4_execute
  };

  Event *events_5 = (Event*)malloc(3 * sizeof(Event));
  events_5[0].index = PIXEL_COUNT;
  events_5[0].previous_time = current_time;
  events_5[1].index = 0;
  events_5[1].previous_time = current_time;
  events_5[2].index = 0;
  events_5[2].previous_time = current_time;
  mode_5 = (Mode) {
    .initialized = 0, .events = events_5, .execute = mode_5_execute
  };

  Event *events_6 = (Event*)malloc(3 * sizeof(Event));
  events_6[0].index = PIXEL_COUNT;
  events_6[0].previous_time = current_time;
  events_6[1].index = 0;
  events_6[1].previous_time = current_time;
  events_6[2].index = 0;
  events_6[2].previous_time = current_time;
  mode_6 = (Mode) {
    .initialized = 0, .events = events_6, .execute = mode_6_execute
  };

  Event *events_7 = (Event*)malloc(2 * sizeof(Event));
  events_7[0].index = PIXEL_COUNT;
  events_7[0].previous_time = current_time;
  events_7[1].index = 0;
  events_7[1].previous_time = current_time;
  mode_7 = (Mode) {
    .initialized = 0, .events = events_7, .execute = mode_7_execute
  }; 

  Event *events_8 = (Event*)malloc(sizeof(Event));
  events_8[0].index = PIXEL_COUNT;
  events_8[0].previous_time = current_time;
  mode_8 = (Mode) {
    .initialized = 0, .events = events_8, .execute = mode_8_execute
  }; 

  Event *events_9 = (Event*)malloc(2 * sizeof(Event));
  events_9[0].index = PIXEL_COUNT;
  events_9[0].previous_time = current_time;
  events_9[1].index = 0;
  events_9[1].previous_time = current_time;
  mode_9 = (Mode) {
    .initialized = 0, .events = events_9, .execute = mode_9_execute
  }; 

  Event *events_10 = (Event*)malloc(4 * sizeof(Event));
  events_10[0].index = PIXEL_COUNT;
  events_10[0].previous_time = current_time;
  events_10[1].index = 0;
  events_10[1].previous_time = current_time;
  events_10[2].index = 0;
  events_10[2].previous_time = current_time;
  events_10[3].index = 0;
  events_10[3].previous_time = current_time;
  mode_10 = (Mode) {
    .initialized = 0, .events = events_10, .execute = mode_10_execute
  }; 

  Event *events_11 = (Event*)malloc(2 * sizeof(Event));
  events_11[0].index = PIXEL_COUNT;
  events_11[0].previous_time = current_time;
  events_11[1].index = 0;
  events_11[1].previous_time = current_time;
  mode_11 = (Mode) {
    .initialized = 0, .events = events_11, .execute = mode_11_execute
  }; 
}
