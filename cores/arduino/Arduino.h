#define main __main__place__holder__ // cancel main weak symbol
#include "api/ArduinoAPI.h"
#undef main
#include "Serial.h"
#include "config.h"

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs
#define abs(x) ((x) > 0 ? (x) : -(x))

#ifdef ENABLE_DLOG
#define DLOG(dom, msg)                                                                             \
    {                                                                                              \
        Serial.print("\33[31m\33[1m[");                                                            \
        Serial.print(dom);                                                                         \
        Serial.print("]\33[0m");                                                                   \
        Serial.print(msg);                                                                         \
        Serial.print("\33[32m(");                                                                  \
        Serial.print(micros() / 1000);                                                             \
        Serial.println("ms)\33[0m");                                                               \
    }
#else
#define DLOG(...)
#endif

using namespace arduino;
