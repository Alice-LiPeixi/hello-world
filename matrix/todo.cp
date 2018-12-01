/*
 * todo.cpp
 *
 *  Created on: Oct 31, 2018
 *      Author: kevinw
 */
#include "matrix.h"

/**
 * Important Notes:
 *
 * 1) All the code that you have written should be in this file.
 * 2) You can add any helper functions. And we suggest you to do it.
 * 3) Global varibles are not allowed, regardless of whether it is const or non const.
 * 4) Two class member functions, namely, print and debug, have been written for you in helper.cpp
 *    and you should not move these two function here, nor reimplement it.
 * 5) You can modify the main function for testing purpose. However, you should also
 *    expect that we will modify the main function when we grade your assignment.
 *
 *
 * If it crashes, take a deep breath.
 *
 */


/*
 * TODO: Constructor of the Matrix class
 * Hint: 1) Remember to initial all data members; if you don't know what values to be used, put nullptr or 0 first.
 *       2) You need to create dynamic Element objects in the constructor. As mentioned in the .h file,
 *          you need to create it using the syntax:
 *              Element* dynamicObject = new Element{nullptr, nullptr, nullptr, nullptr, id};
 *       3) You are advised to create some helper global functions to help you to do this task.
 */

  Matrix::Matrix(int height, int width) {

    this->height = height;
    this->width = width;

    Element* ups[width];
    for (int i = 0; i < width; i++) {
      ups[i] = nullptr;
    }    

    // init and do left & right
    for (int i = 0; i < height; i++ ) {

      Element* last = nullptr;

      for (int j = 0; j < width; j++ ) {
        // Element* current = new Element{nullptr, nullptr, nullptr, nullptr, i * width + j + 1};
        Element* current = new Element{nullptr, nullptr, nullptr, nullptr, (height - i) * width - j};

        if (i == 0) { // row = 0
          colHeads[j] = current;
        }

        if (j == 0) { // col = 0
          rowHeads[i] = current;
        }

        if (last != nullptr) { // gives right&left pointer
          last->right = current;
          current->left = last;
        }

        if (j == width - 1) { // last node in a row
          current->right = rowHeads[i];
          rowHeads[i]->left = current;
        }     

        last = current;

        if (ups[j] != nullptr) { // up & down pointer
          ups[j]->down = current;
          current->up = ups[j];
        }
        if (i == height - 1) { // last row in a col
          current->down = colHeads[j];
          colHeads[j]->up = current;
        }

        ups[j] = current;
      }
    }    

  }

/*
 * TODO: isReverse() of the Matrix class
 * Hint: This should be a easier task, comparing with the others. Try to do it after the constructor is implemented.
 *
 */

  bool Matrix::isReverse() const{
    
    for (int i = 0; i < height; i++ ) {
        Element* current = rowHeads[i];
        for (int j = 0; j < width; j++ ) {
            if (current->id != (height - i) * width - j) {
              cout << "isReverse: false" << endl;
              return false;
            }
            current = current->right;
        }
    }
    cout << "isReverse: true" << endl;
    return true;
  }

  Element* reverseFromNode(Element *current, Element *left) {
    if (current == nullptr) {
      return left;
    }
    Element *right = current->right;
    current->right = left;
    current->left = right;

    return reverseFromNode(right, current);
  }

/*
 * TODO: reverseRow() of the Matrix class
 * Hint: This is not supposed to be simple and easy if you are not using recursion.
 */

  void Matrix::reverseRow(int row) {
    Element *head = rowHeads[row];
    Element *up = head->up;
    Element *down = head->down;

    Element *tail = head->left;
    tail->right = nullptr;
    head->left = nullptr;
    rowHeads[row] = reverseFromNode(head, nullptr);

    rowHeads[row]->left = head;
    head->right = rowHeads[row];

    Element *current = rowHeads[row];
    for (int j = 0; j < width; j++) {
      if (row == 0) {
        colHeads[j] = current;
      }         
      current->up = up;
      up->down = current;
      current->down = down;
      down->up = current;

      current = current->right;
      up = up->right;
      down = down->right; 
    }
    printcolHeads();
  }

/*
 * TODO: circularShift() of the Matrix class
 * Hint: 1) You might first split this function into two parts, UP/DOWN and LEFT/RIGHT.
 * 	 2) Remember to update both horizontal linked list and vertical linked list.
 *
 */

  void Matrix::circularShift(Direction direction, int number) {
    if (direction == LEFT || direction == RIGHT) {
      int row = number;
      Element *current = rowHeads[row];    

      // move row head
      rowHeads[row] = direction == LEFT ? rowHeads[row]->right : rowHeads[row] = rowHeads[row]->left;

      if (row == 0) { // if shift first row, need to change colHeads
        for (int col = 0; col < width; col++) {
          colHeads[col] = direction == LEFT ? colHeads[col]->right : colHeads[col]->left; 
        }
      }     

      // move elements' up&down
      for (int col = 0; col < width; col++) {

        Element *newUp = direction == LEFT ? current->up->left : current->up->right;
        Element *newDown = direction == LEFT ? current->down->left : current->down->right;  

        current->up = newUp;
        newUp->down = current;

        current->down = newDown;
        newDown->up = current;

        current = current->right; // go to next node in a row
      }
    }
    if (direction == UP || direction == DOWN) {
      int col = number;
      Element *current = colHeads[col];

      if (col == 0) { 
        for (int row = 0; row < height; row++) {
          rowHeads[row] = direction == UP ? rowHeads[row]->down : rowHeads[row]->up; 
        }
      }         

      for (int row = 0; row < height; row++) {

        Element *newLeft = direction == UP ? current->left->up : current->left->down; 
        Element *newRight = direction == UP ? current->right->up : current->right->down; 

        current->left = newLeft;
        newLeft->right = current;

        current->right = newRight;
        newRight->left = current;

        current = current->down;
      }
    }    
    printcolHeads();
  }


/*
 * TODO: Destructor of the Matrix class
 * Hint: 1) Leave this task to the very end of your assignment. The worst case is you don't pick up the
 * 	    memory leak point. Fail to do this will not affect the correctness of your program output.
 * 	    However, if you do it wrongly, your program may crash.
 *
 */

  Matrix::~Matrix() {
    Element* current = nullptr;
    for (int i = 0; i < height; i++) {
      current = rowHeads[i];
      for (int j = 0; j < width; j++) {
        Element* del = current;
        current = current->right;
        delete del;
      }
    }
  }

