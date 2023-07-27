#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "snake.h"


SnakeBody::SnakeBody()
{
}


SnakeBody::SnakeBody(int x, int y): mX(x), mY(y)
{
}

Bullet::Bullet(): mX(-1), mY(-1)
{
}

Bullet::Bullet(int x, int y): mX(x), mY(y)
{
}

int SnakeBody::getX() const
{
    return mX;
}

int Bullet::getX() const
{
    return mX;
}

int SnakeBody::getY() const
{
    return mY;
}

int Bullet::getY() const
{
    return mY;
}

bool SnakeBody::operator == (const SnakeBody& snakeBody)
{
		// TODO overload the == operator for SnakeBody comparision.
    if (mX == snakeBody.getX()
        && mY == snakeBody.getY())
        return true;

    return false;
}

Snake::Snake(int gameBoardWidth, int gameBoardHeight, int initialSnakeLength): mGameBoardWidth(gameBoardWidth), mGameBoardHeight(gameBoardHeight), mInitialSnakeLength(initialSnakeLength)
{
    this->initializeSnake();
    this->setRandomSeed();
}

void Snake::setRandomSeed()
{
    // use current time as seed for random generator
    std::srand(std::time(nullptr));
}

void Snake::initializeSnake()
{
    // Instead of using a random initialization algorithm
    // We always put the snake at the center of the game mWindows
    //int centerX = 1;
    //int centerY = 0;
    int centerX = this->mGameBoardWidth / 2;
    int centerY = this->mGameBoardHeight / 2;

    for (int i = 0; i < this->mInitialSnakeLength; i ++)
    {
        this->mSnake.push_back(SnakeBody(centerX, centerY + i));
    }
    this->mDirection = Direction::Up;
    this->mPowerPath.push_back(SnakeBody(-1, -1));
}

bool Snake::isPartOfSnake(int x, int y)
{
		// TODO check if a given point with axis x, y is on the body of the snake.
    for (int i = 1; i < this->mSnake.size(); i++) {
        if (x == this->mSnake[i].getX() && y == this->mSnake[i].getY())
            return true;
    }

    return false;
}

/*
 * Assumption:
 * Only the head would hit wall.
 */
bool Snake::hitWall()
{
		// TODO check if the snake has hit the wall
    SnakeBody head = this->mSnake[0];
    int x = head.getX(), y = head.getY();
    if (x == 1 || x == this->mGameBoardWidth-1
        || y == 0 || y == this->mGameBoardHeight-1)
        return true;
    return false;
}

/*
 * The snake head is overlapping with its body
 */
bool Snake::hitSelf()
{
		// TODO check if the snake has hit itself.
    SnakeBody head = this->mSnake[0];
    int x = head.getX(), y = head.getY();

 /*   switch (this->mDirection)
    {
        case Direction::Up:
        {
            y--;
            break;

        }
        case Direction::Down:
        {
            y++;
            break;
        }
        case Direction::Left:
        {
            x--;
            break;

        }
        case Direction::Right:
        {
            x++;
            break;

        }
    }
    */
    if (this->isPartOfSnake(x, y))
        return true;

    return false;
}


