#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include "snake.h"


class Map
{
public:

    Map(int gameBoardWidth, int gameBoardHeight, int initialObstacleNum, int initialPowerPathLength, int mapNumber);
    void initializeMap(int level);
    std::vector<SnakeBody>& getObstacle();
    std::vector<SnakeBody>& getPowerPath();
    void setPowerPath(std::vector<SnakeBody> pp);
    void popStartPowerPath();
    void popEndPowerPath();
    void resetPowerPath();
    void powerPathCase_2(int x, int y);
    void powerPathCase_3(int x, int y);
    void powerPathCase_4(int x, int y);
    void powerPathCase_5(int x, int y);
    int getPowerPathLength();
    int getObstacleNum();

private:

    std::vector<SnakeBody> obstacle;
    std::vector<SnakeBody> powerPath;
    const int mGameBoardWidth;
    const int mGameBoardHeight;
    const int mInitialObstacleNum;
    const int mInitialPowerPathLength;
};

#endif // MAP_H_INCLUDED
