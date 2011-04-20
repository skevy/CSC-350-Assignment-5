//***************************************************************************//
// Event Class Implementation
//
// Created: Oct 22, 2006
// By: Jeremy M Miller (info@bluehabu.com)
//
// Copyright (c) 2007  Jeremy M Miller.  
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
#include "Event.hpp"
//***************************************************************************//

//***************************************************************************//
#include <assert.h>
//***************************************************************************//

//***************************************************************************//
#ifdef WINDOWS_THREADS
#include <windows.h>
#endif 
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{

  //*************************************************************************//
  Event::Event()
  {
#ifdef WINDOWS_THREADS
    mvpSyncObject = CreateEvent(NULL, true, false, NULL); 
    assert(mvpSyncObject);
#endif
  }
  //*************************************************************************//

  //*************************************************************************//
  Event::~Event()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Event::Signal()
  {
    assert(mvpSyncObject);
    bool bReturnValue = false;
    if(this->mvpSyncObject)
    {
#ifdef WINDOWS_THREADS
      // Using tertiary operator because the visual studio compiler is stupid.
      bReturnValue = SetEvent(this->mvpSyncObject) ? true : false;
#endif 
    }
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Event::Reset()
  {
    assert(mvpSyncObject);
    bool bReturnValue = false;
    if(this->mvpSyncObject)
    {
#ifdef WINDOWS_THREADS
      // Using tertiary operator because the visual studio compiler is stupid.
      bReturnValue = ResetEvent(this->mvpSyncObject) ? true : false;
#endif 
    }
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Event::WaitForSignal(unsigned long ulWait)
  {
    assert(mvpSyncObject);

    //-----------------------------------------------------------------------//
    if(this->mvpSyncObject)
    {
      unsigned long ulResult = 0L;

      if(ulWait == ULONG_MAX)
      {
#ifdef WINDOWS_THREADS
        ulResult = WaitForSingleObject(this->mvpSyncObject, INFINITE);
#endif
      } // End of if(ulWait == ULONG_MAX)
      else
      {
#ifdef WINDOWS_THREADS
        ulResult = WaitForSingleObject(this->mvpSyncObject, ulWait);
#endif
      }

#ifdef WINDOWS_THREADS
      if(ulResult & WAIT_FAILED || ulResult & WAIT_TIMEOUT)
        return false;
#endif

      return true;
    } // End of if(this->mvpSyncObject)
    //-----------------------------------------------------------------------//
    else
      return false;
  }
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//
