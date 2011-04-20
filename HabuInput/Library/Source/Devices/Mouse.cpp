//D***************************************************************************//
// Mouse Class Implementation
//
// Created Aug 27, 2006
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

#include "Devices\Mouse.hpp"

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // Public
  // Constructor.
  Mouse::Mouse()
  {
    //-----------------------------------------------------------------------//
    // Initialize all data members to 0.  It might be easier and quicker to 
    // just use memset.
    mlCurrentPixel_X_Position   = 0L;
    mlCurrentPixel_Y_Position   = 0L;
    mlPreviousPixel_X_Position  = 0L;
    mlPreviousPixel_Y_Position  = 0L;

    mlWidth                     = 0L;
    mlHeight                    = 0L;

    mlUpperLimit                = 0L;
    mlLowerLimit                = 0L;
    mlLeftLimit                 = 0L;
    mlRightLimit                = 0L;
    //-----------------------------------------------------------------------//
  } // End of Mouse::Mouse()
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // Destructor.
  Mouse::~Mouse()
  {
  } // End of Mouse::~Mouse()
  //*************************************************************************//

  //*************************************************************************//
  // Private
  // This method will center the mouse relative to the window.
  void Mouse::Center()
  {
    SetCursorPos(mlLeftLimit  + (this->mlWidth  >> 1), 
                 mlUpperLimit + (this->mlHeight >> 1));
  } // End of void Mouse::Center()
  //*************************************************************************//

  //*************************************************************************//
  // Private
  // This method will should be called everytime the windows postion has changed
  // so that offsets for the mouse can be updated.
  // Parameter 1: The parameter is the current rectangle of the window.  If no
  //              rectangle is passed to this method, the mthod will make a windows
  //              call to find the dimesions and location of the window.
  void Mouse::SetWindowPosition(RECT* pRectangle)
  {
    //-----------------------------------------------------------------------//
    // This bool will be used if this method creates a rectangle object.
    // If this bool is true then we need to delete the object that is created.
    bool bCleanUp = false;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If no valid rectangle was passed inot this method; we neet to create one 
    // and get the dimensions and the location of the window.
    if(pRectangle == NULL)
    {
      pRectangle = new RECT;
      // Set this bool to true so that we know that we need to delete
      // the rectangle created above
      bCleanUp = true;

      GetWindowRect(mhMainWindow, pRectangle);
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Set the width and height of the window
    this->mlWidth  = pRectangle->right  - pRectangle->left;
    this->mlHeight = pRectangle->bottom - pRectangle->top;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Set the limits of the window
    mlUpperLimit = pRectangle->top;
    mlLowerLimit = pRectangle->bottom - 1;
    mlLeftLimit  = pRectangle->left;
    mlRightLimit = pRectangle->right - 1;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If we created the rectangle we need to delete it.
    if(bCleanUp)
      delete pRectangle;
    //-----------------------------------------------------------------------//
  } // End of void Mouse::SetWindowPosition(RECT* pRectangle)
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // The below method uses a pointer from a the directinput interface to 
  // create and initialze communication with the mouse using directinput.  
  // This method also sets the mouse to be used via windows calls so that 
  // pixel position information can be provided by this class. This method 
  // is required by the Device base class.
  // Parameter 1: An establised pointer to a directinput interface.
  // Parameter 2: A valid window handle to which mouse movements need to be tracked
  // Return Value: If the method was unable to setup directinput for the mouse
  //               this method will return false. Otherwise it will return true.
  //               We assume that we can always use the mouse windows calls.
  bool Mouse::Initialize(IDirectInput8* pDirectInput, HWND hMainWindow)
  {
    //-----------------------------------------------------------------------//
    // Clear the current state of the mouse
    memset(&mMouseState,     0L, sizeof(mMouseState));
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Store the handle to window so that we can access the windows location 
    // in the event it is moved or resized
    mhMainWindow = hMainWindow;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Create the mouse device
    pDirectInput->CreateDevice(GUID_SysMouse,    &mpMouse, 0);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Set Data Format and the cooperation level
    mpMouse->   SetDataFormat(&c_dfDIMouse2);
    mpMouse->   SetCooperativeLevel(mhMainWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Aquire Device via directinput
    long lResult = mpMouse->Acquire();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Set the get the latest window postions from the OS and set the cusor to
    // be in the center of the that window
    this->SetWindowPosition();
    this->Center();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If we successfully acquired the mouse via directinput return true 
    // otherwise return false.
    if(lResult == DI_OK)
      return true;
    return false;
    //-----------------------------------------------------------------------//
  } // End of bool Mouse::Initialize(IDirectInput8* pDirectInput, HWND hMainWindow)
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // The below method will uninitialize and release the mouse from directinput.
  // This method is required by the Device base class.
  // Return Value: This method will return true if the release and uninitialization
  //               was sucessful. Otherwise it will return false.
  bool Mouse::Uninitialize()
  {
    //-----------------------------------------------------------------------//
    // If the we attained a valid pointer for the mouse via directinput...
    if(this->mpMouse)
    {
      //---------------------------------------------------------------------//
      // ... release the mouse
      long lResult = this->mpMouse->Unacquire();
      this->mpMouse->Release();
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // If we sucessfully released the mouse return true. Otherwise return false.
      if(lResult == DI_OK)
        return true;
      //---------------------------------------------------------------------//
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // We can only get here if we failed to release the mouse from directinput.
    // In that case return false.
    return false;
    //-----------------------------------------------------------------------//
  } // End of bool Mouse::Uninitialize()
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // The below methods get the delta for their respective basis vector that is
  // reported by direct input.
  // Return Value: The delta/change in postion the mouse moved.
  float Mouse::Direct_DX() const
  {
    return (float)mMouseState.lX;
  }

  float Mouse::Direct_DY() const
  {
    return (float)mMouseState.lY;
  } 

  float Mouse::Direct_DZ() const
  {
    return (float)mMouseState.lZ;
  }
  
  bool Mouse::LeftButton() const
  {
      return (mMouseState.rgbButtons[0] & 0x80);
  }

  bool Mouse::RightButton() const
  {
      return (mMouseState.rgbButtons[2] & 0x80);
  }
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // The below methods get the delta for their respective basis vector that is
  // reported by windows in units of pixels.
  // Return Value: The delta/change in postion the mouse moved in pixels.
  long Mouse::Pixel_DX_Position() const
  {
    return this->mlCurrentPixel_X_Position - this->mlPreviousPixel_X_Position;
  }

  long Mouse::Pixel_DY_Position() const
  {
    return this->mlCurrentPixel_Y_Position - this->mlPreviousPixel_Y_Position;
  }
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // The below methods get the relative (to the current windows) position 
  // for their respective basis vector that is reported by windows in units 
  // of pixels.
  // Return Value: The relative in postion the mouse moved in pixels
  long Mouse::Pixel_X_Position() const
  {
    return this->mlCurrentPixel_X_Position;
  }

  long Mouse::Pixel_Y_Position() const
  {
    return this->mlCurrentPixel_Y_Position;
  }
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // Currently this method does nothing.  A better name would be SetCursorImage
  // TODO: Implement this method
  bool Mouse::SetCursor(std::string strFileName)
  {
    return false;
  } // End of bool Mouse::SetCursor(std::string strFileName)
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // This is method is required to poll the mouse and should be called once per
  // program loop.  This method is required by the Device base class.
  void Mouse::Poll()
  {
    //-----------------------------------------------------------------------//
    // These object wil be used to get the current rectangle of the window and 
    // the current point postion of the mouse.
    RECT oRectangle;
    POINT oPoint;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method will get the mouse data from directinput.
    long lResult = this->mpMouse->GetDeviceState(sizeof(mMouseState),
      (void**)&mMouseState);
    //-----------------------------------------------------------------------//
 
    //-----------------------------------------------------------------------//
    // Get the current position and size of the window.
    GetWindowRect(mhMainWindow, &oRectangle);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If the window size of position had changed...
    if((oRectangle.top != this->mlUpperLimit)   || 
       (oRectangle.left != this->mlLeftLimit)   || 
       (oRectangle.right != this->mlRightLimit) || 
       (oRectangle.bottom != this->mlLowerLimit))
    {
      // ... Update the windows position
      this->SetWindowPosition(&oRectangle);
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Get the position of the cursor
    GetCursorPos(&oPoint);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If the cursor position is within the bounds of the window...
    if((oPoint.y <= this->mlLowerLimit) && 
       (oPoint.y >= this->mlUpperLimit) && 
       (oPoint.x <= this->mlRightLimit) && 
       (oPoint.x >= this->mlLeftLimit))
    {
      // ... update the postion of the mouse

      //---------------------------------------------------------------------//
      // First we need to store the previous postion of the cursor so that deltas can be
      // derived.
      this->mlPreviousPixel_X_Position = this->mlCurrentPixel_X_Position;
      this->mlPreviousPixel_Y_Position = this->mlCurrentPixel_Y_Position;
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // Then set the current position of the mouse
      this->mlCurrentPixel_X_Position = oPoint.x - this->mlLeftLimit;
      this->mlCurrentPixel_Y_Position = oPoint.y - this->mlUpperLimit;
      //---------------------------------------------------------------------//
    }
    //-----------------------------------------------------------------------//
    else 
    {
      //---------------------------------------------------------------------//
      // ... otherwise just set the current position from the previous valid postion.
      // This will ensure the deltas are zero.
      this->mlCurrentPixel_X_Position = this->mlPreviousPixel_X_Position;
      this->mlCurrentPixel_Y_Position = this->mlPreviousPixel_Y_Position;
      //---------------------------------------------------------------------//
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If we unsuccessful reading mouse data from directinput...
    if(lResult != DI_OK)
    {
      // ... try to reacquire the mouse
      memset(&mMouseState, 0L, sizeof(mMouseState));
      mpMouse->Acquire();
    }//-----------------------------------------------------------------------//
  } // End of void Mouse::Poll()
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//