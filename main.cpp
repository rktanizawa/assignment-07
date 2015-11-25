/* ----------------------------------------------------------------------------
* Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>
                        Randy Tanizawa <rtanizawa@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

/**
* Program to read files containing Points of different types and sizes and
* determine which Point is furthest from 0. This program is an exercise
* in templates and exceptions.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "point.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;


template <typename P, const unsigned int SIZE>
void print( const string &file )
{
    ifstream infile(file);
    Point<P,SIZE> p, pmax;

    if(!infile)
        cout << "Error: cannot open file" << endl;

    try{ infile >> pmax; }
    catch(std::exception & e)
    {
        cerr << "Error: unable to read first Point (" << e.what() << " )" << endl;
        cerr << "       source code line: " << __LINE__ << endl;
        cerr << "       read from       : " << file << endl;
        cerr << "       at position     : " << infile.tellg() << endl;
        return;
    }

    for(;;){
    try
    {
        infile >> p;
    }
    catch(typename Point<P,SIZE>::Empty_Stream & e)
    {
        break;
    }
    catch(typename Point<P,SIZE>::Invalid_Input & i)
    {
        cerr << "Error: invalid input ("    << i.what() << ")" << endl;
        cerr << "       source code line: " << __LINE__ << endl;
        cerr << "       read from       : " << file << endl;
        cerr << "       at position     : " << infile.tellg() << endl;
        while(infile.get() != '\n');
    }
    catch(std::exception & e)
    {
        cerr << "Error: unable to recover (" << e.what() << " )" << endl;
        cerr << "       source code line: " << __LINE__ << endl;
        cerr << "       read from       : " << file << endl;
        cerr << "       at position     : " << infile.tellg() << endl;
        return;
    }

    if(p > pmax)
        pmax = p;
    }

    cout << "The Point furthest from " << Point<P,SIZE>() << " in " << file
         << " is: " << pmax << endl;
    cout << "-----------------------" << endl;
}

int main()
{
    print<int, 1>("input-int-1.txt");
    print<int, 2>("input-int-2.txt");
    print<int, 3>("input-int-3-bad.txt");
    print<int, 4>("input-int-4-very-bad.txt");
    print<int, 5>("input-int-5.txt");

    print<double, 2>("input-double-2.txt");
    print<double, 3>("input-double-3.txt");


    return 0;
}
