//***************************************************************************//
// Utility Classes Interfaces
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2010 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//
// Usage of HabuGraphics is subject to the appropriate license agreement.
// A proprietary/commercial licenses are available.
//                 
// HabuGraphics is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HabuGraphics is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HabuGraphics.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

#ifndef HABU_GRAPHICS_UTILITY_HPP
#define HABU_GRAPHICS_UTILITY_HPP

//***************************************************************************//
// System Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <fstream>
#include <sstream>
#include <string>
//***************************************************************************//

//***************************************************************************//
// BlueHabu Technologies Includes
#include <HabuMath.hpp>
//***************************************************************************//

//***************************************************************************//
// Local Includes
//#include "HabuGraphics.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  template <class T>
  class Color
  {
  private:
    //***********************************************************************//
    /// This data member stores information about the current color
    T mfColors[4];
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    /// Constructor sets all the colors to zero or black
    Color() { memset(this->mfColors, 0UL, 4 * sizeof(T)); }
    Color(T fAlpha, T fRed, T fGreen, T fBlue) 
    { mfColors[3] = fAlpha; mfColors[0] = fRed; mfColors[1] = fGreen; mfColors[2] = fBlue; }
    /// Destructor does nothing
    ~Color() {}
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// These methods return the value of the color
    T A() const { return this->mfColors[3]; }
    T R() const { return this->mfColors[0]; }
    T G() const { return this->mfColors[1]; }
    T B() const { return this->mfColors[2]; }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// These methods set the value of the color
    void A(T fAlpha) { this->mfColors[3] = fAlpha; }
    void R(T fRed)   { this->mfColors[0] = fRed; }
    void G(T fGreen) { this->mfColors[1] = fGreen; }
    void B(T fBlue)  { this->mfColors[2] = fBlue;}
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    T* Array() { return this->mfColors; }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Overloaded '=" operator so assignment of one color to another can be managed
    /// Current this method does nothing more than the non-overloaded '=' operator
    class Color& operator=(const class Color& rhs)
    {
      //---------------------------------------------------------------------//
      memcpy(this->mfColors, rhs.mfColors, 4 * sizeof(T));
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      return *this; // return address of data just copied
      //---------------------------------------------------------------------//
    } // End of class Color& operator=(const class Color& rhs)
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Color
  //*************************************************************************//

  //*************************************************************************//
  class Vertex
  {
  private:
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // TODO Vertex() {mfaNormal[0] = 0.0F; mfaNormal[1] = 0.0F; mfaNormal[2] = 0.0F;}
    Vertex() { mPosition[0] = 0.0F; mPosition[1] = 0.0F; mPosition[2] = 0.0F; 
    mNormal[0] = 0.0F; mNormal[1] = 0.0F; mNormal[2] = 0.0F; }
    Vertex(float fX, float fY, float fZ) {mPosition[0] = fX; mPosition[1] = fY; mPosition[2] = fZ;
    mNormal[0] = 0.0F; mNormal[1] = 0.0F; mNormal[2] = 0.0F; }
    ~Vertex() {} 
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    HabuTech::Point <float, 3>  mPosition;
    HabuTech::Vector<float, 3>  mNormal;
    Color<float> mColor;
    float mTextureUV[2];
    //-----------------------------------------------------------------------//

    static void DeclareVertex()
    {
      #define BUFFER_OFFSET(i) ((char *)NULL + (i))

      glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
      glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
      glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));
      glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(40));
    }
  }; // End of class Vertex
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_UTILITY_HPP
