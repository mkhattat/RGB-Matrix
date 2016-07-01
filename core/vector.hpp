// ==========================================================================
//
// File      : vector.hpp
// Part of   : led matrix library
// Copyright : mostafa@khattat.nl 2016
//
// led matrix implementation for an Arduino Due (ATSAM3X8E chip)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef VECTOR_HPP
#define VECTOR_HPP

/// Implementation of vector class to store x and y
//
/// This class used by several classes in this library to store
/// x and y or width and height.
class vector {
public:
    int x;
    int y; 
   
   vector(  int x,  int y ): 
      x( x ), y( y )
   {}
   
   vector( const vector & rhs ):
      x( rhs.x ),
      y( rhs.y )
   {}
   
   vector & operator+=( const vector & rhs ){
      x += rhs.x;
      y += rhs.y;
      return *this;
   }
   
   vector operator+( const vector & rhs ) const {
      vector temp = *this;
      temp += rhs;
      return temp;
   }
   
   vector & operator-=( const vector & rhs ){
      x -= rhs.x;
      y -= rhs.y;
      return *this;
   }
   
   vector operator-( const vector & rhs ) const {
      vector temp = *this;
      temp -= rhs;
      return temp;
   }
   
   vector & operator*=(  int n ){
      x *= n;
      y *= n;
      return *this;
   }
   
   vector operator*(  int n ) const {
      vector temp = *this;
      temp *= n;
      return temp;
   }
};

#endif // VECTOR_HPP