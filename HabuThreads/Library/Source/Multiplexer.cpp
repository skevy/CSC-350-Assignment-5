//***************************************************************************//
// Multiplexer Implementation
//
// Created: Oct 6, 2008
// By: Jeremy M Miller (info@bluehabu.com)
//
// Copyright (c) 2008 Jeremy M Miller.  
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
// Local Includes
#include "Sync.hpp"
#include "Mutex.hpp"
#include "Multiplexer.hpp"
//***************************************************************************//

//***************************************************************************//
// System Includes
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
  //-------------------------------------------------------------------------//
  Multiplexer::Multiplexer()
  {
    this->mpMutex = new Mutex();
    mpArrayOfHandles = NULL;
    mulCurrentArraySize = 0UL;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Multiplexer::~Multiplexer()
  {
    if(mpArrayOfHandles)
      delete [] mpArrayOfHandles;
    delete mpMutex;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Multiplexer::AddHandle(void* pHandle)
  {
    bool bReturnValue = true;
    this->mpMutex->Lock();

    // This assertion is to notify the callee of a limitation of this method
    // This method assumes that size of long* and void* are the same.  This
    // without casting void* to long* things like array subsscripts would 
    // not compile.
    assert(sizeof(void*) == sizeof(long*));
    if(this->mvPersistentHandles.size() < MAXIMUM_WAIT_OBJECTS)
    {
      this->mvPersistentHandles.push_back(pHandle);

      if(!mpArrayOfHandles || (mulCurrentArraySize < this->mvPersistentHandles.size()))
      {
        if(mpArrayOfHandles)
          delete [] mpArrayOfHandles;

        this->mpArrayOfHandles = new long[this->mvPersistentHandles.size()];
      }

      for(unsigned long i = 0; i < this->mvPersistentHandles.size(); i++)
         ((long*)(this->mpArrayOfHandles))[i] = (long)(this->mvPersistentHandles[i]);

      this->mulCurrentArraySize = (unsigned long)this->mvPersistentHandles.size();
    }
    else
      bReturnValue = false;
      
    this->mpMutex->Unlock();

    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Multiplexer::WaitForTrigger(unsigned long ulWait)
  {
    bool bReturnValue = true;

    if(this->mpMutex->Lock())
    {
      unsigned long ulResult = WaitForMultipleObjects(this->mulCurrentArraySize, (HANDLE*)this->mpArrayOfHandles, false, ulWait);

      // Throw an assertion if the wait failed.
      assert(ulResult != WAIT_FAILED);
      if((ulResult == WAIT_TIMEOUT) || (ulResult == WAIT_FAILED) || (ulResult >= WAIT_ABANDONED_0))
        bReturnValue = false;
      else if(((ulResult - WAIT_OBJECT_0) > 0) && ((ulResult - WAIT_OBJECT_0) <= (int)this->mulCurrentArraySize))
        ResetEvent((HANDLE)((long*)(this->mpArrayOfHandles))[ulResult - WAIT_OBJECT_0]);

      this->mpMutex->Unlock();
    }

    return bReturnValue;
  }
  //-------------------------------------------------------------------------//
} // End of namespace HabuTech
//***************************************************************************//