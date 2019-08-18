#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif
#include"Game.h"
#include<cassert>
using namespace std;
//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else.
//Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie.
//If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void sstatus(const Board& b,bool& over, bool& hasWinner, Side& winner) {
	bool an = false;
	bool as = false;
	for (int i = 1; i != b.holes() + 1; i++) {
		if (b.beans(NORTH, i) != 0) {
			an = true;
		}
		if (b.beans(SOUTH, i) != 0) {
			as = true;
		}
	}
	if (an&&as) {//if there is no available move for one side
		over = false;
		return;
	}
	over = true;
	int n_total = 0;
	int s_total = 0;
	for (int i = 1; i != b.holes() + 1; i++) {
		n_total += b.beans(NORTH, i);
	}
	for (int i = 1; i != b.holes() + 1; i++) {
		s_total += b.beans(SOUTH, i);
	}
	if (b.beans(NORTH, 0) + n_total > b.beans(SOUTH, 0) + s_total) {//deciding the winner
		hasWinner = true;
		winner = NORTH;
	}
	else if (b.beans(NORTH, 0) + n_total < b.beans(SOUTH, 0) + s_total) {
		hasWinner = true;
		winner = SOUTH;
	}
	else {
		hasWinner = false;
	}
}
//function created to make a complete move
int cmove(Game* g,Board& b, Side s,const Player* p,int d) {
	Side stop = SOUTH;
	int h = 0;
	int c = 0;
	int* ap = new int[b.holes()];//arrays created to store number of beans in each side
	int* bp = new int[b.holes()];
	bool add = true;
	while (add) {
		for (int i = 1; i != b.holes() + 1; i++) {//copy the number of beans in each side to corresponding array
			ap[i - 1] = b.beans(s, i);
			bp[i - 1] = b.beans(opponent(s), i);
		}
		if (g==nullptr&&abs(b.beans(SOUTH,0) - b.beans(NORTH,0)) >= b.totalBeans() / 2) {//if the win is in sight
			delete[] ap;
			delete[] bp;
			return 0;
		}
		if (d != 0) {//if it is called by tra function
			c = d;
		}
		else {
			c = p->chooseMove(b, s);
		}
		b.sow(s, c, stop, h);
		if (stop == s && h == 0&&c!=-1) {//if an additional move has to be made
			if (d != 0) {
				return 1;
			}
			else if(g!=nullptr){
				g->display();
				cout << p->name() << " takes an additional move" << endl;
			}
		}
		else {
			add = false;
			if (h != 0) {
				if (ap[h - 1] == 0 && stop == s) {
					if(b.beans(opponent(s),h)!=0){//if a capture is possible
						if (g != nullptr) {
							cerr << "capture for" << p->name()<<endl;
						}
						b.moveToPot(opponent(s), h, s);
						b.moveToPot(s, h, s);
					}
				}
			}
		}
		bool isover;
		bool p1;
		Side s = NORTH;
		sstatus(b,isover, p1, s);
		bool an = false;
		bool as = false;
		if (isover) {//if the game is over
			add = false;
			for (int i = 1; i != b.holes() + 1; i++) {
				if (b.beans(NORTH, i) != 0) {
					an = true;
				}
				if (b.beans(SOUTH, i) != 0) {
					as = true;
				}
			}//move all the remaining beans to their pot
			if (an) {
				for (int i = 1; i != b.holes() + 1; i++) {
					if (b.beans(NORTH, i) != 0) {
						b.moveToPot(NORTH, i, NORTH);
					}
				}
			}
			else {
				for (int i = 1; i != b.holes() + 1; i++) {
					if (b.beans(SOUTH, i) != 0) {
						b.moveToPot(SOUTH, i, SOUTH);
					}
				}
			}
		}
	}
	delete[] ap;
	delete[] bp;
	return 0;
}
int main()
{
	HumanPlayer hp("Marge");
	SmartPlayer bp("Homer");
	Board b(6, 2);
	Game g(b, &hp, &bp);
	g.play();
}
