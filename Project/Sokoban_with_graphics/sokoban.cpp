#include "mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}

sokoban::sokoban()
:move(0),push(0),curAction(0){}

sokoban::~sokoban() {}

int sokoban::getWidth() {
    return mapSize.x();
}

int sokoban::getHeight() {
    return mapSize.y();
}

int sokoban::getData( int x, int y ) {
    return grid[y][x];
}

QVector<QPoint>& sokoban::getHistory() {
    return history;
}

QVector<QPoint>& sokoban::getTargetPos() {
    return target;
}

QPoint sokoban::getAgentPos() {
    return QPoint(agentPos.x(),agentPos.y());
}

bool sokoban::gameProgress( int ctr_key ) {
	bool win_flag = false;
    int curX, curY;
    QPoint agentBackup = agentPos;
    curX = agentPos.x();
    curY = agentPos.y();
    curAction = ctr_key;
    switch(ctr_key) {
        case 0: // UP
            if( grid[curY-1][curX] == ROAD ) {
                agentPos.setY(curY-1); agentPos.setX(curX);
                history.append(QPoint(curX,curY));
                history.append(QPoint(curX,curY-1));
                move++;
            } else if( grid[curY-1][curX] == BOX ) {
                if( grid[curY-1][curX] + grid[curY-2][curX] < 4 ) {
                    agentPos.setY(curY-1); agentPos.setX(curX);
                    history.append(QPoint(curX,curY));
                    history.append(QPoint(curX,curY-1));
                    history.append(QPoint(curX,curY-2));
                    push++; move++;
                }
            }
            break;
        case 1: // DOWN
            if( grid[curY+1][curX] == ROAD ) {
                agentPos.setY(curY+1); agentPos.setX(curX);
                history.append(QPoint(curX,curY));
                history.append(QPoint(curX,curY+1));
                move++;
            } else if( grid[curY+1][curX] == BOX ) {
                if( grid[curY+1][curX] + grid[curY+2][curX] < 4 ) {
                    agentPos.setY(curY+1); agentPos.setX(curX);
                    history.append(QPoint(curX,curY));
                    history.append(QPoint(curX,curY+1));
                    history.append(QPoint(curX,curY+2));
                    push++; move++;
                }
            }
            break;
        case 2: // LEFT
            if( grid[curY][curX-1] == ROAD ) {
                agentPos.setY(curY); agentPos.setX(curX-1);
                history.append(QPoint(curX,curY));
                history.append(QPoint(curX-1,curY));
                move++;
            } else if( grid[curY][curX-1] == BOX ) {
                if( grid[curY][curX-1] + grid[curY][curX-2] < 4 ) {
                    agentPos.setY(curY); agentPos.setX(curX-1);
                    history.append(QPoint(curX,curY));
                    history.append(QPoint(curX-1,curY));
                    history.append(QPoint(curX-2,curY));
                    push++; move++;
                }
            }
            break;
        case 3: // RIGHT
            if( grid[curY][curX+1] == ROAD ) {
                agentPos.setY(curY); agentPos.setX(curX+1);
                history.append(QPoint(curX,curY));
                history.append(QPoint(curX+1,curY));
                move++;
            } else if( grid[curY][curX+1] == BOX ) {
                if( grid[curY][curX+1] + grid[curY][curX+2] < 4 ) {
                    agentPos.setY(curY); agentPos.setX(curX+1);
                    history.append(QPoint(curX,curY));
                    history.append(QPoint(curX+1,curY));
                    history.append(QPoint(curX+2,curY));
                    push++; move++;
                }
            }
            break;
        case 4: // RESTART
            win_flag = false;
            move = push = 0;
            grid = backup;
            agentPos= agentBackup;
            break;
        default:
            break;
        }

    for( int i = 0; i < history.size(); i++ ) {
         grid[history[i].y()][history[i].x()] = i;
    }
    if (win_check()) {
        win_flag = true;
    }
    return win_flag;
}


bool sokoban::win_check() {
	int count = 0;
    for ( QPoint &p: target ) {
        if( grid[p.y()][p.x()] == 2 )
			count++;
	}
	
	if( count == target.size() )
		return true;
	else
		return false;
}

