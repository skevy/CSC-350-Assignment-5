//***************************************************************************//
// Mutex Class Implementation
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
#include "Mutex.hpp"
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <assert.h>
#include <sstream>
//***************************************************************************//

//***************************************************************************//
#ifdef WINDOWS_THREADS
#include <windows.h>
#endif 
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  Mutex::Mutex()
  {
#ifdef WINDOWS_THREADS
    mvpSyncObject = CreateMutex(NULL, false, NULL);
    assert(mvpSyncObject);
#endif
  }
  //************************************************************************//

  //*************************************************************************//
  Mutex::~Mutex()
  {
#ifdef WINDOWS_THREADS
    CloseHandle(mvpSyncObject);
#endif 
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Mutex::Lock(unsigned long ulWait)
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

  //*************************************************************************//
  void Mutex::Unlock()
  {
    assert(this->mvpSyncObject);
    if(this->mvpSyncObject)
    {
#ifdef WINDOWS_THREADS
      ReleaseMutex(this->mvpSyncObject);
      //ReleaseSemaphore(this->mvpSyncObject, 1, NULL);
#endif 
    }
  }
  //*************************************************************************//

} // End of namespace HabuTech
//***************************************************************************//