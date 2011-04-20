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

#ifndef HABU_MATH_FIBONACCI_HPP
#define HABU_MATH_FIBONACCI_HPP

#include <iostream>

namespace HabuTech
{
  class Fibonacci
  {
  private:
  public:
    Fibonacci();
    ~Fibonacci();

    static void* Generate(void* ulEnd/*, std::ostream& ostmOutput, char cSeperator = ' '*/);
  };
}

#endif HABU_MATH_FIBONACCI_HPP