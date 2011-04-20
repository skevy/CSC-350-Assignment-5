//***************************************************************************//
// Sleep Method Interface
//
// Created: Jun 23, 2008
// By: Jeremy M Miller (info@bluehabu.com)
//
// Copyright (c) 2005-2008 Jeremy M Miller.  
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

#ifndef HABU_THREADS_WAIT_HPP
#define HABU_THREADS_WAIT_HPP

//***************************************************************************//
namespace HabuTech
{
  /// This method will block while waiting for the passed in amount of time to
  /// expire.
  /// \param [in] ulTime
  /// This parameter this is amount of time this method will block. This 
  /// parameters units are in milliseconds.
  void _cdecl Wait(unsigned long ulTime);
} // End of namespace HabuThread
//***************************************************************************//

#endif HABU_THREADS_WAIT_HPP