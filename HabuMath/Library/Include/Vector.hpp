//***************************************************************************//
// Vector Class Interface
//
// Created: April 3, 2007
// By: Jeremy M Miller
//
// Copyright (c) 2007 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//
// Usage of HabuMath is subject to the appropriate license agreement.
// A proprietary/commercial licenses are available. (info@bluehabu.com)
//                 
// HabuMath is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HabuMath is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HabuThreads.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

#ifndef HABU_MATH_VECTOR_HPP
#define HABU_MATH_VECTOR_HPP

#include "Point.hpp"

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  template <class T, unsigned char  D> class Matrix;
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char  D>
  class Vector : public Point<T, D>
  {
  private:
  public:
    Vector()  {}
    ~Vector() { Point::~Point(); } // Calling base class's destructor since base 
                                   // class's destructor is not virtual for 
                                   // performance reasons.

    void Cross(const Vector<T, D>& rVector1, const Vector<T, D>& rVector2);
   
    T Dot(const Vector<T,D>& rInput) const;

    T Magnitude() const;
    void Normalize();


    T operator()(unsigned char ucIndex) const
    {
      assert(ucIndex < D);

      if(ucIndex < D)
        return mtaComponent[ucIndex];
      return mtaComponent[D - 1];
    }

    T& operator[](unsigned char ucIndex)
    {
      assert(ucIndex < D);

      if(ucIndex < D)
        return mtaComponent[ucIndex];
      return mtaComponent[D - 1];
    }

    Vector<T,D> operator+(const Vector<T,D>& rhs) const;
    Vector<T,D> operator-(const Vector<T,D>& rhs) const;
    Vector<T,D> operator*(const T& rhs) const
    {

      Vector<T,D> tTempVector;
      for(unsigned char i = 0; i < D; i++)
      {
        tTempVector[i] = mtaComponent[i] * rhs;
      }
      return tTempVector;
    }
    Vector<T,D> operator/(const T& rhs) const
    {
      Vector<T,D> tTempVector;
      for(unsigned char i = 0; i < D; i++)
      {
        tTempVector[i] = mtaComponent[i] / rhs;
      }
      return tTempVector;
    }

    void Transform(Matrix<T,D>& rMatrix);
    void Clear()
    {
      for(unsigned char i = 0; i < D; i++)
      {
        mtaComponent[i] = 0.0;
      }
    }
  }; // End of class Vector
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_MATH_VECTOR_HPP