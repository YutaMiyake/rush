/**
@file rush.cpp
@author Yuta Miyake
@brief This program finds the minimal solution for the given rush game input
@details
       Given a set of vehicle data, this program solves the problem.
       This program uses Breadth-first search algorithm (level order traversal).
       A map called "dejavu" holds boards that you have seen before by using
       the unique hash key calculated from an arrangement of each vehicle as
       both key and value. Current board is always contained in the 2D global
       array global. Additionally, a queue is used for containing boards,
       represented by string class, to be checked. Each iteration, single level
       is checked. Also this program uses a vehicle class to update the all vehicles' data.
@date 10/2 2015
*/
// Header files ///////////////////////////////////////////////////
#include <queue>
#include <stack>
#include <map>
#include <string>
#include "vehicle.h"
#include "Timer.h"
#include <iostream>
using namespace std;

// global constant /////////////////////////////////////////////////
#define MAX_ROW 6
#define MAX_COL 6
const int MAX_MOVES = 60;

// global variable /////////////////////////////////////////////////
int bestMoves;
int ** board;
map<unsigned int,unsigned int> dejavu;
stack<int> solution;
stack<int> bestSolution;
vehicle* vehicles;
int numVehicles;

// function prototypes ////////////////////////////////////////
bool solve_It(int numMoves, queue<string> q);
bool forward(int n);
bool backward(int n);
void displayBoard(int ** temp);
bool isSolved(int num);
unsigned int hash_func(int ** bd);
void board2str(string& str, int ** bd);
void str2board(const string &str, int ** bd);
void updateCars();

// main driver  /////////////////////////////////////////////////
int main(int argc, char** argv){

  // declarations and initializations
  vehicle * temp;
  int numScenario = 0;
  int type,row,col;
  char direction;
  int i,j;
  queue<string> queue;

  int idx;
  string option;
  bool m_solution = false;
  bool m_timer = false;

  // command line arguments
  if(argc >= 2){
    for(idx = 1; idx < argc; idx++){
      option = argv[idx];
      if(option == "-s"){
        m_solution = true;
      }else if(option == "-t"){
        m_timer = true;
      }else{
        cout << "Unknown option: " << option << endl;
        return -1;
      }
    }
  }

  // allocate board
  board = new int* [MAX_ROW];
  for(i = 0; i < MAX_ROW; i++){
    board[i] = new int [MAX_COL];
  }

  cin >> numVehicles;

  // start rush solver --------------
  while(numVehicles!= 0){
    numScenario++;

      // init board
      for(i = 0; i < MAX_ROW; i++){
        for(j = 0; j < MAX_COL; j++){
          board[i][j] = -1;
        }
      }

      // read in vehicles
      vehicles = new vehicle [numVehicles];
      for(i = 0; i< numVehicles; i++){
        cin >> type >> direction >> row >> col;
        temp = new vehicle(type,direction,row,col);
        vehicles[i] = *temp;

        // place vehicles onto the board
        if(direction == 'H'){
          for(j = 0; j < type; j++){
            board[row][col+j] = i;
          }
        }else{
          for(j = 0; j < type; j++)
            board[row+j][col] = i;
        }
      }

      // solve it
      Timer t(m_timer);
      t.start();
      if(solve_It(0,queue)){
        cout << "Scenario "<< numScenario << " requires "
             << bestMoves << " moves" << endl;
      }
      t.stop();
      if(m_timer){
        cout << "Time: " << t.getElapsedTime() << endl;
      }

      // clear all records
      dejavu.clear();

       // get the next scenario
      cin >> numVehicles;

  } // end rush solver -------------

  return 0;
}

// function implementation /////////////////////////////////////////
bool solve_It(int numMoves, queue<string> queue){
  string str;
  int i,j,size,hash;

  // initializations
  hash = hash_func(board);
  board2str(str,board);
  queue.push(str);
  dejavu[hash] = hash;

  // loop till the queue becomes empty
  while(!queue.empty()){
    size = queue.size();

    // loop through boards in a single level
    for(i = 0; i < size; i++){
      // pop out
      str = queue.front();
      queue.pop();

      // convertion from string to board
      str2board(str,board);

      // update car's positions
      updateCars();

      // if the game is solved, return true
      if(isSolved(numMoves)){
        return true;
      }

      // loop through all vehicles
      for(j = 0; j < numVehicles; j++){
        // take a backward if it's possible
          if(backward(j)){
            hash = hash_func(board);

            // if the board is not found, push it
            if(dejavu.find(hash) == dejavu.end()){
              board2str(str,board);
              dejavu[hash]= hash;
              queue.push(str);
            }
            forward(j);   // undo
          }
          // take a forward if it's possible
          if(forward(j)){
            hash = hash_func(board);

            // if the board is not found, push it
            if(dejavu.find(hash) == dejavu.end()){
              board2str(str,board);
              dejavu[hash]= hash;
              queue.push(str);
            }
            backward(j);    // undo
          }
      }
    }
    numMoves++;  // increment moves

    // if the number of hmoves exceed the max, stop the loop and return false
    if(numMoves > MAX_MOVES){
      return false;
    }
  }
  return false;
}

