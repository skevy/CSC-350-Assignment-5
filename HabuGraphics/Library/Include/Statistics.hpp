//***************************************************************************//
// Statistics Class Interface
//
// Created Aug 17, 2006
// By: Jeremy M Miller
//
// Copyright (c) 2006-2010 Jeremy M Miller.  All rights reserved.
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

#ifndef HABU_GRAPHICS_STATISTICS_HPP
#define HABU_GRAPHICS_STATISTICS_HPP

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  class Font;
  //*************************************************************************//

  //*************************************************************************//
  class Statistics
  {
  private:
    //***********************************************************************//
    class Font* mpFont;

    float fET;
    float faDT[5];
    float fDT_sum;
    //***********************************************************************//
  public:
    //***********************************************************************//
    Statistics(class Graphics* pGraphics);
    ~Statistics();

    void Display(float fDT);
    float AverageFPS() { return fDT_sum/5.0F; }
    //***********************************************************************//
  }; // End of class Statistics
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_STATISTICS_HPP