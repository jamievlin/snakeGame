#include "Snake.h"

Snake::Snake(int boundsX, int boundsY, int length) : 
    direction(0), len(length) , pendingGrowth(false), boundX(boundsX), boundY(boundsY)
{
    int startPosX = 10;
    int startPosY = 10;

    for (int i = 0; i < len; i++)
    {
        snakeLine.push_back(intpair(startPosX + i, startPosY));
    }
}

Snake::~Snake()
{

}

void Snake::move()
{
    if (not pendingGrowth)
    {
        snakeLine.pop_front();
    }
    else
    {
        len++;
        pendingGrowth = false;
    }
    intpair head = snakeLine.back();

    switch (direction)
    {
    // counterclockwise
    case 0:
        head.first++;
        break;
    case 1:
        head.second--;
        break;
    case 2:
        head.first--;
        break;
    case 3:
        head.second++;
        break;
    default:
        break;
    }

    snakeLine.push_back(head);
}

bool Snake::checkValid()
{
    std::unordered_set<intpair, boost::hash<intpair>> testSet;

    for (auto const &pts : snakeLine)
    {
        bool outofBounds = pts.first < 0 or pts.second < 0 or pts.first >= boundX or pts.second >= boundY;
        bool duplicate = testSet.count(pts) != 0;
        if (outofBounds or duplicate)
        {
            return false;
        }
        testSet.emplace(pts);
    }

    return true;
}

bool Snake::setDirection(int const &newDirection)
{
    int testDir = newDirection - direction;
    if (testDir == 2 or newDirection > 3 or newDirection < 0)
    {
        return false;
    }
    else
    {
        direction = newDirection;
        return true;
    }
}

void Snake::grow()
{
    pendingGrowth = true;
}