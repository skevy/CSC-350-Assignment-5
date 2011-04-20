//***************************************************************************//
// Surface Class Interface
//
// Created Dec 10, 2005
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

#ifndef HABU_GRAPHICS_SURFACE_HPP
#define HABU_GRAPHICS_SURFACE_HPP

//***************************************************************************//
// System Includes
#include <vector>
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // Base classes for all surfaces. I call anything that "fills" any polygon
  // a surface
  class Surface
  {
  private:
    //***********************************************************************//
    // No private members
    //***********************************************************************//
  protected:
    //***********************************************************************//
    class Material* mpActiveMaterial;

    std::vector<class Material*> mvMaterials;
    std::vector<class Texture*>  mvTextures;

    void RenderMaterial();
    void RenderTextures();
    //***********************************************************************//
  public:
    //***********************************************************************//
    /// Both the constructor and the destructor do nothing
    Surface();
    Surface(const Surface& rSource);
    virtual ~Surface();

    void Create();

    void Destroy();

    void Clone(const Surface& rSource);

    //-----------------------------------------------------------------------//
    bool AddMaterial(class Material* pMaterial);
    bool AddTexture(class Texture* pTexture);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void Render();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Surface
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_SURFACE_HPP