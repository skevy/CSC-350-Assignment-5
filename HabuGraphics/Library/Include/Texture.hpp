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

#ifndef HABU_GRAPHICS_TEXTURE_HPP
#define HABU_GRAPHICS_TEXTURE_HPP

//***************************************************************************//
// System Includes
#include <string>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Surface.hpp"
#include "Utility.hpp"
//***************************************************************************//
	
using namespace std;
	
//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  enum TextureType
  {
    TGA_TEXTURE_TYPE,
    NO_TEXTURE_TYPE
  };
  //*************************************************************************//

  //*************************************************************************//
  class Texture : public Surface
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    
    //-----------------------------------------------------------------------//

    //***********************************************************************//
  protected:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    
    /// Depth of color 
    unsigned char mucDepthInBytes;
    unsigned char mucDepthInBits;
    /// Width of texture
    unsigned short musWidth;
    /// Height of texture
    unsigned short musHeight;

    // Buffer that holds the color map
    Color<unsigned char>* mpImage;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    enum TextureType meTextureType;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // To store texture binding
    unsigned long mulTextureBinding;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    std::string mstrName;
    std::string mstrTextureFileName;
    
    /// Creates space in mucpImage for the color map
    void GenerateTexture();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Texture(const string& strName);
    Texture();
    virtual ~Texture();
    //-----------------------------------------------------------------------//

    const std::string& Name() const;

    //-----------------------------------------------------------------------//
    unsigned long Binding() {return mulTextureBinding;}
    //-----------------------------------------------------------------------//

    bool Load(std::ifstream& ifs);
    
    //-----------------------------------------------------------------------//
    // Binds the the current texture to make it active
    void Bind() const;
    void Unbind() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void Initialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// The below methods are getters for this classes private members
    /// The const keyword is not needed for Width(), Height(), Depth() but 
    /// it signifies that these methods are read only getters
    unsigned char DepthInBits()    const;
    unsigned char DepthInBytes()   const;
    unsigned short Width()   const;
    unsigned short Height()  const;
    
    /// Returns the a pointer to the image buffer
    Color<unsigned char>* Image()   const;
    //-----------------------------------------------------------------------//

    void Render();
    //***********************************************************************//
  }; // End of class Texture : public Surface
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_TEXTURE_HPP