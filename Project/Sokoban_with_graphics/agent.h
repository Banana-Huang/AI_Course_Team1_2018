#ifndef AGENT_H
#define AGENT_H
#include <QVector>
#include <QPoint>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <iostream>
#include <cmath>
#include <deque>
#include <list>
#include <map>
#include "point.h"
struct target {
    int barrier;
    Point position;
public:
    target( const int& bar, const Point& pos ) {
        barrier = bar;
        position = pos;
    }
};

inline bool operator<( const target& a, const target& b ) {
    return a.barrier > b.barrier;
}

struct box {
    int barrier;
    Point position;
public:
    box( const int& bar, const Point& pos ) {
        barrier = bar;
        position = pos;
    }
};

inline bool operator<( const box& a, const box& b ) {
    return a.barrier < b.barrier;
}

struct state {
    int action;
    float heuristic;
    Point position;
public:
    state( const float& h, const Point& s, int a = -1 ) { // -1 mean no action
        action = a;
        heuristic = h;
        position = s;
    }
};

inline bool operator<( const state& a, const state& b ) {
    return a.heuristic < b.heuristic;
}

class agent {
public:
    agent( std::vector<std::vector<int>> maze, std::vector<Point> target, Point agentPos );
    agent( QVector<QVector<int>> maze, QVector<QPoint> target, QPoint agentPos );
    virtual ~agent() {};
    void setConfig( std::vector<std::vector<int>> maze, std::vector<Point> target, Point agentPos );
    void edgeScan();
    bool planAction();
    int getAction();
    bool boxTurn( std::vector<target>, std::map<Point, int>, Point, bool , std::set<Point>, std::set<Point> );
    bool agentTurn( std::vector<target>, std::map<Point, int>, Point, state&, std::set<Point>, std::set<Point>  );
    std::vector<std::vector<int>> getAgentView() const;
    std::vector<std::vector<int>> getBoxView() const;
    float manhattanDistance( Point src, Point dst );
    float euclideanDistance( Point src, Point dst );
    void evaluateTarget( std::vector<target>&, std::map<Point, int> );
    void evaluateBox( const target&, std::map<Point, int>& );
    void printTargetPos() const;
    void printBoxPos() const;
    virtual void showMaze( std::vector<std::vector<int>> );
private:
    Point mapSize;
	Point agentPos;
    std::vector<std::vector<int>> agentView;
    std::vector<std::vector<int>> boxView;
    std::vector<Point> targetVector;
    std::vector<Point> boxVector;
    std::deque<int> actionStack;
};
#endif