void sokoban::loadGame( std::string filename ) {
	FILE* file;
    if( !(file = fopen(const_cast<char*>(filename.c_str()),"r"))) {
		return;
	}
	int x, y, target_number;
	fscanf(file,"%d %d", &x, &y); // get map size
	mapSize.setX(x); mapSize.setY(y);
	fscanf(file,"%d %d", &x, &y); // get agent position
	agentPos.setX(x); agentPos.setY(y);
	fscanf( file,"%d", &target_number );
	target.resize(target_number);
    for( QPoint& p: target ) {
		fscanf(file,"%d %d", &x, &y); // get target position
        p.setX(x); p.setY(y);
	}
	
    grid.resize(mapSize.y());
    for ( QVector<int> &temp : grid ) {
        temp.resize(mapSize.x());
        for( int& number: temp ) {
            fscanf(file,"%d", &x);
            number = x;
        }
    }
	move = push = 0;
	backup = grid;
}

void sokoban::edgeScan() {
    QVector<QPoint> nextAction = {{0,-1},{1,0},{0,1},{-1,0}}; // Possible action
    QSet<QPoint> explored; // Explored state
    QQueue<QPoint> frontier; // breath first search frontier
    for ( QPoint &p: target ) { // explicit annotate target
        if(grid[p.y()][p.x()] != 2 && grid[p.y()][p.x()] != 1 )
            grid[p.y()][p.x()] = 5;
        explored.insert(p); // insert targets into explored set
    }
    frontier.enqueue(agentPos); // begin at agent position
    explored.insert(agentPos); // add begin position into frontier
    QPoint currentState, nextState;
    while( !frontier.empty() ) {
        currentState = frontier.dequeue();
        for( QPoint &p: nextAction ) {
            nextState.setX(p.x() + currentState.x());
            nextState.setY(p.y() + currentState.y());
            if((grid[nextState.y()][nextState.x()] == 0 || grid[nextState.y()][nextState.x()] == 2 )
                && explored.find(nextState) == explored.end() )
            {
                frontier.enqueue(nextState);
                explored.insert(nextState);
            }
        }
        for( int it = 0; it < nextAction.size(); ++it ) {
            if( grid[currentState.y()+nextAction[it].y()][currentState.x()+nextAction[it].x()] == 3 // check L region
            && grid[currentState.y()+nextAction[(it+1)%4].y()][currentState.x() + nextAction[(it+1)%4].x()] == 3 ) {
                if( grid[currentState.y()][currentState.x()] == 0 || grid[currentState.y()][currentState.x()] == 1) {
                    grid[currentState.y()][currentState.x()] = 8;
                    break;
                } else if (grid[currentState.y()][currentState.x()] == 2){
                    std::cout << "The game has no solutions" << std::endl;
                    break;
                }
            }
        }

        for( int it = 0; it != nextAction.size(); ++it ) {
            if( grid[currentState.y()+nextAction[it].y()][currentState.x()+nextAction[it].x()] == 3 ) { // Only one side has wall
                QPoint w_side(nextAction[it].x(), nextAction[it].y()); // wall side
                QPoint a_side(nextAction[(it+1)%4].x(),nextAction[(it+1)%4].y()); // forward side
                QPoint b_side(nextAction[(it+3)%4].x(),nextAction[(it+3)%4].y()); // backward side

                bool has_open = false;
                int x = currentState.x(), y = currentState.y();
                while( grid[y][x] != 3 && !has_open ) {
                    if( grid[y+w_side.y()][x+w_side.x()] == 0 || grid[y+a_side.y()][x+a_side.x()] == 5|| grid[y+w_side.y()][x+w_side.x()] == 8|| grid[y+w_side.y()][x+w_side.x()] == 2 ) {
                        has_open = true;
                        break;
                    }
                    x += a_side.x();
                    y += a_side.y();
                }

                x = currentState.x(); y = currentState.y();
                while( grid[y][x] != 3 && !has_open ) {
                    if( grid[y+w_side.y()][x+w_side.x()] == 0 || grid[y+b_side.y()][x+b_side.x()] == 5|| grid[y+w_side.y()][x+w_side.x()] == 8||grid[y+w_side.y()][x+w_side.x()] == 2 ) {
                        has_open = true;
                        break;
                    }
                    x += b_side.x();
                    y += b_side.y();
                }
                if( !has_open )
                    grid[currentState.y()][currentState.x()] = 8;
            }
        }
    }

    for ( QPoint &p: target ) {
        if(grid[p.y()][p.x()] == 5 )
            grid[p.y()][p.x()] = 0;
    }
}

void sokoban::restore() {
    grid = backup;
}




