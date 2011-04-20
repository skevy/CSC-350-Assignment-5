//***************************************************************************//
// Thread Class Implementation
//
// Created: Feb 16, 2009
// By: Jeremy M Miller (info@bluehabu.com)
//
// Copyright (c) 2009 Jeremy M Miller.  
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
// System Include
#include <Windows.h>
#include <process.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Thread.hpp"
#include "Mutex.hpp"
#include "Event.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //-------------------------------------------------------------------------//
  Thread::Thread()
  {
    mfpRoutine         = 0;
    mvpDerivedThis     = 0;
    mbThreadRunning    = false;
    mulPauseTime       = 0;
    mpThreadMutex      = new Mutex();
    mpResumeEvent      = new Event();
    mpThreadStartEvent = new Event();
    mpThreadStopEvent  = new Event();
  }
  //-------------------------------------------------------------------------//
  
  //-------------------------------------------------------------------------//
  Thread::~Thread()
  {
    this->mpThreadMutex->Lock();
    delete mpResumeEvent;
    delete mpThreadStartEvent;
    delete mpThreadStopEvent;
    this->mpThreadMutex->Unlock();
    delete mpThreadMutex;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Thread::SetRoutine(void (*fpRoutine)(void*), void* pThis)
  {
    mfpRoutine = fpRoutine;
    mvpDerivedThis = pThis;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Thread::SignalStarted()
  {
    if(!this->mbThreadRunning)
    {
      this->mpThreadMutex->Lock();
      this->mbThreadRunning = true;
      this->mpThreadStartEvent->Signal();
    }
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Thread::SignalStopped()
  {
    this->mbThreadRunning = false;
    this->mpThreadStopEvent->Signal();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Continue()
  {
    if(this->mbThreadRunning)
    {
      if(this->mulPauseTime)
      {
        this->mpResumeEvent->WaitForSignal(this->mulPauseTime);
        this->mulPauseTime = 0UL;
      }
    }
    return this->mbThreadRunning;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Thread::End()
  {
    this->mpThreadMutex->Unlock();
    _endthread();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Start()
  {
    bool bReturnvalue = false;
    if(!this->mbThreadRunning)
    {
      this->mpThreadMutex->Unlock();
      _beginthread(mfpRoutine, 0L, mvpDerivedThis);
      this->mpThreadStartEvent->WaitForSignal();
      bReturnvalue = true;
    }
    return bReturnvalue;

  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Stop(unsigned long ulTimeout)
  {
    this->mbThreadRunning = false;
    this->mulPauseTime = 0;
    this->mpResumeEvent->Signal();
    this->mpThreadStopEvent->WaitForSignal(ulTimeout);
    return true;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Pause(unsigned long ulTime)
  {
    bool bReturnValue = false;
    if(this->mbThreadRunning && ulTime)
    {
      this->mulPauseTime = ulTime;
      bReturnValue = true;
    }
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Resume()
  {
    bool bReturnValue = false;
    if(this->mbThreadRunning && this->mulPauseTime)
    {
      this->mulPauseTime = 0;
      if(this->mpResumeEvent->Signal())
        bReturnValue = true;
    }
    return bReturnValue;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Thread::Running() const
  {
    return this->mbThreadRunning;
  }
  //-------------------------------------------------------------------------//
}
//***************************************************************************//