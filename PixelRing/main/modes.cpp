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

void alternate_colors(uint32_t color_1, uint32_t color_2) {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    if (i % 2 == 0) {
      pixels.setPixelColor(i, color_1);
    } else {
      pixels.setPixelColor(i, color_2);
    }
    pixels.show();
  }
}

void alternate_3_colors(uint32_t color_1, uint32_t color_2, uint32_t color_3) {
  for (int i = 0; i < PIXEL_COUNT; i++) {
    if (i % 3 == 0) {
      pixels.setPixelColor(i, color_1);
    } else if (i % 2 == 0) {
      pixels.setPixelColor(i, color_2);
    } else {
      pixels.setPixelColor(i, color_3);
    }
    pixels.show();
  }
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

void initialize_mode(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill(color(0, 0, 0));
    for (int i = 1; i <= mode_index; i++) {
      set_color(i, color(2, 0, 4));
    }
  }
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
    case 12:
      *mode = &mode_12;
      mode_index = 12;
      break;
    case 13:
      *mode = &mode_13;
      mode_index = 13;
      break;
    case 14:
      *mode = &mode_14;
      mode_index = 14;
      break;
    case 15:
      *mode = &mode_15;
      mode_index = 15;
      break;
    case 16:
      *mode = &mode_16;
      mode_index = 16;
      break;
    case 17:
      *mode = &mode_17;
      mode_index = 17;
      break;
    case 18:
      *mode = &mode_18;
      mode_index = 18;
      break;
    case 19:
      *mode = &mode_19;
      mode_index = 19;
      break;
    case 20:
      *mode = &mode_20;
      mode_index = 20;
      break;
    case 21:
      *mode = &mode_21;
      mode_index = 21;
      break;
    case 22:
      *mode = &mode_22;
      mode_index = 22;
      break;
    case 23:
      *mode = &mode_23;
      mode_index = 23;
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

  // Subtracting 10 to avoid the flutter around max value
  int selected_mode = map(knob_value(), 0, KNOB_MAX - 10, 0, MODE_COUNT - 1);

  unsigned long current_time = millis();
  unsigned long *previous_time = &(mode->events[0].previous_time);
  if (current_time - *previous_time >= 30) {
    for (int i = 0; i <= PIXEL_COUNT ; i++) {
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
  initialize_mode(mode);

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
  initialize_mode(mode);

  unsigned long current_time = millis();
  int *index_0;
  index_0 = &mode->events[0].index;
  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  float knob_val = knob_value();

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 300);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, random_color(4, 4, 4));
    (*index_0)++;
    *index_0 %= PIXEL_COUNT;
    *previous_time_0 = current_time;
  }
}

void mode_2_execute(Mode *mode) {
  initialize_mode(mode);

  unsigned long current_time = millis();
  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  float knob_val = knob_value();

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 400);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color((int)random(PIXEL_COUNT), random_color(5, 2, 3));
    *previous_time_0 = current_time;
  }
}

void mode_3_execute(Mode *mode) {
  initialize_mode(mode);

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
  initialize_mode(mode);

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
  initialize_mode(mode);

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
      set_color(*index_0 + 1, color(4, 0, 4));
    } else {
      set_color(*index_0, color(5, 0, 0));
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
    set_color(*index_1, color(0, 0, 5));
    set_color(*index_1 - 1, color(0, 0, 0));
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }
}

void mode_6_execute(Mode *mode) {
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;
  int *index_1;
  index_1 = &mode->events[1].index;

  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  float knob_val = knob_value();
  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 800);
  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 600);
  if (current_time - *previous_time_0 > delay_0) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
      if ((i + *index_0 + 1) % 6 == 0) {
        set_color(i, color(1, 8, 0));
      } else {
        set_color(i, color(8, (i + *index_0) % 6, 0));
      }
    }
    *index_0 += 1;
    *index_0 %= PIXEL_COUNT;

    *previous_time_0 = current_time;
  }
}

