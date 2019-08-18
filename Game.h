#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include"Player.h"
class Game {
public:
	//to see what these function do, refer to Game.cpp
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const {
		if (hole > m_b.holes() || hole < 0) {
			return -1;
		}
		return m_b.beans(s, hole);
	}
private:
	Side turn;
	Player* m_s;
	Player* m_n;
	Board m_b;
};
#endif
