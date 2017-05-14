#include <Adafruit_NeoPixel.h>
#include "modes.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, LIGHT_PIN, NEO_GRB + NEO_KHZ800);

void light_color_at_index(Color color, int index) {
  int red = color.red, green = color.green, blue = color.blue;
  pixels.setPixelColor(index, pixels.Color(red, green, blue));
  pixels.show();
}

int mode_index = 0;

void fill(Color color) {
  int red = color.red, green = color.green, blue = color.blue;
  for (int i = 0; i < PIXEL_COUNT; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
    pixels.show();
  }
}

Color random_color(Color max_color) {
  int red = max_color.red, green = max_color.green, blue = max_color.blue;
  return (Color) {
    (int)random(red), (int)random(green), (int)random(blue)
  };
}

Color random_color_between(Color min_color, Color max_color) {
  int max_red = max_color.red, max_green = max_color.green, max_blue = max_color.blue;
  int min_red = min_color.red, min_green = min_color.green, min_blue = min_color.blue;
  return (Color) {
    min_red + (int)random(max_red), min_green + (int)random(max_green), min_blue + (int)random(max_blue)
  };
}

void update_mode(Mode *mode) {
    switch (mode_index) {
    case 0:
      (*mode) = mode_0;
      mode_index = 0;
      break;
    case 1:
      (*mode) = mode_1;
      mode_index = 1;
      break;
    case 2:
      (*mode) = mode_2;
      mode_index = 2;
      break;
    case 3:
      (*mode) = mode_3;
      mode_index = 3;
      break;
    case 4:
      (*mode) = mode_4;
      mode_index = 4;
      break;
    case 5:
      (*mode) = mode_5;
      mode_index = 5;
      break;
    case 6:
      (*mode) = mode_6;
      mode_index = 6;
      break;
    case 7:
      (*mode) = mode_7;
      mode_index = 7;
      break;
    case 8:
      (*mode) = mode_8;
      mode_index = 8;
      break; 
    case 9:
      (*mode) = mode_9;
      mode_index = 9;
      break; 
    case 10:
      (*mode) = mode_10;
      mode_index = 10;
      break;
  }
}

void change_mode(Mode *mode) {
  mode_index++;
  mode_index %= MODE_COUNT;

  update_mode(mode);
}

float knob_value() {
  return analogRead(KNOB_PIN);
}

void mode_off_execute(Mode *mode) {
  fill((Color) {
    0, 0, 0
  });
}

void mode_held_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  int blah = *initialized;
  Serial.println("executing with index");
  Serial.println(mode_index);
  if (!*initialized) {
    Serial.println("initializing");
    *initialized = 1;
    fill((Color){0, 0, 0});
  }

  int selected_mode = map(knob_value(), 0, KNOB_MAX, 0, MODE_COUNT - 1);

  unsigned long current_time = millis();
  unsigned long *previous_time = &(mode->events[0].previous_time);
  if (current_time - *previous_time >= 30) {
    for (int i = 0; i < PIXEL_COUNT ; i++) {
      if (i <= selected_mode) {
        Color color = (Color){2, 0, 4};
        light_color_at_index(color, i);
      } else {
        light_color_at_index((Color){0, 0, 0}, i);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 1; i++) {
      light_color_at_index(color, i);
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
    Color color = random_color_between((Color) { 1, 0, 0 }, (Color) { 2, 0, 0 });
    light_color_at_index(color, *index_0);
    (*index_0)++;
    *index_0 %= PIXEL_COUNT;
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 1000);
  if (current_time - *previous_time_1 >= delay_1) {
    Color color = random_color_between((Color) { 0, 0, 0 }, (Color) {0, 0, 5 });
    light_color_at_index(color, *index_1);
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }

  int delay_2 = map(knob_val, 0, KNOB_MAX, 25, 2100);
  if (current_time - *previous_time_2 >= delay_2) {
    Color color = random_color_between((Color) { 0, 0, 0 }, (Color) {0, 5, 0 });
    light_color_at_index(color, *index_2);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 2; i++) {
      light_color_at_index(color, i);
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
    Color color = random_color((Color) { 2, 2, 2 });
    light_color_at_index(color, *index_0);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 3; i++) {
      light_color_at_index(color, i);
    }
  }
  
  unsigned long current_time = millis();
  unsigned long *previous_time_0;
  previous_time_0 = &(mode->events[0].previous_time);

  float knob_val = knob_value();

  int delay_0 = map(knob_val, 0, KNOB_MAX, 25, 400);
  if (current_time - *previous_time_0 >= delay_0) {
    Color color = random_color((Color) { 3, 2, 3 });
    light_color_at_index(color, (int)random(PIXEL_COUNT));
    *previous_time_0 = current_time;
  }
}

