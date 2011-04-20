//***************************************************************************//
// Statistics Class Implementation
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

//***************************************************************************//
#include <sstream>
#include <string>

#include "Font.hpp"
#include "Statistics.hpp"
#include "HabuGraphics.hpp"
//***************************************************************************//

//***************************************************************************//
#define TIME_BETWEEN_UPDATES 1.0F
#define X_PIXEL_POSITION 5
#define Y_PIXEL_POSITION 5
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  Statistics::Statistics(class Graphics* pGraphics)
  {
    //-----------------------------------------------------------------------//
    mpFont = NULL;
    mpFont->SetPosition(X_PIXEL_POSITION, Y_PIXEL_POSITION);
    mpFont->SetString("", 0L);
    //-----------------------------------------------------------------------//
    
    //-----------------------------------------------------------------------//
    fET = 0.0F;
    fDT_sum = 0.0F;
    faDT[0] = 0.0F;
    faDT[1] = 0.0F;
    faDT[2] = 0.0F;
    faDT[3] = 0.0F;
    faDT[4] = 0.0F;
    //-----------------------------------------------------------------------//
  } // End of Statistics::Statistics()
  //*************************************************************************//

  //*************************************************************************//
  Statistics::~Statistics()
  {
    if(mpFont)
      delete mpFont;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Statistics::Display(float fDT)
  {
    fET += fDT;

    if(mpFont)
    {
      if(fET > TIME_BETWEEN_UPDATES)
      {
        fDT_sum -= faDT[4];
        faDT[4] = faDT[3];
        faDT[3] = faDT[2];
        faDT[2] = faDT[1];
        faDT[1] = faDT[0];
        faDT[0] = fDT;
        fDT_sum += fDT;

        fET = 0.0F;
        stringstream sstmFPS;
        sstmFPS << "Frames Per Second: ";
        sstmFPS << 1.0F/(fDT_sum/5.0F);
        mpFont->SetString(sstmFPS.str());
      }
    }
    return;
  } // End of void Statistics::Display(float fDT)
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//