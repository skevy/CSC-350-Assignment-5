//***************************************************************************//
// HabuGraphics Base Class Interface
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2010 Jeremy M Miller.  All rights reserved.
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

#ifndef HABU_GRAPHICS_HPP
#define HABU_GRAPHICS_HPP

//***************************************************************************//

//***************************************************************************//
#define DEFAULT_WINDOW_WIDTH  800
#define DEFAULT_WINDOW_HEIGHT 600

#define HABU_GRAPHICS_VERSION 0.004F
//***************************************************************************//

//***************************************************************************//
#include <assert.h>
#include <vector>
#include <string>

#include <windows.h>

//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  enum Transforms
  {
    HG_VIEW_TRANSFORM,
    HG_PROJECTION_TRANSFORM
  };
  //*************************************************************************//

  //*************************************************************************//
  // Graphics is the class that enables D3D and manages window creation
  class Graphics
  {
  private:
    //***********************************************************************//
    class Scene* mpActiveScene;

    //-----------------------------------------------------------------------//
    static HDC       smhDeviceContext;
    static HGLRC     smhRenderingContext;
    static HWND      smhWindow;
    static HINSTANCE smhInstance;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long mulWindowWidth;
    unsigned long mulWindowHeight;
    //-----------------------------------------------------------------------//

    static unsigned int smuiMaxNumberOfVertexElements;
    static unsigned int smuiMaxNumberOfIndexElements;

    //-----------------------------------------------------------------------//
    // This member is used to store the index to the current adapter being used.
    unsigned long mulAdapter;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// This method will check to see if the Device is lost.
    /// Return Value: True if the device is lost otherwise this will return false.
    bool DeviceLost();

    /// The method will reset the device and reallocation and resource allocated
    /// in the D3DPOOL_DEFAULT
    /// Return Value: True if the device was reset otherwise this will return false.
    bool ResetDevice();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// This method will load a configuration file. This configuration file can
    /// used to communicate things such are resolution and anti-aliasing.
    /// Return Value: This method will return true when the configuration file
    ///               loads successfully, otherwise this method will return false.
    bool LoadConfig(const std::string& strFileName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// This method will attempt the set the multi-sample value. IE anti-alias.
    /// The method will only succeed is the current device can do the requested
    /// number of multi-samples in hardware.
    /// Parameter 1: This parameter is used to communication the desired number
    ///              multi-samples to do per frame
    /// Return value: This method will return true if the desired multi-sample 
    ///               value was set otherwise this method will return false.
    bool SetMultiSample(unsigned long ulSamples);
    //-----------------------------------------------------------------------//

    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Graphics(bool bWindowed);
    ~Graphics();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long GetNumberOfAdapters();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    static long Initialize(HWND hWindow, unsigned long ulWidth = DEFAULT_WINDOW_WIDTH, unsigned long ulHeight = DEFAULT_WINDOW_HEIGHT);
    static long Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void WindowDimensions(unsigned long ulWidth, unsigned long ulHeight);
    unsigned long WindowWidth() const;
    unsigned long WindowHeight() const;

    void  NearClipPlane(float fNear);
    float NearClipPlane() const;
    
    void  FarClipPlane(float fFar);
    float FarClipPlane() const;
    
    void  FieldOfVeiw(float fDegrees);
    float FieldOfView() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void SetBackBufferSize(unsigned long ulWidth, unsigned long ulHeight);
    //-----------------------------------------------------------------------//

    unsigned int MaxVertexBufferSize() const;
    unsigned int MaxIndexBufferSize() const;

    //-----------------------------------------------------------------------//
    /// HabuGraphics::RenderScene() clears the depth and color buffer and starts
    /// rendering the scene
    int Render();
    /// HabuGraphics::SwapBuffers uses GLFW to swap buffer since GLFW is managing the
    /// video card device context and windows management
    void SwapBuffer();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Scene* CreateScene(const std::string& rstrName);
    void DestroyScene(const std::string& rstrName);
    void DestroyScene(class Scene** ppScene);
    class Scene* GetScene(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool LoadScene(const std::string& strSceneFileName)
    {
      /// \TODO redo
      return false;
    }
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  };
  //*************************************************************************//
}
//***************************************************************************//

#include "Utility.hpp"
#include "Font.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Cylinder.hpp"
#include "Scene.hpp"

#include "Camera.hpp"
#include "Statistics.hpp"

#endif HABU_GRAPHICS_HPP
