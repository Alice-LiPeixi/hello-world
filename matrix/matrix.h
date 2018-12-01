/*
 * matrix.h
 *
 *  Created on: Oct 31, 2018
 *      Author: kevinw
 */


#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

using namespace std;

const int MAX_SIZE = 8;
enum Direction {UP, DOWN, LEFT, RIGHT};


/**
 * Representing an element in a matrix.
 *
 */
struct Element {
    Element* up;    // To link to the element on the same col in the above row. If this element is in the top row (Row-0), it links to the elements on Row-(m-1)
    Element* down;  // Similar to up but it is to link to the element in the row below.
    Element* left;  // To link to the element on the left.
    Element* right; // To link to the element on the right.
    const int id;   // We intentionally to have it as a const so you need to handle the links instead of changing the value.
    // Since this is a const int, when you create a dynamic object Element you need to initialize it with curly brackets, e.g.
    //         Element* dynamicObject = new Element{nullptr, nullptr, nullptr, nullptr, index};
};

class Matrix {
    private:
	int width;      // The width of the matrix
	int height;		// The height of the matrix
	Element* rowHeads[MAX_SIZE];   // Pointer arrays. Please refer to the PA3 webpage
	Element* colHeads[MAX_SIZE];
    public:

	/**
	 * TODO
	 * The constructor of the class. Given the width and height of the matrix, it should construct a height-by-width in-order matrix.
	 * Please refer to the definition of "in-order" in the HTML file.
	 */
	Matrix(int height, int width);
	/**
	 * TODO
	 * You should delete any dynamic memory created in the Matrix.
	 */
	~Matrix();

	/**
	 * TODO
	 * To perform a "reverse row" operation. The parameter indicates the row number that to be reversed.
	 */
	void reverseRow(int);

	// *
	//  * TODO
	//  * To perform a "circular shift" operation.
	//  * The first parameter is of the enum type, Direction. Possible values: RIGHT, LEFT, UP, DOWN
	//  * For example, if it is RIGHT, it means to perform a "right circular shift".
	//  * The second parameter is the row number or the col number for the operation.
	 
	void circularShift(Direction, int);

	/**
	 * TODO
	 * To check if the matrix is in-reverse-order. Returns true if it is, otherwise returns false.
	 */
	bool isReverse() const;



	/**
	 *  This function has been completed for you. It prints a matrix. Do NOT move or copy it into your todo.cpp
	 */
	void print() const;
	void printcol() const;

	void printcolHeads() const;
	/**
	 *  This function has been completed for you. It helps you check the matrix. Do NOT move or copy it into your todo.cpp
	 */
	void debug() const;

};



#endif
