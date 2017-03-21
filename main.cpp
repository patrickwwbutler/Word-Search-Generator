/*
 * main.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: patrickbutler
 */
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
 * Personal Notes
 * For all unique solutions:
 * Make a branching recursive function, that, for each word, makes a path going forward to the next word for every single possible position
 * For every single possible position of the first word, check every single possible position for the second word...  At the very end, add all the grids to a referenced vector of grids.
 *
 * Use symmetry of the grid to cut down on runtime - If there is a solution, flipping that solution is also a solution
 * Use intersections to find solutions more easily
 *
 * To do:
 * For single solution, be able to fix grids with banned words
 *
 * For all solutions, write recursive function creating solutions
 * Clear out solutions with banned words, simply check for each banned word, and if any are found, just remove that solution from the list
 *
 * Make the correct output for both single and all solutions
 */

//findViableSpot searched through the grid, and finds a spot in there that could fit the selected word.
//Returns the coordinates in r and c, and the direction the word faces in dir
void findViableSpot(string word, vector<vector<string> > grid, int& r, int& c, int& dir){
	int len = word.length();
	int width = grid.size();
	int height = grid.size();
	if(len > width && len > height){ //Check if the word is too large for this grid
		r = -1;
		c = -1;
		dir = -1;
		return;
	}
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			//Check for just left to right
			if((width - j) >= len){
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i][j+k] == " " || grid[i][j+k] == word.substr(k, 1))){
						good = false;
						break; //If there isn't either an open space or a letter that matches the matching index of the word, break out
					}
				}
				if(good){
					r = i;
					c = j;
					dir = 0; //0 means it is simply left to right, horizontal
				}
			}
			if(j + 1 > len){ //Checking backwards from this spot
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i][j-k] == " " || grid[i][j-k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					r = i;
					c = j;
					dir = 1; //1 means backwards, or left
					return;
				}
			}
			if((height - i) >= len){ //Downwards
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i+k][j] == " " || grid[i+k][j] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					r = i;
					c = j;
					dir = 2; //2 means downwards
					return;
				}
			}
			if(i+1 >= len){ //Upwards
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i-k][j] == " " || grid[i-k][j] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					r = i;
					c = j;
					dir = 3; //3 means upwards
					return;
				}
			}
			if((width - j) >= len && (height - i) >= len){ //Down and to the right diagonally
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i+k][j+k] == " " || grid[i+k][j+k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					r = i;
					c = j;
					dir = 4; //4 means down and to the right
					return;
				}
			}
			if((j+1) >= len && (height - i) >= len){ //Down and to the left diagonally
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i+k][j-k] == " " || grid[i+k][j-k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					r = i;
					c = j;
					dir = 5; //5 means down and to the left
					return;
				}
			}
			if((width - j) >= len && (i+1) >= len){ //Up and to the right diagonally
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i-k][j+k] == " " || grid[i-k][j+k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					r = i;
					c = j;
					dir = 6;
					return;
				}
			}
			if((j+1) >= len && (i+1) >= len){ //Up and to the left diagonally
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i-k][j-k] == " " || grid[i-k][j-k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					r = i;
					c = j;
					dir = 7;
					return;
				}
			}
		}
	}
}

void singlePuzzle(vector<vector<string> >& grid, vector<string>& words, int wordIndex){
	if(wordIndex == words.size()){
		return;
	}
	string word = words[wordIndex];
	int r, c, dir;
	findViableSpot(word, grid, r, c, dir);
	for(int i = 0; i < word.length(); i++){
		if(dir == 0){ //Right
			grid[r][c+i] = word.substr(i, 1);
		}
		if(dir == 1){ //Left
			grid[r][c-i] = word.substr(i, 1);
		}
		if(dir == 2){ //Down
			grid[r+i][c] = word.substr(i, 1);
		}
		if(dir == 3){ //Up
			grid[r-1][c] = word.substr(i, 1);
		}
		if(dir == 4){ //Down and right
			grid[r+i][c+i] = word.substr(i, 1);
		}
		if(dir == 5){ //Down and left
			grid[r+i][c-i] = word.substr(i, 1);
		}
		if(dir == 6){ //Up and right
			grid[r-i][c+i] = word.substr(i, 1);
		}
		if(dir == 7){ //Up and left
			grid[r-i][c-i] = word.substr(i, 1);
		}
	}
	wordIndex++;
	singlePuzzle(grid, words, wordIndex);
}

