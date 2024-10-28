#pragma once
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "random.h"

class Game:Random {
public:
	Game();
	void restart();
	bool leftClickProcessing(int, int);
	bool rightClickProcessing(int, int);

	bool getIsSeccess();
	bool getIsBad();
	bool getIsCostomMap();
	int getGameTime();
	int getFlagSum();
	sf::Vector2i getGameSize();
	std::vector<std::vector<Tile>> getTiles();

	void setBombDensity(float);
	void setNewSize(int, int);
	void setCostomeMap(int);
	
private:
	void setBombAway(int, int);
	void openIt(int,int);
	void BadEnd();
	bool isSuccess();
	void initializeBomb();

	std::vector<std::vector<Tile>> tiles;
	std::chrono::steady_clock::time_point startGameTime;
	std::chrono::steady_clock::time_point now;
	float bombDensity; // отношение бомб к общкму количеству €чеек
	int flagSum;
	int width;
	int height;
	int bombSum;
	bool isCastomMap;
	bool isFirstClick;
	bool badEnd;
	bool success;
};