void mode_3_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 4; i++) {
      light_color_at_index(color, i);
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
    Color color = (Color) {0, 1, 1};
    light_color_at_index(color, *index_0);
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    Color color = (Color) {1, 1, 0};
    light_color_at_index(color, *index_1);
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }

  int delay_2 = map(knob_val, 0, KNOB_MAX, 25, 1500);
  if (current_time - *previous_time_2 >= delay_2) {
    Color color = (Color) {1, 0, 1};
    light_color_at_index(color, *index_2);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 5; i++) {
      light_color_at_index(color, i);
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
    Color color = (Color) {4, 1, 3};
    light_color_at_index(color, *index_0);
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    Color color = (Color) {2, 0, 0};
    light_color_at_index(color, *index_1);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 6; i++) {
      light_color_at_index(color, i);
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
    Color color = (Color) {1, 0, 0};
    if (*index_0 == *index_1) {
      light_color_at_index((Color) {1, 0, 1}, *index_0 + 1);
    } else {
      light_color_at_index(color, *index_0);
      light_color_at_index((Color) {0, 0, 0}, *index_0 + 1);
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
    Color color = (Color) {0, 0, 1};
    light_color_at_index(color, *index_1);
    light_color_at_index((Color) {0, 0, 0}, *index_1 - 1);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 7; i++) {
      light_color_at_index(color, i);
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
    Color color = random_color_between((Color) { 2, 0, 0 }, (Color) {2, 0, 2 });
    light_color_at_index(color, *index_0);
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    Color color = random_color_between((Color) { 1, 3, 0 }, (Color) {2, 4, 0 });
    light_color_at_index(color, *index_1);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 8; i++) {
      light_color_at_index(color, i);
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
    
    Color color = random_color_between((Color) { 0, 0, 1 }, (Color) { 2, 0, 2 });
    light_color_at_index(color, *index_0);
    light_color_at_index((Color){0, 0, 0}, previous_int);
    
    *previous_time_0 = current_time;
  }
} 

void mode_8_execute(Mode *mode) {
  int *initialized;
  initialized = &(mode->initialized);
  if (!*initialized) {
    *initialized = 1;
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 9; i++) {
      light_color_at_index(color, i);
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
    Color color = random_color_between((Color) { 2, 0, 0 }, (Color) {2, 0, 2 });
    light_color_at_index(color, *index);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 10; i++) {
      light_color_at_index(color, i);
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
    fill((Color) {0, 0, 0});
    
    *previous_time_0 = current_time;
  }
  
  int delay_1 = map(knob_val, 0, KNOB_MAX, 200, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    Color color = random_color((Color) { 2, 2, 2 });
    light_color_at_index(color, *index_1);
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
    fill((Color){0, 0, 0});
    Color color = (Color){2, 0, 4};
    for (int i = 1; i <= 11; i++) {
      light_color_at_index(color, i);
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
    Color color = random_color_between((Color) { 2, 0, 0 }, (Color) {2, 0, 2 });
    light_color_at_index(color, *index_0);
    (*index_0)--;
    *index_0 %= PIXEL_COUNT;

    if (*index_0 == 0) {
      *index_0 = PIXEL_COUNT - 1;
    }
    *previous_time_0 = current_time;
  }

  int delay_1 = map(knob_val, 0, KNOB_MAX, 25, 550);
  if (current_time - *previous_time_1 >= delay_1) {
    Color color = random_color_between((Color) { 1, 3, 0 }, (Color) {2, 4, 0 });
    light_color_at_index(color, *index_1);
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
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
}
