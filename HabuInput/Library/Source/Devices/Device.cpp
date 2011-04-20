//***************************************************************************//
// Device Class Implementation
//
// Created Sep 27, 2006
// By: Jeremy M Miller
//
// Copyright (c) 2006  Jeremy M Miller.  All rights reserved.
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

//***************************************************************************//
#include "Devices\Device.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  Device::Device()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  Device::~Device()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Device::Initialize(IDirectInput8* pDirectInput, HWND hMainWindow)
  {
    return false;
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Device::Uninitalize()
  {
    return false;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Device::Poll()
  {
  }
  //*************************************************************************//
} // End of HabuInput
//***************************************************************************//