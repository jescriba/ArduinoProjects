#define PIXEL_COUNT 24
#define MODE_COUNT  11
#define LIGHT_PIN   6
#define KNOB_PIN    2
#define KNOB_MAX 1023

typedef struct {
  int red;
  int green;
  int blue;
} Color;

typedef struct Event {
  int index;
  unsigned long previous_time;
} Event;

typedef struct Mode {
  int initialized;
  Event *events;
  void (*execute)(Mode *mode);
} Mode;

void initialize();
void fill(Color color);
void update_mode(Mode *mode); 
void change_mode(Mode *mode);
float knob_value();
extern int mode_index;
extern Mode mode_off;
extern Mode mode_held;
extern Mode mode_0;
extern Mode mode_1;
extern Mode mode_2;
extern Mode mode_3;
extern Mode mode_4;
extern Mode mode_5;
extern Mode mode_6;
extern Mode mode_7;
extern Mode mode_8;
extern Mode mode_9;
extern Mode mode_10;
