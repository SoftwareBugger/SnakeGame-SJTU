#include <string>
#include <iostream>
#include <cmath>

// For terminal delay
#include <chrono>
#include <thread>

#include <fstream>
#include <algorithm>

#include "game.h"

Game::Game()
{
    // Separate the screen to three windows
    this->mWindows.resize(3);
    initscr();
    // Initialize needed colours
    initializeColour();
    // If there wasn't any key pressed don't wait for keypress
    nodelay(stdscr, true);
    // Turn on keypad control
    keypad(stdscr, true);
    // No echo for the key pressed
    noecho();
    // No cursor show
    curs_set(0);
    // Get screen and board parameters
    getmaxyx(stdscr, this->mScreenHeight, this->mScreenWidth);
    this->mGameBoardWidth = this->mScreenWidth - this->mInstructionWidth;
    this->mGameBoardHeight = this->mScreenHeight - this->mInformationHeight;

    this->createInformationBoard();
    this->createGameBoard();
    this->createInstructionBoard();

    // Initialize the leader board to be all zeros
    this->mLeaderBoard.assign(this->mNumLeaders, 0);
}

Game::~Game()
{
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        delwin(this->mWindows[i]);
    }
    endwin();
}

void Game::initializeColour()
{
    start_color();
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_CYAN, 500, 540, 528);
    init_color(COLOR_RED, 1000, 0, 0);
    /* 1 Snake
       2 Food
       3 Obstacle
       4 Arrow & Bullet
       5 Level Square
       6 Level Select
       7 Energy Rail */
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_GREEN, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLUE);
    init_pair(7, COLOR_BLUE, COLOR_BLACK);
}

void Game::OpenScene()
{
    this->createLetters();
    this->renderLetters();
}

void Game::createLetters()
{
    int centerX = this->mGameBoardWidth / 2;
    int gap = 10;
    // Letter S
    for (int i = 0; i < 7; i++){
        letters.push_back({centerX-2*gap+3-i, 2});
    }for (int i = 0; i < 2; i++){
        letters.push_back({centerX-2*gap-3, 3+i});
    }for (int i = 0; i < 7; i++){
        letters.push_back({centerX-2*gap-3+i, 5});
    }for (int i = 0; i < 2; i++){
        letters.push_back({centerX-2*gap+3, 6+i});
    }for (int i = 0; i < 7; i++){
        letters.push_back({centerX-2*gap+3-i, 8});
    }
    // Letter N
    for (int i = 0; i < 7; i++){
        letters.push_back({centerX-gap-3, 2+i});
    }for (int i = 0; i < 5; i++){
        letters.push_back({centerX-gap-2+i, 3+i});
    }for (int i = 0; i < 7; i++){
        letters.push_back({centerX-gap+3, 8-i});
    }
    // Letter A
    for (int i = 0; i < 4; i++){
        letters.push_back({centerX-i, 2+i});
    }for (int i = 0; i < 3; i++){
        letters.push_back({centerX-3, 6+i});
    }for (int i = 0; i < 3; i++){
        letters.push_back({centerX+1+i, 3+i});
    }for (int i = 0; i < 3; i++){
        letters.push_back({centerX+3, 6+i});
    }for (int i = 0; i < 5; i++){
        letters.push_back({centerX-2+i, 6});
    }
    // Letter K
    for (int i = 0; i < 7; i++){
        letters.push_back({centerX+gap-3, 2+i});
    }for (int i = 0; i < 5; i++){
        letters.push_back({centerX+gap+2-i, 2+i});
    }for (int i = 0; i < 3; i++){
        letters.push_back({centerX+gap+i, 6+i});
    }letters.push_back({centerX+gap+3, 8});
    // Letter E
    for (int i = 0; i < 7; i++){
        letters.push_back({centerX+2*gap-3+i, 2});
    }for (int i = 0; i < 5; i++){
        letters.push_back({centerX+2*gap-3, 3+i});
    }for (int i = 0; i < 7; i++){
        letters.push_back({centerX+2*gap-3+i, 8});
    }for (int i = 0; i < 4; i++){
        letters.push_back({centerX+2*gap-2+i, 5});
    }
}

