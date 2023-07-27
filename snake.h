#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

enum class Direction
{
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3,
};

class SnakeBody
{
public:
    SnakeBody();
    SnakeBody(int x, int y);
    int getX() const;
    int getY() const;
    bool operator == (const SnakeBody& snakeBody);
private:
    int mX;
    int mY;
};

class Bullet
{
public:
    Bullet();
    Bullet(int x, int y);
    int getX() const;
    int getY() const;
    Direction mdir;
private:
    int mX;
    int mY;
};

// Snake class should have no depency on the GUI library
class Snake
{
public:
    //Snake();
    Snake(int gameBoardWidth, int gameBoardHeight, int initialSnakeLength);
    // Set random seed
    void setRandomSeed();
    // Initialize snake
    void initializeSnake();
    // Checking API for generating random food
    bool isPartOfSnake(int x, int y);
    void senseFood(SnakeBody food);
    bool touchFood();

    void senseObstacle(SnakeBody obstacle);
    void clear_mObstacle();
    int touchObstacle(int key);
    bool obstacleSurviveCheck(int key);


    void sensePowerPath(std::vector<SnakeBody> powerPath);
    bool checkEnterStart();
    bool checkEnterEnd();
    bool checkInPath();
    void resetPowerPath();
    bool checkFinishPath();
    void popStartPowerPath();
    void popEndPowerPath();
    // Check if the snake is dead
    bool hitWall();
    bool hitSelf();
    bool checkCollision();
    bool checkDeath(int key);

    bool changeDirection(Direction newDirection);
    std::vector<SnakeBody>& getSnake();
    int getLength();
    Direction getDirection() const;
    SnakeBody createNewHead();
    SnakeBody newHead();
    int moveFoward(int key);

private:
    const int mGameBoardWidth;
    const int mGameBoardHeight;
    // Snake information
    const int mInitialSnakeLength;
    Direction mDirection;
    SnakeBody mFood;
    std::vector<SnakeBody> mObstacle;
    std::vector<SnakeBody> mPowerPath;
    std::vector<SnakeBody> mSnake;
};

#endif

