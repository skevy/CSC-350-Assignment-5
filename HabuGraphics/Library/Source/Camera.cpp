//***************************************************************************//
// Camera Class Implementation
//
// Created Dec 12, 2005
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

//***************************************************************************//
// System Includes
#include <assert.h>

#include <fstream>
#include <sstream>
#include <string>
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Camera.hpp"
#include "Scene.hpp"
#include "HabuGraphics.hpp"
//***************************************************************************//

//***************************************************************************//
#define RIGHT_BASIS_VECTOR_LABEL   "Right"
#define UP_BASIS_VECTOR_LABEL      "Up"
#define FORWARD_BASIS_VECTOR_LABEL "Forward"
#define LOCATION_LABEL             "Loc"
#define FAR_CLIP_PLANE_LABEL       "Far"
#define NEAR_CLIP_PLANE_LABEL      "Near"
#define FIELD_OF_VIEW_LABEL        "FOV"
#define NUMBER_OF_CAMERA_PARAMETERS 7

#define DEFAULT_NEAR_CLIP_PLANE 0.1F
#define DEFAULT_FAR_CLIP_PLANE 100.0F
#define DEFAULT_FIELD_OF_VIEW_DEGREES 65.0F
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // Constructor
  Camera::Camera(const std::string& rstrName, class Scene* pScene) : Object(rstrName)
  {
    mpScene = pScene;

    //-----------------------------------------------------------------------//
    // Initialize matrices
    mProjectionMatrix.Identity();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    LoadDefaults();
    //-----------------------------------------------------------------------//
  } // End of Camera::Camera(const std::string& strName)
  //*************************************************************************//

  //*************************************************************************//
  Camera::~Camera()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Camera::LoadDefaults()
  {
    bool bReturnValue = false;
    Object::Position(0.0F, 0.0F, 15.0F);
    Object::Right   (1.0F, 0.0F, 0.0F);
    Object::Up      (0.0F, 1.0F, 0.0F);
    Object::Forward (0.0F, 0.0F, 1.0F);

    mfVerticalFOV   = DEFAULT_FIELD_OF_VIEW_DEGREES;
    mfNearClipPlane = DEFAULT_NEAR_CLIP_PLANE;
    mfFarClipPlane  = DEFAULT_FAR_CLIP_PLANE;
    
    this->UpdateProjection();
     
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Camera::Scene(class Scene* pScene)
  {
    this->mpScene = pScene;
  }
  //*************************************************************************//

  //*************************************************************************//
  class Scene* const Camera::Scene() const
  {
    return this->mpScene;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Camera::UpdateProjection()
  {
    // Reset view port
    glViewport(0, 0, this->Scene()->GetGraphics()->WindowWidth(), this->Scene()->GetGraphics()->WindowHeight());

    // Select Projection Matrix and reset it
    glMatrixMode(GL_PROJECTION);					
    glLoadIdentity();									      
    gluPerspective(
      static_cast<GLdouble>(this->mfVerticalFOV),
      static_cast<GLfloat>(this->Scene()->GetGraphics()->WindowWidth())/static_cast<GLfloat>(this->Scene()->GetGraphics()->WindowHeight()),
      this->mfNearClipPlane,
      this->mfFarClipPlane);
    
    this->mProjectionMatrix.Perspective(
      mfVerticalFOV,
      (float)this->mpScene->GetGraphics()->WindowWidth() / (float)this->mpScene->GetGraphics()->WindowHeight(),
      mfNearClipPlane,
      mfFarClipPlane);
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Camera::Load(std::ifstream& ifs)
  {
    //-----------------------------------------------------------------------//
    // Throw assertion is file streams is not open.
    assert(ifs.is_open() && ifs.good());
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If the file stream is not open return false.
    if(!ifs.is_open() || !ifs.good())
      return false;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This string will hold the label that describes some camera parameter.
    string strLabel;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This unsigned short will count the number of camera parameters read in
    // and will be used to verify that the correct number of parameters have 
    // been initialized.
    unsigned short usParameterCount = 0;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // The for loop will read in data from the file stream and will set 
    // the objects data members accordingly.
    for(unsigned short i = 0; i < NUMBER_OF_CAMERA_PARAMETERS; i++)
    {
      //---------------------------------------------------------------------//
      // Read in the label
      ifs >> strLabel;
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // Match the label to some predefined token and set the proper data member.
      float fX, fY, fZ;
      if(strLabel == RIGHT_BASIS_VECTOR_LABEL)
      {
        ifs >> fX;
        ifs >> fY;
        ifs >> fZ;
        Object::Right(fX, fY, fZ);
        usParameterCount++;
      }
      else if(strLabel == UP_BASIS_VECTOR_LABEL)
      {
        ifs >> fX;
        ifs >> fY;
        ifs >> fZ;
        Object::Up(fX, fY, fZ);
        usParameterCount++;
      }
      else if(strLabel == FORWARD_BASIS_VECTOR_LABEL)
      {
        ifs >> fX;
        ifs >> fY;
        ifs >> fZ;
        Object::Forward(fX, fY, fZ);
        usParameterCount++;
      }
      else if(strLabel == LOCATION_LABEL)
      {
        ifs >> fX;
        ifs >> fY;
        ifs >> fZ;
        Object::Position(fX, fY, fZ);
        usParameterCount++;
      }
      else if(strLabel == FAR_CLIP_PLANE_LABEL)
      {
        ifs >> mfFarClipPlane;
        usParameterCount++;
      }
      else if(strLabel == NEAR_CLIP_PLANE_LABEL)
      {
        ifs >> mfNearClipPlane;
        usParameterCount++;
      }
      else if(strLabel == FIELD_OF_VIEW_LABEL)
      {
        ifs >> mfVerticalFOV;
        // Convert radians to degrees
        mfVerticalFOV *= (180.0F/3.14F); 
        usParameterCount++;
      } // End of if-else chain that matches the read in label 
        // to predefined token.
      //---------------------------------------------------------------------//
    } // End of for(unsigned short i = 0; i < NUMBER_OF_CAMERA_PARAMETERS; i++)
    //-----------------------------------------------------------------------//

    this->UpdateProjection();

    assert(usParameterCount == NUMBER_OF_CAMERA_PARAMETERS);
    return (usParameterCount == NUMBER_OF_CAMERA_PARAMETERS);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Camera::SetFOV(float fAngle)
  {
    this->mfVerticalFOV = fAngle;

    this->UpdateProjection();
  }
  //*************************************************************************//

  //*************************************************************************//
  void Camera::ChangeFOV(float fAngle)
  {
    this->mfVerticalFOV += fAngle;
    SetFOV(this->mfVerticalFOV);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Camera::Render()
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Object::TransformToViewSpace();

    GLfloat m[16];
    Object::mTransformMatrix.RowMajor(m);
    glMultMatrixf(m);
  }
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//