void mode_7_execute(Mode *mode) {
  initialize_mode(mode);

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

  int delay_0 = map(knob_val, 0, KNOB_MAX, 500, 1000);
  int delay_1 = map(knob_val, 0, KNOB_MAX, 100, 900);
  int delay_2 = map(knob_val, 0, KNOB_MAX, 200, 1200);
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

    if (*index_0 <= 0) {
      *index_0 = PIXEL_COUNT - 1;
    }

    set_color(*index_0, random_color(5, 0, 5));
    set_color(previous_int, color(0, 0, 0));

    *previous_time_0 = current_time;
  }
  if (current_time - *previous_time_1 >= delay_1) {
    int rand_int = random(2);
    int previous_int = *index_1;
    if (rand_int == 1) {
      (*index_1)++;
    } else {
      (*index_1)--;
    }
    *index_1 %= PIXEL_COUNT;
    if (*index_1 <= 0) {
      *index_1 = PIXEL_COUNT - 1;
    }

    set_color(*index_1, random_color(5, 5, 0));
    set_color(previous_int, color(0, 0, 0));

    *previous_time_1 = current_time;
  }
  if (current_time - *previous_time_2 >= delay_2) {
    int rand_int = random(3);
    int previous_int = *index_2;
    if (rand_int == 1) {
      (*index_2)++;
    } else if (rand_int == 2) {
      (*index_2)--;
    } else {
      (*index_2)+=3;
    }
    *index_2 %= PIXEL_COUNT;
    if (*index_2 <= 0) {
      *index_2 = PIXEL_COUNT - 1;
    }

    set_color(*index_2, random_color(5, 5, 2));
    set_color(previous_int, color(0, 0, 0));

    *previous_time_2 = current_time;
  }
}

void mode_8_execute(Mode *mode) {
  initialize_mode(mode);

  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  float knob_val = knob_value();
  int rotation_direction = map(knob_val, 0, KNOB_MAX - 10, 0, 100);
  int delay_0 = map(knob_val, 0, KNOB_MAX, 5, 250);
  if (current_time - *previous_time_0 > delay_0) {
    int third = PIXEL_COUNT / 3;
    for (int i = 0; i < PIXEL_COUNT; i++) {
      // red then add green then add blue then red
      if (i <= third) {
        set_color((i + *index_0) % PIXEL_COUNT , color(third - i, 0, i));
      } else if (i < 2 * third) {
        set_color((i + *index_0) % PIXEL_COUNT, color(0, i % third, third - i % third));
      } else {
        set_color((i + *index_0) % PIXEL_COUNT, color(i % third, third - i % third, 0));
      }
    }

    if (rotation_direction <= 25) {
      *index_0 += 1;
      *index_0 %= PIXEL_COUNT; 
    } else if (rotation_direction <= 50) {
      *index_0 -= 1;
      *index_0 %= PIXEL_COUNT; 
    } else {
      int rand_direction = random(3);
      if (rand_direction == 1) {
         *index_0 += 1;
        *index_0 %= PIXEL_COUNT; 
      } else {
        *index_0 -= 1;
        *index_0 %= PIXEL_COUNT; 
      }
    }
    *previous_time_0 = current_time;
  }
}

void mode_9_execute(Mode *mode) {
  initialize_mode(mode);

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

  int rand_int = (int)random(100);

  int delay_0 = map(knob_val, 0, KNOB_MAX, 300, 30000);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, color(0, 5, 0));
  
    *index_0 = random(PIXEL_COUNT);
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 50, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, random_color(6, 4, 4));
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
  initialize_mode(mode);

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
    set_color(*index_0, color(3, 5, 0));
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    set_color(*index_1, color(0, 0, 4));
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }

  int delay_2 = map(knob_val, 0, KNOB_MAX, 15, 700);
  if (current_time - *previous_time_2 >= delay_2) {
    set_color(*index_2, color(4, 2, 0));
    (*index_2)++;
    *index_2 %= PIXEL_COUNT;
    *previous_time_2 = current_time;
  }
}

