#ifndef AGENT_H
#define AGENT_H
#include <vector>
#include <set>
#include <queue>
#include <iostream>
#include "point.h"
class agent {
public:
    agent( std::vector<std::vector<int>> maze, std::vector<Point> target, Point agentPos );
    ~agent() {};
    void edgeScan();
    virtual void showMaze();
private:
    Point mapSize;
	Point agentPos;
    std::vector<std::vector<int>> grid;
    std::vector<Point> target;
};
#endif