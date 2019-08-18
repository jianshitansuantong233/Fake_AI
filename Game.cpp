#include"Game.h"
#include<iostream>
using namespace std;
//Construct a Game to be played with the indicated players on a copy of the board b.
//The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north) 
	:m_b(b)
{
	turn = SOUTH;
	m_s = south;
	m_n = north;
}
//Display the game's board in a manner of your choosing, 
//provided you show the names of the players and a reasonable representation of the state of the board.
void Game::display()const {
	cout << "      " << m_n->name() << endl;
	for (int i = 1; i != m_b.holes() + 1; i++) {
		cout << "  " << m_b.beans(NORTH, i);
	}
	cout << endl << m_b.beans(NORTH, 0);
	
	for (int i = 1; i != m_b.holes() + 1; i++) {
		cout << "   ";
	}
	cout << m_b.beans(SOUTH, 0) << endl;
	for (int i = 1; i != m_b.holes() + 1; i++) {
		cout << "  " << m_b.beans(SOUTH, i);
	}
	cout << endl << "      " << m_s->name() << endl;
}
//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. 
//Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. 
//If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const {
	sstatus(m_b, over, hasWinner, winner);
}
//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is 
//(so that it becomes the other player's turn) and return true.
bool Game::move() {
	bool an = false;
	bool as = false;
	for (int i = 1; i != m_b.holes() + 1; i++) {
		if (m_b.beans(NORTH, i) != 0) {
			an = true;
		}
		if (m_b.beans(SOUTH, i) != 0) {
			as = true;
		}
	}
	if (!(an&&as)) {
		return false;
	}
	cmove(this, m_b, turn, turn == NORTH ? m_n : m_s);
	turn = opponent(turn);
	return true;
}
//Play the game.Display the progress of the game in a manner of your choosing, 
//provided that someone looking at the screen can follow what's happening.
void Game::play() {
	bool stop = false;
	bool h = false;
	Side w = NORTH;
	status(stop, h, w);
	display();
	while (!stop) {
		cout << "Press enter to continue" << endl;
		cin.ignore(1000, '\n');
		move();
		display();
		status(stop, h, w);
	}
}