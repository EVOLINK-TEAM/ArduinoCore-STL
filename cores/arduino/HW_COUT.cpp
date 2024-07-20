#include "HW_COUT.h"

namespace arduino
{
    void setNonBlockingInput()
    {
#ifdef _WIN32
        // Windows不需要额外的设置
#else
        struct termios ttystate;
        tcgetattr(STDIN_FILENO, &ttystate);
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_cc[VMIN] = 1;
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
#endif
    }
    bool kbhit()
    {
#ifdef _WIN32
        return _kbhit();
#else
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if (ch != EOF)
        {
            ungetc(ch, stdin);
            return true;
        }

        return false;
#endif
    }
    char getch()
    {
#ifdef _WIN32
        return _getch();
#else
        return getchar();
#endif
    }

    HW_COUT Serial(false);
    int HW_COUT::inputService()
    {
        while (status)
            if (kbhit())
            {
                while (!mutex)
                    ;

                mutex = false;
                char ch = getch();
                buffer += ch;
                if (ch == 0xE0 || ch == 0)
                {
                    ch = getch();
                    buffer += ch;
                }
                mutex = true;
            }
        return 1;
    }

    void HW_COUT::begin(unsigned long baudrate)
    {
        if (status || !baudrate)
            return;
        status = true;
        setNonBlockingInput();
        t = std::thread(&HW_COUT::inputService, this);
    }
    void HW_COUT::begin(unsigned long baudrate, uint16_t config) { return begin(baudrate); }
    void HW_COUT::end()
    {
        status = false;
        if (t.joinable())
            t.join();
    }
    int HW_COUT::available()
    {
        if (!status)
            return 0;
        return buffer.length();
    };
    int HW_COUT::peek()
    {
        if (!status)
            return 0;
        return buffer[0];
    };
    int HW_COUT::read()
    {
        if (!status || !buffer.length())
            return 0;

        while (!mutex)
            ;

        mutex = false;
        int c = buffer[0];
        buffer = String(buffer.c_str() + 1, buffer.length() - 1);
        mutex = true;
        return c;
    };
    void HW_COUT::flush() { std::cout.flush(); }
    size_t HW_COUT::write(uint8_t c)
    {
        std::cout.put((char)c);
        // std::cout << (char)c;
        return 1;
    }
    HW_COUT::operator bool() { return status; }

    HW_COUT::HW_COUT(bool begin) : status(false), mutex(true)
    {
        if (begin)
            this->begin();
    }
    HW_COUT::~HW_COUT() { end(); }
}