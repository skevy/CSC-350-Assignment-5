//***************************************************************************//
// HabuGraphics Base Class Implementation
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2010  Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//
// Usage of HabuGraphics is subject to the appropriate license agreement.
// A proprietary/commercial licenses are available.
//                 
// HabuGraphics is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HabuGraphics is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HabuGraphics.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <assert.h>
//***************************************************************************//

//***************************************************************************//
// 3rd Party Includes
#include <GL\glew.h> // Must be called before GL.h
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "HabuGraphics.hpp"
#include "Utility.hpp"
//***************************************************************************//

//***************************************************************************//
#define CLEAR_COLOR 0xFFEEEEEE
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  HDC       Graphics::smhDeviceContext = NULL;
  HGLRC     Graphics::smhRenderingContext = NULL;
  HWND      Graphics::smhWindow = NULL;
  HINSTANCE Graphics::smhInstance = NULL;
  unsigned int Graphics::smuiMaxNumberOfIndexElements = 0UL;
  unsigned int Graphics::smuiMaxNumberOfVertexElements = 0UL;

  //*************************************************************************//
  Graphics::Graphics(bool bWindowed)
  {
    //-----------------------------------------------------------------------//
    this->mpActiveScene        = NULL;
    this->mulWindowHeight      = DEFAULT_WINDOW_HEIGHT;
    this->mulWindowWidth       = DEFAULT_WINDOW_WIDTH;
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  Graphics::~Graphics()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Graphics::SetMultiSample(unsigned long ulSamples)
  {
    // This bool is for returning to the callee the success or failure
    // or trying to set the given multi-sample type.
    bool bReturnValue = false;

    // Return either success or failure.
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  long Graphics::Initialize(HWND hWindow, unsigned long ulWidth, unsigned long ulHeight)										
  {
    //-----------------------------------------------------------------------//
    // Create a data member to hold the result of this method. In this method's
    // case it will hold any error codes. By default set to 1 to signal no error. 
    long lResultCode = 1;
    //-----------------------------------------------------------------------//

    smhWindow = hWindow;

    static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
    {
      sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
      1,											// Version Number
      PFD_DRAW_TO_WINDOW |						// Format Must Support Window
      PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
      PFD_DOUBLEBUFFER,							// Must Support Double Buffering
      PFD_TYPE_RGBA,								// Request An RGBA Format
      32,										// Select Our Color Depth
      0, 0, 0, 0, 0, 0,							// Color Bits Ignored
      0,											// No Alpha Buffer
      0,											// Shift Bit Ignored
      0,											// No Accumulation Buffer
      0, 0, 0, 0,									// Accumulation Bits Ignored
      16,											// 16Bit Z-Buffer (Depth Buffer)  
      0,											// No Stencil Buffer
      0,											// No Auxiliary Buffer
      PFD_MAIN_PLANE,								// Main Drawing Layer
      0,											// Reserved
      0, 0, 0										// Layer Masks Ignored
    };

    GLuint		PixelFormat;
    if(!(smhDeviceContext = GetDC(hWindow)))
    {
      lResultCode = -1;
      smhDeviceContext = NULL;
    }

    if(lResultCode > 0 && !(PixelFormat = ChoosePixelFormat(smhDeviceContext, &pfd)))	// Did Windows Find A Matching Pixel Format?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !SetPixelFormat(smhDeviceContext, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !(smhRenderingContext = wglCreateContext(smhDeviceContext)))				// Are We Able To Get A Rendering Context?
    {
      lResultCode = -1;
    }

    if(lResultCode > 0 && !wglMakeCurrent(smhDeviceContext, smhRenderingContext))					// Try To Activate The Rendering Context
    {
      lResultCode = -1;
    }

    if(lResultCode > 0)
    {
      // Check Required Extensions
      GLenum err = glewInit();
      if(err == GLEW_OK)
      {
        glewGetString(GLEW_VERSION);
        /// \TODO DO something with version.
        if(GLEW_ARB_vertex_buffer_object)
        {
          
          glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
          glClearDepth(1.0f);									// Depth Buffer Setup
          glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
          glEnable ( GL_LIGHTING ) ;
          float global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
          glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
          GLfloat specular[] = {1.0f, 1.0f, 1.0f , 1.0f};
          glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
          glShadeModel(GL_SMOOTH);

          glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
          glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
          glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
          glEnable(GL_TEXTURE_2D);

          glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, reinterpret_cast<GLint*>(&(smuiMaxNumberOfVertexElements)));
          glGetIntegerv(GL_MAX_ELEMENTS_INDICES, reinterpret_cast<GLint*>(&(smuiMaxNumberOfIndexElements)));
        }
        else
        {
          lResultCode = -1;
        }
      }
      else
      {
        glewGetErrorString(err);
        lResultCode = -1;
        /// \TODO do something with error.
      }
    }

    //-----------------------------------------------------------------------//
    // Return result/error code
    return lResultCode;
    //-----------------------------------------------------------------------//
  } // End of long Graphics::Initialize(HWND hWindow)	
  //*************************************************************************//

  //*************************************************************************//
  long Graphics::Uninitialize()
  {
    long lReturnCode = 1;
    if(smhRenderingContext)											// Do We Have A Rendering Context?
    {
      if(!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
      {
        MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        lReturnCode = -1;
      }

      if(!wglDeleteContext(smhRenderingContext))						// Are We Able To Delete The RC?
      {
        MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        lReturnCode = -1;
      }
      smhRenderingContext = NULL;										// Set RC To NULL
    }
    if(smhDeviceContext && !ReleaseDC(smhWindow, smhDeviceContext))					// Are We Able To Release The DC
    {
      MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
      smhDeviceContext = NULL;										// Set DC To NULL
      lReturnCode = -1;
    }

    return lReturnCode;
  } // End of long Graphics::Uninitialize()
  //*************************************************************************//

  //*************************************************************************//
  void Graphics::WindowDimensions(unsigned long ulWidth, unsigned long ulHeight)
  {
    this->mulWindowWidth  = ulWidth;
    this->mulWindowHeight = ulHeight;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned long Graphics::WindowWidth() const
  {
    return this->mulWindowWidth;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned long Graphics::WindowHeight() const
  {
    return this->mulWindowHeight;
  }
  //*************************************************************************//

  //*************************************************************************//
  // Base::RenderScene() clears the depth and color buffer and starts
  // rendering the scene
  int Graphics::Render()									
  {
    mpActiveScene->Render();

    return 0;
  }
  //*************************************************************************//

  //*************************************************************************//
  // Base::SwapBuffers 
  void Graphics::SwapBuffer()
  {
    SwapBuffers(smhDeviceContext);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  //*************************************************************************//

  //*************************************************************************//
  class Scene* Graphics::CreateScene(const std::string& rstrName)
  {
    this->mpActiveScene = new Scene(this);
    return this->mpActiveScene;
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Graphics::LoadConfig(const std::string& strFileName)
  {
    return false;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned long Graphics::GetNumberOfAdapters()
  {
    return 0;
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Graphics::DeviceLost()
  {
    bool bReturnValue = false;
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Graphics::SetBackBufferSize(unsigned long ulWidth, unsigned long ulHeight)
  {
    this->ResetDevice();
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Graphics::ResetDevice()
  {
    bool bReturnValue = true;
    return bReturnValue;
  }
  //*************************************************************************//

  unsigned int Graphics::MaxVertexBufferSize() const
  {
    return smuiMaxNumberOfVertexElements;
  }

  unsigned int Graphics::MaxIndexBufferSize() const
  {
    return smuiMaxNumberOfIndexElements;
  }
}
//***************************************************************************//
