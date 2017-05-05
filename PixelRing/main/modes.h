#define PIXEL_COUNT 24
#define MODE_COUNT  3
#define LIGHT_PIN   6

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
void change_mode(Mode *mode, int *current_mode_index);
extern Mode mode_off;
extern Mode mode_held;
extern Mode mode_0;
extern Mode mode_1;
extern Mode mode_2;
