#include <iostream>
#include <vector>
#include <string>
#include "sokoban.h"
#include "agent.h"
using namespace std;
int main ()
{
	string filename;
  	sokoban game;
	cout << "Which level you want to play? ";
	getline(cin,filename);
  	game.loadGame(const_cast<char*>(filename.c_str()));
  	agent man( game.getMaze(),game.getTarget(),game.getAgentPos());
	man.showMaze();
	cout << endl;
	man.edgeScan();
	man.showMaze();
  	return 0;
} 
