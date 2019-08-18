#ifndef SIDE_INCLUDED
#define SIDE_INCLUDED
class Board;
class Player;
class Game;
enum Side { NORTH, SOUTH };
const int NSIDES = 2;
const int POT = 0;
int cmove(Game* g,Board& b,Side s,const Player* p,int d=0);
void sstatus(const Board& b,bool& over, bool& hasWinner, Side& winner);
inline

Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}

#endif