bool forward(int n){
  int r, c, t;
  r = vehicles[n].row;
  c = vehicles[n].col;
  t = vehicles[n].type;

  // if the car direction is horizontal
  if(vehicles[n].dir == 'H' ){
    // check bounders and othe vehicles ahead
    // if not update the board and the car's info
    if(c+t >= MAX_COL){
      return false;
    }
    else{
      if(board[r][c+t] != -1 ){
        return false;
      }else{
        board[r][c] = -1;
      }
        board[r][c+t] = n;
        ++vehicles[n];
      return true;
    }
  }
  // if the car direction is vertical
  else{
      // check bounders and othe vehicles ahead
      // if not update the board and the car's info
      if(r+t >= MAX_ROW)
        return false;
      else
      {
        if(board[r+t][c] != -1 ){
          return false;
        }else{
          board[r][c] = -1;
        }
          board[r+t][c] = n;
          ++vehicles[n];
        return true;
      }
  }
}
bool backward(int n){
  int r, c, t;
  r = vehicles[n].row;
  c = vehicles[n].col;
  t = vehicles[n].type;

  // if the car direction is horizontal
  if(vehicles[n].dir == 'H' ){
    // check bounders and othe vehicles ahead
    // if not update the board and the car's info
    if(c-1 < 0){
      return false;
    }
    else{
      if(board[r][c-1] != -1){
        return false;
      }
      else{
        board[r][c+t-1] = -1;
      }
        board[r][c-1] = n;
        --vehicles[n];
      return true;
    }
  }
  // if the car direction is vertical
  else{
      // check bounders and othe vehicles ahead
      // if not update the board and the car's info
      if(r-1 < 0 ){
        return false;
      }
      else{
        if(board[r-1][c] != -1 ){
          return false;
        }
        else{
          board[r+t-1][c] = -1;
        }
          board[r-1][c] = n;
          --vehicles[n];
        return true;
      }
  }

}
void displayBoard(int ** temp){
  // display a given board in the form of 6x6 matrix
    for(int x = 0; x < MAX_ROW; x++){
        for(int y = 0; y< MAX_COL; y++){
            cout << temp[x][y] << " ";
  }
  cout << endl;
     }
     cout << endl;
}
bool isSolved(int num){
  // if your car reaches the most right column
    if(vehicles[0].col + (vehicles[0].type -1) == 5)
    {
      // update the bestmove based on the current # of moves and return true
      bestMoves = num;
      return true;
    }
    // otherwise false
    return false;
}
unsigned int hash_func(int ** bd){
  // return an unique hash index given a board
  unsigned int hash = 1;
  for(int i = 0; i < MAX_ROW; i++)
    for(int j = 0; j < MAX_COL; j++)
      hash+= i*j+3 * bd[i][j] + (hash << 1);
  return hash;
}
void board2str(string& str, int ** bd){
  // clear string
  str.clear();

  // convert a board to a string
  // by looping through each cell of the board
  for(int i = 0; i < MAX_ROW; i++)
    for(int j = 0; j < MAX_COL; j++)
      str.push_back(bd[i][j]+'0');
}
void  str2board(const string &str, int ** bd){
  // convert a string to a board
  // by looping through each cell of the board
  for(int i = 0; i < MAX_ROW; i++)
    for(int j = 0; j < MAX_COL; j++)
      bd[i][j] = str[i*MAX_ROW+j]- '0';
}

void updateCars(){
  // definitions
  int x,i,j;

  // reset cars' positions
  for(j = 0; j < numVehicles; j++)
    vehicles[j].row = -1;

  // update them
  for(i = 0; i < MAX_ROW; i++)
    for(j = 0; j < MAX_COL; j++){
      x = board[i][j];

      // if a point x is not negative one
      // and the position specified by the x
      // is not negative one, update
      if(x != -1){
        if(vehicles[x].row == -1){
          vehicles[x].row = i;
          vehicles[x].col = j;
        }
      }
    }
}
