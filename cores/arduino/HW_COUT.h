#ifndef _HW_COUT_H_
#define _HW_COUT_H_

#include "api/HardwareSerial.h"
#include <iostream>  //output--cout
#include <thread>
#ifdef _WIN32       //input
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

namespace arduino
{
    void setNonBlockingInput();
    bool kbhit();
    char getch();

    class HW_COUT : public HardwareSerial
    {
    private:
        std::thread t;
        String buffer;
        bool status; // flag
        bool mutex;  // flag
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