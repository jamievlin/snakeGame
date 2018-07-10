#include "mainTerminal.h"

MainTerminal::MainTerminal() : active(true), gameContinue(true), counter(0)
{
    initscr();
    noecho();

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, sizeY, sizeX);
    snake = std::unique_ptr<Snake>(new Snake(sizeX, sizeY));

    foodLocation = selectRandomPoint();
}

MainTerminal::~MainTerminal()
{
    endwin();
}

void MainTerminal::handleKeyPress()
{
    int ch = getch();
    int newDir;
    if (ch != ERR)
    {
        switch (ch)
        {
        case KEY_RIGHT:
            newDir = 0;
            break;
        case KEY_UP:
            newDir = 1;
            break;
        case KEY_DOWN:
            newDir = 3;
            break;
        case KEY_LEFT:
            newDir = 2;
            break;

        // other cmds

        case 'q': // 'q'
            gameContinue = false;
            break;

        default:
            newDir = -1;
            break;
        }
        snake->setDirection(newDir);
    }
}

intpair MainTerminal::selectRandomPoint()
{
    std::vector<intpair> candinatePoints;
    std::unordered_set<intpair, boost::hash<intpair>> snakePts;

    for (auto const &pts : snake->line)
    {
        snakePts.emplace(pts);
    }

    for (int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++)
        {
            if (snakePts.count(intpair(i, j)) == 0)
            {
                candinatePoints.push_back(intpair(i, j));
            }
        }
    }

    if (candinatePoints.size() <= 0)
    {
        return intpair(-1, -1);
    }
    else
    {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<int> dist(0, candinatePoints.size() - 1);

        int chosenIndex = dist(generator);

        return candinatePoints[chosenIndex];
    }
}

void MainTerminal::event()
{
    erase();
    handleKeyPress();
    snake->move();

    active = snake->checkValid() and gameContinue;
    if (not active)
    {
        return;
    }

    for (intpair const &pts : snake->line)
    {
        int x = pts.first;
        int y = pts.second;

        mvaddch(y, x, '0');
    }

    if (snake->line.back() == foodLocation)
    {
        snake->grow();
        foodLocation = selectRandomPoint();
    }

    if (foodLocation != intpair(-1, -1))
    {
        mvaddch(foodLocation.second, foodLocation.first, 'X');
    }

    counter++;
}

void MainTerminal::refresh_()
{

    refresh();
}