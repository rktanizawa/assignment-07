/* ----------------------------------------------------------------------------
* Copyright &copy; 2015 Ben Blazak <bblazak@fullerton.edu>
                        Randy Tanizawa <rtanizawa@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <exception>
#include <fstream>
#include <string>

using std::ostream;
using std::istream;

template <typename P, const unsigned int SIZE>
class Point
{
    private:
        P nums[SIZE];
    public:
        Point();
        double distance( const Point & p ) const;
        bool operator>( const Point & p ) const;
        istream &read( istream &in );
        ostream &write( ostream &out) const;
        class Error : public std:: exception
        {
            const char *err;
            public:
                Error(const char *e) : err(e) {}
                const char *what() const noexcept
                {
                    return err;
                }
        };
        class Empty_Stream : public Error
        {
            public:
                Empty_Stream( const char *es = "Empty Stream" ) : Error(es){}
        };
        class Invalid_Input : public Error
        {
            public:
                Invalid_Input( const char *ii = "Invalid Input" ) : Error(ii){}
        };
};


template <typename P, const unsigned int SIZE>
Point<P,SIZE>::Point() : nums{} {};

template <typename P, const unsigned int SIZE>
istream &operator>>( istream &in , Point<P, SIZE> &p );

template <typename P, const unsigned int SIZE>
ostream &operator<<( ostream &out, const Point<P, SIZE> &p);

template <typename P, const unsigned int SIZE>
istream &Point<P,SIZE>::read( istream &in )
{
    P num;
    char p_open;
    char p_close = ')';

    in >> p_open;
    if( !in.good() )
    {
        in.clear();
        throw Empty_Stream();
    }
    if( p_open != '(' )
        throw Invalid_Input();

    for(unsigned int i = 0; i < SIZE; i++)
    {
        in >> num;
        if( !in.good() )
        {
            in.clear();
            throw Invalid_Input("Incompatible type");
        }
        nums[i] = num;

    }

    in >> p_close;
    if( !p_close )
    {
        in.clear();
        throw Invalid_Input();
    }

    return in;
}

template <typename P, const unsigned int SIZE>
ostream &Point<P,SIZE>::write( ostream &out ) const
{
    out << "( ";
    for(unsigned int i = 0; i < SIZE; i++)
        out << nums[i] << " ";
    out << ")";
    return out;
}

template <typename P, const unsigned int SIZE>
double Point<P,SIZE>::distance( const Point & p ) const
{
    double sum = 0;
    for(unsigned int i = 0; i < SIZE; i++)
        sum += std::pow( nums[i] - p.nums[i], 2 );
    return std::sqrt(sum);
}

template <typename P, const unsigned int SIZE>
bool Point<P,SIZE>::operator>( const Point & p ) const
{
    return distance( Point{}) > p.distance(Point{});
}

template <typename P, const unsigned int SIZE>
istream &operator>>( istream &in , Point<P,SIZE> &p )
{
    return p.read(in);
}

template <typename P, const unsigned int SIZE>
ostream &operator<<( ostream &out, const Point<P,SIZE> &p)
{
    return p.write(out);
}


#endif // POINT_H
