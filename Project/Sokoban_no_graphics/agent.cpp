#include "agent.h"
using namespace std;
agent::agent( vector<vector<int>> maze,vector<Point> target, Point agentPos ) {
    this->mapSize.setY( maze.size() );
    this->mapSize.setX( maze[0].size() );
    this->agentPos = agentPos;
    this->target = target;
    this->grid = maze;
}

void agent::edgeScan() { // Use breath first search to scan the maze
	vector<Point> nextAction = {{0,-1},{1,0},{0,1},{-1,0}}; // Possible action
    set<Point> explored; // Explored state
	queue<Point> frontier; // breath first search frontier
	for ( Point &p: target ) { // explicit annotate target
		if(grid[p.getY()][p.getX()] != 2 && grid[p.getY()][p.getX()] != 1 )
			grid[p.getY()][p.getX()] = 5;
		explored.insert(p); // insert targets into explored set
	}
	frontier.push(agentPos); // begin at agent position
	explored.insert(agentPos); // add begin position into frontier
	Point currentState, nextState;
	while( !frontier.empty() ) {
		currentState = frontier.front();
		frontier.pop();
		for( Point &p: nextAction ) {
			nextState.setX(p.getX() + currentState.getX());
			nextState.setY(p.getY() + currentState.getY());
			if((grid[nextState.getY()][nextState.getX()] == 0 || grid[nextState.getY()][nextState.getX()] == 2 ) 
				&& explored.find(nextState) == explored.end() ) 
			{
				frontier.push(nextState);
				explored.insert(nextState);
			}
		}
		for( int it = 0; it < nextAction.size(); ++it ) {
			if( grid[currentState.getY()+nextAction[it].getY()][currentState.getX()+nextAction[it].getX()] == 3 // check L region
			&& grid[currentState.getY()+nextAction[(it+1)%4].getY()][currentState.getX() + nextAction[(it+1)%4].getX()] == 3 ) {
				if( grid[currentState.getY()][currentState.getX()] == 0 || grid[currentState.getY()][currentState.getX()] == 1) {
					grid[currentState.getY()][currentState.getX()] = 8;
					break;
				} else if (grid[currentState.getY()][currentState.getX()] == 2){
					std::cout << "The game has no solutions" << std::endl;
					break;
				}
			} 
		}

		for( int it = 0; it != nextAction.size(); ++it ) {
			if( grid[currentState.getY()+nextAction[it].getY()][currentState.getX()+nextAction[it].getX()] == 3 ) { // Only one side has wall
				Point w_side(nextAction[it].getX(), nextAction[it].getY()); // wall side
				Point a_side(nextAction[(it+1)%4].getX(),nextAction[(it+1)%4].getY()); // forward side
				Point b_side(nextAction[(it+3)%4].getX(),nextAction[(it+3)%4].getY()); // backward side
				
				bool has_open = false;
				int x = currentState.getX(), y = currentState.getY();
				while( grid[y][x] != 3 && !has_open ) {
					if( grid[y+w_side.getY()][x+w_side.getX()] == 0 || grid[y+a_side.getY()][x+a_side.getX()] == 5|| grid[y+w_side.getY()][x+w_side.getX()] == 8|| grid[y+w_side.getY()][x+w_side.getX()] == 2 ) {
						has_open = true;
						break;
					}
					x += a_side.getX();
					y += a_side.getY();
				}

				x = currentState.getX(); y = currentState.getY();
				while( grid[y][x] != 3 && !has_open ) {
					if( grid[y+w_side.getY()][x+w_side.getX()] == 0 || grid[y+b_side.getY()][x+b_side.getX()] == 5|| grid[y+w_side.getY()][x+w_side.getX()] == 8||grid[y+w_side.getY()][x+w_side.getX()] == 2 ) {
						has_open = true;
						break;
					}
					x += b_side.getX();
					y += b_side.getY();
				}
				if( !has_open )
					grid[currentState.getY()][currentState.getX()] = 8;
			}
		}
	}

	for ( Point &p: target ) {
		if(grid[p.getY()][p.getX()] == 5 )
			grid[p.getY()][p.getX()] = 0;
	}
}

void agent::showMaze(){ // print the maze
	for ( Point &p: target ) {
		if(grid[p.getY()][p.getX()] != 2 && grid[p.getY()][p.getX()] != 1 )
			grid[p.getY()][p.getX()] = 5;
	}
	for ( vector<int> &temp: grid ) {
		for ( int &number: temp ) {
			switch(number) {
				case 0: // ROAD
					cout << "  ";
					break;
				case 4: // BLACK
					cout << " .";
					break;
				case 1: // AGENT
					cout << " !";
					break;
				case 2: // BOX
					cout << " ^";
					break;
				case 3: // WALL
					cout << " #";
					break;
				case 5: // TARGET
					cout << " @";
					break;
                case 8: // Box can't move
                    cout << " X";
                    break;
				default:
					break;
			}
		}
		cout << endl;
	}
	for ( Point &p: target ) {
		if(grid[p.getY()][p.getX()] == 5 )
			grid[p.getY()][p.getX()] = 0;
	}
}