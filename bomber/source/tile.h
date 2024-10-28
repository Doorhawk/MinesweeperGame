#pragma once

enum tile_status { opened, closed, markered, blownuped };

class Tile {
public:
	Tile();
	Tile(const Tile& p);

	tile_status getStatus();
	bool getIsBomb();
	int getBombAway();
	
	void setIsBomb(bool);
	void plusBombAway(int);
	void setStatus(tile_status);
private:
	int bombAway;
	bool isBomb;
	tile_status status;

};