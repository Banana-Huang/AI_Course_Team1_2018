#ifndef SOKOBAN_H
#define SOKOBAN_H
#include <vector>
#include <string>

class sokoban {
public:
	sokoban();
	~sokoban();
	void gameProgress();
	bool win_check();
	virtual void loadGame(char* filename);
	virtual int getControl();
	virtual void showGame();
private:
	class Point{
	public:
		Point( int x = 0, int y = 0 ) {
			this->x = x;
			this->y = y;
		}
	~Point() {}
		inline void setX( int x ) { this->x = x; }
		inline void setY( int y ) { this->y = y; }
		inline int getX() const { return x; }
		inline int getY() const { return y; }
	private:
		int x;
		int y;
	};
	const int ROAD = 0, AGENT = 1, BOX = 2, WALL = 3, BLACK = 4, TARGET = 5,BOX_ON_TARGET=6, MAN_ON_TARGET=7;
	const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, RESTART = 4, LEAVE = 5;
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
