#include <iostream>
#include <thread>
#include <chrono>

#include "mainTerminal.h"

int main(int argc, char* argv[])
{
    MainTerminal term;

    while (term.active)
    {
        auto nowClock = std::chrono::system_clock::now();
        term.event();
        // std::cout << "event tick" << std::endl;
        term.refresh_();
        std::this_thread::sleep_until(nowClock + std::chrono::milliseconds(500));
    }
}

