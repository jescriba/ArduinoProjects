#include <Adafruit_NeoPixel.h>
#include "modes.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, LIGHT_PIN, NEO_GRB + NEO_KHZ800);

void light_color_at_index(Color color, int index) {
  int red = color.red, green = color.green, blue = color.blue;
  pixels.setPixelColor(index, pixels.Color(red, green, blue));
  pixels.show();
}

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

void change_mode(Mode *mode, int *current_mode_index) {
  switch (*current_mode_index) {
    case 0:
      (*current_mode_index)++;
      (*mode) = mode_1;
      break;
    case 1:
      (*current_mode_index)++;
      (*mode) = mode_2;
      break;
    case 2:
      (*current_mode_index)++;
      (*mode) = mode_0;
      break;
  }
  (*current_mode_index) %= MODE_COUNT;
}

void mode_off_execute(Mode *mode) {
  fill((Color) {
    0, 0, 0
  });
}

void mode_held_execute(Mode *mode) {
  fill((Color) {
    1, 0, 0
  });
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
  if (current_time - *previous_time_0 >= 500) {
    Color color = random_color_between((Color) { 1, 0, 0 }, (Color) { 2, 0, 0 });
    light_color_at_index(color, *index_0);
    (*index_0)++;
    *index_0 %= PIXEL_COUNT;
    *previous_time_0 = current_time;
  }
  if (current_time - *previous_time_1 >= 1000) {
    Color color = random_color_between((Color) { 0, 0, 0 }, (Color) {0, 0, 5 });
    light_color_at_index(color, *index_1);
    (*index_1)++;
    *index_1 %= PIXEL_COUNT;
    *previous_time_1 = current_time;
  }
  if (current_time - *previous_time_2 >= 2100) {
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
  if (current_time - *previous_time_0 >= 300) {
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
  if (current_time - *previous_time_0 >= 300) {
    Color color = random_color((Color) { 2, 2, 2 });
    light_color_at_index(color, (int)random(PIXEL_COUNT));
    *previous_time_0 = 0;
  }
}

Mode mode_off;
Mode mode_held;
Mode mode_0;
Mode mode_1;
Mode mode_2;
void initialize() {
  pixels.begin(); // This initializes the NeoPixel library.
  unsigned long current_time = millis();
  Event mode_off_event = (Event){ 0, current_time };
  Event events_off[1] = {mode_off_event};
  mode_off = (Mode) {
    .initialized = 0, .events = events_off, .execute = mode_off_execute
  };

  Event mode_held_event = (Event){ 0, current_time };
  Event events_held[1] = {mode_held_event};
  mode_held = (Mode) {
    .initialized = 0, .events = events_held, .execute = mode_held_execute
  };

  Event *events_0 = malloc(3 * sizeof(Event));
  events_0[0].index = 0;
  events_0[0].previous_time = current_time;
  events_0[1].index = 0;
  events_0[1].previous_time = current_time;
  events_0[2].index = 0;
  events_0[2].previous_time = current_time;
  mode_0 = (Mode) {
    .initialized = 0, .events = events_0, .execute = mode_0_execute
  };

  Event mode_1_event = (Event){ 0, current_time };
  Event events_1[1] = {mode_1_event};
  mode_1 = (Mode) {
    .initialized = 0, .events = events_1, .execute = mode_1_execute
  };


  Event mode_2_event = (Event){ 0, current_time };
  Event events_2[1] = {mode_2_event};
  mode_2 = (Mode) {
    .initialized = 0, .events = events_2, .execute = mode_2_execute
  };
}
