//***************************************************************************//
// Event Class Interface
//
// Created: Oct 22, 2007
// By: Jeremy M Miller (info@bluehabu.com)
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

#ifndef HABU_THREADS_EVENT_HPP
#define HABU_THREADS_EVENT_HPP

//***************************************************************************//
// System Includes
#include <limits.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Sync.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  /// \brief The Event class provides the ability to use signals to trigger 
  /// a notification in waiting thread about events happening in other threads. 
  class Event : public Sync
  {
  private:
  public:
    //***********************************************************************//
    Event();
    ~Event();

    /// This method will signal to any waiting thread.
    /// \return 
    /// This method will return true if the signal was successfully sent.
    /// Otherwise, this method will return false.
    bool _cdecl Signal();
    /// This method will reset event so that it can be signaled again.
    /// \return 
    /// This method will return true if the event was successfully reset.
    /// Otherwise, the method will return false.
    bool _cdecl Reset();
    /// This method will block while waiting for a signal to occur on an Event
    /// instance. 
    /// \param [in] ulWait
    /// This parameter will inform the method how long it should wait while 
    /// waiting for the Event to signaled. This parameters units are in 
    /// milliseconds.
    /// \return
    /// This method will return true of method successfully detected a signal 
    /// on the Event. Otherwise, if the wait time has expired before any signal 
    /// was detected, this method will return false.
    bool _cdecl WaitForSignal(unsigned long ulWait = ULONG_MAX);
    //***********************************************************************//
  }; // End of class Event
  //*************************************************************************//
} // End of namespace HabuThread
//***************************************************************************//

#endif HABU_THREADS_EVENT_HPP