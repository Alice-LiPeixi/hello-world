#include "matrix.h"

// A helper function to be used in Matrix member function, debug() : 
// given a pointer to an element, check if it is circular linked list in a particular direction.
bool print_CLL(const Element* list, Direction dir, bool debug = true) {
    const Element* current = list;
    do {
	cout << current->id << " ";
	switch (dir) {
	    case UP:	current = current->up; break;
	    case DOWN:  current = current->down; break;
	    case LEFT:  current = current->left; break;
	    case RIGHT: current = current->right; break;
	}
    } while (current != list && current != nullptr);

    if (debug) {
	if (current == nullptr)
	    cout << "\t\tIt is not circular" << endl;
	else
	    cout << "\t\tIt is circular" << endl;
    }
    return current != nullptr;
}

// Print the matrix object
void Matrix::print() const {
    const Element* current;
    for (int i = 0; i < height; i++) {
    	cout << "|\t";
    	current = rowHeads[i];
    	for (int j = 0; j < width; j++) {
    	    cout << current->id << 
               "(" << "up: " << current->up->id << 
               " down: " << current->down->id << 
               " left: " << current->left->id << 
               " right: " << current->right->id << 
               " \t";
    	    current = current->right;
    	}
    	cout << "|" << endl;
    }
    cout << endl;
}

// Print the matrix object
void Matrix::printcol() const {
    const Element* current;
    for (int i = 0; i < width; i++) {
      cout << "|\t";
      current = colHeads[i];
      for (int j = 0; j < height; j++) {
          cout << current->id << "\t";
          current = current->down;
      }
      cout << "|" << endl;
    }
    cout << endl;
}

void Matrix::printcolHeads() const {
  cout << "colHeads: ";
  for (int i = 0; i < width; i++) {
    cout << " " << colHeads[i]->id;
  }
  cout << endl;

  cout << "rowHeads: ";
  for (int i = 0; i < height; i++) {
    cout << " " << rowHeads[i]->id;
  }
  cout << endl;  
}

// Check the matrix object
void Matrix::debug() const {
    cout << "Traverse right" << endl;
    for (int i = 0; i < height; i++) {
    	cout << "Row " << i << "\t"; 
    	if (!print_CLL(rowHeads[i], RIGHT))
    	    cout << "Row " << i << " is not a circular linked list (right pointer)." << endl;
    }


    cout << "Traverse left" << endl;
    for (int i = 0; i < height; i++) {
	cout << "Row " << i << "\t"; 
	if (!print_CLL(rowHeads[i], LEFT))
	    cout << "Row " << i << " is not a circular linked list (left pointer)." << endl;

    }
    cout << "Traverse down" << endl;
    for (int i = 0; i < width; i++) {
	cout << "Col " << i << "\t"; 
	if (!print_CLL(colHeads[i], DOWN))
	    cout << "Col " << i << " is not a circular linked list (down pointer)." << endl;


    }
    cout << "Traverse up" << endl;
    for (int i = 0; i < width; i++) {
	cout << "Col " << i << "\t"; 
	if (!print_CLL(colHeads[i], UP))
	    cout << "Col " << i << " is not a circular linked list (up pointer)." << endl;

    }
}


