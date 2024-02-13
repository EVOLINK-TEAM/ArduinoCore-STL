#ifndef _HW_COUT_H_
#define _HW_COUT_H_

#include "api/HardwareSerial.h"
#include <iostream> //output--cout
#include <conio.h>  //input--keyboard
#include <thread>

namespace arduino
{
    class HW_COUT : public HardwareSerial
    {
    private:
        std::thread t;
        String buffer;
        bool status; // flag
        int inputService();

    public:
        void begin(unsigned long = 0) override;
        void begin(unsigned long baudrate, uint16_t config) override;
        void end() override;
        int available() override;
        int peek() override;
        int read() override;
        void flush() override;
        size_t write(uint8_t c) override;
        using Print::write;
        operator bool() override;

        HW_COUT(bool begin = false);
        ~HW_COUT();
    };

    extern HW_COUT Serial;
    typedef HW_COUT UartClass;
}
#endif