#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED
#include"Side.h"
#include<vector>
class Board {
public:
	Board(int nHoles, int nInitialBeansPerHole);
	int holes() const {
		return m_holes;
	}
	int beans(Side s, int hole) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	int beansInPlay(Side s) const;
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);
private:
	int m_holes;//not include pot
	std::vector<int> south_holes;
	std::vector<int> north_holes;
	int north_pot;
	int south_pot;
};
#endif
