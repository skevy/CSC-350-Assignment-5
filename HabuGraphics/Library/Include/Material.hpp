//***************************************************************************//
// Material Class Interface
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

#ifndef HABU_GRAPHICS_MATERIAL_HPP
#define HABU_GRAPHICS_MATERIAL_HPP

#include "Utility.hpp"

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  class Material
  {
  private:
    //***********************************************************************//

    std::string mstrName;

    //***********************************************************************//
  public:
    //***********************************************************************//
    Material(const std::string& rstrName);
    ~Material();

    Color<float>* mpAmbient;
    Color<float>* mpDiffuse;
    Color<float>* mpSpecular;
    float mfSpecularPower;
    //***********************************************************************//

    const std::string& Name() const;

    //-----------------------------------------------------------------------//
    bool Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void SetAmbient(float fRed, float fGreen, float fBlue);
    void SetAmbient(float faColor[3]);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void SetDiffuse(float fRed, float fGreen, float fBlue);
    void SetDiffuse(float faColor[3]);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void SetSpecular(float fRed, float fGreen, float fBlue);
    void SetSpecular(float faColor[3]);
    //-----------------------------------------------------------------------//
    
    void Render();
  }; // End of class Material
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_MATERIAL_HPP

