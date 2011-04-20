//***************************************************************************//
// Texture Class Implementation
//
// Created Mar 06, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2006 Jeremy M Miller.  All rights reserved.
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
// along with HabuThreads.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

//***************************************************************************//
#include <windows.h>

#include <GL\GL.h>

#include <assert.h>
#include <stdio.h>

#include <fstream>
#include <sstream>
#include <string>

#include "Texture.hpp"
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
#define DEFAULT_TEXTURE_WIDTH  32  // Pixels
#define DEFAULT_TEXTURE_HEIGHT 32  // Pixels
#define DEFAULT_TEXTURE_DEPTH  4   // Bytes

#define NUMBER_OF_TEXTURE_PARAMETERS 2


#define TEXTURE_TYPE_LABEL     "Type"
#define TEXTURE_FILE_LABEL     "File"
//***************************************************************************//

using namespace std;

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  Texture::Texture(const string& strName)
  {
    this->mstrName = strName;
    //-----------------------------------------------------------------------//
    mpImage          = NULL;
    musWidth           = DEFAULT_TEXTURE_WIDTH;
    musHeight          = DEFAULT_TEXTURE_HEIGHT;
    mucDepthInBytes    = DEFAULT_TEXTURE_DEPTH;

    meTextureType = NO_TEXTURE_TYPE;
    
    glGenTextures(1, reinterpret_cast<GLuint*>(&mulTextureBinding));
    
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//
  
  //*************************************************************************//
  Texture::Texture()
  {
    //-----------------------------------------------------------------------//
    mpImage          = NULL;
    musWidth           = DEFAULT_TEXTURE_WIDTH;
    musHeight          = DEFAULT_TEXTURE_HEIGHT;
    mucDepthInBytes    = DEFAULT_TEXTURE_DEPTH;

    meTextureType = NO_TEXTURE_TYPE;
    //-----------------------------------------------------------------------//
  }
  //*************************************************************************//

  //*************************************************************************//
  Texture::~Texture()
  {
    glDeleteTextures(1, reinterpret_cast<GLuint*>(&mulTextureBinding));
    
    if(this->mpImage)
      delete [] this->mpImage;
  }
  //*************************************************************************//

  bool Texture::Load(ifstream& ifs) {
      assert(ifs.is_open() && ifs.good());
      
      if(!ifs.is_open() || !ifs.good())
          return false;
          
      string strLabel;
      
      unsigned short usParameterCount = 0;
      
      for(unsigned short i = 0; i < NUMBER_OF_TEXTURE_PARAMETERS; i++) {
          ifs >> strLabel;
          
          if(strLabel == TEXTURE_TYPE_LABEL) {
              string strType;
              ifs >> strType;
              if(strType == "TGA") {
                  this->meTextureType = TGA_TEXTURE_TYPE;
              } else if (strType == "Target") {
                  usParameterCount++;
              }
              usParameterCount++;
          } else if (strLabel == TEXTURE_FILE_LABEL) {
              string strFilename;
              ifs >> strFilename;
              usParameterCount++;
          }
      }
      
      assert(usParameterCount == NUMBER_OF_TEXTURE_PARAMETERS);
      return (usParameterCount == NUMBER_OF_TEXTURE_PARAMETERS);
  }
  
  const std::string& Texture::Name() const
  {
    return this->mstrName;
  }

  //*************************************************************************//
  void Texture::Bind() const
  {
      glBindTexture(GL_TEXTURE_2D, this->mulTextureBinding);
  }
  //*************************************************************************//

  //*************************************************************************//
  void Texture::Unbind() const
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  void Texture::GenerateTexture()
  {
   
  }
  //*************************************************************************//

  void Texture::Render()
  {
    this->Bind();
  }

  //*************************************************************************//
  void Texture::Initialize()
  {
      this->Bind();
      glTexImage2D(GL_TEXTURE_2D, 0, 4, Texture::musWidth, Texture::musHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture::mpImage);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT  );
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT  );
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned char Texture::DepthInBytes()   const
  {
    return mucDepthInBytes;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned char Texture::DepthInBits()   const
  {
    return mucDepthInBits;;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned short Texture::Width()   const
  {
    return musWidth;
  }
  //*************************************************************************//

  //*************************************************************************//
  unsigned short Texture::Height()  const
  {
    return musHeight;
  }
  //*************************************************************************//

  //*************************************************************************//
  Color<unsigned char>* Texture::Image()   const
  {
    return mpImage;
  }
  //*************************************************************************//
}
//***************************************************************************//