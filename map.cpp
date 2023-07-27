#include <string>
#include <cstdlib>
#include <vector>

#include <iostream>
#include "map.h"

using namespace std;


Map::Map(int gameBoardWidth, int gameBoardHeight, int initialObstacleNum, int initialPowerPathLength, int mapNumber)
        : mGameBoardWidth(gameBoardWidth), mGameBoardHeight(gameBoardHeight), mInitialObstacleNum(initialObstacleNum), mInitialPowerPathLength(initialPowerPathLength)
{
    this->initializeMap(mapNumber);
}


void Map::initializeMap(int level)
{
    int centerX = this->mGameBoardWidth/2 ;
    int centerY = this->mGameBoardHeight / 2;
    if (level == 1){
        for (int i = 0; i < 15; i ++)
        {
            this->obstacle.push_back(SnakeBody(centerX-20 + i, centerY - 4));
            this->obstacle.push_back(SnakeBody(centerX+19 - i, centerY - 4));
        }

        for (int i = 0; i < 40; i ++)
        {
            this->obstacle.push_back(SnakeBody(centerX -20+ i, centerY + 4));
        }
    }
    else if (level == 2) {
        for (int i = 0; i < 15; i ++)
        {
            this->obstacle.push_back(SnakeBody(centerX - 10 + i, centerY + 6));
        }
        for (int i = 0; i < 3; i ++)
        {
            this->obstacle.push_back(SnakeBody(centerX + 5 + 2*i, centerY + 5 - i));
            this->obstacle.push_back(SnakeBody(centerX + 6 + 2*i, centerY + 5 - i));
        }
        for (int i = 1; i < 8; i++ ) {
            this->obstacle.push_back(SnakeBody(centerX-20+i, centerY-5));
            this->obstacle.push_back(SnakeBody(centerX+11+i, centerY-5));
        }
        for (int i = 0; i < 18; i++) {
            this->obstacle.push_back(SnakeBody(centerX-30, centerY-9+i));
            this->obstacle.push_back(SnakeBody(centerX+29, centerY-9+i));
        }
            this->obstacle.push_back(SnakeBody(centerX-15, centerY-4));
            this->obstacle.push_back(SnakeBody(centerX+16, centerY-4));
    }
    else if (level == 3) {
        for (int i = 0; i < 40; i ++)
        {
            this->obstacle.push_back(SnakeBody(centerX-20 + i, centerY));
        }

        for (int i = 0; i < 40; i ++)
        {
            this->obstacle.push_back(SnakeBody(centerX -20+ i, centerY + 7));
        }
        for (int i = 1; i <= 6; i++ ) {
            this->obstacle.push_back(SnakeBody(centerX-20, centerY + i));
            this->obstacle.push_back(SnakeBody(centerX+19, centerY + i));
        }
        for (int i = 0; i < 22; i++) {
            this->obstacle.push_back(SnakeBody(centerX-40+i, centerY+10-i));
            this->obstacle.push_back(SnakeBody(centerX+39-i, centerY+10-i));
        }
    }

    else if (level == 4){
        this->obstacle.push_back(SnakeBody(centerX + centerY-1, centerY-1 +centerY-1));
        this->obstacle.push_back(SnakeBody(centerX - centerY+1, centerY-1 +centerY-1));
        this->obstacle.push_back(SnakeBody(centerX, centerY));
        for (int i = 1; i <= centerY-2; i++){
            this->obstacle.push_back(SnakeBody(centerX + i, centerY-1 + i));
            this->obstacle.push_back(SnakeBody(centerX - i, centerY-1 + i));
            this->obstacle.push_back(SnakeBody(centerX + i, centerY-1 - i));
            this->obstacle.push_back(SnakeBody(centerX - i, centerY-1 - i));
        }
        for (int i = 1; i < mGameBoardHeight-1; i+=2) {
            this->obstacle.push_back(SnakeBody(centerX - 30, i));
            this->obstacle.push_back(SnakeBody(centerX - 31, i+1));
            this->obstacle.push_back(SnakeBody(centerX + 30, i));
            this->obstacle.push_back(SnakeBody(centerX + 31, i+1));
        }
    }

    else{
        for (int i = 0; i < 22; i++){
            this->obstacle.push_back(SnakeBody(centerX + 16, 1+i));
            this->obstacle.push_back(SnakeBody(centerX - 16, 1+i));
        }for (int i = 0; i < 10; i++){
            this->obstacle.push_back(SnakeBody(centerX + 30, 7+i));
            this->obstacle.push_back(SnakeBody(centerX - 30, 7+i));
        }
    }
}

