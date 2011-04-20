//***************************************************************************//
// Device Class Interface
//
// Created Sept 27, 2006
// By: Jeremy M Miller
//
// Copyright (c) 2006 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//
// Usage of HabuInput is subject to the appropriate license agreement.
// A proprietary/commercial licenses are available. (info@bluehabu.com)
//                 
// HabuInput is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HabuInput is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HabuThreads.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

#ifndef HABU_INPUT_DEVICE_HPP
#define HABU_INPUT_DEVICE_HPP

//***************************************************************************//
#include "HabuInput.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // This class is the base class for all input devices
  class Device
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Device();
    virtual ~Device();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // All input devices need these methods. The implemenation of the devices
    // in Devices.cpp currently does nothing
    virtual bool Initialize(IDirectInput8* pDirectInput, HWND hMainWindow);
    virtual bool Uninitalize();

    virtual void Poll();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Device
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_INPUT_DEVICE_HPP