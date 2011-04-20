//***************************************************************************//
// Matrix Class Implementation
//
// Created: April 6, 2007
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

//***************************************************************************//
// System Includes
#include <math.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Matrix.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // Explicit instantiations
  template class Matrix<float, 2>;
  template class Matrix<float, 3>;
  template class Matrix<float, 4>;
  template class Matrix<double, 2>;
  template class Matrix<double, 3>;
  template class Matrix<double, 4>;
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  T Matrix<T, D>::operator()(unsigned char ucRow, unsigned char ucColumn) const
  {
    return mtMatrix[ucRow](ucColumn);
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  Vector<T, D>& Matrix<T, D>::operator[](unsigned char ucRow)
  {
    return mtMatrix[ucRow];
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  Matrix<T, D> Matrix<T, D>::operator*(const Matrix<T, D>& rhs) const
  {
    Matrix<T, D> tTempMatrix;
    for(unsigned char r = 0; r < D; r++)
    {
      for(unsigned char c = 0; c < D; c++)
      {
        tTempMatrix[r][c]  = this->mtMatrix[r].Dot(rhs.mtMatrix[c]);
      }
    }
    return tTempMatrix;
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  Matrix<T, D> Matrix<T, D>::operator*(const T& rhs) const
  {
    Matrix<T, D> tTempMatrix;
    for(unsigned char r = 0; r < D; r++)
    {
      tTempMatrix[r] = this->mtMatrix[r] * rhs;
    }
    return tTempMatrix;
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  Matrix<T, D> Matrix<T, D>::operator+(const Matrix<T, D>& rhs) const
  {
    Matrix<T, D> tTempMatrix;
    for(unsigned char r = 0; r < D; r++)
    {
      (Point<T,D>)this->mtMatrix[r] = (Point<T,D>)((Vector<T,D>)this->mtMatrix[r] + (Vector<T,D>)rhs.mtMatrix[r]);
    }
    return tTempMatrix;
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  Matrix<T, D> Matrix<T, D>::operator-(const Matrix<T, D>& rhs) const
  {
    Matrix<T, D> tTempMatrix;
    for(unsigned char r = 0; r < D; r++)
    {
      (Point<T,D>)this->mtMatrix[r] = (Point<T,D>)((Vector<T,D>)this->mtMatrix[r] - (Vector<T,D>)rhs.mtMatrix[r]);
    }
    return tTempMatrix;
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  T Matrix<T, D>::Determinate() const
  {
    return 0.0;
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::RotateAboutX(T& rtAngle)
  {
    assert(D >= 3); // Matrix dimensions must be greater than 3 and in 
    // most cases should be 4.
    if(D >= 3)
    {
      T tCosineResult = cos((T)rtAngle);
      T tSineResult   = sin((T)rtAngle);
      Matrix<T, D> oTemp;
#ifdef LEFT_HAND
      oTemp[0][0] =  tCosineResult; 
      oTemp[0][1] =  tSineResult;
      oTemp[1][0] =  -tSineResult;
      oTemp[1][1] =  tCosineResult;
#else
      oTemp[1][1] =  tCosineResult; 
      oTemp[1][2] = -tSineResult;
      oTemp[2][1] =  tSineResult;
      oTemp[2][2] =  tCosineResult;
#endif LEFT_HAND
      *this = *this * oTemp;
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::RotateAboutY(T& rtAngle)
  {
    assert(D >= 3); // Matrix dimensions must be greater than 3 and in 
    // most cases should be 4.
    if(D >= 3)
    {
      T tCosineResult = cos((T)rtAngle);
      T tSineResult   = sin((T)rtAngle);
      Matrix<T, D> oTemp;
#ifdef LEFT_HAND
      oTemp[0][0] =  tCosineResult; 
      oTemp[0][2] = -tSineResult;
      oTemp[2][0] =  tSineResult;
      oTemp[2][2] =  tCosineResult;
#else
      oTemp[0][0] =  tCosineResult; 
      oTemp[0][2] =  tSineResult;
      oTemp[2][0] = -tSineResult;
      oTemp[2][2] =  tCosineResult;
#endif LEFT_HAND
      *this = *this * oTemp;
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::RotateAboutZ(T& rtAngle)
  {
    assert(D >= 3); // Matrix dimensions must be greater than 3 and in 
    // most cases should be 4.
    if(D >= 3)
    {
      T tCosineResult = cos((T)rtAngle);
      T tSineResult   = sin((T)rtAngle);
      Matrix<T, D> oTemp;
#ifdef LEFT_HAND
      oTemp[0][0] =  tCosineResult; 
      oTemp[0][1] =  tSineResult;
      oTemp[1][0] = -tSineResult;
      oTemp[1][1] =  tCosineResult;
#else
      oTemp[0][0] =  tCosineResult; 
      oTemp[0][1] = -tSineResult;
      oTemp[1][0] =  tSineResult;
      oTemp[1][1] =  tCosineResult;
#endif LEFT_HAND
      *this = *this * oTemp;
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::RotateAboutAxis(Vector<T, D>& rtAxis, T& rtAngle)
  {
    assert(D >= 3); // Matrix dimensions must be greater than 3 and in 
    // most cases should be 4.
    if(D >= 3)
    {
      T tCosineResult = cos((T)rtAngle);
      T tSineResult   = sin((T)rtAngle);
      T tOneMinusCosineResult = 1.0 - tCosineResult;

      Matrix<T, D> oTemp;

      // Reference Page 123 from "Essential Mathematics For Games and Interactive Applications" by
      // James M. Van Verth and Lars M. Bishop
#ifdef LEFT_HAND
      oTemp[0][0] = tOneMinusCosineResult * rtAxis.X() * rtAxis.X() + tCosineResult;
      oTemp[0][1] = tOneMinusCosineResult * rtAxis.X() * rtAxis.Y() + tSineResult * rtAxis.Z();
      oTemp[0][2] = -tOneMinusCosineResult * rtAxis.X() * rtAxis.Z() + tSineResult * rtAxis.Y();

      oTemp[1][0] = tOneMinusCosineResult * rtAxis.X() * rtAxis.Y() - tSineResult * rtAxis.Z();
      oTemp[1][1] = tOneMinusCosineResult * rtAxis.Y() * rtAxis.Y() + tCosineResult;
      oTemp[1][2] = -tOneMinusCosineResult * rtAxis.Y() * rtAxis.Z() - tSineResult * rtAxis.X();

      oTemp[2][0] = -tOneMinusCosineResult * rtAxis.X() * rtAxis.Z() - tSineResult * rtAxis.Y();
      oTemp[2][1] = -tOneMinusCosineResult * rtAxis.Y() * rtAxis.Z() + tSineResult * rtAxis.X();
      oTemp[2][2] = tOneMinusCosineResult * rtAxis.Z() * rtAxis.Z() + tCosineResult;
#else
      oTemp[0][0] = tOneMinusCosineResult * rtAxis.X() * rtAxis.X() + tCosineResult;
      oTemp[0][1] = tOneMinusCosineResult * rtAxis.X() * rtAxis.Y() - tSineResult * rtAxis.Z();
      oTemp[0][2] = tOneMinusCosineResult * rtAxis.X() * rtAxis.Z() + tSineResult * rtAxis.Y();

      oTemp[1][0] = tOneMinusCosineResult * rtAxis.X() * rtAxis.Y() + tSineResult * rtAxis.Z();
      oTemp[1][1] = tOneMinusCosineResult * rtAxis.Y() * rtAxis.Y() + tCosineResult;
      oTemp[1][2] = tOneMinusCosineResult * rtAxis.Y() * rtAxis.Z() - tSineResult * rtAxis.X();

      oTemp[2][0] = tOneMinusCosineResult * rtAxis.X() * rtAxis.Z() - tSineResult * rtAxis.Y();
      oTemp[2][1] = tOneMinusCosineResult * rtAxis.Y() * rtAxis.Z() + tSineResult * rtAxis.X();
      oTemp[2][2] = tOneMinusCosineResult * rtAxis.Z() * rtAxis.Z() + tCosineResult;
#endif LEFT_HAND
      *this = *this * oTemp;
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::Translate(T& rtX, T& rtY, T& rtZ)
  {
    assert(D == 4); // Can only translate 4 by 4 matrix when point is 3D
    if(D == 4)
    {
      Matrix<T, D> oTemp;
#ifdef LEFT_HAND
      oTemp[3][0] = rtX;
      oTemp[3][1] = rtY;
      oTemp[3][2] = rtZ;
#else
      oTemp[0][3] = rtX;
      oTemp[1][3] = rtY;
      oTemp[2][3] = rtZ;
#endif LEFT_HAND
      *this = *this * oTemp;
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::Translate(Vector<T, D>& rtVector)
  {
    assert(D == 4); // Can only translate 4 by 4 matrix when point is 3D
    if(D == 4)
    {
      Matrix<T, D> oTemp;
#ifdef LEFT_HAND
      oTemp[3][0] = rtVector.X();
      oTemp[3][1] = rtVector.Y();
      oTemp[3][2] = rtVector.Z();
#else
      oTemp[0][3] = rtVector.X();
      oTemp[1][3] = rtVector.Y();
      oTemp[2][3] = rtVector.Z();
#endif LEFT_HAND
      *this = *this * oTemp;
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::Transpose()
  {
    //for(unsigned char r = 0; r < D; r++)
    //{
    //  for(unsigned char c = 0; c < D; c++)
    //  {


    //  }
    //}
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::Identity()
  {
    this->Zero();
    for(unsigned char d = 0; d < D; d++)
    {
      mtMatrix[d][d] = 1.0F;
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::Zero()
  {
    memset(&(this->mtMatrix), 0L, sizeof(T) * D * D);
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::Perspective(T tVerticalFOV, T tAspect, T tNearClipPlane, T tFarClipPlane)
  {
#ifdef LEFT_HAND
    assert(D == 4); // Matrix dimensions must 4
    if(D == 4)
    {
      this->Zero();
      (*this)(1,1) = 1.0 / tan(tVerticalFOV/2.0F);
      (*this)(0,0) = (*this)(1,1)/ tAspect;
      T tTemp      = tFarClipPlane - tNearClipPlane;
      (*this)(2,2) = tFarClipPlane / tTemp;
      (*this)(2,3) = 1.0;
      (*this)(3,2) = -tNearClipPlane * tFarClipPlane / tTemp;
    }
#endif LEFT_HAND
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::ColumnMajor(T pArray[D * D]) const
  {
    unsigned long ulArrayIndex = 0UL;
    for(unsigned long ulRow = 0UL; ulRow < D; ulRow++)
    {
      for(unsigned long ulColumn = 0UL; ulColumn < D; ulColumn++)
      {
        pArray[ulArrayIndex]  = (*this)(ulColumn, ulRow);
        ulArrayIndex++;
      }
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char D>
  void Matrix<T, D>::RowMajor(T pArray[D * D]) const
  {
    unsigned long ulArrayIndex = 0UL;
    for(unsigned long ulColumn = 0UL; ulColumn < D; ulColumn++)
    {
      for(unsigned long ulRow = 0UL; ulRow < D; ulRow++)
      {
        pArray[ulArrayIndex] = (*this)(ulColumn, ulRow);
        ulArrayIndex++;
      }
    }
  }
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//