bool foundWord(vector<vector<string> >& grid, string word, int letterInd, int r, int c, int dir){
	if(letterInd == word.length()){
		return true;
	}
	string letter = word.substr(letterInd, 1);
	if(r == -1 && c == -1){
		for(int i = 0; i < grid.size(); i++){
			for(int j = 0; j < grid[0].size(); j++){
				if(grid[i][j] == letter){
					letterInd++;
					return foundWord(grid, word, letterInd, i, j, -1);
				}
			}
		}
		return false;
	}
	else{
		if(dir == -1){
			for(int i = -1; i < 2; i++){
				for(int j = -1; j < 2; j++){
					if(!(i == 0 && j == 0)){
						if(grid[r+i][c+j] == letter){
							letterInd++;
							int d;
							if(i == 0 && j == 1) d = 0;
							if(i == 0 && j == -1) d = 1;
							if(i == 1 && j == 0) d = 2;
							if(i == -1 && j == 0) d = 3;
							if(i == 1 && j == 1) d = 4;
							if(i == 1 && j == -1) d= 5;
							if(i == -1 && j == 1) d = 6;
							if(i == -1 && j == -1) d= 7;
							if(foundWord(grid, word, letterInd, r+i, c+j, d)){
								return true;
							}
						}
					}
				}
			}
			return false;
		}
		if(dir == 0){
			if(grid[r][c+1] == letter){
				letterInd++;
				if(foundWord(grid, word, letterInd, r, c+1, dir)){
					return true;
				}
			}
			else{return false;}
		}
		if(dir == 1){
			if(grid[r][c-1] == letter){
				letterInd++;
				if(foundWord(grid, word, letterInd, r, c+1, dir)){
					return true;
				}
			}
			else{return false;}
		}
		if(dir == 2){
			if(grid[r+1][c] == letter){
				letterInd++;
				if(foundWord(grid, word, letterInd, r, c+1, dir)){
					return true;
				}
			}
			else{return false;}
		}
		if(dir == 3){
			if(grid[r-1][c] == letter){
				letterInd++;
				if(foundWord(grid, word, letterInd, r, c+1, dir)){
					return true;
				}
			}
			else{return false;}
		}
		if(dir == 4){
			if(grid[r+1][c+1] == letter){
				letterInd++;
				if(foundWord(grid, word, letterInd, r, c+1, dir)){
					return true;
				}
			}
		}
		if(dir == 5){
			if(grid[r+1][c-1] == letter){
				letterInd++;
				if(foundWord(grid, word, letterInd, r, c+1, dir)){
					return true;
				}
			}
			else{return false;}
		}
		if(dir == 6){
			if(grid[r-1][c+1] == letter){
				letterInd++;
				if(foundWord(grid, word, letterInd, r, c+1, dir)){
					return true;
				}
			}
			else{return false;}
		}
		if(dir == 7){
			if(grid[r-1][c-1] == letter){
				letterInd++;
				if(foundWord(grid, word, letterInd, r, c+1, dir)){
					return true;
				}
			}
			else{return false;}
		}
	}
}

vector<vector<string> > placeWord(vector<vector<string> > grid, string word, int r, int c, int dir){
	if(dir == 0){
		for(int i = 0; i < word.length(); i++){
			grid[r][c+i] = word.substr(i, 1);
		}
	}
	if(dir == 1){
		for(int i = 0; i < word.length(); i++){
			grid[r][c-i] = word.substr(i, 1);
		}
	}
	if(dir == 2){
		for(int i = 0; i < word.length(); i++){
			grid[r+1][c] = word.substr(i, 1);
		}
	}
	if(dir == 3){
		for(int i = 0; i < word.length(); i++){
			grid[r-1][c] = word.substr(i, 1);
		}
	}
	if(dir == 4){
		for(int i = 0; i < word.length(); i++){
			grid[r+i][c+i] = word.substr(i, 1);
		}
	}
	if(dir == 5){
		for(int i = 0; i < word.length(); i++){
			grid[r+i][c-i] = word.substr(i, 1);
		}
	}
	if(dir == 6){
		for(int i = 0; i < word.length(); i++){
			grid[r-i][c+i] = word.substr(i, 1);
		}
	}
	if(dir == 7){
		for(int i = 0; i < word.length(); i++){
			grid[r-i][c-i] = word.substr(i, 1);
		}
	}
	return grid;
}

