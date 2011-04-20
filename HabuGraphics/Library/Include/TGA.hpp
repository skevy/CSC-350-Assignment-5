//***************************************************************************//
// Texture Class Interface
//
// Created May 13, 2005
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

#ifndef HABU_GRAPHICS_TGA_HPP
#define HABU_GRAPHICS_TGA_HPP

//***************************************************************************//
// System Includes
#include <string>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Texture.hpp"
//***************************************************************************//
	
using namespace std;
	
//***************************************************************************//
namespace HabuTech
{

  //*************************************************************************//
  class TGA : public Texture
  {
  private:
    //-----------------------------------------------------------------------//
    unsigned char mcID_Length;
    unsigned char mcColorMapType;
    unsigned char mcDataTypeCode;
    unsigned char* msColorMapOrigin;
    unsigned char* msColorMapLength;
    unsigned char mcColorMapDepth;
    unsigned char* msX_Origin;
    unsigned char* msY_Origin;
    unsigned short msWidth;
    unsigned short msHeight;
    
    unsigned char mcBitsPerPixel;
    unsigned char mcImageDescription;
    
    //***********************************************************************//
  protected:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    /// Creates space in mucpImage for the color map
    void GenerateTexture();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    TGA(const std::string& name);
    virtual ~TGA();
    //-----------------------------------------------------------------------//

    bool Load(std::ifstream& ifs);

    bool Deserialize(unsigned char* cpHeader);
    //-----------------------------------------------------------------------//

    void Render() {};
    //***********************************************************************//
  }; // End of class Texture : public Surface
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_TGA_HPP