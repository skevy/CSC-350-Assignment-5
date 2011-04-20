//***************************************************************************//
// Object Class Implementation
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
#include "Object.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //-------------------------------------------------------------------------//
  Object::Object(const std::string& rstrName)
  {
    Create(rstrName);
  }
  //-------------------------------------------------------------------------//

  Object::Object(const Object& rSource)
  {
    Create(rSource.Name());
    Clone(rSource);
  }

  Object::Object(const Object& rSource, const std::string& rstrDestinationName)
  {
    Create(rstrDestinationName);
    Clone(rSource);
  }

  //-------------------------------------------------------------------------//
  Object::~Object()
  {
    try
    {
      Destroy();
    }
    catch(...)
    {
    }
  }
  //-------------------------------------------------------------------------//

  void Object::Create(const std::string &rstrName)
  {
    //-----------------------------------------------------------------------//
    mfPitch = 0.0F;
    mfYaw   = 0.0F;
    mfRoll  = 0.0F;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    mPosition.Set     (0.0F, 0.0F, 0.0F); 
    mRightVector.Set  (1.0F, 0.0F, 0.0F);
    mUpVector.Set     (0.0F, 1.0F, 0.0F);
    mForwardVector.Set(0.0F, 0.0F, 1.0F);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    mstrName = rstrName;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    mTransformMatrix.Identity();
    //-----------------------------------------------------------------------//
  }

  void Object::Destroy()
  {
  }

  void Object::Clone(const Object& rSource)
  {
    this->mPosition = rSource.mPosition;
    this->mForwardVector = rSource.mForwardVector;
    this->mRightVector = rSource.mRightVector;
    this->mUpVector = rSource.mUpVector;

    this->mfPitch = rSource.mfPitch;
    this->mfYaw = rSource.mfYaw;
    this->mfRoll = rSource.mfRoll;

    this->mTransformMatrix = rSource.mTransformMatrix;
  }

  //-------------------------------------------------------------------------//
  void Object::Name(const std::string& rstrName)
  {
    this->mstrName = rstrName;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Position(float fX, float fY, float fZ)
  {
    mPosition.Set(fX, fY, fZ);
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Move(float fX, float fY, float fZ)
  {
    mPosition.rX() += fX;
    mPosition.rY() += fY;
    mPosition.rZ() += fZ;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::RelativePitch(float fAngle)
  {
    this->mfPitch = fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::RelativeRoll(float fAngle)
  {
    this->mfRoll = fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::RelativeYaw(float fAngle)
  {
    this->mfYaw = fAngle;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::AbsolutePitch(float fAngle)
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::AbsoluteRoll(float fAngle)
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::AbsoluteYaw(float fAngle)
  {
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Strafe(float fVelocity)
  {
	  this->mPosition.X(this->mPosition.X() + (this->mRightVector.X() * fVelocity));
	  this->mPosition.Z(this->mPosition.Z() + (this->mRightVector.Z() * fVelocity));
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Advance(float fVelocity)
  {
    this->mPosition.X(this->mPosition.X() + (this->mForwardVector.X() * fVelocity));
	  this->mPosition.Z(this->mPosition.Z() + (this->mForwardVector.Z() * fVelocity));
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Elevate(float fVelocity)
  {
    this->mPosition.X(this->mPosition.X() + (this->mUpVector.X() * fVelocity));
	  this->mPosition.Y(this->mPosition.Y() + (this->mUpVector.Y() * fVelocity));
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Forward(float fX, float fY, float fZ)
  {
    this->mForwardVector.X(fX);
    this->mForwardVector.Y(fY);
    this->mForwardVector.Z(fZ);
    this->mForwardVector.Normalize();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Up(float fX, float fY, float fZ)
  {
    this->mUpVector.X(fX);
    this->mUpVector.Y(fY);
    this->mUpVector.Z(fZ);
    this->mUpVector.Normalize();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::Right(float fX, float fY, float fZ)
  {
    this->mRightVector.X(fX);
    this->mRightVector.Y(fY);
    this->mRightVector.Z(fZ);
    this->mRightVector.Normalize();
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::TransformToModelSpace()
  {
    HabuTech::Matrix<float, 4> oTempMatrix;

    oTempMatrix.RotateAboutX(mfPitch);
    oTempMatrix.RotateAboutY(mfYaw);
    oTempMatrix.RotateAboutZ(mfRoll);

    mfYaw = 0.0F;
    mfRoll = 0.0F;
    mfPitch = 0.0F;

    this->mRightVector.  Transform(oTempMatrix);
    this->mUpVector.     Transform(oTempMatrix);
    this->mForwardVector.Transform(oTempMatrix);

    this->mRightVector.  Cross(this->mUpVector,       this->mForwardVector);
    this->mUpVector.     Cross(this->mForwardVector,  this->mRightVector);
    this->mForwardVector.Cross(this->mRightVector,    this->mUpVector);

    this->mRightVector.Normalize();
    this->mUpVector.Normalize();
    this->mForwardVector.Normalize();
    
    this->mTransformMatrix[0][0] = this->mRightVector.X();
    this->mTransformMatrix[1][0] = this->mUpVector.X();
    this->mTransformMatrix[2][0] = this->mForwardVector.X();
    this->mTransformMatrix[3][0] = 0.0F;

    this->mTransformMatrix[0][1] = this->mRightVector.Y();
    this->mTransformMatrix[1][1] = this->mUpVector.Y();
    this->mTransformMatrix[2][1] = this->mForwardVector.Y();
    this->mTransformMatrix[3][1] = 0.0F;

    this->mTransformMatrix[0][2] = this->mRightVector.Z();
    this->mTransformMatrix[1][2] = this->mUpVector.Z();
    this->mTransformMatrix[2][2] = this->mForwardVector.Z();
    this->mTransformMatrix[3][2] = 0.0F;

    this->mTransformMatrix[0][3] = this->mPosition.X();
    this->mTransformMatrix[1][3] = this->mPosition.Y();
    this->mTransformMatrix[2][3] = this->mPosition.Z();
    this->mTransformMatrix[3][3] = 1.0F;
  }
  //-------------------------------------------------------------------------//

  //-------------------------------------------------------------------------//
  void Object::TransformToViewSpace()
  {
    HabuTech::Matrix<float, 4> oTempMatrix;

    oTempMatrix.RotateAboutX(mfPitch);
    oTempMatrix.RotateAboutY(mfYaw);
    oTempMatrix.RotateAboutZ(mfRoll);

    mfYaw = 0.0F;
    mfRoll = 0.0F;
    mfPitch = 0.0F;

    this->mRightVector.  Transform(oTempMatrix);
    this->mUpVector.     Transform(oTempMatrix);
    this->mForwardVector.Transform(oTempMatrix);

    this->mRightVector.  Cross(this->mForwardVector,  this->mUpVector);
    this->mUpVector.     Cross(this->mRightVector,    this->mForwardVector);
    this->mForwardVector.Cross(this->mUpVector,       this->mRightVector);

    this->mRightVector.  Normalize();
    this->mUpVector.     Normalize();
    this->mForwardVector.Normalize();

    this->mTransformMatrix[0][0] = this->mRightVector.X();
    this->mTransformMatrix[1][0] = this->mRightVector.Y();
    this->mTransformMatrix[2][0] = this->mRightVector.Z();
    this->mTransformMatrix[3][0] = -(this->mPosition.Dot(this->mRightVector));

    this->mTransformMatrix[0][1] = this->mUpVector.X();
    this->mTransformMatrix[1][1] = this->mUpVector.Y();
    this->mTransformMatrix[2][1] = this->mUpVector.Z();
    this->mTransformMatrix[3][1] = -(this->mPosition.Dot(this->mUpVector));

    this->mTransformMatrix[0][2] = this->mForwardVector.X();
    this->mTransformMatrix[1][2] = this->mForwardVector.Y();
    this->mTransformMatrix[2][2] = this->mForwardVector.Z();
    this->mTransformMatrix[3][2] = -(this->mPosition.Dot(this->mForwardVector));

    this->mTransformMatrix[0][3] = 0.0F;
    this->mTransformMatrix[1][3] = 0.0F; 
    this->mTransformMatrix[2][3] = 0.0F;
    this->mTransformMatrix[3][3] = 1.0F;

    return;
  }
  //-------------------------------------------------------------------------//
}// End of namespace HabuTech
//***************************************************************************//