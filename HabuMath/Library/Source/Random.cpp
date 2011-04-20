//***************************************************************************//
// Random Class Implementation
//
// Created: April 14, 2007
// By: Jeremy M Miller
//
// Copyright (c) 2007 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//
// Usage of HabuMath is subject to the appropriate license agreement.
// A proprietary/commercial licenses are available. (info@bluehabu.com)
//                 
// HabuMath is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HabuMath is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HabuThreads.  If not, see <http://www.gnu.org/licenses/>.
//***************************************************************************//

//***************************************************************************//
#include "Random.hpp"
//***************************************************************************//

//***************************************************************************//
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //-------------------------------------------------------------------------//
  // To see why I do this you can visit this site http://www.bluehabu.com/?p=8
  // TODO rational types do not work.
  //template class Random<unsigned char>;
  //template class Random<char>;
  //template class Random<unsigned short>;
  //template class Random<short>;
  //template class Random<unsigned long>;
  //template class Random<long>;
  //template class Random<unsigned long long>;
  //template class Random<long long>;
  template class Random<float>;
  template class Random<double>;
  template class Random<long double>;
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  template <class T>
  Random<T>::Random()
  {
    // TODO Come up with a better seed generation.
    srand(rand() * time(0)); 
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  template <class T>
  Random<T>::~Random()
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  template <class T>
  T Random<T>::Generate()
  {
    return rand()/T(RAND_MAX); 
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  template <class T>
  T Random<T>::Generate(T tMax)
  {
    return (T)(tMax * rand()/T(RAND_MAX));
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  template <class T>
  T Random<T>::Generate(T tMin, T tMax)
  {
    assert(tMin < tMax);  // Why is your min greater or equal to your max
    if(tMin > tMax)
    {
      return tMax + T((tMin - tMax) * rand()/T(RAND_MAX)); 
    }
    return tMin + T((tMax - tMin) * rand()/T(RAND_MAX));
  }
  //-------------------------------------------------------------------------//
} // End of namespace HabuTech
//***************************************************************************//
