/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * roboHockey
 * Copyright (C) Emil Brissman 2010 <>
 * 
 * roboHockey is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * roboHockey is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <cmath>
//#include <iostream>

namespace Math
{
	
template<class T> 	
class Vector2D 
{ 

	public:
		
        // Data members
        T x;
        T y;
 
        //Konstruktor
        Vector2D() : x(0), y(0) {}
        Vector2D(T _x, T _y) : x(_x), y(_y) {}
        
        // Member functions
        
        // Vector norm
        inline double norm() { return sqrt(x*x+y*y); }
		inline double squareNorm() { return x*x+y*y; }
        
        // Operators
        
        inline Vector2D operator+ (const Vector2D& v) const { return Vector2D(x+v.x,y+v.y); }

        inline const Vector2D& operator+= (const Vector2D& v) { x+=v.x; y+=v.y; return *this; }
        
        inline Vector2D operator- (const Vector2D& v) { return Vector2D(x-v.x,y-v.y); } 
        
        inline Vector2D operator+(double num) const { return Vector2D(x+num,y+num); }
        
        inline Vector2D operator-(double num) const { return Vector2D(x-num,y-num); }

		// Unary minus
		friend inline Vector2D<T> operator-(Vector2D& v) { return Vector2D(-v.x, -v.y); }
        
        // Dot product
        inline double operator*(const Vector2D& v) const { return x*v.x+y*v.y; }
	
		// Scaling
		inline Vector2D operator/(double num) const { return Vector2D(x*(1/num),y*(1/num)); }
		friend inline Vector2D operator/(const double num, const Vector2D& v){ return Vector2D(v.x*(1/num),v.y*(1/num)); }
        
        inline Vector2D operator*(double num) const { return Vector2D(x*num,y*num); }
		friend inline Vector2D operator*(const double num, const Vector2D& v) { return Vector2D(v.x*num,v.y*num); }
        
        // Smaller than or equal for both x and y.
        bool operator<=(const Vector2D& v) const;
		bool operator>(const Vector2D& v) const;
        
        // V1 == V2?
        bool operator==(const Vector2D& v) const;
           
        // V1 = V2, assignment
        const Vector2D& operator=(const Vector2D&);
        
        /*// Printing
        friend std::ostream& operator<<(std::ostream &os, const Vector2D<T> &v);*/

};

// V1 = V2, assignment
template<class T>
const Vector2D<T>& Vector2D<T>::operator=(const Vector2D &v) 
{
	// Check self assignment
	if (&v != this)
	{
		x = v.x;
		y = v.y;
	}
	
	return *this;
}

// V1 == V2?
template<class T>
bool Vector2D<T>::operator==(const Vector2D& v) const
{
	if(x == v.x && y == v.y)
		return true;
	else
		return false;  
}

// Less or equal for both x and y
template<class T>
bool Vector2D<T>::operator<=(const Vector2D& v) const
{
	if(x<=v.x && y<=v.y)
		return true;
	else
		return false;
}

template<class T>
bool Vector2D<T>::operator>(const Vector2D& v) const
{
	if(x>v.x && y>v.y)
		return true;
	else
		return false;
}

/*template<class T>
std::ostream& operator<<(std::ostream &os,const Vector2D<T> &v)
{
	// Print the vector in format (x,y)
	os << "(" << v.x << "," << v.y << ")";

	return os;
}*/


} // Namespace Math
#endif // _VECTOR2D_H_
