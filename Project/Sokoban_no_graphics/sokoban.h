#ifndef SOKOBAN_H
#define SOKOBAN_H
#include "point.h"
#include <vector>
#include <string>

const int ROAD = 0, AGENT = 1, BOX = 2, WALL = 3, BLACK = 4, TARGET = 5,BOX_ON_TARGET=6, MAN_ON_TARGET=7;
const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, RESTART = 4, LEAVE = 5;

class sokoban {
public:
	sokoban();
	~sokoban();
	void gameProgress();
	bool win_check();
	Point getAgentPos() const { return agentPos; };
	std::vector<Point> getTarget() const { return target; };
	std::vector<std::vector<int>> getMaze() const { return grid; };
	virtual void loadGame(char* filename);
	virtual int getControl();
	virtual void showGame();
private:
	Point mapSize;
	Point agentPos;
	int curAction;
	int move;
	int push;
	std::vector<std::vector<int>> grid;
	std::vector<std::vector<int>> backup;
	std::vector<Point> target;
};
#endif
