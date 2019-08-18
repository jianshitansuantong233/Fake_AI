#include"Player.h"
using namespace std;
//A HumanPlayer chooses its move by prompting a person running the program for a move
//(reprompting if necessary until the person enters a valid hole number), and returning that choice.
int HumanPlayer::chooseMove(const Board& b, Side s) const {
	string p;
	bool stop = true;
	while (stop) {
		cout << "enter a number for" << name() << endl;
		getline(cin, p);
		if (p.size() == 0) {
			continue;
		}
		for (int i = 0; i != p.size(); i++) {
			if (!isdigit(p[i])) {//if the human player did not enter a digit
				continue;
			}
		}
		int hole=stoi(p);
			if (hole > b.holes() || hole <= 0||b.beans(s,hole) == 0) {
				continue;
			}
			else {
				return hole;				
			}
		}
	return -1;
}
//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. 
int BadPlayer::chooseMove(const Board& b, Side s)const {
	for (int i = 1; i != b.holes() + 1; i++) {
		if (b.beans(s, i) != 0) {
			return i;
		}
	}
	return -1;
}
int SmartPlayer::chooseMove(const Board& b, Side s) const {
	int r = 0;
	int re = 0;
	int a = 0;
	for (int i = 1; i != b.holes() + 1; i++) {
		if (b.beans(s, i) != 0) {
			re++;
			a = i;
		}
	}
	if (re == 1) {//if there is only one available move, then return that one
		return a;
	}
	int dd = re*(b.totalBeans() - b.beans(NORTH, 0) - b.beans(SOUTH, 0));//classify the Board
	if ( dd >= 150) {
		tra(b, s, 6, r);
	}
	else if(dd >= 60){
		tra(b, s, 7, r);
	}
	else{
		tra(b, s, 10, r);
	}
	return r;
}
int SmartPlayer::tra(const Board& b, Side s,int d,int& r) const{
	Board bb = b;//copy of the board used to simulate movement
	map<int, int> ma;//the map used to map values of each choice with the chosen hole
	int re = 0;
	bool isover = false;
	Side w = NORTH;
	bool h1 = false;
	sstatus(b, isover, h1, w);
	if (isover||d==0){
		if (isover) {//if the game is over
			if (h1) {
				return w == SOUTH ? 10000000 : -10000000;
			}
		}//if we reached the set depth
		return bb.beans(SOUTH, 0) - bb.beans(NORTH, 0);
	}
	int result = b.beans(SOUTH,0);
	int op_result = b.beans(NORTH, 0);
	if (abs(result-op_result)>=bb.totalBeans()/2) {//if a majority of beans in on one side
		for (int i = 1; i != bb.holes() + 1; i++) {
			if (b.beans(s, i) != 0) {
				r = i;
				break;
			}
		}
		return result < op_result ? -10000000 : 10000000;
	}
	for (int i = 1; i != bb.holes() + 1; i++) {
		if (bb.beans(s, i) != 0) {
			bool f = false;
			for (int j = i; j != bb.holes() + 1; j++) {
				if (b.beans(s, j) != 0) {//if there is only one choice available
					f = true;
					break;
				}
			}
			if (!f) {
				r = i;//set the hole to that choice and return the difference between number of beans in two pots
				return bb.beans(SOUTH, 0) - bb.beans(NORTH, 0);
			}
			else {
				int q = cmove(nullptr, bb, s, this, i);//make a general move
				if (q == 1) {//if we need an additional move
					int p = tra(bb, s, d, r);
					ma[p] = i;
					bb = b;
					r = i;
				}
				else {
					int p = tra(bb, opponent(s), d - 1, r);
					ma[p] = i;	
					bb = b;	
					r = i;
				}						
			}
		}
	}
	map<int, int>::iterator it = ma.begin();
	if (s == SOUTH) {//if s is SOUTH, we want the biggest possible value for a choice
		while (it != ma.end()) {
			re = (*it).first;
			r  = (*it).second;
			it++;
		}
	}
	else {//if it is NORTH, we want the smallest
		re = (*it).first;
		r = (*it).second;
	}
	return re;
}