bool Snake::touchFood()
{
    SnakeBody newHead = this->createNewHead();
    if (this->mFood == newHead)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Snake::obstacleSurviveCheck(int key)
{
    if (key == 'g' || key == 'G')
        return true;
    else
        return false;
}
int Snake::touchObstacle(int key)
{
    SnakeBody newHead = this->mSnake[0];

    for (int i = 0; i < this->mObstacle.size(); i++) {
        if (this->mObstacle[i] == newHead) {
            if (this->obstacleSurviveCheck(key))
                return 1;
            else
                return 2;
        }
    }

    return 0;
   /* if (!(this->mObstacle == newHead)) {
        return 0; //not meet the obstacle
    }
    else if (this->obstacleSurviveCheck(key)) {
        return 1; //survive
    }
    else return 2; // dead*/
}

void Snake::senseFood(SnakeBody food)
{
    this->mFood = food;
}

void Snake::senseObstacle(SnakeBody obstacle)
{
    this->mObstacle.push_back(obstacle);
}

void Snake::clear_mObstacle()
{
    this->mObstacle = {};
}

void Snake::sensePowerPath(std::vector<SnakeBody> powerPath)
{
    this->mPowerPath = powerPath;
}

bool Snake::checkEnterStart()
{
    SnakeBody head = this->mSnake[0];
    if (head == this->mPowerPath[0])
        return true;
    else
        return false;
}

bool Snake::checkEnterEnd()
{
    SnakeBody head = this->mSnake[0];
    int i = this->mPowerPath.size()-1;
    if (head == this->mPowerPath[i])
        return true;
    else
        return false;
}

bool Snake::checkInPath()
{
    SnakeBody head = this->mSnake[0];
    for (int i = 0; i < this->mPowerPath.size(); i++){
        if (head == this->mPowerPath[i])
            return true;
    }
    return false;
}

void Snake::resetPowerPath()
{
    std::vector<SnakeBody> reset;
    reset.push_back(SnakeBody(-1, -1));
    this->mPowerPath = reset;
}

bool Snake::checkFinishPath()
{
    SnakeBody head = this->mSnake[0];
    if (this->mPowerPath.size() == 1 && head == this->mPowerPath[0])
        return true;
    return false;
}


void Snake::popEndPowerPath()
{
    this->mPowerPath.pop_back();
}

void Snake::popStartPowerPath()
{
    auto it = this->mPowerPath.begin();
    this->mPowerPath.erase(it);
}

std::vector<SnakeBody>& Snake::getSnake()
{
    return this->mSnake;
}

bool Snake::changeDirection(Direction newDirection)
{
    switch (this->mDirection)
    {
        case Direction::Up:
        {
						// what you need to do when the current direction of the snake is Up
						// and the user inputs a new direction?  TODO
            if (newDirection == Direction::Up || newDirection == Direction::Down)
                break;
            else {
                this->mDirection = newDirection;
                return true;
            }

        }
        case Direction::Down:
        {
						// what you need to do when the current direction of the snake is Down
						// and the user inputs a new direction? TODO
            if (newDirection == Direction::Up || newDirection == Direction::Down)
                break;
            else {
                this->mDirection = newDirection;
                return true;
            }

        }
        case Direction::Left:
        {
						// what you need to do when the current direction of the snake is Left
						// and the user inputs a new direction? TODO

            if (newDirection == Direction::Left || newDirection == Direction::Right)
                break;
            else {
                this->mDirection = newDirection;
                return true;
            }

        }
        case Direction::Right:
        {
						// what you need to do when the current direction of the snake is Right
						// and the user inputs a new direction? TODO

            if (newDirection == Direction::Left || newDirection == Direction::Right)
                break;
            else {
                this->mDirection = newDirection;
                return true;
            }

        }
    }

    return false;
}
SnakeBody Snake::newHead()
{
    SnakeBody head = this->mSnake[0];
    int x = head.getX(), y = head.getY();

    switch (this->mDirection)
    {
        case Direction::Up:
        {
            y--;
            break;

        }
        case Direction::Down:
        {
            y++;
            break;
        }
        case Direction::Left:
        {
            x--;
            break;

        }
        case Direction::Right:
        {
            x++;
            break;

        }
    }
    SnakeBody newHead = SnakeBody(x, y);
    return newHead;
}

SnakeBody Snake::createNewHead()
{
		/* TODO
		 * read the position of the current head
		 * read the current heading direction
		 * add the new head according to the direction
		 * return the new snake
		 */
    SnakeBody head = this->mSnake[0];
    int x = head.getX(), y = head.getY();

    switch (this->mDirection)
    {
        case Direction::Up:
        {
            y--;
            break;

        }
        case Direction::Down:
        {
            y++;
            break;
        }
        case Direction::Left:
        {
            x--;
            break;

        }
        case Direction::Right:
        {
            x++;
            break;

        }
    }
    this->mSnake.insert(this->mSnake.begin(),SnakeBody(x, y));
    //this->mSnake.pop_back();


    SnakeBody newHead = this->mSnake[0];
    return newHead;
}

/*
 * If eat food, return true, otherwise return false
 */
int Snake::moveFoward(int key)
{
    /*
		 * TODO
		 * move the snake forward.
     * If eat food, return true, otherwise return false
     */

    if (this->touchFood())
        return 0;
    else if (this->touchObstacle(key) == 1) {
        this->mSnake.pop_back();
        this->mSnake.pop_back();
        return 1;
    }
    else if (this->checkFinishPath()) {
        //this->resetPowerPath();
        return 3;
    }
    else {
        //this->createNewHead();
        this->mSnake.pop_back();
        return 2;
    }


}

bool Snake::checkCollision()
{
    if (this->hitWall() || this->hitSelf())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Snake::checkDeath(int key)
{
    if (this->checkCollision() || this->mSnake.size()==0 || this->touchObstacle(key)==2)
        return true;
    return false;
}

int Snake::getLength()
{
    return this->mSnake.size();
}

Direction Snake::getDirection() const
{
    return this->mDirection;
}