#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() {
	isCastomMap = false;
	width = 6;
	height = 6;
	flagSum = 0;
	isFirstClick = true;
	bombDensity = 0.1;
	bombSum =  width* height * bombDensity;
	badEnd = false;
	success = false;
	startGameTime = std::chrono::steady_clock::now();
	now = std::chrono::steady_clock::now();
	for (int i = 0; i < width; i++) {
		std::vector<Tile> vec(height);
		tiles.push_back(vec);
	}
	initializeBomb();
}
void Game::restart() {
	
	
	isFirstClick = true;
	badEnd = false;
	success = false;
	bombSum = width * height * bombDensity;
	now = std::chrono::steady_clock::now();
	startGameTime = std::chrono::steady_clock::now();
	tiles.clear();
	for (int i = 0; i < width; i++) {
		std::vector<Tile> vec(height);
		tiles.push_back(vec);
	}
	initializeBomb();
}
bool Game::leftClickProcessing(int x,int y) {

	bool ret = false;
	if(!success&&!badEnd){

		if (isFirstClick) {
			startGameTime = std::chrono::steady_clock::now();
			isFirstClick = false;
		}

		if (tiles[x][y].getStatus() == closed)
		{
			ret = true;
			if (!tiles[x][y].getIsBomb()) {
				openIt(x, y);
			}
			else {
				BadEnd();
				ret = false;
			}
		}
		if (!flagSum) {
			if (isSuccess()) {
				success = true;
			}
		}
	}
	return ret;
}
bool Game::rightClickProcessing(int x, int y) {
	bool ret = false;

	if (!success && !badEnd) {
		if (isFirstClick) {
			startGameTime = std::chrono::steady_clock::now();
			isFirstClick = false;
		}

		if (tiles[x][y].getStatus() == closed) {
			ret = true;
			tiles[x][y].setStatus(markered);
			flagSum--;
		}
		else if (tiles[x][y].getStatus() == markered) {
			ret = true;
			tiles[x][y].setStatus(closed);
			flagSum++;
		}

		if (!flagSum) {
			if (isSuccess()) {
				success = true;
				ret = false;
			}
		}
	}
	return ret;
}

sf::Vector2i Game::getGameSize() {
	return sf::Vector2i(width, height);
}
std::vector<std::vector<Tile>> Game::getTiles() {
	return tiles;
}
int Game::getGameTime() {

	if (success||badEnd) {
		int time = std::chrono::duration_cast<std::chrono::seconds>(now - startGameTime).count();
		return time >= 0 ? time : 0;
	}
	else if(!isFirstClick){
		now = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::seconds>(now - startGameTime).count();
	}
	else {
		return 0;
	}
}
int Game::getFlagSum() {
	return flagSum;
}
bool Game::getIsCostomMap(){
	return isCastomMap;
}
bool Game::getIsBad() {
	return badEnd;
}
bool Game::getIsSeccess() {
	return success;
}

void Game::setNewSize(int wi, int he) {
	width = 1;
	height = 1;
	if (wi > 0) {
		width = wi;
	}
	if (he > 0) {
		height = he;
	}
	
	restart();

}
void Game::setCostomeMap(int) {
	std::vector<std::vector<std::vector<int>>> maps = {
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
			{1,0,1,1,1,1,1,1,1,1,1,0,1,0,1},
			{1,0,1,0,0,0,0,0,0,0,1,0,1,0,1},
			{1,0,1,0,1,1,1,1,1,0,1,0,1,0,1},
			{1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
			{1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
			{1,0,1,0,1,0,0,0,0,0,1,0,1,0,1},
			{1,0,1,0,1,1,1,1,1,1,1,0,1,0,1},
			{1,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
			{1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		}

	};

}
void Game::setBombDensity(float x) {
	bombDensity = x;
	if (bombDensity > 1) {
		bombDensity = 1;
	}
	else if (bombDensity < 0) {
		bombDensity = 0;
	}
}

void Game::openIt(int x, int y) {
	if (x>=0&&x<width&&y>=0&&y<height) {
		if (tiles[x][y].getStatus() == closed) {
			if (tiles[x][y].getBombAway() == 0) {
				tiles[x][y].setStatus(opened);
				openIt(x - 1, y - 1);
				openIt(x, y - 1);
				openIt(x + 1, y - 1);
				openIt(x - 1, y);
				openIt(x + 1, y);
				openIt(x - 1, y + 1);
				openIt(x, y + 1);
				openIt(x + 1, y + 1);
			}
			else {
				tiles[x][y].setStatus(opened);
			}
		}
	}
	
	
	
}
bool Game::isSuccess() {
	int guessed = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (tiles[i][j].getStatus() == markered && (!tiles[i][j].getIsBomb())) {
				return false;
			}
			else if(tiles[i][j].getStatus() == closed) {
				return false;
			}
		}
	}
}
void Game::BadEnd() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (tiles[i][j].getIsBomb()) {
				tiles[i][j].setStatus(blownuped);
			}
		}
	}
	badEnd = true;
}
void Game::initializeBomb() {

	//init  bimb and bombAway
	if (!bombSum) {
		bombSum = 1;
	}
	if (bombDensity > 0.91) {
		bombSum--;
	}
	int bombs = bombSum;
	flagSum = bombs;
	while (bombs > 0) {
		int i = get_random_int(0, width-1);
		int j = get_random_int(0, height-1);
		if (!tiles[i][j].getIsBomb()) {
			tiles[i][j].setIsBomb(true);

			setBombAway(i - 1, j - 1);
			setBombAway(i, j - 1);
			setBombAway(i + 1, j - 1);
			setBombAway(i - 1, j);
			setBombAway(i + 1, j);
			setBombAway(i - 1, j + 1);
			setBombAway(i, j + 1);
			setBombAway(i + 1, j + 1);

			bombs--;
		}
		
	}

	

}
void Game::setBombAway(int i,int j) {

	if (i >= 0 && i < width && j >= 0 && j < height) {
		tiles[i][j].plusBombAway(1);
	}
}