void allSolutions(vector<vector<vector<string> > >& solutionList, vector<vector<string> > grid, vector<string> wordList, int wordIndex){
	if(wordIndex = wordList.size()){
		solutionList.push_back(grid);
		return;
	}
	string word = wordList[wordIndex];
	int len = word.length();
	int width = grid.size();
	int height = grid.size();
	if(len > width && len > height){ //Check if the word is too large for this grid
		cerr << "The word " << word << " does not fit within this grid." << endl;
		exit(1);
		return;
	}
	for(int i = 0; i < grid.size(); i++){
		for(int j = 0; j < grid[0].size(); j++){
			//Check for just left to right
			if((width - j) >= len){
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i][j+k] == " " || grid[i][j+k] == word.substr(k, 1))){
						good = false;
						break; //If there isn't either an open space or a letter that matches the matching index of the word, break out
					}
				}
				if(good){
					allSolutions(solutionList, placeWord(grid, word, i, j, 0), wordList, wordIndex+1);
				}
			}
			if(j + 1 > len){ //Checking backwards from this spot
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i][j-k] == " " || grid[i][j-k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					allSolutions(solutionList, placeWord(grid, word, i, j, 1), wordList, wordIndex+1);
				}
			}
			if((height - i) >= len){ //Downwards
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i+k][j] == " " || grid[i+k][j] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					allSolutions(solutionList, placeWord(grid, word, i, j, 2), wordList, wordIndex+1);
				}
			}
			if(i+1 >= len){ //Upwards
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i-k][j] == " " || grid[i-k][j] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					allSolutions(solutionList, placeWord(grid, word, i, j, 3), wordList, wordIndex+1);
				}
			}
			if((width - j) >= len && (height - i) >= len){ //Down and to the right diagonally
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i+k][j+k] == " " || grid[i+k][j+k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					allSolutions(solutionList, placeWord(grid, word, i, j, 4), wordList, wordIndex+1);
				}
			}
			if((j+1) >= len && (height - i) >= len){ //Down and to the left diagonally
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i+k][j-k] == " " || grid[i+k][j-k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					allSolutions(solutionList, placeWord(grid, word, i, j, 5), wordList, wordIndex+1);
				}
			}
			if((width - j) >= len && (i+1) >= len){ //Up and to the right diagonally
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i-k][j+k] == " " || grid[i-k][j+k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					allSolutions(solutionList, placeWord(grid, word, i, j, 6), wordList, wordIndex+1);
				}
			}
			if((j+1) >= len && (i+1) >= len){ //Up and to the left diagonally
				bool good = true;
				for(int k = 0; k < len; k++){
					if(!(grid[i-k][j-k] == " " || grid[i-k][j-k] == word.substr(k, 1))){
						good = false;
						break;
					}
				}
				if(good){
					allSolutions(solutionList, placeWord(grid, word, i, j, 7), wordList, wordIndex+1);
				}
			}
		}
	}
}

void clearBadSolutions(vector<vector<vector<string> > > answers, vector<string> bannedWords){

}

int main(int argc, char* argv[]){
	if(argc != 4){
		cerr << "Error: Incorrect argument length" << endl;
		exit(1);
	}
	ifstream fileIn(argv[1]);
	if(!fileIn.good()){
		cerr << "Can't open " << argv[1] << "to read." << endl;
		exit(1);
	}
	int width;
	int height;
	fileIn >> width >> height;
	vector<string> words;
	vector<string> bannedWords;
	string read;
	while(fileIn >> read){
		if(read == "+"){
			fileIn >> read;
			words.push_back(read);
		}
		else if(read == "-"){
			fileIn >> read;
			bannedWords.push_back(read);
		}
	}
	ofstream fileOut;
	fileOut.open(argv[2]);


	return 0;
}




