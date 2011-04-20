//***************************************************************************//
// Object Class Interface
//
// Created: February 1, 2007
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

#ifndef HABU_GRAPHICS_OBJECT_HPP
#define HABU_GRAPHICS_OBJECT_HPP

//***************************************************************************//
// BlueHabu Technologies Includes
#include <HabuMath.hpp>
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // Object is the base class for all objects in a 3D scene
  class Object
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  protected:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // Describes the position of the object.
    HabuTech::Vector<float, 4> mPosition; // Position is a vector so we can use HabuMath's Dot function
    HabuTech::Vector<float, 4> mForwardVector;
    HabuTech::Vector<float, 4> mRightVector;
    HabuTech::Vector<float, 4> mUpVector;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    float mfPitch;
    float mfYaw;
    float mfRoll;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    HabuTech::Matrix<float, 4> mTransformMatrix;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void TransformToModelSpace();
    void TransformToViewSpace();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    /// Name of object
    std::string mstrName;
    //-----------------------------------------------------------------------//
    
    void Create(const std::string& rstrName);
    void Clone(const Object& rSource);
    void Destroy();
    
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Object(const std::string& rstrName);
    Object(const Object& rSource);
    Object(const Object& rSource, const std::string& rStrDestinationname);
    virtual ~Object();
    //-----------------------------------------------------------------------//

    Object& Object::operator=(const Object& rSource)
    {
      if(this != &rSource)
      {
        Clone(rSource);
      }
      return *this;
    }

    //-----------------------------------------------------------------------//
    const std::string& Name() const { return mstrName; } 
    void Name(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual void RelativePitch(float fAngle);
    virtual void RelativeRoll(float fAngle);
    virtual void RelativeYaw(float fAngle);

    virtual void AbsolutePitch(float fAngle);
    virtual void AbsoluteRoll(float fAngle);
    virtual void AbsoluteYaw(float fAngle);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual void _cdecl Position(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual void Move(float fX, float fY, float fZ);
    /// Moves the object left or right relative to its current orientation
    virtual void Strafe(float fX);
    /// Moves the object forward or backwards relative to its current orientation
    virtual void Advance(float fZ);
    /// Moves the object up or down relative to its current orientation
    virtual void Elevate(float fY);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    virtual void Forward(float fX, float fY, float fZ);
    virtual void Up(float fX, float fY, float fZ);
    virtual void Right(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Object
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_OBJECT_HPP