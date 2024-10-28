#include "tile.h"

Tile::Tile() {

	status = closed;
	isBomb = false;
	bombAway = 0;

}
Tile::Tile(const Tile& p)
{
	bombAway = p.bombAway;
	isBomb = p.isBomb;
	status = p.status;   
}

tile_status Tile::getStatus() {
	return status;
}
bool Tile::getIsBomb() {
	return isBomb;
}
int Tile::getBombAway() {
	return bombAway;
}

void Tile::setIsBomb(bool isB) {
	isBomb = isB;
}
void Tile::plusBombAway(int boAw) {
	bombAway += boAw;
}
void Tile::setStatus(tile_status stat) {
	status = stat;	
}

