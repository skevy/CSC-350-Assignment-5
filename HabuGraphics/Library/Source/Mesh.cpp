//***************************************************************************//
// Mesh Class Implementation
//
// Created Aug 8, 2005
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

//***************************************************************************//
// 3rd Party Includes
#include <GL\glew.h> // Must be called before GL.h
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <cmath>
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <fstream>
#include <sstream>
#include <string>
//***************************************************************************//

//***************************************************************************//
//Local Includes
#include "HabuGraphics.hpp"
#include "Surface.hpp"
//***************************************************************************//

#include <HabuMath.hpp>

//***************************************************************************//
#define LOCATION_LABEL "Loc"
//***************************************************************************//

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  BoundingVolume::BoundingVolume()
  {
    Create();
  }

  BoundingVolume::BoundingVolume(const BoundingVolume& rSource)
  {
    Clone(rSource);
  }

  BoundingVolume::~BoundingVolume()
  {
    try
    {
      Destroy();
    }
    catch(...)
    {

    }
  }

  void BoundingVolume::Create()
  {
  }

  void BoundingVolume::Clone(const BoundingVolume& rSource)
  {
    this->mUpperFrontRight = rSource.mUpperFrontRight;
    this->mLowerBackLeft = rSource.mLowerBackLeft;
  }

  void BoundingVolume::Destroy()
  {

  }

  void BoundingVolume::Examine(const class Vertex& rVertex)
  {
    if(rVertex.mPosition.X() < this->mLowerBackLeft.X())
      this->mLowerBackLeft.X(rVertex.mPosition.X());
    else if(rVertex.mPosition.X() > this->mUpperFrontRight.X())
      this->mUpperFrontRight.X(rVertex.mPosition.X());

    if(rVertex.mPosition.Y() < this->mLowerBackLeft.Y())
      this->mLowerBackLeft.Y(rVertex.mPosition.Y());
    else if(rVertex.mPosition.Y() > this->mUpperFrontRight.Y())
      this->mUpperFrontRight.Y(rVertex.mPosition.Y());

    if(rVertex.mPosition.Z() < this->mLowerBackLeft.Z())
      this->mLowerBackLeft.Z(rVertex.mPosition.Z());
    else if(rVertex.mPosition.Z() > this->mUpperFrontRight.Z())
      this->mUpperFrontRight.Z(rVertex.mPosition.Z());
  }

  float BoundingVolume::Width() const
  {
    return fabs(this->mLowerBackLeft.X() - this->mUpperFrontRight.X());
  }

  float BoundingVolume::Height() const
  {
    return fabs(this->mLowerBackLeft.Y() - this->mUpperFrontRight.Y());
  }

  float BoundingVolume::Depth() const
  {
    return fabs(this->mLowerBackLeft.Z() - this->mUpperFrontRight.Z());
  }

  //*************************************************************************//
  Mesh::Mesh(const std::string& rstrName, class Scene* pScene) : Object(rstrName)
  {
    Create(rstrName, pScene);
  }
  //*************************************************************************//

  Mesh::Mesh(const Mesh& rSource) : Object(rSource)
  {
    Create(rSource.Name(), rSource.mpScene);
    Clone(rSource);
  }

  Mesh::Mesh(const Mesh& rSource, const std::string& rstrDestinationName) : Object(rSource, rstrDestinationName)
  {
    Create(rstrDestinationName, rSource.mpScene);
    Clone(rSource);
  }

  //*************************************************************************//
  Mesh::~Mesh()
  {
    try
    {
      Destroy();
    }
    catch(...)
    {
    }
  }
  //*************************************************************************//

  void Mesh::Create(const std::string& rstrName, class Scene* pScene)
  {
    this->mulNumberOfVertices = 0UL;
    this->mulNumberOfIndices = 0UL;
    this->mulNumberOfFaces = 0UL;

    this->mpScene = pScene;
    this->mpVertexArray = NULL;
    this->mpIndexArray = NULL;

    this->mpGeometryBuffer = NULL;

    this->mpSurface = new Surface();

    this->mpBoundingVolume = new BoundingVolume();

    mbWireFrame = false;
  }

  void Mesh::Destroy()
  {
    if(this->mpSurface)
      delete this->mpSurface;

    if(this->mpBoundingVolume)
      delete this->mpBoundingVolume;

    if(this->mpVertexArray != NULL)
      delete [] this->mpVertexArray;

    if(this->mpIndexArray != NULL)
      delete [] this->mpIndexArray;

    if(this->mpGeometryBuffer != NULL)
      delete this->mpGeometryBuffer;
  }

  void Mesh::Clone(const Mesh& rSource)
  {
    this->mpScene = rSource.mpScene;

    this->mulNumberOfFaces = rSource.mulNumberOfFaces;
    this->mulNumberOfVertices = rSource.mulNumberOfVertices;
    this->mulNumberOfIndices = rSource.mulNumberOfIndices;
    this->mulIndicesOffset = rSource.mulIndicesOffset;

    this->mpSurface = new Surface(*(rSource.mpSurface));
    
    this->mpVertexArray = new Vertex[rSource.mulNumberOfVertices];
    memcpy_s(this->mpVertexArray, this->mulNumberOfVertices, rSource.mpVertexArray, rSource.mulNumberOfVertices);

    this->mpGeometryBuffer = new GeometryBuffer(*(rSource.mpGeometryBuffer));

    this->mbWireFrame = rSource.mbWireFrame;

    this->mpBoundingVolume = new BoundingVolume(*(rSource.mpBoundingVolume));
  }

  //*************************************************************************//
  bool Mesh::Load(std::ifstream& ifs)
  {
    bool bReturnValue = false;

    //-----------------------------------------------------------------------//
    // Ensure the file stream passed into this method is open
    assert(ifs.is_open());
    if(ifs.is_open())
    {
      ifs >> mulNumberOfFaces;
      ifs >> mulNumberOfVertices;
      ifs >> mulNumberOfIndices;

      unsigned long ulArrayIndex = 0UL;
      unsigned long ulIndicesIndex = 0UL;

      //---------------------------------------------------------------------//
      if(this->mpIndexArray != NULL)
        delete [] this->mpIndexArray;

      this->mpIndexArray = new unsigned long[mulNumberOfIndices];
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // Clear vertex data is any exist and create a new buffer for this mesh
      if(this->mpVertexArray != NULL)
        delete [] this->mpVertexArray;

      this->mpVertexArray = new Vertex[mulNumberOfVertices];
      //---------------------------------------------------------------------//

      //this->muiVertexBufferID = 0;
      //this->muiIndexBufferID = 0;
      //if(mulNumberOfVertices > 0)
      //{
      //  glGenBuffersARB(1, static_cast<GLuint*>(&muiVertexBufferID));
      //  glGenBuffersARB(1, static_cast<GLuint*>(&muiIndexBufferID));
      //}

      while(!ifs.eof() && ((ulIndicesIndex < mulNumberOfIndices) || (ulArrayIndex < mulNumberOfVertices)))
      {
        string strLabel;
        ifs >> strLabel;
        if(strLabel == "Loc")
        {
          float fX, fY, fZ;
          ifs >> fX;
          ifs >> fY;
          ifs >> fZ;
          Object::Position(fX, fY, fZ);
        }
        else if(strLabel == "v")
        {
          ifs >> this->mpVertexArray[ulArrayIndex].mPosition.rX();
          ifs >> this->mpVertexArray[ulArrayIndex].mPosition.rY();
          ifs >> this->mpVertexArray[ulArrayIndex].mPosition.rZ();

          ifs >> strLabel;
          if(strLabel == "n")
          {
            ifs >> this->mpVertexArray[ulArrayIndex].mNormal.rX();
            ifs >> this->mpVertexArray[ulArrayIndex].mNormal.rY();
            ifs >> this->mpVertexArray[ulArrayIndex].mNormal.rZ();
            
            ifs >> strLabel;
            if(strLabel == "uv")
            {
                ifs >> this->mpVertexArray[ulArrayIndex].mTextureUV[0];
                ifs >> this->mpVertexArray[ulArrayIndex].mTextureUV[1];
            }
          }

          this->mpBoundingVolume->Examine(this->mpVertexArray[ulArrayIndex]);
          ulArrayIndex++;
        }
        else if(strLabel == "i")
        {
          ifs >> this->mpIndexArray[ulIndicesIndex];
          ulIndicesIndex++;
        }
        else if(strLabel == "Material")
        {
          string strMaterialName;
          ifs >> strMaterialName;
          Material* pMaterial = this->mpScene->GetMaterial(strMaterialName);
          assert(pMaterial);
          if(pMaterial)
          {
            this->mpSurface->AddMaterial(pMaterial);
          }
        }
        else if(strLabel == "Texture")
        {
          string strTextureName;
          ifs >> strTextureName;
          Texture* pTexture = this->mpScene->GetTexture(strTextureName);
          assert(pTexture);
          if(pTexture)
          {
            this->mpSurface->AddTexture(pTexture);
          }
        }
      }

      //if(this->muiVertexBufferID && this->muiIndexBufferID)
      //{
      //  glBindBuffer(GL_ARRAY_BUFFER, muiVertexBufferID);

      //  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mulNumberOfVertices, NULL, GL_STATIC_DRAW);
      //  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * mulNumberOfVertices, this->mpVertexArray); // Actually upload the data

      //  glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));
      //  glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
      //  glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));
      //  glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(40));

      //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, muiIndexBufferID); 
      //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mulNumberOfIndices * sizeof(unsigned long), this->mpIndexArray, GL_STATIC_DRAW);
      //  bReturnValue = true;
      //}

      bReturnValue = true;
    }
    //-----------------------------------------------------------------------//
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Mesh::Position(float fX, float fY, float fZ)
  {
    mPosition.Set(fX, fY, fZ);
  }
  //*************************************************************************//

  class Vertex* Mesh::VertexArray()
  {
    return this->mpVertexArray;
  }

  unsigned long* Mesh::IndexArray()
  {
    return this->mpIndexArray;
  }

  unsigned long Mesh::VertexCount() const
  {
    return this->mulNumberOfVertices;
  }

  unsigned long Mesh::IndexCount() const
  {
    return this->mulNumberOfIndices;
  }

  void Mesh::AssignBuffer(HabuTech::GeometryBuffer *const pBuffer, unsigned long ulOffset)
  {
    this->mpGeometryBuffer = pBuffer;
    this->mulIndicesOffset = ulOffset;
  }

  //*************************************************************************//
  void Mesh::SetLOD(unsigned long ulLOD)
  {

  }
  //*************************************************************************//

  //*************************************************************************//
  // Mesh::Render draws the mesh
  void Mesh::Render()
  {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    Object::TransformToModelSpace();

    GLfloat m[16];
    Object::mTransformMatrix.ColumnMajor(m);
    glMultMatrixf(m);

    assert(this->mpSurface);
    assert(this->mpGeometryBuffer);

    if(this->mpSurface && this->mpGeometryBuffer)
    {
      this->mpSurface->Render();

      this->mpGeometryBuffer->Bind();

      // Set the state of what we are drawing (I don't think order matters here, but I like to do it in the same 
      // order I set the pointers
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_VERTEX_ARRAY);

      // Actually do our drawing, parameters are Primitive (Triangles, Quads, Triangle Fans etc), Elements to 
      // draw, Type of each element, Start Offset
      glDrawElements(GL_TRIANGLES, this->mulNumberOfIndices, GL_UNSIGNED_INT, BUFFER_OFFSET(this->mulIndicesOffset * sizeof(unsigned long)));

      // Disable our client state back to normal drawing
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
    
      this->mpGeometryBuffer->UnBind();
    }

    glPopMatrix();
  }
  //*************************************************************************//
}