void mode_11_execute(Mode *mode) {
  initialize_mode(mode);

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
      set_color(i, random_color(4, 3, 3));
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

void mode_12_execute(Mode *mode) {
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;
  int *index_1;
  index_1 = &mode->events[1].index;
  int *index_2;
  index_2 = &mode->events[2].index;
  int *index_3;
  index_3 = &mode->events[3].index;
  int *index_4;
  index_4 = &mode->events[4].index;
  int *index_5;
  index_5 = &mode->events[5].index;
  int *index_6;
  index_6 = &mode->events[6].index;
  int *index_7;
  index_7 = &mode->events[7].index;
  int *index_8;
  index_8 = &mode->events[8].index;
  int *index_9;
  index_9 = &mode->events[9].index;

  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;
  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);
  unsigned long *previous_time_2;
  previous_time_2 = &(mode->events[2].previous_time);
  unsigned long *previous_time_3;
  previous_time_3 = &(mode->events[3].previous_time);
  unsigned long *previous_time_4;
  previous_time_4 = &(mode->events[4].previous_time);
  unsigned long *previous_time_5;
  previous_time_5 = &(mode->events[5].previous_time);
  unsigned long *previous_time_6;
  previous_time_6 = &(mode->events[6].previous_time);
  unsigned long *previous_time_7;
  previous_time_7 = &(mode->events[7].previous_time);
  unsigned long *previous_time_8;
  previous_time_8 = &(mode->events[8].previous_time);
  unsigned long *previous_time_9;
  previous_time_9 = &(mode->events[9].previous_time);

  float knob_val = knob_value();
  int rotating_pixel_count = map(knob_val, 0, KNOB_MAX - 10, 0, 10);

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, color(1, 0, 0));
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  if (rotating_pixel_count < 1) {
    return;
  }

  if (current_time - *previous_time_1 >= delay_0) {
      set_color(*index_1, color(0, 1, 0));
      (*index_1)++;
      *index_1 %= PIXEL_COUNT;
      *previous_time_1 = current_time;
   }

  if (rotating_pixel_count < 2) {
    return;
  }

  if (current_time - *previous_time_2 >= delay_0) {
    set_color(*index_2, color(0, 0, 1));
    (*index_2)--;
    *index_2 %= PIXEL_COUNT;
    if (*index_2 == 0) {
      *index_2 = PIXEL_COUNT - 1;
    }
    *previous_time_2 = current_time;
  }

  if (rotating_pixel_count < 3) {
    return;
  }

  if (current_time - *previous_time_3 >= delay_0) {
    set_color(*index_3, color(1, 0, 1));
    (*index_3)++;
    *index_3 %= PIXEL_COUNT;
    *previous_time_3 = current_time;
  }

  if (rotating_pixel_count < 4) {
    return;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 50, 650);
  if (current_time - *previous_time_4 >= delay_1) {
    set_color(*index_4, color(1, 1, 0));
    (*index_4)--;
    *index_4 %= PIXEL_COUNT;

    if (*index_4 == 0) {
      *index_4 = PIXEL_COUNT - 1;
    }
    *previous_time_4 = current_time;
  }

  if (rotating_pixel_count < 5) {
    return;
  }

  if (current_time - *previous_time_5 >= delay_0) {
    set_color(*index_5, color(0, 1, 1));
    (*index_5)++;
    *index_5 %= PIXEL_COUNT;
    *previous_time_5 = current_time;
  }

  if (rotating_pixel_count < 6) {
    return;
  }

  if (current_time - *previous_time_6 >= delay_0) {
    set_color(*index_6, color(2, 0, 1));
    (*index_6)++;
    *index_6 %= PIXEL_COUNT;
    *previous_time_6 = current_time;
  }

  if (rotating_pixel_count < 7) {
    return;
  }

  if (current_time - *previous_time_7 >= delay_0) {
    set_color(*index_7, color(1, 0, 2));
    (*index_7)--;
    *index_7 %= PIXEL_COUNT;
    if (*index_7 == 0) {
      *index_7 = PIXEL_COUNT - 1;
    }
    *previous_time_7 = current_time;
  }

  if (rotating_pixel_count < 8) {
    return;
  }

  if (current_time - *previous_time_8 >= delay_0) {
    set_color(*index_8, color(3, 0, 1));
    (*index_8)++;
    *index_8 %= PIXEL_COUNT;
    *previous_time_8 = current_time;
  }

  if (rotating_pixel_count < 9) {
    return;
  }

  if (current_time - *previous_time_9 >= delay_0) {
    set_color(*index_9, color(3, 1, 0));
    (*index_9)--;
    *index_9 %= PIXEL_COUNT;
    if (*index_9 == 0) {
      *index_9 = PIXEL_COUNT - 1;
    }
    *previous_time_9 = current_time;
  }

}

