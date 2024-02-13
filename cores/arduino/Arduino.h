#define main __main__place__holder__ // cancel main weak symbol
#include "api/ArduinoAPI.h"
#undef main
#include "Serial.h"

int atexit(void (* /*func*/)()) __attribute__((weak));
// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs
#define abs(x) ((x) > 0 ? (x) : -(x))

using namespace arduino;