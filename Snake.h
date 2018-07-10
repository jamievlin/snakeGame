#include <deque>
#include <boost/functional/hash.hpp>
#include <unordered_set>

typedef std::pair<int, int> intpair;

class Snake
{
    public:
    Snake(int boundsX, int boundsY, int length = 8);
    ~Snake();

    void move();
    bool checkValid();
    bool setDirection(int const &newDirection);
    std::deque<intpair> const &line = snakeLine;

    int direction;

    void grow();
    
    private: 
    int len;
    bool pendingGrowth;
    int boundX, boundY;

    std::deque<intpair> snakeLine;
};
