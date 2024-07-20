#include <Arduino.h>
#include <chrono>

const auto initTime = std::chrono::high_resolution_clock::now();

unsigned long micros(void)
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - initTime);
    return duration.count();
}
unsigned long millis(void)
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - initTime);
    return duration.count();
}

void delay(unsigned long ms)
{
    uint32_t start = micros();

    while (ms > 0)
    {
        yield();
        while (ms > 0 && (micros() - start) >= 1000)
        {
            ms--;
            start += 1000;
        }
    }
}
void delayMicroseconds(unsigned long us)
{
    uint32_t start = micros();

    while (us > 0)
    {
        yield(); // 允许其他任务运行

        while (us > 0 && (micros() - start) >= 1)
        {
            us--;
            start++;
        }
    }
}

void pinMode(pin_size_t pin, PinMode mode) {};
void digitalWrite(pin_size_t pin, PinStatus val);
PinStatus digitalRead(pin_size_t pin);
void analogWrite(pin_size_t pin, int val);
int analogRead(pin_size_t pin);

void init() {}