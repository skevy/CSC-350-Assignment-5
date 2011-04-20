//***************************************************************************//
// Font Class Implementation
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
// System Includes
#include <assert.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "HabuGraphics.hpp"
//***************************************************************************//

#define MAX_LENGTH_OF_STRING 65535 // 2^16 - 1 (for null)

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  Font::Font()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  Font::~Font()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  void Font::SetString(const std::string& str)
  {
    assert(str.size() <= MAX_LENGTH_OF_STRING);
    

    if(str.size() > MAX_LENGTH_OF_STRING)
    {
      // get how much to remove 
      // Doing cast of str.size() since no string should 
      // be longer than 2^32 in length.
      std::string strTemp = str;
      assert(str.size() > 0xFFFFFFFF);
      unsigned long ulRemove = (unsigned long)(strTemp.size()) - MAX_LENGTH_OF_STRING;
      strTemp.erase(strTemp.end() - ulRemove, strTemp.end());
      this->mstrText = strTemp;
    }
    else
      this->mstrText = str;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Font::SetString(char* cpStr, unsigned short usLength)
  {
    assert(usLength <=  MAX_LENGTH_OF_STRING);

    if(this->mstrText.size() > 0)
      this->mstrText.erase(mstrText.begin(), mstrText.end());

    // check for null
    if(strnlen(cpStr, usLength) <= MAX_LENGTH_OF_STRING)
     this->mstrText = cpStr;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Font::SetPosition(unsigned short usX, unsigned short usY)
  {
    // TODO bound check
    //mRect.top = usY;
    //mRect.left = usX;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Font::Draw()
  {
    //if(mstrText.size() > 0 && mbRender)
    //{
    //  // The below call returns 0 on error.
    //  int iResult = mpFont->DrawText(0, (LPCSTR)this->mstrText.c_str(), -1, (LPRECT)&mRect, DT_NOCLIP, D3DCOLOR_XRGB(255,0,0));
    //  assert(iResult != 0);
    //}
  }
  //*************************************************************************//
}
//***************************************************************************//