void Game::renderLetters()
{
    wattron(this->mWindows[1], COLOR_PAIR(1));
    for (int i = 0; i < this->letters.size(); i++){
        mvwaddch(this->mWindows[1], this->letters[i][1], this->letters[i][0], this->mSnakeSymbol);
        wrefresh(this->mWindows[1]);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    wattroff(this->mWindows[1], COLOR_PAIR(1));
}

void Game::createInformationBoard()
{
    int startY = 0;
    int startX = 0;
    this->mWindows[0] = newwin(this->mInformationHeight, this->mScreenWidth, startY, startX);
}

void Game::renderInformationBoard() const
{
    mvwprintw(this->mWindows[0], 1, 2, "Welcome to The Snake Game 2.0!");
    mvwprintw(this->mWindows[0], 2, 2, "Jointly designed by Zongrui Wang, Yizhou Zhang and Han Lyu");
    mvwprintw(this->mWindows[0], 3, 2, "Adapted from the primitive version");
    mvwprintw(this->mWindows[0], 4, 2, "Implemented using C++ and libncurses library.");
    wrefresh(this->mWindows[0]);
}

void Game::createGameBoard()
{
    int startY = this->mInformationHeight;
    int startX = 0;
    this->mWindows[1] = newwin(this->mScreenHeight - this->mInformationHeight, this->mScreenWidth - this->mInstructionWidth, startY, startX);
}

void Game::renderGameBoard() const
{
    wrefresh(this->mWindows[1]);
}

void Game::createInstructionBoard()
{
    int startY = this->mInformationHeight;
    int startX = this->mScreenWidth - this->mInstructionWidth;
    this->mWindows[2] = newwin(this->mScreenHeight - this->mInformationHeight, this->mInstructionWidth, startY, startX);
}

void Game::renderInstructionBoard() const
{
    mvwprintw(this->mWindows[2], 1, 2, "Manual");

    mvwprintw(this->mWindows[2], 3, 2, "Up: W");
    mvwprintw(this->mWindows[2], 4, 2, "Down: S");
    mvwprintw(this->mWindows[2], 5, 2, "Left: A");
    mvwprintw(this->mWindows[2], 6, 2, "Right: D");

    mvwprintw(this->mWindows[2], 8, 2, "Difficulty");
    mvwprintw(this->mWindows[2], 11, 2, "Points");
    mvwprintw(this->mWindows[2], 14, 2, "Bullets");

    wrefresh(this->mWindows[2]);
}


void Game::renderLeaderBoard() const
{
    // If there is not too much space, skip rendering the leader board
    if (this->mScreenHeight - this->mInformationHeight - 14 - 2 < 3 * 2)
    {
        return;
    }
    mvwprintw(this->mWindows[2], 17, 2, "Leader Board");
    std::string pointString;
    std::string rank;
    for (int i = 0; i < std::min(this->mNumLeaders, this->mScreenHeight - this->mInformationHeight - 14 - 2); i ++)
    {
        pointString = std::to_string(this->mLeaderBoard[i]);
        rank = "#" + std::to_string(i + 1) + ":";
        mvwprintw(this->mWindows[2], 18 + (i + 1), 2, rank.c_str());
        mvwprintw(this->mWindows[2], 18 + (i + 1), 6, pointString.c_str());
    }
}

bool Game::renderMainMenu() const
{
    WINDOW * menu;
    int width = this->mGameBoardWidth * 0.25;
    int height = this->mGameBoardHeight * 0.25;
    int startX = this->mGameBoardWidth * 0.375;
    int startY = this->mGameBoardHeight * 0.375 + this->mInformationHeight + 4;

    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);
    std::vector<std::string> menuItems = {"Start Game", "Quit"};

    int index = 0;
    int offset = 2;
    int centerX = width/2;
    // mvwprintw(menu, 1, 1, "Your Final Score:");
    // std::string pointString = std::to_string(this->mPoints);
    // mvwprintw(menu, 2, 1, pointString.c_str());
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 0 + offset, centerX-5, menuItems[0].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 1 + offset, centerX-2, menuItems[1].c_str());

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        switch(key)
        {
            case 'W':
            case 'w':
            case KEY_UP:
            {
                mvwprintw(menu, index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
            case 'S':
            case 's':
            case KEY_DOWN:
            {
                mvwprintw(menu, index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
        }
        wrefresh(menu);
        if (key == ' ' || key == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delwin(menu);

    if (index == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Game::renderRestartMenu() const
{
    WINDOW * menu;
    int width = this->mGameBoardWidth * 0.5;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25 + this->mInformationHeight;

    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);
    std::vector<std::string> menuItems = {"Restart", "Quit"};

    int index = 0;
    int offset = 5;
    int centerX = width/2;
    mvwprintw(menu, 2, centerX-10, "Your Final Score:");
    std::string pointString = std::to_string(this->mPoints);
    mvwprintw(menu, 2, centerX+9, pointString.c_str());
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 0 + offset, centerX-menuItems[0].size()/2, menuItems[0].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 2 + offset, centerX-menuItems[1].size()/2, menuItems[1].c_str());

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        switch(key)
        {
            case 'W':
            case 'w':
            case KEY_UP:
            {
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
            case 'S':
            case 's':
            case KEY_DOWN:
            {
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
        }
        wrefresh(menu);
        if (key == ' ' || key == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delwin(menu);

    if (index == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int Game::renderPauseMenu() const
{
        WINDOW * menu;
    int width = this->mGameBoardWidth * 0.5;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25 + this->mInformationHeight;

    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);
    std::vector<std::string> menuItems = {"Continue","Restart", "Quit"};

    int index = 0;
    int offset = 4;
    int centerX = width/2;
    mvwprintw(menu, 2, centerX-2, "PAUSE");
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 0 + offset, centerX-menuItems[0].size()/2, menuItems[0].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 2 + offset, centerX-menuItems[1].size()/2, menuItems[1].c_str());
    mvwprintw(menu, 4 + offset, centerX-menuItems[2].size()/2, menuItems[2].c_str());

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        switch(key)
        {
            case 'W':
            case 'w':
            case KEY_UP:
            {
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
            case 'S':
            case 's':
            case KEY_DOWN:
            {
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
        }
        wrefresh(menu);
        if (key == ' ' || key == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delwin(menu);

    if (index == 0)
    {
        return 1;
    }
    else if (index == 1)
    {
        return 2;
    }
    else
        return 3;
}

int Game::renderWinningBoard(int currentLevel)
{
        WINDOW * menu;
    int width = this->mGameBoardWidth * 0.5;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25 + this->mInformationHeight;

    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);
    std::vector<std::string> menuItems = {"Next level", "Restart", "Quit"};
    int index = 0;
    int offset = 5;
    int centerX = width/2;
    mvwprintw(menu, 2, centerX-8, "Congratulations!");
    mvwprintw(menu, 3, centerX-9, "You won in level ");
    mvwaddch(menu, 3, centerX+8, currentLevel + '0');
    if (currentLevel < levelNumber)
    {
        wattron(menu, A_STANDOUT);
        mvwprintw(menu, 0 + offset, centerX-menuItems[0].size()/2, menuItems[0].c_str());
        wattroff(menu, A_STANDOUT);
        mvwprintw(menu, 2 + offset, centerX-menuItems[1].size()/2, menuItems[1].c_str());
        mvwprintw(menu, 4 + offset, centerX-menuItems[2].size()/2, menuItems[2].c_str());
    }
    else 
    {
        wattron(menu, A_STANDOUT);
        mvwprintw(menu, 2 + offset, centerX-menuItems[1].size()/2, menuItems[1].c_str());
        wattroff(menu, A_STANDOUT);
        mvwprintw(menu, 4 + offset, centerX-menuItems[2].size()/2, menuItems[2].c_str());
        index = 1;
    }

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        switch(key)
        {
            case 'W':
            case 'w':
            case KEY_UP:
            {
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
            case 'S':
            case 's':
            case KEY_DOWN:
            {
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 2*index + offset, centerX-menuItems[index].size()/2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
        }
        wrefresh(menu);
        if (key == ' ' || key == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delwin(menu);

    if (currentLevel == levelNumber) return index;
    else return index + 1;
}

void Game::renderTip(int mapNumber) const
{
    WINDOW * menu;
    int width = this->mGameBoardWidth * 0.5 + 2;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25 + this->mInformationHeight;

    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);

    int offset = 4;
    int centerX = width/2;
    switch (mapNumber)
    {
        case 1:
            mvwprintw(menu, 2, 2, "Welcome to snake world, we'll begin our trip here.");
            mvwprintw(menu, 3, 2, "There're some instructions on the right board,");
            mvwprintw(menu, 4, 2, "that can tell you how to control your snake.");
            mvwprintw(menu, 5, 2, "You need to get 5 points to pass the level.");
            mvwprintw(menu, 7, 2, "If you get ready, press SPACE or ENTER to start.");
            break;
        case 2:
            mvwprintw(menu, 2, 2, "In this level, we can see a energy rail.");
            mvwprintw(menu, 3, 2, "Like this:");
            wattron(menu, COLOR_PAIR(7));
            mvwprintw(menu, 3, 13, "***************");
            wattroff(menu, COLOR_PAIR(7));
            mvwprintw(menu, 4, 2, "Go along with it, and you will get extra points.");
            mvwprintw(menu, 5, 2, "You need to get 7 points to pass the level.");
            mvwprintw(menu, 7, 2, "If you get ready, press SPACE or ENTER to start.");
            break;
        case 3:
            mvwprintw(menu, 2, 2, "Now, the snake is equipped with a... gun?");
            mvwprintw(menu, 3, 2, "Press O to shoot and break those obstacles.");
            mvwprintw(menu, 4, 2, "You can see bullet number on the right board.");
            mvwprintw(menu, 5, 2, "You need to get 8 points to pass the level.");
            mvwprintw(menu, 7, 2, "If you get ready, press SPACE or ENTER to start.");
            break;
        case 4:
            mvwprintw(menu, 2, 2, "This level is dangerous.");
            mvwprintw(menu, 3, 2, "Good luck.");
            mvwprintw(menu, 5, 2, "You need to get 10 points to pass the level.");
            mvwprintw(menu, 7, 2, "If you get ready, press SPACE or ENTER to start.");
            break;
        case 5:
            mvwprintw(menu, 2, 2, "Finally, we reach the last level.");
            mvwprintw(menu, 3, 2, "This is an endless level.");
            mvwprintw(menu, 4, 2, "Try to get more points and renew the leader board.");
            mvwprintw(menu, 5, 2, "Enjoy your time!");
            mvwprintw(menu, 7, 2, "If you get ready, press SPACE or ENTER to start.");
            break;
    }
    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        wrefresh(menu);
        if (key == ' ' || key == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delwin(menu);
}


void Game::renderPoints() const
{
    std::string pointString = std::to_string(this->mPoints);
    mvwprintw(this->mWindows[2], 12, 2, pointString.c_str());
    wrefresh(this->mWindows[2]);
}

void Game::renderDifficulty() const
{
    std::string difficultyString = std::to_string(this->mDifficulty);
    mvwprintw(this->mWindows[2], 9, 2, difficultyString.c_str());
    wrefresh(this->mWindows[2]);
}

void Game::renderBulletNum() const
{
    std::string numOfShotsString = std::to_string(this->mNumOfShots);
    mvwprintw(this->mWindows[2], 15, 2, numOfShotsString.c_str());
    wrefresh(this->mWindows[2]);
}


void Game::initializeGame(int mapNumber)
{
    // allocate memory for a new snake
		this->mPtrSnake.reset(new Snake(this->mGameBoardWidth, this->mGameBoardHeight, this->mInitialSnakeLength));
		this->mPtrMap.reset(new Map(this->mGameBoardWidth, this->mGameBoardHeight, this->mInitialObstacleNum, this->mInitialPowerPathLength, mapNumber));

    /* TODO
     * initialize the game pionts as zero
     * create a food at randome place
     * make the snake aware of the food
     * other initializations
     */
     this->mPoints = 0;
     this->createRandomFood();
     this->renderFood();
     switch (mapNumber)
     {
        case 1:
            this->mNumOfShots = 0;
            break;
        case 2:
            this->createRandomPowerPath_2();
            this->mNumOfShots = 0;
            break;
        case 3:
            this->createRandomPowerPath_3();
            this->mNumOfShots = 12;
            break;
        case 4:
            this->createRandomPowerPath_4();
            this->mNumOfShots = 6;
            break;
        case 5:
            this->createRandomPowerPath_5();
            this->mNumOfShots = 8;
            break;
     }
    //  if (mapNumber == 1) this->createRandomPowerPath_1();
    //  else if (mapNumber == 2) this->createRandomPowerPath_2();
    //  else this->createRandomPowerPath_3();

     this->renderPowerPath();
     this->Bullets = {};
     this->mDelay = this->mBaseDelay;
}

void Game::createRandomFood()
{
/* TODO
 * create a food at random places
 * make sure that the food doesn't overlap with the snake.
 */
    int x, y, condition = 1;
    while (condition) {
        x = rand()%(this->mGameBoardWidth-2) + 2;
        y = rand()%(this->mGameBoardHeight-2) + 1;
        std::vector<SnakeBody>& s = this->mPtrSnake->getSnake();
        std::vector<SnakeBody>& o = this->mPtrMap->getObstacle();
        for (int i = 0; i < s.size(); i++){
            int sx = (s[i]).getX();
            int sy = (s[i]).getY();
            if (x == sx && y == sy) {
                condition = 2;
                break;
            }
        }
        for (int i = 0; i < o.size(); i++) {
            int ox = (o[i]).getX();
            int oy = (o[i]).getY();
            if (x == ox && y == oy) {
                condition = 2;
                break;
            }
        }
        if (condition == 2) {
            condition = 1;
            continue;
        }
        else {
            break;
        }
    }
    if (x == 0) x++;
    if (y == 0) y++;
    if (x == this->mGameBoardHeight - 1) x--;
    if (y == this->mGameBoardWidth - 1) y--;
    SnakeBody food(x, y);
    mPtrSnake->senseFood(food);
    this->mFood = food;
   // mvwaddch(this->mWindows[1], y, x, this->mFoodSymbol);
   // wrefresh(this->mWindows[1]);
}

void Game::renderFood() const
{
    wattron(this->mWindows[1], COLOR_PAIR(2));
    mvwaddch(this->mWindows[1], this->mFood.getY(), this->mFood.getX(), this->mFoodSymbol);
    wattroff(this->mWindows[1], COLOR_PAIR(2));
    wrefresh(this->mWindows[1]);
}

bool Game::powerPathValid()
{

    std::vector<SnakeBody>& p = this->mPtrMap->getPowerPath();
    std::vector<SnakeBody>& s = this->mPtrSnake->getSnake();
    std::vector<SnakeBody>& o = this->mPtrMap->getObstacle();
    for (int i = 0; i < p.size(); i++){
        for (int j = 0; j < s.size(); j++){
            if (p[i].getX() == s[j].getX() && p[i].getY() == s[j].getY())
                return false;
        }
        for (int j = 0; j < o.size(); j++){
            if (p[i].getX() == o[j].getX() && p[i].getY() == o[j].getY())
                return false;
        }
        if (p[i].getX() < 2 || p[i].getX() > this->mGameBoardWidth - 2
            || p[i].getY() < 2 || p[i].getY() > this->mGameBoardHeight - 3)
            return false;
        if (p[i].getX() == this->mFood.getX() && p[i].getY() == this->mFood.getY())
            return false;
    }
    return true;

}

void Game::createRandomPowerPath_2()
{
    this->mPtrMap->resetPowerPath();
    int x, y;
    while(true) {
        x = rand()%(this->mGameBoardWidth-2) + 1;
        y = rand()%(this->mGameBoardHeight-2) + 1;
        this->mPtrMap->powerPathCase_2(x, y);
        if (this->powerPathValid())
            break;
        else
            this->mPtrMap->resetPowerPath();
    }
    this->mPtrSnake->sensePowerPath(this->mPtrMap->getPowerPath());
}

void Game::createRandomPowerPath_3()
{
    this->mPtrMap->resetPowerPath();
    int x, y;
    while(true) {
        x = rand()%(this->mGameBoardWidth-2) + 1;
        y = rand()%(this->mGameBoardHeight-2) + 1;
        this->mPtrMap->powerPathCase_3(x, y);
        if (this->powerPathValid())
            break;
        else
            this->mPtrMap->resetPowerPath();
    }
    this->mPtrSnake->sensePowerPath(this->mPtrMap->getPowerPath());
}

void Game::createRandomPowerPath_4()
{
    this->mPtrMap->resetPowerPath();
    int x, y;
    while(true) {
        x = rand()%(this->mGameBoardWidth-2) + 1;
        y = rand()%(this->mGameBoardHeight-2) + 1;
        this->mPtrMap->powerPathCase_4(x, y);
        if (this->powerPathValid())
            break;
        else
            this->mPtrMap->resetPowerPath();
    }
    this->mPtrSnake->sensePowerPath(this->mPtrMap->getPowerPath());
}

void Game::createRandomPowerPath_5()
{
    this->mPtrMap->resetPowerPath();
    int x, y;
    while(true) {
        x = rand()%(this->mGameBoardWidth-2) + 1;
        y = rand()%(this->mGameBoardHeight-2) + 1;
        this->mPtrMap->powerPathCase_5(x, y);
        if (this->powerPathValid())
            break;
        else
            this->mPtrMap->resetPowerPath();
    }
    this->mPtrSnake->sensePowerPath(this->mPtrMap->getPowerPath());
}

void Game::renderPowerPath() const
{
    int length = this->mPtrMap->getPowerPathLength();
    std::vector<SnakeBody>& powerPath = this->mPtrMap->getPowerPath();
    wattron(this->mWindows[1], COLOR_PAIR(7));
    for (int i = 0; i < length; i ++)
    {
        mvwaddch(this->mWindows[1], powerPath[i].getY(), powerPath[i].getX(), this->mPowerPathSymbol);
    }
    wattroff(this->mWindows[1], COLOR_PAIR(7));
    wrefresh(this->mWindows[1]);
}

void Game::renderObstacle() const
{
    int length = this->mPtrMap->getObstacleNum();
    std::vector<SnakeBody>& obstacle = this->mPtrMap->getObstacle();
    wattron(this->mWindows[1], COLOR_PAIR(3));
    for (int i = 0; i < length; i ++)
    {
        mvwaddch(this->mWindows[1], obstacle[i].getY(), obstacle[i].getX(), this->mObstacleSymbol);
    }
    wattroff(this->mWindows[1], COLOR_PAIR(3));
    wrefresh(this->mWindows[1]);
}

void Game::renderSnake() const
{
    int snakeLength = this->mPtrSnake->getLength();
    std::vector<SnakeBody>& snake = this->mPtrSnake->getSnake();
    wattron(this->mWindows[1], COLOR_PAIR(1));
    for (int i = 0; i < snakeLength; i ++)
    {
        mvwaddch(this->mWindows[1], snake[i].getY(), snake[i].getX(), this->mSnakeSymbol);
    }
    wattroff(this->mWindows[1], COLOR_PAIR(1));
    wrefresh(this->mWindows[1]);
}

void Game::controlSnake(int key)
{
    //int key;
   // key = getch();
    switch(key)
    {
        case 'W':
        case 'w':
        case KEY_UP:
        {
				    // TODO change the direction of the snake.

            this->mPtrSnake->changeDirection(Direction::Up);


            break;
        }
        case 'S':
        case 's':
        case KEY_DOWN:
        {
				    // TODO change the direction of the snake.

            this->mPtrSnake->changeDirection(Direction::Down);


            break;
        }
        case 'A':
        case 'a':
        case KEY_LEFT:
        {
				    // TODO change the direction of the snake.

            this->mPtrSnake->changeDirection(Direction::Left);


            break;
        }
        case 'D':
        case 'd':
        case KEY_RIGHT:
        {
				    // TODO change the direction of the snake.

            this->mPtrSnake->changeDirection(Direction::Right);


            break;
        }
        case 'O':
        case 'o':
        {
            if (this->mNumOfShots > 0) 
            {
                this->shoot();
                this->mNumOfShots--;
            }
            this->renderLeaderBoard();
        }
        default:
        {
            break;
        }
    }
}

void Game::shoot()
{
    Bullet b =  Bullet(this->mPtrSnake->getSnake()[0].getX(), this->mPtrSnake->getSnake()[0].getY());
    b.mdir = this->mPtrSnake->getDirection();
    this->Bullets.push_back(b);
}

void Game::moveBullet()
{
    if (this->Bullets.size() == 0) return;
    int i = 0;
    while (i < this->Bullets.size()) {
        if (checkBullet(this->Bullets[i]))
        {
            switch(this->Bullets[i].mdir) 
            {
                case Direction::Up:
                {
                    this->Bullets[i] = Bullet(this->Bullets[i].getX(), this->Bullets[i].getY() - 2);
                    this->Bullets[i].mdir = Direction::Up;
                    break;
                }
                case Direction::Down:
                {
                    this->Bullets[i] = Bullet(this->Bullets[i].getX(),this->Bullets[i].getY() + 2);
                    this->Bullets[i].mdir = Direction::Down;
                    break;
                }
                case Direction::Left:
                {
                    this->Bullets[i] = Bullet(this->Bullets[i].getX() - 2, this->Bullets[i].getY());
                    this->Bullets[i].mdir = Direction::Left;
                    break;
                }
                case Direction::Right:
                {
                    this->Bullets[i] = Bullet(this->Bullets[i].getX() + 2, this->Bullets[i].getY());
                    this->Bullets[i].mdir = Direction::Right;
                    break;
                }
            }
            i++;
        }
        else this->Bullets.erase(this->Bullets.begin() + i);
    }    
}

void Game::destroyObstruction()
{
    int j = 0;
    while(j < this->Bullets.size())
    {
        int state = 0;
        int i = 0;
        while (i < this->mPtrMap->getObstacle().size()) 
        {
            if (this->Bullets[j].mdir == Direction::Left)
            {
                if (this->mPtrMap->getObstacle()[i].getY() == this->Bullets[j].getY() && - this->mPtrMap->getObstacle()[i].getX() + this->Bullets[j].getX() <= -1 && - this->mPtrMap->getObstacle()[i].getX() + this->Bullets[j].getX() >= -2) 
                {
                    this->mPtrMap->getObstacle().erase(this->mPtrMap->getObstacle().begin() + i);
                    this->Bullets.erase(this->Bullets.begin() + j);
                    state = 1;
                    break;
                }
                else i++;
            }
            if (this->Bullets[j].mdir == Direction::Right)
            {
                if (this->mPtrMap->getObstacle()[i].getY() == this->Bullets[j].getY() &&  this->mPtrMap->getObstacle()[i].getX() - this->Bullets[j].getX() <= -1 && this->mPtrMap->getObstacle()[i].getX() - this->Bullets[j].getX() >= -2) 
                {
                    this->mPtrMap->getObstacle().erase(this->mPtrMap->getObstacle().begin() + i);
                    this->Bullets.erase(this->Bullets.begin() + j);
                    state = 1;
                    break;
                }
                else i++;
            }
            if (this->Bullets[j].mdir == Direction::Up)
            {
                if (this->mPtrMap->getObstacle()[i].getX() == this->Bullets[j].getX() && - this->mPtrMap->getObstacle()[i].getY() + this->Bullets[j].getY() <= -1 && - this->mPtrMap->getObstacle()[i].getY() + this->Bullets[j].getY() >= -2) 
                {
                    this->mPtrMap->getObstacle().erase(this->mPtrMap->getObstacle().begin() + i);
                    this->Bullets.erase(this->Bullets.begin() + j);
                    state = 1;
                    break;
                }
                else i++;
            }
            if (this->Bullets[j].mdir == Direction::Down)
            {
                if (this->mPtrMap->getObstacle()[i].getX() == this->Bullets[j].getX() &&  this->mPtrMap->getObstacle()[i].getY() - this->Bullets[j].getY() <= -1 &&  this->mPtrMap->getObstacle()[i].getY() - this->Bullets[j].getY() >= -2) 
                {
                    this->mPtrMap->getObstacle().erase(this->mPtrMap->getObstacle().begin() + i);
                    this->Bullets.erase(this->Bullets.begin() + j);
                    state = 1;
                    break;
                }
                else i++;
            }   
        }
        if (state == 0) j++;
    }
}

void Game::renderBullet() 
{
    if (this->Bullets.size() == 0) return;
    for (int i = 0; i < this->Bullets.size(); i++)
    {
        if (checkBullet(this->Bullets[i]))
        {
            wattron(this->mWindows[1], COLOR_PAIR(4));
            switch (this->Bullets[i].mdir) 
            {
                case Direction::Up:
                {
                    mvwaddch(this->mWindows[1], this->Bullets[i].getY(), this->Bullets[i].getX(), '^');
                    wrefresh(this->mWindows[1]);
                    break;
                }
                case Direction::Down:
                {
                    mvwaddch(this->mWindows[1], this->Bullets[i].getY(), this->Bullets[i].getX(), 'v');
                    wrefresh(this->mWindows[1]);
                    break;
                }
                case Direction::Left:
                {
                    mvwaddch(this->mWindows[1], this->Bullets[i].getY(), this->Bullets[i].getX(), '<');
                    wrefresh(this->mWindows[1]);
                    break;
                }
                case Direction::Right:
                {
                    mvwaddch(this->mWindows[1], this->Bullets[i].getY(), this->Bullets[i].getX(), '>');
                    wrefresh(this->mWindows[1]);
                    break;
                }
            }
            wattroff(this->mWindows[1], COLOR_PAIR(4));
        }
    }

}

bool Game::checkBullet(Bullet b)
{
    return (b.getY() >= 0 && b.getY() <= this->mGameBoardHeight - 1 && b.getX() >= 0 && b.getX() <= this->mGameBoardWidth - 1);
}



void Game::renderBoards() const
{
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        werase(this->mWindows[i]);
    }
    this->renderInformationBoard();
    this->renderGameBoard();
    this->renderInstructionBoard();
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        box(this->mWindows[i], 0, 0);
        wrefresh(this->mWindows[i]);
    }
    this->renderLeaderBoard();
}

int Game::renderLevelsSelect(int index)
{
    WINDOW * menu;
    std::vector<WINDOW *> levels;
    levels.resize(levelNumber);
    int width = this->mGameBoardWidth * 0.6;
    int height = this->mGameBoardHeight * 0.6;
    int startX = this->mGameBoardWidth * 0.2;
    int startY = this->mGameBoardHeight * 0.2 + this->mInformationHeight;
    int offset = height - 1;
    int gap = 10;

    menu = newwin(height, width, startY, startX);
    for (int i = 0; i < levelNumber; i++){
        levels[i] = newwin(3, 5, startY+offset-1, startX+4+i*gap);
        box(levels[i], 0, 0);
    }
    std::vector<std::string> levelInstruction = {"Collapsed Stone Wall\n\n      There's a village on the hill. \n      But it is abandoned for years.",
                                                 "Little Jack\n\n      People always say that Jack is a bad boy. \n      But I don't think so.",
                                                 "Huge Tower\n\n      The tower has been there since I was a child. \n      It is so huge. \n      Do you know what it is for?", 
                                                 "Chains\n\n      These chains are tight. \n      But you know what, \n      I can still make a narrow escape.", 
                                                 "Endless Highway\n\n      I can't see my destination. \n      But I'm so excited!"};

    index--;
    index = (index == -1) ? 0 : index;
    mvwprintw(menu, 1, 1, "Select Level");
    mvwprintw(menu, 3, 4, ("Level " + std::to_string(index+1)).c_str());
    mvwprintw(menu, 4, 4, levelInstruction[index].c_str());
    wattron(levels[index], COLOR_PAIR(6));
    mvwprintw(levels[index], 1, 2, "  ");
    wattroff(levels[index], COLOR_PAIR(6));
    wattron(menu, COLOR_PAIR(4));
    mvwprintw(menu, offset-3, 6+gap*index, "][");
    mvwprintw(menu, offset-2, 6+gap*index, "\\/");
    wattroff(menu, COLOR_PAIR(4));
    wattron(menu, COLOR_PAIR(3));
    for (int i = 0; i < levelNumber-1; i++){
        mvwprintw(menu, offset, 10+i*gap, "====");
    }
    wattroff(menu, COLOR_PAIR(3));
    mvwprintw(menu, offset, width-4, "Back");

    wrefresh(menu);
    for (int i = 0; i < 3; i++){
        wrefresh(levels[i]);
    }

    int key;
    while (true)
    {
        key = getch();
        switch(key)
        {
            case 'A':
            case 'a':
            case KEY_LEFT:
            {
                werase(menu);
                for (int i = 0; i < levelNumber; i++){
                    werase(levels[i]);
                }
                index --;
                index = (index < 0) ? levelNumber : index;
                if (index == levelNumber){
                    wattron(menu, A_STANDOUT);
                    mvwprintw(menu, offset, width-4, "Back");
                    wattroff(menu, A_STANDOUT);
                    for (int i = 0; i < levelNumber; i++){
                        box(levels[i], 0, 0);
                    }
                }else{
                    mvwprintw(menu, offset, width-4, "Back");
                    wattron(levels[index], COLOR_PAIR(6));
                    mvwprintw(levels[index], 1, 2, "  ");
                    wattroff(levels[index], COLOR_PAIR(6));
                    mvwprintw(menu, 3, 4, ("Level " + std::to_string(index+1)).c_str());
                    mvwprintw(menu, 4, 4, levelInstruction[index].c_str());
                    wattron(menu, COLOR_PAIR(4));
                    mvwprintw(menu, offset-3, 6+gap*index, "][");
                    mvwprintw(menu, offset-2, 6+gap*index, "\\/");
                    wattroff(menu, COLOR_PAIR(4));
                    for (int i = 0; i < levelNumber; i++){
                        box(levels[i], 0, 0);
                    }
                }
                break;
            }
            case 'D':
            case 'd':
            case KEY_RIGHT:
            {
                werase(menu);
                for (int i = 0; i < levelNumber; i++){
                    werase(levels[i]);
                }
                index ++;
                index = (index > levelNumber) ? 0 : index;
                if (index == levelNumber){
                    wattron(menu, A_STANDOUT);
                    mvwprintw(menu, offset, width-4, "Back");
                    wattroff(menu, A_STANDOUT);
                    for (int i = 0; i < levelNumber; i++){
                        box(levels[i], 0, 0);
                    }
                }else{
                    mvwprintw(menu, offset, width-4, "Back");
                    wattron(levels[index], COLOR_PAIR(6));
                    mvwprintw(levels[index], 1, 2, "  ");
                    wattroff(levels[index], COLOR_PAIR(6));
                    mvwprintw(menu, 3, 4, ("Level " + std::to_string(index+1)).c_str());
                    mvwprintw(menu, 4, 4, levelInstruction[index].c_str());
                    wattron(menu, COLOR_PAIR(4));
                    mvwprintw(menu, offset-3, 6+gap*index, "][");
                    mvwprintw(menu, offset-2, 6+gap*index, "\\/");
                    wattroff(menu, COLOR_PAIR(4));
                    for (int i = 0; i < levelNumber; i++){
                        box(levels[i], 0, 0);
                    }
                }
                break;
            }
        }
        mvwprintw(menu, 1, 1, "Select Level");
        wattron(menu, COLOR_PAIR(3));
        for (int i = 0; i < levelNumber-1; i++){
            mvwprintw(menu, offset, 10+i*gap, "====");
        }
        wattroff(menu, COLOR_PAIR(3));
        wrefresh(menu);
        for (int i = 0; i < levelNumber; i++){
            wrefresh(levels[i]);
        }
        if (key == ' ' || key == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delwin(menu);

    if (index < levelNumber)
    {
        return index + 1;
    }
    else
        return 0;
}


void Game::adjustDelay()
{
    this->mDifficulty = this->mPoints / 5;
    if (mPoints % 5 == 0)
    {
        this->mDelay = this->mBaseDelay * pow(0.75, this->mDifficulty);
    }
}

int Game::runGame(int mapChoice)
{
    int moveCondition;
    int keyOne, keyTwo;
    int condition;
    int pathCondition = 0;
    int passPoint;

    switch (mapChoice)
    {
        case 1:
            passPoint = 5;
            break;
        case 2:
            passPoint = 7;
            break;
        case 3:
            passPoint = 8;
            break;
        case 4:
            passPoint = 10;
            break;
    }
    while (true)
    {
				/* TODO
				 * this is the main control loop of the game.
				 * it keeps running a while loop, and does the following things:
				 * 	1. process your keyboard input
				 * 	2. clear the window
				 * 	3. move the current snake forward
				 * 	4. check if the snake has eaten the food after movement
				 * 	5. check if the snake dies after the movement
				 * 	6. make corresponding steps for the ``if conditions'' in 3 and 4.
				 *   7. render the position of the food and snake in the new frame of window.
				 *   8. update other game states and refresh the window
				 */
        this->adjustDelay();


        //clear();

        keyOne = getch();
       // keyTwo = getch();
        if (keyOne == 'p' || keyOne == 'P') {
            condition = renderPauseMenu();
            if (condition == 1) {
                continue;
            }
            else if (condition == 2) {
                return 2;
           }
           else
                return 3;
        }
        this->controlSnake(keyOne);

        for (int i = 0; i < this->mPtrMap->getObstacle().size(); i++){
                this->mPtrSnake->senseObstacle(this->mPtrMap->getObstacle()[i]);
        }
        werase(this->mWindows[1]);
        box(this->mWindows[1], 0, 0);
        moveCondition = this->mPtrSnake->moveFoward(keyOne);
        if (moveCondition == 0){
            this->createRandomFood();
            this->mPoints += 1;
        }

        if (pathCondition == 1) {
            bool finish = false;
            if (moveCondition == 3) {
                if (mapChoice == 1);
                else if (mapChoice == 2) this->createRandomPowerPath_2();
                else if (mapChoice == 3) this->createRandomPowerPath_3();
                else if (mapChoice == 4) this->createRandomPowerPath_4();
                else this->createRandomPowerPath_5();
                this->mPoints += 2;
                finish = true;
                pathCondition = 0;
            }
            if (!this->mPtrSnake->checkInPath() && !finish){
                if (mapChoice == 1);
                else if (mapChoice == 2) this->createRandomPowerPath_2();
                else if (mapChoice == 3) this->createRandomPowerPath_3();
                else if (mapChoice == 4) this->createRandomPowerPath_4();
                else this->createRandomPowerPath_5();
                pathCondition = 0;
            }
        }
        if (this->mPtrSnake->checkInPath()) {
            if (this->mPtrSnake->checkEnterStart()) {
                this->mPtrSnake->popStartPowerPath();
                this->mPtrMap->popStartPowerPath();
                pathCondition = 1;
            }
            else if (this->mPtrSnake->checkEnterEnd()) {
                this->mPtrSnake->popEndPowerPath();
                this->mPtrMap->popEndPowerPath();
                pathCondition = 1;
            }
            else {
                pathCondition = 2;
                if (mapChoice == 1);
                else if (mapChoice == 2) this->createRandomPowerPath_2();
                else if (mapChoice == 3) this->createRandomPowerPath_3();
                else if (mapChoice == 4) this->createRandomPowerPath_4();
                else this->createRandomPowerPath_5();
            }
        }
        this->moveBullet();
        this->destroyObstruction();
        this->mPtrSnake->clear_mObstacle();
        for (int i = 0; i < this->mPtrMap->getObstacle().size(); i++){
                this->mPtrSnake->senseObstacle(this->mPtrMap->getObstacle()[i]);
        }
        this->renderSnake();
        this->renderBullet();
        this->renderFood();
        this->renderObstacle();
        this->renderPowerPath();


        if (this->mPtrSnake->checkDeath(keyOne))
            break;



        werase(this->mWindows[2]);
        box(this->mWindows[2], 0, 0);
        this->renderInstructionBoard();
        this->renderLeaderBoard();
        this->renderPoints();
        this->renderDifficulty();
        this->renderBulletNum();
        if (this->mPoints >= 3 && mapChoice != 5) return 4;
        //if (this->mPoints >= passPoint && mapChoice != 5) return 4;


        std::this_thread::sleep_for(std::chrono::milliseconds(this->mDelay));

        refresh();
    }
    this->renderBoards();
}

void Game::startGame()
{
    refresh();
    bool choice, choiceMainMenu;
    int condition, choiceLevel = 1;
    while (true)
    {
        this->readLeaderBoard();
        this->renderBoards();
        this->OpenScene();
        choiceMainMenu = this->renderMainMenu();
        if (choiceMainMenu){
            while (true)
            {
                this->renderBoards();
                choiceLevel = this->renderLevelsSelect(choiceLevel);
                if (choiceLevel == 0){
                    break;
                }else{
                    while (true)
                    {
                        werase(this->mWindows[1]);
                        box(this->mWindows[1], 0, 0);
                        this->renderGameBoard();
                        this->initializeGame(choiceLevel);
                        this->renderTip(choiceLevel);
                        condition = this->runGame(choiceLevel);
                        this->updateLeaderBoard();
                        this->writeLeaderBoard();
                        if (condition == 2){
                            continue;
                        }
                        else if (condition == 3){
                            break;
                        }
                        if (condition == 4){
                            int c = renderWinningBoard(choiceLevel);
                            if (choiceLevel < levelNumber){
                                if (c == 1) {
                                    choiceLevel++;
                                    continue;
                                }
                                else if (c == 2) {
                                    continue;
                                }
                                else break;
                            }
                            else {
                                if (c == 1) continue;
                                else break;
                            }
                        }
                        choice = this->renderRestartMenu();
                        if (choice == false)
                        {
                            break;
                        }
                    }
                }
            }
        }else{
            break;
        }
    }
}

// https://en.cppreference.com/w/cpp/io/basic_fstream
bool Game::readLeaderBoard()
{
    std::fstream fhand(this->mRecordBoardFilePath, fhand.binary | fhand.in);
    if (!fhand.is_open())
    {
        return false;
    }
    int temp;
    int i = 0;
    while ((!fhand.eof()) && (i < mNumLeaders))
    {
        fhand.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        this->mLeaderBoard[i] = temp;
        i ++;
    }
    fhand.close();
    return true;
}

bool Game::updateLeaderBoard()
{
    bool updated = false;
    int newScore = this->mPoints;
    for (int i = 0; i < this->mNumLeaders; i ++)
    {
        if (this->mLeaderBoard[i] >= this->mPoints)
        {
            continue;
        }
        int oldScore = this->mLeaderBoard[i];
        this->mLeaderBoard[i] = newScore;
        newScore = oldScore;
        updated = true;
    }
    return updated;
}

bool Game::writeLeaderBoard()
{
    // trunc: clear the data file
    std::fstream fhand(this->mRecordBoardFilePath, fhand.binary | fhand.trunc | fhand.out);
    if (!fhand.is_open())
    {
        return false;
    }
    for (int i = 0; i < this->mNumLeaders; i ++)
    {
        fhand.write(reinterpret_cast<char*>(&this->mLeaderBoard[i]), sizeof(this->mLeaderBoard[i]));;
    }
    fhand.close();
    return true;
}