vector<SnakeBody>& Map::getObstacle()
{
    return this->obstacle;
}


int Map::getObstacleNum()
{
    return this->obstacle.size();
}


vector<SnakeBody>& Map::getPowerPath()
{
    return this->powerPath;
}

int Map::getPowerPathLength()
{
    return this->powerPath.size();
}

void Map::setPowerPath(vector<SnakeBody> pp)
{
    this->powerPath = pp;
}

void Map::resetPowerPath()
{
    this->powerPath.clear();
}

void Map::popEndPowerPath()
{
    this->powerPath.pop_back();
}

void Map::popStartPowerPath()
{
    auto it = this->powerPath.begin();
    this->powerPath.erase(it);
}


void Map::powerPathCase_2(int x, int y)
{
    this->powerPath.push_back(SnakeBody(x, y));
    this->powerPath.push_back(SnakeBody(x+1, y));
    this->powerPath.push_back(SnakeBody(x+2, y));
    this->powerPath.push_back(SnakeBody(x+3, y));
    this->powerPath.push_back(SnakeBody(x+4, y));
    this->powerPath.push_back(SnakeBody(x+5, y));
    this->powerPath.push_back(SnakeBody(x+6, y));
    this->powerPath.push_back(SnakeBody(x+7, y));
    this->powerPath.push_back(SnakeBody(x+8, y));
    this->powerPath.push_back(SnakeBody(x+9, y));
}


void Map::powerPathCase_3(int x, int y)
{
    this->powerPath.push_back(SnakeBody(x, y));
    this->powerPath.push_back(SnakeBody(x+1, y));
    this->powerPath.push_back(SnakeBody(x+2, y));
    this->powerPath.push_back(SnakeBody(x+2, y+1));
    this->powerPath.push_back(SnakeBody(x+2, y+2));
    this->powerPath.push_back(SnakeBody(x+2, y+3));
    this->powerPath.push_back(SnakeBody(x+2, y+4));
    this->powerPath.push_back(SnakeBody(x+2, y+5));
    this->powerPath.push_back(SnakeBody(x+2, y+6));
    this->powerPath.push_back(SnakeBody(x+2, y+7));
}

void Map::powerPathCase_4(int x, int y)
{
    this->powerPath.push_back(SnakeBody(x, y));
    this->powerPath.push_back(SnakeBody(x+1, y));
    this->powerPath.push_back(SnakeBody(x+2, y));
    this->powerPath.push_back(SnakeBody(x+2, y+1));
    this->powerPath.push_back(SnakeBody(x+2, y+2));
    this->powerPath.push_back(SnakeBody(x+1, y+2));
    this->powerPath.push_back(SnakeBody(x, y+2));
    this->powerPath.push_back(SnakeBody(x, y+3));
    this->powerPath.push_back(SnakeBody(x, y+4));
    this->powerPath.push_back(SnakeBody(x+1, y+4));
}

void Map::powerPathCase_5(int x, int y)
{
    int randomNum = rand()%4;
    switch (randomNum)
    {
        case 0:
            for (int i = 0; i < 5; i++){
                this->powerPath.push_back(SnakeBody(x+i, y));
            }for (int i = 1; i < 5; i++){
                this->powerPath.push_back(SnakeBody(x+4, y+i));
            }break;
        case 1:
            for (int i = 0; i < 5; i++){
                this->powerPath.push_back(SnakeBody(x-i, y));
            }for (int i = 1; i < 5; i++){
                this->powerPath.push_back(SnakeBody(x-4, y+i));
            }break;
        case 2:
            for (int i = 0; i < 5; i++){
                this->powerPath.push_back(SnakeBody(x, y+i));
            }for (int i = 1; i < 5; i++){
                this->powerPath.push_back(SnakeBody(x+i, y+4));
            }break;
        case 3:
            for (int i = 0; i < 5; i++){
                this->powerPath.push_back(SnakeBody(x, y+i));
            }for (int i = 1; i < 5; i++){
                this->powerPath.push_back(SnakeBody(x-i, y+4));
            }break;
    }
}