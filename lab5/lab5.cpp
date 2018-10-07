/*
 * Lab 5 Skeleton

This lab implements a classic two-player battleship game. It helps you to practice the use of 2D array data structure and function, and you must use them in your code. You may download the demo program for Windows (updated) to try it out.

The game runs as follows:

1.Game board is 10 x 10

2.Each player has a fleet of 5 battle ships: Carrier, Battleship, Destroyer, Submarine and Patrol boat. The sizes of the ships follow the popular Hasbro version (as described in the pdf BattleShip_(2002).PDF).

3.Lab 5 modifies the original battle ship game as a single player game. Computer places all ships at the beginning of the game, one-by-one
(1)Pick a random position in game board
(2)Pick a random direction for the ship (either horizontal or vertical)
(3)Put the ship

Each boat should be put in a valid location, e.g. within the boundary of the game board, not overlapping with other ships. Fig 4 of BattleShip_(2002).PDF gives an example of valid boat arrangement on the board.

4.Once ships are set, it's hidden from the player. The player starts to shot. For each shot, player knows whether it's a HIT or MISS. This may give player hint on next shot.
5.Game continues until the player sinks all ships. Count how many shots the player uses.

The game runs in either DEBUG or GAME mode. Debug mode shows the ships to player (actually the programmer) for easy debugging. Game mode hides the ships and presents an intuitive visualization of the board.
TASKS
You can start with the given skeleton code. Read it carefully to understand the data structures (i.e. array) and general program structure. Implement the below 3 functions:

void placeShip(char map[][WIDTH], int size);    // for item 3 as described above
bool isHit(char map[][WIDTH], int col, int row); // for item 4
bool isGameOver(const char map[][WIDTH]);   // for item 5

More details of the functions can be found in skeleton code.

NOTE:
Your game output does not necessarily to be exactly the same as sample program. Make the interface simple, clear, and fun that even a primary student can understand the game instructions.
You can start from scratch (without using skeleton code) if you feel capable to do so.
 *
 */

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;
const char SHIP = 'U';
const char HIT = '*';
const char EMPTY = '.';
const char MISS = 'x';

//This function is to print the map. The first parameter is a 2D array that represents the
//map. The second parameter check if it is in the debug mode.
void printMap(const char map[][WIDTH], bool debug = true) {
  cout << " ";
  for (int i = 0; i < WIDTH; i++) {
    cout << " " << i ;
  }
  cout << endl;

  for (int i = 0; i < HEIGHT; i++) {
    cout << i << " ";

    for (int j = 0; j < WIDTH; j++) {
      if (!debug && map[i][j] == SHIP)
        cout << EMPTY << " ";
      else
        cout << map[i][j] << " ";
      }
    cout << endl;
  }
}

// Place a ship of a particular size on the map.
// Make sure that the battle ships cannot overlap with each other, nor can
// they be placed out of the game board.
// You need to randomly place them on the board.
// You can always assume the map has enough room to place the battle ship when the function is being called.
void placeShip(char map[][WIDTH], int size) {
    //add your code here
  int x = 0, y = 0;
  int pos = rand() % (2);
  x = rand() % (10);
  y = rand() % (10);

  x = 7;
  y = 8;
  pos = 1;

  cout << "x, y, pos, size: " << x << ", " << y << ", " << pos << ", " << size << endl;

  int shipPosition[size][2];

  bool hasConfict = false;
  for (int i = 0; i < size; i++) {
    bool singleConflict = true;
    if (pos == 0) {
      if (y + i < WIDTH) {
        if (map[x][y + i] != SHIP) {
          // map[x][y + i] = SHIP;
          shipPosition[i][0] = x;
          shipPosition[i][1] = y + i;
          singleConflict = false;
        }
      }
    } else {
      if (x + i < HEIGHT) {
        if (map[x][y + i] != SHIP) {
          // map[x + i][y] = SHIP;
          shipPosition[i][0] = x + i;
          shipPosition[i][1] = y;
          singleConflict = false;
        }
      }
    }
    hasConfict = hasConfict && !singleConflict;
  }

  cout << "hasConfict: " << hasConfict << endl;

  if (!hasConfict) {
    for (int i = 0; i < size; i++) {
      map[shipPosition[i][0]][shipPosition[i][1]] = SHIP;
    }
  }

  cout << "end...." << endl;
}


// To check if a cannon hits a battleship.
// Put the correct symbol on the map and return true if  a ship is hit.
// Note: repeated firing on the hit area of an already damaged ship is
// considered as a miss and the symbol for the area should remain '*'.
bool isHit(char map[][WIDTH], int col, int row) {
    //add your code here
}


// It checks if the game ends. It returns true if there is no more SHIP symbol on the map.
// It returns false otherwise.
bool isGameOver(const char map[][WIDTH]) {
    //add your code here
}


int main() {
    srand(time(NULL));

    char map[HEIGHT][WIDTH];
    for (int row = 0; row < HEIGHT; row++)
      for (int col = 0; col < WIDTH; col++)
          map[row][col] = EMPTY;

    placeShip(map, 5);
    // placeShip(map, 4);
    // placeShip(map, 3);
    // placeShip(map, 3);
    // placeShip(map, 2);

    int fire_count = 0;

    char input;
    cout << "Are you playing in the debug/demo mode? (Y for yes; no Otherwise)" << endl;
    // cin >> input;
    input = 'Y';
    bool debug = (input == 'Y');


    while (!isGameOver(map)) {
      printMap(map, debug);

      int col, row;
      cout << "\nPlease enter your col and row separated by a space: ";
      cin >> col >> row;

      if (col < 0 || col >= WIDTH || row < 0 || row >= HEIGHT) {
          cout << "Invalid coordinate, please enter again." << endl;
          continue;
      }

      if (isHit(map, col, row))
          cout << "It is a hit! " << endl << endl;
      else
          cout << "It is a miss :( " << endl << endl;

      fire_count++;
    }

    cout << "Game over. You have fire " << fire_count
         << " cannons to destroy your enemy battleships." << endl;

    if (fire_count == 17)
      cout << "Super! You make the impossible possible!" << endl;
        else if (fire_count < 40)
      cout << "Brilliant!" << endl;
        else if (fire_count < 70)
      cout << "Good shot!" << endl;
        else
      cout << "Improve your skill next time!" << endl;

    printMap(map);
  }