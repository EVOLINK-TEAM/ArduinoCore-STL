#include "HW_COUT.h"

namespace arduino
{
    HW_COUT Serial(false);
    int HW_COUT::inputService()
    {
        while (status)
        {
            if (_kbhit())
                buffer += (char)_getch();
        }
        return 1;
    }

    void HW_COUT::begin(unsigned long baudrate)
    {
        if (status || !baudrate)
            return;
        status = true;
        t = std::thread(&HW_COUT::inputService, this);
    }
    void HW_COUT::begin(unsigned long baudrate, uint16_t config)
    {
        return begin(baudrate);
    }
    void HW_COUT::end()
    {
        status = false;
        if (t.joinable())
            t.join();
    }
    int HW_COUT::available()
    {
        if (!status)
        {
            return 0;
        }
        return buffer.length();
    };
    int HW_COUT::peek()
    {
        if (!status)
        {
            return 0;
        }
        return buffer[0];
    };
    int HW_COUT::read()
    {
        if (!status)
        {
            return 0;
        }
        char c = buffer[0];
        buffer = buffer.substring(1, buffer.length() - 1);
        return c;
    };
    void HW_COUT::flush()
    {
        std::cout.flush();
    }
    size_t HW_COUT::write(uint8_t c)
    {
        std::cout.put((char)c);
        return 1;
    }
    HW_COUT::operator bool()
    {
        return status;
    }

    HW_COUT::HW_COUT(bool begin) : status(false)
    {
        if (begin)
            this->begin();
    }
    HW_COUT::~HW_COUT()
    {
        end();
    }
}