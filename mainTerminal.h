#include <random>
#include <memory>
#include <curses.h>
#include "Snake.h"

class MainTerminal
{
  public:
    MainTerminal();
    ~MainTerminal();

    void event();
    void refresh_();

    bool active;
    bool gameContinue;
  private:
    int sizeX, sizeY;
    intpair foodLocation;
    uint64_t counter;
    std::unique_ptr<Snake> snake;

    void handleKeyPress();
    intpair selectRandomPoint();
};