void mode_13_execute(Mode *mode) {
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;
  int *index_1;
  index_1 = &mode->events[1].index;
  int *index_2;
  index_2 = &mode->events[2].index;

  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);
  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);
  unsigned long *previous_time_2;
  previous_time_2 = &(mode->events[2].previous_time);

  float knob_val = knob_value();
  int rotating_pixel_count = map(knob_val, 0, KNOB_MAX - 10, 0, 4);

  int delay_0 = map(knob_val, 0, KNOB_MAX - 10, 25, 300);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, color(rotating_pixel_count + 1, 0, *index_0 % 3));
    *index_0 += 1;
    *index_0 %= PIXEL_COUNT;
    *previous_time_0 = current_time;
  }

  if (rotating_pixel_count < 1) {
    return;
  }

  if (current_time - *previous_time_1 >= delay_0) {
      set_color(*index_1, color(0, *index_1 % 3, rotating_pixel_count + 1));
      *index_1 += 1;
      *index_1 %= PIXEL_COUNT;
      *previous_time_1 = current_time;
   }

  if (rotating_pixel_count < 2) {
    return;
  }

  if (current_time - *previous_time_2 >= delay_0) {
    set_color(*index_2, color(*index_2 % 3, rotating_pixel_count + 1, 0));
    *index_2 += 1;
    *index_2 %= PIXEL_COUNT;
    *previous_time_2 = current_time;
  }

}

void mode_14_execute(Mode *mode) {
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;
  int *index_1;
  index_1 = &mode->events[1].index;
  int *index_2;
  index_2 = &mode->events[2].index;
  int *index_3;
  index_3 = &mode->events[3].index;
  int *index_4;
  index_4 = &mode->events[4].index;
  int *index_5;
  index_5 = &mode->events[5].index;
  int *index_6;
  index_6 = &mode->events[6].index;
  int *index_7;
  index_7 = &mode->events[7].index;
  int *index_8;
  index_8 = &mode->events[8].index;
  int *index_9;
  index_9 = &mode->events[9].index;

  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;
  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);
  unsigned long *previous_time_2;
  previous_time_2 = &(mode->events[2].previous_time);
  unsigned long *previous_time_3;
  previous_time_3 = &(mode->events[3].previous_time);
  unsigned long *previous_time_4;
  previous_time_4 = &(mode->events[4].previous_time);
  unsigned long *previous_time_5;
  previous_time_5 = &(mode->events[5].previous_time);
  unsigned long *previous_time_6;
  previous_time_6 = &(mode->events[6].previous_time);
  unsigned long *previous_time_7;
  previous_time_7 = &(mode->events[7].previous_time);
  unsigned long *previous_time_8;
  previous_time_8 = &(mode->events[8].previous_time);
  unsigned long *previous_time_9;
  previous_time_9 = &(mode->events[9].previous_time);

  float knob_val = knob_value();
  int rotating_pixel_count = map(knob_val, 0, KNOB_MAX - 10, 0, 10);

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 400);
  if (current_time - *previous_time_0 >= delay_0) {
    set_color(*index_0, color(1, 0, 0));
    set_color(*index_0 + 1, color(0, 0, 0));
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  if (rotating_pixel_count < 1) {
    return;
  }

  if (current_time - *previous_time_1 >= delay_0) {
      set_color(*index_1, color(0, 1, 0));
       set_color(*index_1 - 1, color(0, 0, 0));
      (*index_1)++;
      *index_1 %= PIXEL_COUNT;
      *previous_time_1 = current_time;
   }

  if (rotating_pixel_count < 2) {
    return;
  }

  if (current_time - *previous_time_2 >= delay_0) {
    set_color(*index_2, color(0, 0, 1));
    set_color(*index_2 + 1, color(0, 0, 0));
    (*index_2)--;
    *index_2 %= PIXEL_COUNT;
    if (*index_2 == 0) {
      *index_2 = PIXEL_COUNT - 1;
    }
    *previous_time_2 = current_time;
  }

  if (rotating_pixel_count < 3) {
    return;
  }

  if (current_time - *previous_time_3 >= delay_0) {
    set_color(*index_3, color(1, 0, 1));
    set_color(*index_3 - 1, color(0, 0, 0));
    (*index_3)++;
    *index_3 %= PIXEL_COUNT;
    *previous_time_3 = current_time;
  }

  if (rotating_pixel_count < 4) {
    return;
  }

  if (current_time - *previous_time_4 >= delay_0) {
    set_color(*index_4, color(3, 1, 0));
    set_color(*index_4 + 1, color(0, 0, 0));
    (*index_4)--;
    *index_4 %= PIXEL_COUNT;

    if (*index_4 == 0) {
      *index_4 = PIXEL_COUNT - 1;
    }
    *previous_time_4 = current_time;
  }

  if (rotating_pixel_count < 5) {
    return;
  }

  if (current_time - *previous_time_5 >= delay_0) {
    set_color(*index_5, color(0, 1, 1));
    set_color(*index_5 - 1, color(0, 0, 0));
    (*index_5)++;
    *index_5 %= PIXEL_COUNT;
    *previous_time_5 = current_time;
  }

  if (rotating_pixel_count < 6) {
    return;
  }

  if (current_time - *previous_time_6 >= delay_0) {
    set_color(*index_6, color(0, 2, 1));
    set_color(*index_6 - 1, color(0, 0, 0));
    (*index_6)++;
    *index_6 %= PIXEL_COUNT;
    *previous_time_6 = current_time;
  }

  if (rotating_pixel_count < 7) {
    return;
  }

  if (current_time - *previous_time_7 >= delay_0) {
    set_color(*index_7, color(1, 0, 2));
    set_color(*index_7 + 1, color(0, 0, 0));
    (*index_7)--;
    *index_7 %= PIXEL_COUNT;
    if (*index_7 == 0) {
      *index_7 = PIXEL_COUNT - 1;
    }
    *previous_time_7 = current_time;
  }

  if (rotating_pixel_count < 8) {
    return;
  }

  if (current_time - *previous_time_8 >= delay_0) {
    set_color(*index_8, color(2, 0, 4));
    set_color(*index_8 - 1, color(0, 0, 0));
    (*index_8)++;
    *index_8 %= PIXEL_COUNT;
    *previous_time_8 = current_time;
  }

  if (rotating_pixel_count < 9) {
    return;
  }

  if (current_time - *previous_time_9 >= delay_0) {
    set_color(*index_9, color(1, 1, 1));
    set_color(*index_9 + 1, color(0, 0, 0));
    (*index_9)--;
    *index_9 %= PIXEL_COUNT;
    if (*index_9 == 0) {
      *index_9 = PIXEL_COUNT - 1;
    }
    *previous_time_9 = current_time;
  }
}

