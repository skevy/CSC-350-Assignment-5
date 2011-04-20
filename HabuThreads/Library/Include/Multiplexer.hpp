//***************************************************************************//
// Multiplexer Interface
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

#ifndef HABU_THREADS_MULTIPLEXER_HPP
#define HABU_THREADS_MULTIPLEXER_HPP

//***************************************************************************//
// System Includes
#include <vector>
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  /// \brief Multiplexer is synchronization mechanism for multiple individual 
  /// synchronization objects.
  class Multiplexer
  {
  private:
    //***********************************************************************//
    // This Mutex is used for protecting the state of this object from possible
    // race conditions.
    class Mutex* mpMutex;

    // This vector holds handles (void*) to the synchronization instances passed
    // to this class.  This class retains the handles so that other class state
    // can be modified to accommodate new handles
    std::vector<void*> mvPersistentHandles;

    // This is array of handles (void*) this class will block on.
    void* mpArrayOfHandles;
    // This data member holds the current number of handles (void*) in the array
    // of handles.
    unsigned long mulCurrentArraySize;
  public:
    //***********************************************************************//
    Multiplexer();
    ~Multiplexer();

    /// This method will add an handle to synchronization object to this class.
    /// For the life of this class, that handle will be able to trigger a release 
    /// of hold the state of class as blocked, until it releases or another added
    /// handles releases.
    /// \param [in] pHandle
    /// Handle to synchronization to be added. NOTE, caller cannot safely free resources
    /// pointed to by the passed handle until caller's instance of this class is destroyed.               
    /// \return 
    /// This method will return true if the handle was successfully added. Otherwise,
    /// it will return false.
    bool _cdecl AddHandle(void* pHandle);
    /// This method will block until one of the added handles releases or until
    /// the specified wait time has expired. If no wait time is specified and no handle
    /// releases, the method will block indefinitely.
    /// \param [in] ulWait
    /// This parameter is the maximum amount of time this method will block while
    /// waiting for a handles to release.  This parameter is in milliseconds.
    /// \return
    /// This method will return true if a handle released. Otherwise, if no handle
    /// released and the wait time expired then the method will return false.
    /// The method will never return if no handle released and no wait time was
    /// passed in.
    bool _cdecl WaitForTrigger(unsigned long ulWait = ULONG_MAX);
    //***********************************************************************//
  }; // End of class Multiplexer 
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_THREADS_MULTIPLEXER_HPP