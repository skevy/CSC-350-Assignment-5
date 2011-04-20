//***************************************************************************//
// Cylinder Class Implementation
//
// Created Feb 1, 2007
// By: Jeremy M Miller
//
// Copyright (c) 2007-2010 Jeremy M Miller.  All rights reserved.
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
#include "Cylinder.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //-------------------------------------------------------------------------//
  Cylinder::Cylinder(const std::string& strName, class Scene* const pScene) : Mesh(strName, pScene)
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  Cylinder::~Cylinder()
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Cylinder::Render()
  {

  }
  //-------------------------------------------------------------------------//
}// End of namespace HabuTech
//***************************************************************************//