void mode_15_execute(Mode *mode) {
  initialize_mode(mode);

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
  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 300);
  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 600);
  int blue = map(knob_val, 0, KNOB_MAX, 0, 4);
  if (current_time - *previous_time_0 > delay_0) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
      if ((i + *index_0 + 1) % 8 == 0) {
        set_color(i, color(8, 1, blue));
      } else {
        set_color(i, color((i + *index_0) % 8, 8, blue));
      }
    }
    *index_0 += 1;
    *index_0 %= PIXEL_COUNT;

    *previous_time_0 = current_time;
  }
}

void mode_16_execute(Mode *mode) {
  initialize_mode(mode);

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
  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 300);
  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 600);
  int red = map(knob_val, 0, KNOB_MAX, 0, 4);
  if (current_time - *previous_time_0 > delay_0) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
      if ((i + *index_0 + 1) % 8 == 0) {
        set_color(i, color(red, 1, 9));
      } else {
        set_color(i, color(red, 8,0));
      }
    }
    *index_0 -= 1;
    *index_0 %= PIXEL_COUNT;

    *previous_time_0 = current_time;
  }
}

void mode_17_execute(Mode *mode) {
  // TODO
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;
  int *index_1;
  index_1 = &mode->events[1].index;

  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);
  unsigned long *previous_time_1;
  previous_time_1 = &(mode->events[1].previous_time);

  float knob_val = knob_value();
  int delay_0 = map(knob_val, 0, KNOB_MAX, 100, 400);
  int delay_1 = map(knob_val, 0, KNOB_MAX, 5, 200);
  if (current_time - *previous_time_1 >= delay_1) {
    *index_1 += 1;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }
  if (current_time - *previous_time_0 >= delay_0) {
    int red, green, blue;
    if ((*index_1 + *index_0) % 3 == 0) {
      red = 4;
      green = 0;
      blue = 0;
    } else if ((*index_1 + *index_0) % 3 == 1) {
      red = 0;
      green = 4;
      blue = 0;
    } else {
      red = 0;
      green = 0;
      blue = 4;
    }
    set_color(*index_0, color(red, green, blue));
    *index_0 += 1;
    *index_0 %= PIXEL_COUNT;
    *previous_time_0 = current_time;
  }
}

