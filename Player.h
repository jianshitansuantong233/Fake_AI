#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED
#include<string>
#include<map>
#include<iostream>
#include"Board.h"
class Game;
using namespace std;
class Player {
public:
	//Create a Player with the indicated name.
	Player(std::string name) {
		m_name = name;
	}
	//Return the name of the player.
	std::string name() const {
		return m_name;
	}
	//Return false if the player is a computer player. Return true if the player is human. 
	//Most kinds of players will be computer players.
	virtual bool isInteractive() const {
		return false;
	}
	//Every concrete class derived from this class must implement this function 
	//so that if the player were to be playing side s and had to make a move given board b, 
	//the function returns the move the player would choose. 
	//If no move is possible, return −1.
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player(){}
private:
	std::string m_name;
};
class HumanPlayer:public Player {
public:
	HumanPlayer(std::string name) 
		:Player(name)
	{

	}
	virtual bool isInteractive() const {
		return true;
	}
	virtual int chooseMove(const Board& b, Side s) const;
};
class BadPlayer :public Player{
public:
	BadPlayer(std::string name)
		:Player(name)
	{

	}
	virtual int chooseMove(const Board& b, Side s) const;
};
class SmartPlayer :public Player {
public:
	SmartPlayer(std::string name)
		:Player(name)
	{
	}
	virtual int chooseMove(const Board& b, Side s) const;
private:
	int tra(const Board& b, Side s,int d,int& r)const;
};
#endif