//***************************************************************************//
// Timer Implementation
//
// Created May 14, 2005
// By: Jeremy M Miller
//
// Version 0.1
// Note: version 0.1 is Windows (tm) dependent
//
// Copyright (c) 2005-2009 Jeremy M Miller.  
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu Technologies(tm).
//
// Usage of HabuThreads is subject to the appropriate license agreement.
// A proprietary/commercial licenses are available. (info@bluehabu.com)
//                 
// HabuThreads is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HabuThreads is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HabuThreads.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <assert.h>
#ifdef WINDOWS_THREADS
#include <windows.h>
#endif WINDOWS_THREADS
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Timer.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //-------------------------------------------------------------------------//
  Timer::Timer()
  {
    //-----------------------------------------------------------------------//
    long long llClockRate  = 0;
    long long llStartClock = 0;
    mdInverseClockRate     = 0.0;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    QueryPerformanceFrequency((LARGE_INTEGER*)&llClockRate);
    assert(llClockRate);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    mdInverseClockRate = 1.0/(double)llClockRate;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    QueryPerformanceCounter((LARGE_INTEGER*)&llStartClock);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    for(unsigned long i = 0; i < NUMBER_OF_TIMERS; i++)
    {
      mllStartClocks[i] = llStartClock;
    }
    //-----------------------------------------------------------------------//
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Timer::~Timer()
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  double Timer::DT(enum Timers eTimer)
  {
    //-----------------------------------------------------------------------//
    double dResult = 0.0;
    long long llEndClock = 0;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    if(QueryPerformanceCounter((LARGE_INTEGER*)&llEndClock))
    {
      dResult = (llEndClock - mllStartClocks[eTimer])*mdInverseClockRate;
      mllStartClocks[eTimer] = llEndClock;
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    return dResult;
    //-----------------------------------------------------------------------//
  } // End of double Timer::DT(enum Timers eTimer)
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  double Timer::ET(enum Timers eTimer)
  {
    //-----------------------------------------------------------------------//
    double dResult = 0.0;
    long long llEndClock = 0;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    if(QueryPerformanceCounter((LARGE_INTEGER*)&llEndClock))
    {
      dResult = (llEndClock - mllStartClocks[eTimer])*mdInverseClockRate;
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    return dResult;
    //-----------------------------------------------------------------------//
  } // End of double Timer::ET(enum Timers eTimer)
  //-------------------------------------------------------------------------//
} // End of namespace HabuTech
//***************************************************************************//
