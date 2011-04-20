//***************************************************************************//
// Keyboard Class Implementation
//
// Created Sept 13, 2006
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
#include "Devices\Keyboard.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  Keyboard::Keyboard()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  Keyboard::~Keyboard()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // The below method uses a pointer from a the directinput interface to 
  // create and initialze communication with the keyboard using directinput.  
  // This method also sets cooperation level for the window. This method 
  // is required by the Device base class.
  // Parameter 1: An establised pointer to a directinput interface.
  // Parameter 2: A valid window handle so we know when the windows is infocus
  //              and therefore know if we should capture the state of the device.
  // Return Value: If the method was unable to setup directinput for the mouse
  //               this method will return false. Otherwise it will return true.
  //               We assume that we can always use the mouse windows calls.
  bool Keyboard::Initialize(IDirectInput8* pDirectInput, HWND hMainWindow)
  {
    //-----------------------------------------------------------------------//
    // Clear the current state of the keyboard
    memset(mcaKeyBoardState, 0L, sizeof(mcaKeyBoardState));
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Create device
    pDirectInput->CreateDevice(GUID_SysKeyboard, &mpKeyBoard, 0);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Set Data Format
    mpKeyBoard->SetDataFormat(&c_dfDIKeyboard);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Set cooperation level
    mpKeyBoard->SetCooperativeLevel(hMainWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Aquire Device
    long lResult = mpKeyBoard->Acquire();
    if(lResult == DI_OK)
      return true;
    return false;
    //-----------------------------------------------------------------------//
  } // End of bool Keyboard::Initialize(IDirectInput8* pDirectInput, HWND hMainWindow)
  //*************************************************************************//

  //*************************************************************************//
  // The below method will uninitialize and release the keyboard from directinput.
  // This method is required by the Device base class.
  // Return Value: This method will return true if the release and uninitialization
  //               was sucessful. Otherwise it will return false.
  bool Keyboard::Uninitialize()
  {
    //-----------------------------------------------------------------------//
    // If the we attained a valid pointer for the keyboard via directinput...
    if(this->mpKeyBoard)
    {
      //---------------------------------------------------------------------//
      // ... release the keyboard.
      long lResult = this->mpKeyBoard->Unacquire();
      this->mpKeyBoard->Release();
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // If we sucessfully released the keyboard return true. Otherwise return false.
      if(lResult == DI_OK)
        return true;
      //---------------------------------------------------------------------//
    }
    //-----------------------------------------------------------------------//
       
    //-----------------------------------------------------------------------//
    // We can only get here if we failed to release the keyboard from directinput.
    // In that case return false.
    return false;
    //-----------------------------------------------------------------------//
  } // End of bool Keyboard::Uninitialize()
  //*************************************************************************//

  //*************************************************************************//
  // This is method is required to poll the mouse and should be called once per
  // program loop.  This method is required by the Device base class.
  void Keyboard::Poll()
  {
    //-----------------------------------------------------------------------//
    // Attemp to get the state of the device and update this objects array of 
    // keys.
    long lResult = this->mpKeyBoard->GetDeviceState(sizeof(mcaKeyBoardState),
      (void**)&mcaKeyBoardState);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If the attempt to get the state failed or we have otherwise lost the 
    // the keyboard device then try to reacquire it.
    if(lResult != DI_OK)
    {
      memset(mcaKeyBoardState, 0L, sizeof(mcaKeyBoardState));
      mpKeyBoard->Acquire();
    }
    //-----------------------------------------------------------------------//
  } // End of void Keyboard::Poll()
  //*************************************************************************//
}
//***************************************************************************//


