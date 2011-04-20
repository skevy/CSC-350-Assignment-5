//***************************************************************************//
// Fibonacci Class Implementation
//
// Created: April 14, 2007
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


#include "Fibonacci.hpp"
using namespace std;

namespace HabuTech
{
  Fibonacci::Fibonacci()
  {
  }

  Fibonacci::~Fibonacci()
  {
  }

  //-------------------------------------------------------------------------//
  void* Fibonacci::Generate(void* ulEnd/*, ostream& ostmOutput, char cSeperator*/)
  {
    //register unsigned long ulCurrent = 1;
    //register unsigned long ulaPast[2] = {1, 0};

    //while(ulCurrent < (unsigned long)ulEnd)
    //{
    //  //ostmOutput << ulCurrent << cSeperator;
    //  cout << ulCurrent << " \r\n";
    //  ulCurrent = ulaPast[0] + ulaPast[1];
    //  ulaPast[1] = ulaPast[0];
    //  ulaPast[0] = ulCurrent;
    //}
    return NULL;
  } // End of void Fibonacci::Generate(unsigned long ulStart, unsigned long ulEnd, ostream& ostmOutput, char cSeperator)
  //-------------------------------------------------------------------------//
}