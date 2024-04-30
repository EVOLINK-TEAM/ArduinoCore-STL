#include <Arduino.h>
#include <chrono>

unsigned long micros(void)
{
    auto start_time = std::chrono::high_resolution_clock::time_point();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return duration.count();
}
unsigned long millis(void)
{
    auto start_time = std::chrono::high_resolution_clock::time_point();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
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

void init() {}