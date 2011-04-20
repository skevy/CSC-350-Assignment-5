//***************************************************************************//
// Material Class Implementation
//
// Created July 06, 2008
// By: Jeremy M Miller
//
// Copyright (c) 2008-2010 Jeremy M Miller.  All rights reserved.
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
#include <GL\glew.h> // Must be called before GL.h
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

// Local Includes
#include "Utility.hpp"
#include "Material.hpp"
//***************************************************************************//

//***************************************************************************//
#define NUMBER_OF_MATERIAL_PARAMETERS 3
#define DIFFUSE_COLOR_LABEL  "Diffuse"
#define AMBIENT_FACTOR_LABEL "Ambient"
#define SPECULAR_COLOR_LABEL "Specular"
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //-------------------------------------------------------------------------//
  Material::Material(const std::string& rstrName)
  {
    this->mpAmbient = new Color<float>(1.0, 1.0, 1.0, 1.0);
    this->mpDiffuse = new Color<float>(1.0, 1.0, 1.0, 1.0);
    this->mpSpecular = new Color<float>(1.0, 1.0, 1.0, 1.0);
    this->mfSpecularPower = 8.0F;

    assert(rstrName.size());
    if(rstrName.size())
      this->mstrName = rstrName;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Material::~Material()
  {
    delete this->mpAmbient;
    delete this->mpDiffuse;
    delete this->mpSpecular;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  const std::string& Material::Name() const
  {
    return this->mstrName;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  bool Material::Load(std::ifstream& ifs)
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
    for(unsigned short i = 0; i < NUMBER_OF_MATERIAL_PARAMETERS; i++)
    {
      //---------------------------------------------------------------------//
      // Read in the label
      ifs >> strLabel;
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // Match the label to some predefined token and set the proper data member.
      float fR, fG, fB, fA;
      if(strLabel == DIFFUSE_COLOR_LABEL)
      {
        ifs >> fR;
        ifs >> fG;
        ifs >> fB;
        ifs >> fA;
        this->SetDiffuse(fR, fG, fB);
        usParameterCount++;
      }
      else if(strLabel == AMBIENT_FACTOR_LABEL)
      {
        float fAmbientFactor;
        ifs >> fAmbientFactor;
        this->SetAmbient(this->mpDiffuse->R() * fAmbientFactor, 
                         this->mpDiffuse->G() * fAmbientFactor,
                         this->mpDiffuse->B() * fAmbientFactor);
        usParameterCount++;
      }
      else if(strLabel == SPECULAR_COLOR_LABEL)
      {
        ifs >> fR;
        ifs >> fG;
        ifs >> fB;
        ifs >> fA;
        this->SetSpecular(fR, fG, fB);
        usParameterCount++;
      } // End of if-else chain that matches the read in label 
      // to predefined token.
      //---------------------------------------------------------------------//
    } // End of for(unsigned short i = 0; i < NUMBER_OF_CAMERA_PARAMETERS; i++)
    //-----------------------------------------------------------------------//

    assert(usParameterCount == NUMBER_OF_MATERIAL_PARAMETERS);
    return (usParameterCount == NUMBER_OF_MATERIAL_PARAMETERS);
  }
  //-------------------------------------------------------------------------//


  //*************************************************************************//
  void Material::SetAmbient(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpAmbient->R(fRed);
    mpAmbient->G(fGreen);
    mpAmbient->B(fBlue);
    mpAmbient->A(1.0F);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetAmbient(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetAmbient(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetDiffuse(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpDiffuse->R(fRed);
    mpDiffuse->G(fGreen);
    mpDiffuse->B(fBlue);
    mpDiffuse->A(1.0F);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetDiffuse(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetDiffuse(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetSpecular(float fRed, float fGreen, float fBlue)
  {
    //-----------------------------------------------------------------------//
    mpSpecular->R(fRed);
    mpSpecular->G(fGreen);
    mpSpecular->B(fBlue);
    mpSpecular->A(0.0F);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  void Material::SetSpecular(float faColor[3])
  {
    //-----------------------------------------------------------------------//
    SetSpecular(faColor[0], faColor[1], faColor[2]);
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //-------------------------------------------------------------------------//
  void Material::Render()
  {
    glMaterialfv(GL_FRONT, GL_AMBIENT,  this->mpAmbient->Array());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  this->mpDiffuse->Array());
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->mpSpecular->Array());
  }
  //-------------------------------------------------------------------------//
}
//***************************************************************************//

