#include"Board.h"
#include<iostream>
using namespace std;
//Construct a Board with the indicated number of holes per side(not counting the pot) and initial number of beans per hole.
//If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
Board::Board(int nHoles, int nInitialBeansPerHole) {
	nHoles = nHoles <= 0 ? 1 : nHoles;
	nInitialBeansPerHole = nInitialBeansPerHole < 0 ? 0 : nInitialBeansPerHole;//dealing with invalid input
	m_holes = nHoles;
	for (int i = 0; i != nHoles; i++) {
		north_holes.push_back(nInitialBeansPerHole);
		south_holes.push_back(nInitialBeansPerHole);
	}
	north_pot = 0;
	south_pot = 0;
}
//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const {
	int result = 0;
	for (int i = 0; i != m_holes; i++) {
		result += s == NORTH? north_holes[i]:south_holes[i];
	}
	return result;
}
//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const {
	if (hole > m_holes||hole < 0) {
		return -1;
	}
	if (hole == 0) {
		return s == NORTH ? north_pot : south_pot;
	}
	return s == NORTH ? north_holes[hole - 1] : south_holes[hole - 1];
}
//Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const {
	vector<int>::const_iterator it=north_holes.begin();
	vector<int>::const_iterator it1=south_holes.begin();
	int result = 0;
	for (int i = 0; i != m_holes; i++) {
		result += *it + *it1;
		it++;
		it1++;
	}
	return result + north_pot + south_pot;
}
bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
	if (hole > m_holes || hole <= 0) {
		return false;
	}//dealing with invalid input
	vector<int>::iterator it = s == NORTH ? north_holes.begin()+ hole - 1 : south_holes.begin() + hole - 1;
	if (*it == 0) {
		return false;
	}
	int a = *it;
	*it = 0;
	switch (s) {
	case(NORTH):
		while (a > 0) {
			if ((s==NORTH&&it == north_holes.begin()) || (s==SOUTH&&hole == south_holes.size())) {
				if (s==NORTH&&it == north_holes.begin()) {//if we encounter the north pot and 
					it = south_holes.begin();//it's NORTH's player who makes the move
					hole = 0;
					north_pot++;
					a--;
					if (a == 0) {//if it happens that the last bean is in that pot
						break;
					}
					(*it)++;
					a--;
					hole = 1;
					s = SOUTH;
				}
				else {// if we encounter the SOUTH's pot, skip it
					it = north_holes.end();
					it--;
					s = NORTH;
					(*it)++;
					a--;
					hole = m_holes;
				}
			}
			else {
				a--;
				it = s == SOUTH ? ++it : --it;
				(*it)++;
				hole = s == SOUTH ? ++hole : --hole;
			}
		}
		break;
	case(SOUTH):
		while (a > 0) {
			if ((s==NORTH&&it == north_holes.begin()) ||s==SOUTH&&hole==south_holes.size()) {//if we encounter the north pot
				if (s==NORTH&&it == north_holes.begin()) {// skip it
					it = south_holes.begin();
					(*it)++;
					a--;
					s = SOUTH;
					hole = 1;
				}
				else {//if we enounter the south pot, and it's the SOUTH's player who makes the move
					it = north_holes.end();
					it--;
					south_pot++;
					a--;
					hole = 0;
					if (a == 0) {//if it happens that the last bean is in that pot
						break;
					}
					(*it)++;
					a--;
					hole = m_holes;
					s = NORTH;
				}
			}
			else {
				a--;
				it = s == SOUTH ? ++it : --it;
				(*it)++;
				hole = s == SOUTH ? ++hole : --hole;
			}
		}
	}
	endSide = s;
	endHole = hole;
	return true;
}
bool Board::moveToPot(Side s, int hole, Side potOwner) {
	if (hole > m_holes || hole <= 0) {
		return false;
	}
	vector<int>::iterator it;
	it = s == NORTH ? north_holes.begin() + hole - 1 : south_holes.begin() + hole - 1;
	if (potOwner == NORTH) {
		north_pot += *it;
	}
	else {
		south_pot += *it;
	}
	*it = 0;
	return true;
}
bool Board::setBeans(Side s, int hole, int beans) {
	if (hole<0 || hole>m_holes||beans<0) {
		return false;
	}
	if (hole == 0) {
		if (s == NORTH) {
			north_pot = beans;
		}
		else {
			south_pot = beans;
		}
		return true;
	}
	vector<int>::iterator it = s == NORTH ? north_holes.begin() + hole - 1 : south_holes.begin() + hole - 1;
	*it = beans;
	return true;
}