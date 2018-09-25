/****************************
 * COMP 2011 - Fall 2018
 * Lab 3 - Pi Estimation
 ****************************/


#include <iostream>
#include <cstdlib>    // srand, rand
#include <ctime>      // time
#include <cmath>

using namespace std;

/* Generate a random real number between [0, 1)
 * Paramters:
 *    (none)
 * Return value
 *    returns a real number between [0, 1)
 */
double random_number()
{
    double r = ((double) rand() / (RAND_MAX));
    return r;
    // add your code here
    // ** RAND_MAX is a constant defined in the standard library
    //    equal to the maximum value returned by rand **
    
}

/* Returns whether the point is inside the circle
 * ( Assume center is at (0, 0) and radius is 1 )
 *
 * Parameters:
 *    x - the x-coordinates of a point
 *    y - the y-coordinates of a point
 * Return value:
 *    returns true if the point is inside the circle, otherwise returns false
 * Notes: marginal case, if the a point touches the arc, returns either true or false)
 */
bool is_in_circle(double x, double y)
{
    x=random_number();
    y=random_number();
    double dis;
    dis = sqrt(x*x + y*y);
    return dis <= 1;
    // add your code here
}

/* Estimate the value of pi and find the number of raindrops inside the circle
 *
 * Parameters:
 *    n - the number of raindrops
 *    num_inside - the number of raindrops inside the circle
 *    pi - the estimated value of pi
 */
void estimate_pi(int n, int& num_inside, double& pi)
{
    double x=0.0,y = 0.0;
    
    for (int m = 0 ; m<=n ; m+=1)
    {
        if (is_in_circle(x,y))
            num_inside+=1;
    }
    pi = 4.0 * num_inside/n;
    
    // add your code here
    // **your code must call the two functions: random_number and is_in_circle**
}

int main()
{
    cout << " __    ___   _      ___  ___   ___   _   _" << endl;
    cout << "/ /`  / / \\ | |\\/| | |_)  ) ) / / \\ / | / |" << endl;
    cout << "\\_\\_, \\_\\_/ |_|  | |_|   /_/_ \\_\\_/ |_| |_|" << endl;
    cout << " ____  __  _____  _   _       __   _____  ____      ___   _ " << endl;
    cout << "| |_  ( (`  | |  | | | |\\/|  / /\\   | |  | |_      | |_) | |" << endl;
    cout << "|_|__ _)_)  |_|  |_| |_|  | /_/--\\  |_|  |_|__     |_|   |_|" << endl;
    
    cout << endl;
    cout << "Imagine ..." << endl;
    cout << "there are raindrops falling on a square with an inscribed circle ..." << endl;
    cout << endl;
    
    // initialize random seed
    srand(time(NULL));
    
    // **you cannot declare other variables except the following three**
    int n = 0, num_inside = 0;
    double pi = 0;
    
    cout << "How many raindrops are there inside the square?" <<endl;
    cout << "Enter the number (n > 0) (enter 0 to exit):";
    cin >> n;
    estimate_pi(n,num_inside,pi);
    if (n == 0)
        cout << "Bye Bye!";
    
    else cout << "The number of raindrops inside the circle =" << num_inside << endl;
    cout << "The estimated pi =" << pi;
    // add your code here
    // ** your code must call the function estimate_pi() **
    
    
    return 0;
}
