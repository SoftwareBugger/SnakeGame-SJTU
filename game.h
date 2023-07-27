#ifndef GAME_H
#define GAME_H

#include "curses.h"
#include <string>
#include <vector>
#include <memory>

#include "snake.h"
#include "map.h"


class Game
{
public:
    Game();
    ~Game();

    void initializeColour();

    void OpenScene();
    void createLetters();
    void renderLetters();

		void createInformationBoard();
    void renderInformationBoard() const;

    void createGameBoard();
    void renderGameBoard() const;

		void createInstructionBoard();
    void renderInstructionBoard() const;

		void loadLeadBoard();
    void updateLeadBoard();
    bool readLeaderBoard();
    bool updateLeaderBoard();
    bool writeLeaderBoard();
    void renderLeaderBoard() const;

		void renderBoards() const;
    int renderLevelsSelect(int choiceLevel);

		void initializeGame(int mapNumber);
    int runGame(int mapChoice);
    void renderPoints() const;
    void renderDifficulty() const;
    void renderBulletNum() const;

		void createRandomFood();
    void renderFood() const;

    void shoot();
    void moveBullet();
    void destroyObstruction();
    bool checkBullet(Bullet b);
    void renderBullet();

    void renderPowerPath() const;
    void renderObstacle() const;
    void renderSnake() const;
    void controlSnake(int key);

    void createRandomPowerPath_2();
    void createRandomPowerPath_3();
    void createRandomPowerPath_4();
    void createRandomPowerPath_5();
    bool powerPathValid();

		void startGame();
    bool renderMainMenu() const;
    bool renderRestartMenu() const;
    int renderPauseMenu() const;
    int renderWinningBoard(int currentLevel);
    void renderTip(int mapNumber) const;
    void adjustDelay();


private:
    // We need to have two windows
    // One is for game introduction
    // One is for game mWindows
    int mScreenWidth;
    int mScreenHeight;
    int mGameBoardWidth;
    int mGameBoardHeight;
    const int mInformationHeight = 6;
    const int mInstructionWidth = 18;
    std::vector<WINDOW *> mWindows;
    // Snake information
    const int mInitialSnakeLength = 2;
    const char mSnakeSymbol = '@';
    std::unique_ptr<Snake> mPtrSnake;

    // Food information
    SnakeBody mFood;
    const char mFoodSymbol = '*';

    const int mInitialObstacleNum = 10;
    const char mObstacleSymbol = '#';
    const int mInitialPowerPathLength = 10;
    const char mPowerPathSymbol = '*';
    std::unique_ptr<Map> mPtrMap;


    std::vector<std::vector<int>> letters;
    int mPoints = 0;
    int mDifficulty = 0;
    int mBaseDelay = 150;
  //  int mBaseDelay = 200;
    int mDelay;
    const std::string mRecordBoardFilePath = "record.dat";
    std::vector<int> mLeaderBoard;
    const int mNumLeaders = 3;
    const int levelNumber = 5;
    std::vector<Bullet> Bullets;
    int mNumOfShots = 0;
};

#endif

