#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "AudioManager.h"


class WindowManager {
public:
	WindowManager();
	void updateWindow();
	
private:
	void changeSceen();
	void drawGame();
	void drawMainScreen();
	void changeTileSise(int);
	void changeBombSum(int);
	void changeSize(int,bool);
	void rightClick(int, int);
	void leftClick(int, int);
	void mainButtone();
	void createWindow(int, int);
	void controlButtons(sf::Event);
	void drawFrame();
	void enableDemonicLevel();
	void restartGame();
	

	AudioManager audio;

	bool soundPlyed;
	bool isEnableDemonicLevel;
	int sceneNum;
	int bombDensity;
	int gameDifficult;
	int height;
	int width;
	int edgeSize;
	int betweenTileSize;
	int tileSize;
	int gameSizeX;
	int gameSizeY;
	Game game;
	sf::RenderWindow window;
	sf::Font font;
};