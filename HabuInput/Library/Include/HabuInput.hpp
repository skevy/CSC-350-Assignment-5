//***************************************************************************//
// HabuInput Base Class Interface
//
// Created Aug 27, 2006
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

#ifndef HABU_INPUT_HPP
#define HABU_INPUT_HPP

//***************************************************************************//
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <vector>
//***************************************************************************//

// Define the current version of this library
#define HABU_INPUT_VERSION 0.002F

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // Singleton -- there can only be one Input object to manage all input devices
  class Input 
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // Pointer to directinput 8
    IDirectInput8* mpDirectInput;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This vector holds all the devices that will be polled with this classes
    // memeber function void Poll(); is called
    std::vector<class Device*> mvDevices;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Singleton requirements
    static Input* mpInstance;
    Input();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // Destructor
    // Note this destructor is not virtual. Do not derive from this class
    ~Input();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Singleton access function
    static class Input* Instance() 
    {
      if(mpInstance == NULL) 
        mpInstance = new Input();

      return mpInstance;
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method will initialize all devices is the mvDevices vector. In the 
    // case that devices are already initialized this method will uninitialize 
    // those devices.
    // Parameter 1: This is the current instance of the application that using 
    //              this library/class.
    // Parameter 2: This is handle to the window the application is running in
    // Return Value: This method will return true if and only if all devices
    //               initialized in the mvDevices vector return true
    bool Initialize(HINSTANCE hApplicationIntance, HWND hMainWindow);
    // This method will release the DirectInput interface and uninitialize all 
    // devices in the mvDevices vector
    void Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method gives public access to the keyboard object so the state of the 
    // keyboard can be attained
    // Return Value: A constant pointer to this class's keyboard device
    const class Keyboard* GetKeyboard() { return (class Keyboard*)this->mvDevices[0]; }
    // This method gives public access to the mouse object so the state of the 
    // mouse can be attained
    // Return Value: A constant pointer to this class's mouse device
    const class Mouse*    GetMouse()    { return (class Mouse*)   this->mvDevices[1]; }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method should be called once per program loop by the user of this 
    // library.  This method will update all the devices in the mvDevices vector
    // TODO: Consider making this concurrent and running it at a constant rate.
    void Poll();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Input
  //*************************************************************************//

} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_INPUT_HPP