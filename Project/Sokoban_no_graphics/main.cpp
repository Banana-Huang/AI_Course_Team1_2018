#include <iostream>
#include <vector>
#include <string>
#include "sokoban.h"
using namespace std;
int main ()
{
	string filename;
  	sokoban game;
	cout << "Which level you want to play? ";
	getline(cin,filename);
  	game.loadGame(const_cast<char*>(filename.c_str()));
  	game.gameProgress();
  	return 0;
} 
