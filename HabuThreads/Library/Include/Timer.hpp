//***************************************************************************//
// Timer Class Interface
//
// Created May 14, 2005
// By: Jeremy M Miller
//
// Version 0.1
// Note: version 0.1 is windows dependent
//
// Copyright (c) 2005 Jeremy M Miller.  
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

#ifndef HABU_THREADS_TIMER_HPP
#define HABU_THREADS_TIMER_HPP

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  /// \brief This enumeration is used to identify individual timers in the 
  /// Timer class.
  enum Timers
  {
    TIMER_1,
    TIMER_2,
    TIMER_3,
    TIMER_4,
    TIMER_5,
    TIMER_6,
    TIMER_7,
    TIMER_8,
    NUMBER_OF_TIMERS
  }; // End of enum Timers
  //*************************************************************************//

  //*************************************************************************//
  /// \brief The Timer class is high resolution timer. It can manage up to 
  /// Timers::NUMBER_OF_TIMERS sets of time.
  class Timer
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // This data member is simply an array of the last tick count for individual
    // timestamps.
    long long mllStartClocks[NUMBER_OF_TIMERS];
    // This data member is calculated when this class is instantiated and used to 
    // convert time in terms of seconds from a tick count.
    double mdInverseClockRate;
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Timer();
    ~Timer();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// This method returns the the amount of time since the last time this 
    /// method was called.
    /// \param [in] eTimer
    /// This parameter is the timer to measure.
    /// \return 
    /// This method returns timer in units of seconds.
    double DT(enum Timers eTimer);
    /// This method returns the the amount of time since the last time the 
    /// DT() method was called.
    /// \param [in] eTimer
    /// This parameter is the timer to measure.
    /// \return 
    /// This method returns timer in units of seconds.
    double ET(enum Timers eTimer);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Timer
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//
#endif HABU_THREADS_TIMER_HPP