//***************************************************************************//
// Light Class Implementation
//
// Created July 8, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2010  Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//                 PROPRIETARY AND CONFIDENTIAL
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "HabuGraphics.hpp"
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <windows.h>
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <fstream>
#include <sstream>
#include <string>
//***************************************************************************//

//***************************************************************************//
#define NUMBER_OF_LIGHT_PARAMETERS 6
#define RIGHT_BASIS_VECTOR_LABEL   "Right"
#define UP_BASIS_VECTOR_LABEL      "Up"
#define FORWARD_BASIS_VECTOR_LABEL "Forward"
#define LOCATION_LABEL             "Loc"
#define TYPE_LABEL                 "Type"
#define OMNI_LIGHT_TYPE_LABEL      "Omni"
#define SPOT_LIGHT_TYPE_LABEL      "Spot"
#define COLOR_LABEL                "Color"
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  Light::Light(const std::string& rstrName, enum LightID eLightID) : Object(rstrName)
  {
    this->mpAmbient = new Color<float>();
    this->mpDiffuse = new Color<float>();
    this->mpSpecular = new Color<float>();
    this->meLightID = eLightID;
    this->meLightType = UNKNOWN_LIGHT_TYPE;
    Initialize();
  }
  //*************************************************************************//

  //*************************************************************************//
  Light::~Light()
  {
    delete this->mpAmbient;
    delete this->mpDiffuse;
    delete this->mpSpecular;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Initialize()
  {
    //-----------------------------------------------------------------------//
    SetAmbient(0.0F, 0.0F, 0.0F);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    SetDiffuse(0.0F, 0.0F, 0.0F);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    SetSpecular(0.0F, 0.0F, 0.0F);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    Object::Forward(0.0F, 0.0F, 1.0F);
    Object::Right(1.0F, 0.0F, 0.0F);
    Object::Up(0.0F, 0.0F, 1.0F);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    Object::Position(0.0F, 0.0F, 0.0F);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    mbLightOn = false;
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Light::Load(std::ifstream& ifs)
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
    for(unsigned short i = 0; i < NUMBER_OF_LIGHT_PARAMETERS; i++)
    {
      //---------------------------------------------------------------------//
      // Read in the label
      ifs >> strLabel;
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // Match the label to some predefined token and set the proper data member.
      float fX, fY, fZ, fR, fG, fB;
      if(strLabel == RIGHT_BASIS_VECTOR_LABEL)
      {
        ifs >> fX;
        ifs >> fY;
        ifs >> fZ;
        this->Right(fX, fY, fZ);
        usParameterCount++;
      }
      else if(strLabel == UP_BASIS_VECTOR_LABEL)
      {
        ifs >> fX;
        ifs >> fY;
        ifs >> fZ;
        this->Up(fX, fY, fZ);
        usParameterCount++;
      }
      else if(strLabel == FORWARD_BASIS_VECTOR_LABEL)
      {
        ifs >> fX;
        ifs >> fY;
        ifs >> fZ;
        this->Forward(fX, fY, fZ);
        usParameterCount++;
      }
      else if(strLabel == LOCATION_LABEL)
      {
        ifs >> fX;
        ifs >> fY;
        ifs >> fZ;
        this->Position(fX, fY, fZ);
        usParameterCount++;
      }
      else if(strLabel == TYPE_LABEL)
      {
        string strType;
        ifs >> strType;
        if(strType == OMNI_LIGHT_TYPE_LABEL)
          this->meLightType = OMNI_LIGHT_TYPE;
        else if(strType == SPOT_LIGHT_TYPE_LABEL)
          this->meLightType = SPOT_LIGHT_TYPE;
        else
          this->meLightType = UNKNOWN_LIGHT_TYPE;

        usParameterCount++;
      }
      else if(strLabel == COLOR_LABEL)
      {
        ifs >> fR;
        ifs >> fG;
        ifs >> fB;
        this->SetDiffuse(fR, fG, fB);
        this->SetAmbient(fR, fG, fB);
        usParameterCount++;
      } // End of if-else chain that matches the read in label 
      // to predefined token.
      //---------------------------------------------------------------------//
    } // End of for(unsigned short i = 0; i < NUMBER_OF_CAMERA_PARAMETERS; i++)
    //-----------------------------------------------------------------------//

    assert(usParameterCount == NUMBER_OF_LIGHT_PARAMETERS);
    return (usParameterCount == NUMBER_OF_LIGHT_PARAMETERS);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Position(float fX, float fY, float fZ)
  {
    Object::Position(fX, fY, fZ);
    glLightfv(meLightID, GL_POSITION, static_cast<GLfloat*>(&Object::mPosition[0]));
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Move(float fX, float fY, float fZ)
  {
    Object::Move(fX, fY, fZ);
    glLightfv(meLightID, GL_POSITION, static_cast<GLfloat*>(&Object::mPosition[0]));
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Strafe(float fX)
  {
    Object::Strafe(fX);
    glLightfv(meLightID, GL_POSITION, static_cast<GLfloat*>(&Object::mPosition[0]));
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Advance(float fZ)
  {
    Object::Advance(fZ);
    glLightfv(meLightID, GL_POSITION, static_cast<GLfloat*>(&Object::mPosition[0]));
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Elevate(float fY)
  {
    Object::Elevate(fY);
    glLightfv(meLightID, GL_POSITION, static_cast<GLfloat*>(&Object::mPosition[0]));
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Forward(float fX, float fY, float fZ)
  {
    Object::Forward(fX, fY, fZ);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Up(float fX, float fY, float fZ)
  {
    Object::Up(fX, fY, fZ);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::Right(float fX, float fY, float fZ)
  {
    Object::Right(fX, fY, fZ);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::SetAmbient(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpAmbient->R(fRed);
    mpAmbient->G(fGreen);
    mpAmbient->B(fBlue);
    mpAmbient->A(1.0F);

    glLightfv(meLightID, GL_AMBIENT, mpAmbient->Array());
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::SetAmbient(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetAmbient(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::SetDiffuse(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpDiffuse->R(fRed);
    mpDiffuse->G(fGreen);
    mpDiffuse->B(fBlue);
    mpDiffuse->A(1.0F);

    glLightfv(meLightID, GL_DIFFUSE, mpDiffuse->Array());
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::SetDiffuse(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetDiffuse(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

    //*************************************************************************//
  void Light::SetSpecular(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpSpecular->R(fRed);
    mpSpecular->G(fGreen);
    mpSpecular->B(fBlue);
    mpSpecular->A(1.0F);

    glLightfv(meLightID, GL_SPECULAR, mpSpecular->Array());
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::SetSpecular(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetSpecular(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::TurnLightOn()
  {
    //-----------------------------------------------------------------------//
    if(this->mbLightOn == false)
    {
      this->mbLightOn = true;
      glEnable(meLightID);
    }

    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Light::TurnLightOff()
  {
    //-----------------------------------------------------------------------//
    if(this->mbLightOn == true)
    {
      this->mbLightOn = false;
      glDisable(meLightID);
    }
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//
}
//***************************************************************************//