void mode_18_execute(Mode *mode) {
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;

  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  float knob_val = knob_value();
  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 700);
  if (current_time - *previous_time_0 > delay_0) {
    for (int i = 0; i < PIXEL_COUNT; i++) {
      if ((i + *index_0 + 1) % 6 == 0) {
        set_color(i, color(6, 0, 1));

      } else {
        set_color(i, color(6, 0, (i + *index_0) % 6));
      }
    }
    *index_0 += 1;
    *index_0 %= PIXEL_COUNT;

    *previous_time_0 = current_time;
  }
}

void mode_19_execute(Mode *mode) {
  // TODO
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;

  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;

  float knob_val = knob_value();
  int delay_0 = map(knob_val, 0, KNOB_MAX, 75, 1000);
  if (current_time - *previous_time_0 >= delay_0) {
//    for (int i )
//    if (*index_0 % 8 == 0) {
//      set_color();
//    } else {
//      
//    }
    *previous_time_0 = current_time;
  }
}

void mode_20_execute(Mode *mode) {
  // TODO
  initialize_mode(mode);
}

void mode_21_execute(Mode *mode) {
  // TODO
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;
  int *index_1;
  index_1 = &mode->events[1].index;

  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;
  unsigned long *previous_time_1;
  previous_time_1 = &mode->events[1].previous_time;

  float knob_val = knob_value();
  int delay_0 = map(knob_val, 0, KNOB_MAX, 100, 2500);
  int delay_1 = map(knob_val, 0, KNOB_MAX, 5, 500);
  if (current_time - *previous_time_0 >= delay_0) {
    if (*index_0 == 1) {
      alternate_3_colors(color(2, 0, 0), color(0, 0, 2), color(0, 2, 0));
      *index_0 = 2;
    } else if (*index_0 == 2) {
      alternate_3_colors(color(0, 2, 0), color(2, 0, 0), color(0, 0, 2));
      *index_0 = 0;
    } else {
      alternate_3_colors(color(0, 0, 2), color(0, 2, 0), color(2, 0, 0));
      *index_0 = 1;
    }
    *previous_time_0 = current_time;
  }

  if (current_time - *previous_time_1 >= delay_1) {
    if (random(2) == 1) {
      *index_1 += 1;
      *index_1 %= PIXEL_COUNT;
    } else {
      *index_1 -= 1;
      *index_1 %= PIXEL_COUNT;
      if (*index_1 < 0) {
        *index_1 = 0; 
      }
    }
    set_color(*index_1, color(3, 0, 2));
    *previous_time_1 = current_time;
  }
}

void mode_22_execute(Mode *mode) {
  initialize_mode(mode);

  unsigned long current_time = millis();
  
  int *index_0;
  index_0 = &mode->events[0].index;

  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  float knob_val = knob_value();
  int delay_0 = map(knob_val, 0, KNOB_MAX, 5, 250);
  if (current_time - *previous_time_0 > delay_0) {
    int third = PIXEL_COUNT / 3;
    for (int i = 0; i < PIXEL_COUNT; i++) {
      // red then add green then add blue then red
      if (i <= third) {
        set_color((i + *index_0) % PIXEL_COUNT , color(third - i, 0, i));
      } else if (i < 2 * third) {
        set_color((i + *index_0) % PIXEL_COUNT, color(0, i % third, third - i % third));
      } else {
        set_color((i + *index_0) % PIXEL_COUNT, color(i % third, third - i % third, 0));
      }
    }
    *index_0 += 1;
    *index_0 %= PIXEL_COUNT; 
    *previous_time_0 = current_time;
  }
}

