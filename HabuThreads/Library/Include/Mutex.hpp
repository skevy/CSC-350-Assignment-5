//***************************************************************************//
// Mutex Class Interface
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

#ifndef HABU_THREADS_MUTEX_HPP
#define HABU_THREADS_MUTEX_HPP

//***************************************************************************//
// System Includes
#include <limits.h> // Used for ULONG_MAX
//***************************************************************************//

//***************************************************************************//
// Local includes
#include "Sync.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  /// \brief Mutex is class that provides synchronization of critical sections
  /// between more than one threads. Single threads that repeatedly call this class's
  /// locking methods will not block.  However, calls to this class's locking 
  /// methods by more than one thread have to potential to block.
  class Mutex : public Sync
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  public:
    //***********************************************************************//
    Mutex();
    ~Mutex();

    /// This method will block and therefore protect a critical section if this
    /// method will called by more than one thread. If them method is called
    /// by the same thread more than once, it will not block
    /// \param [in] ulWait
    /// This parameter is the amount of time this method attempts to attain a
    /// lock.  If no wait time is specified this method will block indefinitely or 
    /// until the lock is attained.
    /// \return
    /// This method will return true if the lock was attained. Otherwise, if the 
    /// wait time has expired before the lock is attained, this method will 
    /// return false.
    bool _cdecl Lock(unsigned long ulWait = ULONG_MAX);
    /// This method will releases an attained locks. If no lock was attained by 
    /// the calling method, this method has no effect.
    void _cdecl Unlock();
    //***********************************************************************//
  }; // End of class Mutex
  //*************************************************************************//
} // End of namespace HabuThread
//***************************************************************************//

#endif HABU_THREADS_MUTEX_HPP