void mode_23_execute(Mode *mode) {
  // TODO
  initialize_mode(mode);

  unsigned long current_time = millis();

  int *index_0;
  index_0 = &mode->events[0].index;
  int *index_1;
  index_1 = &mode->events[1].index;
  int *index_2;
  index_2 = &mode->events[2].index;
  int *index_3;
  index_3 = &mode->events[2].index;

  unsigned long *previous_time_0;
  previous_time_0 = &mode->events[0].previous_time;
  unsigned long *previous_time_1;
  previous_time_1 = &mode->events[1].previous_time;
  unsigned long *previous_time_2;
  previous_time_2 = &mode->events[2].previous_time;
  unsigned long *previous_time_3;
  previous_time_3 = &mode->events[3].previous_time;

  float knob_val = knob_value();
  int delay_0 = map(knob_val, 0, KNOB_MAX, 80, 1500);
  int delay_1 = map(knob_val, 0, KNOB_MAX, 30, 2500);
  int delay_2 = map(knob_val, 0, KNOB_MAX, 150, 2000);
  int delay_3 = map(knob_val, 0, KNOB_MAX, 150, 1400);
  if (current_time - *previous_time_0 >= delay_0) {
    if (random(2) == 1) {
      *index_0 += 1;
      *index_0 %= PIXEL_COUNT;
    } else {
      *index_0 -= 1;
      *index_0 %= PIXEL_COUNT;
      if (*index_0 < 0) {
        *index_0 = 0; 
      }
    }
    set_color(*index_0, color(6, 0, 1));
    *previous_time_0 = current_time;
  }

  if (current_time - *previous_time_1 >= delay_1) {
    if (random(2) == 1) {
      *index_1 += 1;
      *index_1 %= PIXEL_COUNT;
    } else {
      *index_1 -= 1;
      *index_1 %= PIXEL_COUNT;
      if (*index_1 < 0) {
        *index_1 = 0; 
      }
    }
    set_color(*index_1, color(5, 2, 0));
    *previous_time_1 = current_time;
  }

  if (current_time - *previous_time_2 >= delay_2) {
    if (random(2) == 1) {
      *index_2 += 1;
      *index_2 %= PIXEL_COUNT;
    } else {
      *index_2 -= 1;
      *index_2 %= PIXEL_COUNT;
      if (*index_3 < 0) {
        *index_3 = 0; 
      }
    }
    set_color(*index_2, color(3, 3, 0));
    *previous_time_2 = current_time;
  }

  if (current_time - *previous_time_3 >= delay_3) {
    if (random(2) == 1) {
      *index_3 += 1;
      *index_3 %= PIXEL_COUNT;
    } else {
      *index_3 -= 1;
      *index_3 %= PIXEL_COUNT;
      if (*index_3 < 0) {
        *index_3 = 0; 
      }
    }
    set_color(*index_3, color(0, 1, 3));
    *previous_time_3 = current_time;
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
Mode mode_12;
Mode mode_13;
Mode mode_14;
Mode mode_15;
Mode mode_16;
Mode mode_17;
Mode mode_18;
Mode mode_19;
Mode mode_20;
Mode mode_21;
Mode mode_22;
Mode mode_23;
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

  Event *events_7 = (Event*)malloc(3 * sizeof(Event));
  events_7[0].index = PIXEL_COUNT;
  events_7[0].previous_time = current_time;
  events_7[1].index = 0;
  events_7[1].previous_time = current_time;
  events_7[2].index = 0;
  events_7[2].previous_time = current_time;
  mode_7 = (Mode) {
    .initialized = 0, .events = events_7, .execute = mode_7_execute
  };

  Event *events_8 = (Event*)malloc(2 * sizeof(Event));
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


  Event *events_12 = (Event*)malloc(10 * sizeof(Event));
  events_12[0].index = PIXEL_COUNT;
  events_12[0].previous_time = current_time;
  events_12[1].index = 0;
  events_12[1].previous_time = current_time;
  events_12[2].index = PIXEL_COUNT;
  events_12[2].previous_time = current_time;
  events_12[3].index = 0;
  events_12[3].previous_time = current_time;
  events_12[4].index = PIXEL_COUNT;
  events_12[4].previous_time = current_time;
  events_12[5].index = 0;
  events_12[5].previous_time = current_time;
  events_12[6].index = 0;
  events_12[6].previous_time = current_time;
  events_12[7].index = PIXEL_COUNT;
  events_12[7].previous_time = current_time;
  events_12[8].index = 0;
  events_12[8].previous_time = current_time;
  events_12[9].index = PIXEL_COUNT;
  events_12[9].previous_time = current_time;
  mode_12 = (Mode) {
    .initialized = 0, .events = events_12, .execute = mode_12_execute
  };


  Event *events_13 = (Event*)malloc(3 * sizeof(Event));
  events_13[0].index = PIXEL_COUNT;
  events_13[0].previous_time = current_time;
  events_13[1].index = 0;
  events_13[1].previous_time = current_time;
  events_13[2].index = 0;
  events_13[2].previous_time = current_time;
  mode_13 = (Mode) {
    .initialized = 0, .events = events_13, .execute = mode_13_execute
  };


  Event *events_14 = (Event*)malloc(10 * sizeof(Event));
  events_14[0].index = PIXEL_COUNT;
  events_14[0].previous_time = current_time;
  events_14[1].index = 0;
  events_14[1].previous_time = current_time;
  events_14[2].index = PIXEL_COUNT;
  events_14[2].previous_time = current_time;
  events_14[3].index = 0;
  events_14[3].previous_time = current_time;
  events_14[4].index = PIXEL_COUNT;
  events_14[4].previous_time = current_time;
  events_14[5].index = 0;
  events_14[5].previous_time = current_time;
  events_14[6].index = 0;
  events_14[6].previous_time = current_time;
  events_14[7].index = PIXEL_COUNT;
  events_14[7].previous_time = current_time;
  events_14[8].index = 0;
  events_14[8].previous_time = current_time;
  events_14[9].index = PIXEL_COUNT;
  events_14[9].previous_time = current_time;
  mode_14 = (Mode) {
    .initialized = 0, .events = events_14, .execute = mode_14_execute
  };


  Event *events_15 = (Event*)malloc(2 * sizeof(Event));
  events_15[0].index = PIXEL_COUNT;
  events_15[0].previous_time = current_time;
  events_15[1].index = 0;
  events_15[1].previous_time = current_time;
  mode_15 = (Mode) {
    .initialized = 0, .events = events_15, .execute = mode_15_execute
  };

  Event *events_16 = (Event*)malloc(2 * sizeof(Event));
  events_16[0].index = PIXEL_COUNT;
  events_16[0].previous_time = current_time;
  events_16[1].index = 0;
  events_16[1].previous_time = current_time;
  mode_16 = (Mode) {
    .initialized = 0, .events = events_16, .execute = mode_16_execute
  };

  Event *events_17 = (Event*)malloc(2 * sizeof(Event));
  events_17[0].index = PIXEL_COUNT;
  events_17[0].previous_time = current_time;
  events_17[1].index = 0;
  events_17[1].previous_time = current_time;
  mode_17 = (Mode) {
    .initialized = 0, .events = events_17, .execute = mode_17_execute
  };

  Event *events_18 = (Event*)malloc(2 * sizeof(Event));
  events_18[0].index = PIXEL_COUNT;
  events_18[0].previous_time = current_time;
  events_18[1].index = 0;
  events_18[1].previous_time = current_time;
  mode_18 = (Mode) {
    .initialized = 0, .events = events_18, .execute = mode_18_execute
  };

  Event *events_19 = (Event*)malloc(2 * sizeof(Event));
  events_19[0].index = PIXEL_COUNT;
  events_19[0].previous_time = current_time;
  events_19[1].index = 0;
  events_19[1].previous_time = current_time;
  mode_19 = (Mode) {
    .initialized = 0, .events = events_19, .execute = mode_19_execute
  };

  Event *events_20 = (Event*)malloc(2 * sizeof(Event));
  events_20[0].index = PIXEL_COUNT;
  events_20[0].previous_time = current_time;
  events_20[1].index = 0;
  events_20[1].previous_time = current_time;
  mode_20 = (Mode) {
    .initialized = 0, .events = events_20, .execute = mode_20_execute
  };

  Event *events_21 = (Event*)malloc(2 * sizeof(Event));
  events_21[0].index = PIXEL_COUNT;
  events_21[0].previous_time = current_time;
  events_21[1].index = 0;
  events_21[1].previous_time = current_time;
  mode_21 = (Mode) {
    .initialized = 0, .events = events_21, .execute = mode_21_execute
  };

  Event *events_22 = (Event*)malloc(2 * sizeof(Event));
  events_22[0].index = 0;
  events_22[0].previous_time = current_time;
  events_22[1].index = 0;
  events_22[1].previous_time = current_time;
  mode_22 = (Mode) {
    .initialized = 0, .events = events_22, .execute = mode_22_execute
  };

  Event *events_23 = (Event*)malloc(3 * sizeof(Event));
  events_23[0].index = random(PIXEL_COUNT);
  events_23[0].previous_time = current_time;
  events_23[1].index = random(PIXEL_COUNT);
  events_23[1].previous_time = current_time;
  events_23[2].index = random(PIXEL_COUNT);
  events_23[2].previous_time = current_time;
  events_23[3].index = random(PIXEL_COUNT);
  events_23[3].previous_time = current_time;
  mode_23 = (Mode) {
    .initialized = 0, .events = events_23, .execute = mode_23_execute
  };
}
