//***************************************************************************//
// Scene Class Implementation
//
// Created Sept 04, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2010  Jeremy M Miller.  All rights reserved.
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
#include <fstream>
#include <string>
#include <sstream>
//***************************************************************************//

//***************************************************************************//
// Platform Includes
#include <Windows.h>
#include <GL\glew.h> // Must be called before GL.h
#include <GL\GL.h>
#include <GL\GLU.h>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Camera.hpp"
#include "Light.hpp"
#include "HabuGraphics.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "TGA.hpp"
#include "Scene.hpp"
//***************************************************************************//

//***************************************************************************//
using namespace std;
//***************************************************************************//

//***************************************************************************//
#define SCENE_LABEL    "Scene"
#define LIGHT_LABEL    "Light"
#define MATERIAL_LABEL "Material"
#define TEXTURE_LABEL  "Texture"
#define MESH_LABEL     "Mesh"
#define CAMERA_LABEL   "Camera"
#define NAME_LABEL     "Name"
#define TYPE_LABEL     "Type"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  GeometryBuffer::GeometryBuffer(const class Graphics* const pGraphics) {
    Create(pGraphics);
  }
  
  GeometryBuffer::GeometryBuffer(const GeometryBuffer& rSource) {
    Create(rSource.mpGraphics);
    Clone(rSource);
  }

  GeometryBuffer::~GeometryBuffer()
  {
    try
    {
      Destroy();
    }
    catch(...)
    {

    }
  }

  void GeometryBuffer::Create(const class Graphics* const pGraphics)
  {
    this->mpGraphics = pGraphics;

    this->muiIndexBufferID = 0;
    this->muiVertexBufferID = 0;

    this->muiMaxVertexSize = this->mpGraphics->MaxVertexBufferSize();
    this->muiMaxIndexSize = this->mpGraphics->MaxIndexBufferSize();

    this->mulIndexFreeElements = this->muiMaxIndexSize;
    this->mulVertexFreeElements = this->muiMaxVertexSize;
  }

  void GeometryBuffer::Clone(const GeometryBuffer& rSource)
  {
    this->mpGraphics = rSource.mpGraphics;
    
    this->muiVertexBufferID = rSource.muiVertexBufferID;
    this->muiIndexBufferID = rSource.muiIndexBufferID;
    
    this->mulVertexFreeElements = rSource.mulVertexFreeElements;
    this->mulIndexFreeElements = rSource.mulIndexFreeElements;

    this->muiMaxVertexSize = rSource.muiMaxVertexSize;
    this->muiMaxIndexSize = rSource.muiMaxIndexSize;
  }

  void GeometryBuffer::Destroy()
  {
    if(this->muiIndexBufferID)
      glDeleteBuffersARB(1, &this->muiIndexBufferID);

    if(this->muiVertexBufferID)
      glDeleteBuffersARB(1, &this->muiVertexBufferID);
  }

  unsigned long GeometryBuffer::VertexFreeElements() const
  {
    return this->mulVertexFreeElements;
  }

  unsigned long GeometryBuffer::IndexFreeElements() const
  {
    return this->mulIndexFreeElements;
  }

  unsigned long _cdecl GeometryBuffer::MaxVertexElements() const
  {
    return this->muiMaxVertexSize;
  }

  unsigned long _cdecl GeometryBuffer::MaxIndexElements() const
  {
    return this->muiMaxIndexSize;
  }

  unsigned long _cdecl GeometryBuffer::UsedVertexElements() const
  {
    return this->muiMaxVertexSize - this->mulVertexFreeElements;
  }

  unsigned long _cdecl GeometryBuffer::UsedIndexElements() const
  {
    return this->muiMaxIndexSize - this->mulIndexFreeElements;
  }

  unsigned long GeometryBuffer::Allocate(const HabuTech::Vertex *const pVerticies, unsigned long ulVerticiesLength, const unsigned long *const pIndicies, unsigned long ulIndiciesLength)
  {
    unsigned long ulReturnValue = ULONG_MAX;

    if((this->mulIndexFreeElements >= ulIndiciesLength) && (this->mulVertexFreeElements >= ulVerticiesLength))
    {
      if(this->muiIndexBufferID == 0 && this->muiVertexBufferID == 0)
      {
        glGenBuffersARB(1, static_cast<GLuint*>(&muiVertexBufferID));
        glGenBuffersARB(1, static_cast<GLuint*>(&muiIndexBufferID));

        glBindBufferARB(GL_ARRAY_BUFFER, this->muiVertexBufferID);
        glBufferDataARB(GL_ARRAY_BUFFER, sizeof(Vertex) * muiMaxVertexSize, NULL, GL_STATIC_DRAW_ARB);

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, this->muiIndexBufferID);
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, muiMaxIndexSize * sizeof(unsigned long), NULL, GL_STATIC_DRAW_ARB);
      }

      glBindBufferARB(GL_ARRAY_BUFFER, this->muiVertexBufferID);
      glBufferSubDataARB(GL_ARRAY_BUFFER, sizeof(Vertex) * (this->UsedVertexElements()), sizeof(Vertex) * ulVerticiesLength, pVerticies); 

      this->mulVertexFreeElements -= ulVerticiesLength;

      Vertex::DeclareVertex();

      glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, this->muiIndexBufferID);
      ulReturnValue = this->UsedIndexElements();
      glBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER, ulReturnValue * sizeof(unsigned long), ulIndiciesLength * sizeof(unsigned long), pIndicies);

      this->mulIndexFreeElements -= ulIndiciesLength;

      glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
      glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
    }

    return ulReturnValue;
  }

  void GeometryBuffer::Bind()
  {
    glBindBufferARB(GL_ARRAY_BUFFER, this->muiVertexBufferID);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, this->muiIndexBufferID);
  }

  void GeometryBuffer::UnBind()
  {
    glBindBufferARB(GL_ARRAY_BUFFER, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  //*************************************************************************//
  Scene::Scene(class Graphics* pGraphics)
  {
    mpGraphics = pGraphics;
  }
  //*************************************************************************//

  //*************************************************************************//
  Scene::~Scene()
  {
    for(unsigned long ulIndex = 0UL; ulIndex < this->mvMeshes.size(); ulIndex++)
    {
      delete this->mvMeshes[ulIndex];
    }
    this->mvMeshes.clear();

    for(unsigned long ulIndex = 0UL; ulIndex < this->mvLights.size(); ulIndex++)
    {
      delete this->mvLights[ulIndex];
    }
    this->mvLights.clear();

    for(unsigned long ulIndex = 0UL; ulIndex < this->mvCameras.size(); ulIndex++)
    {
      delete this->mvCameras[ulIndex];
    }
    this->mvCameras.clear();
    this->mpActiveCamera = NULL;

    for(unsigned long ulIndex = 0UL; ulIndex < this->mvMaterials.size(); ulIndex++)
    {
      delete this->mvMaterials[ulIndex];
    }
    this->mvMaterials.clear();

    for(unsigned long ulIndex = 0UL; ulIndex < this->mvTextures.size(); ulIndex++)
    {
      delete this->mvTextures[ulIndex];
    }
    this->mvTextures.clear();
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Scene::Load(std::ifstream& ifs)
  {
    bool bReturnValue = false;
    assert(ifs.is_open());

    if(!ifs.is_open())
      return bReturnValue;

    unsigned long ulLightCount = 0UL;

    while(!ifs.eof())
    {
      string strLine;
      getline(ifs, strLine);
      stringstream sstmLine(strLine);
      string strType;
      sstmLine >> strType;
      if(strType == CAMERA_LABEL)
      {
        // Get Camera Name
        string strName;
        sstmLine >> strName;
        class Camera* pCamera = this->CreateCamera(strName);
        if(!pCamera->Load(ifs))
        {
          this->DestroyCamera(strName);
        }
        // TODO Make sure each scene has at least one mesh, one camera and one light
        bReturnValue = true;
      }
      else if(strType == LIGHT_LABEL)
      {
        // Get Light Name
        string strName;
        sstmLine >> strName;
        enum LightID eID;
        if(ulLightCount == 0)
          eID = LIGHT_ID_0;
        else if(ulLightCount == 1)
          eID = LIGHT_ID_1;
        else if(ulLightCount == 2)
          eID = LIGHT_ID_2;
        else if(ulLightCount == 3)
          eID = LIGHT_ID_3;
        else if(ulLightCount == 4)
          eID = LIGHT_ID_4;
        else if(ulLightCount == 5)
          eID = LIGHT_ID_5;
        else if(ulLightCount == 6)
          eID = LIGHT_ID_6;
        else if(ulLightCount == 7)
          eID = LIGHT_ID_7;
        else 
          eID = LIGHT_ID_COUNT;
        ulLightCount++;
        assert(eID != LIGHT_ID_COUNT);
        if(eID != LIGHT_ID_COUNT)
        {
          class Light* pLight = this->CreateLight(strName, eID);
          if(!pLight->Load(ifs))
          {
            this->DestroyLight(strName);
          }
          // TODO Make sure each scene has at least one mesh, one camera and one light
          bReturnValue = true;
        }
      }
      else if(strType == MATERIAL_LABEL)
      {
        // Get Material Name
        string strName;
        sstmLine >> strName;
        class Material* pMaterial = new Material(strName);
        if(pMaterial->Load(ifs))
        {
          this->mvMaterials.push_back(pMaterial);
          // TODO Make sure each scene has at least one mesh, one camera and one light
          bReturnValue = true;
        }
        else
          delete pMaterial;
      }
      else if(strType == MESH_LABEL)
      {
        // Get Mesh Name
        string strName;
        sstmLine >> strName;
        class Mesh* pMesh = this->CreateMesh(strName);
        if(!pMesh->Load(ifs))
        {
          this->DestroyMesh(&pMesh);
        }
        else
        {
          GeometryBuffer* pBuffer = NULL;
          if((this->mvGeometryBuffers.size() == 0) || (this->mvGeometryBuffers.back()->VertexFreeElements() < pMesh->VertexCount()) || (this->mvGeometryBuffers.back()->IndexFreeElements() < pMesh->IndexCount()))
          {
            pBuffer = new GeometryBuffer(this->mpGraphics);
            this->mvGeometryBuffers.push_back(pBuffer);
          }
          else
          {
            pBuffer = this->mvGeometryBuffers.back();
          }
          unsigned long ulVertexOffset = pBuffer->UsedVertexElements();

          if(ulVertexOffset > 0)
          {
            for(unsigned long ulIndex = 0UL; ulIndex < pMesh->IndexCount(); ulIndex++)
            {
              pMesh->IndexArray()[ulIndex] += ulVertexOffset;
            }
          }

          unsigned long ulIndexOffset = pBuffer->Allocate(pMesh->VertexArray(), pMesh->VertexCount(), pMesh->IndexArray(), pMesh->IndexCount());
          if(ulIndexOffset != ULONG_MAX)
          {
            pMesh->AssignBuffer(pBuffer, ulIndexOffset);
          }
        }
      }
      else if(strType == TEXTURE_LABEL)
      {
        string strTextureType;
        sstmLine >> strTextureType;
        string strName;
        sstmLine >> strName;
        class TGA* pTexture;
        if(strTextureType == "TGA") {
          pTexture = new TGA(strName);
        }
        
        if(pTexture->Load(ifs))
        {
          this->mvTextures.push_back(pTexture);
          bReturnValue = true;
        }
        else
          delete pTexture;
      }
    }

    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Scene::Render()
  {
    this->mpActiveCamera->Render();

    for(unsigned short i = 0; i < mvMeshes.size(); i++)
    {
      mvMeshes[i]->Render();
    }
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Scene::SetupCamera()
  {
    bool bReturnValue = true;
    // Camera constructor will setup a default parameters for the camera. There 
    // is no need to call LoadDefaults again.
    class Camera* pCamera = this->CreateCamera(static_cast<string>("DEFAULT_CAM"));
    this->mvCameras.push_back(pCamera);
    this->mpActiveCamera = pCamera;
    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  bool Scene::SetupLight()
  {
    bool bReturnValue = true;
    /// \todo does nothing.  Relys on OGL default lighting

    return bReturnValue;
  }
  //*************************************************************************//

  //*************************************************************************//
  class Mesh* const Scene::CreateMesh(const std::string& rstrName)
  {
    class Mesh* pReturnValue = NULL;
    if(this->GetMesh(rstrName) == NULL)
    {
      pReturnValue = new class Mesh(rstrName, this);
      this->mvMeshes.push_back(pReturnValue);
    }
    return pReturnValue;
  }
  //*************************************************************************//

  Mesh* const Scene::CloneMesh(const std::string& rstrSourceName, const std::string& rstrDestinationName)
  {
    Mesh* pReturnValue = this->GetMesh(rstrSourceName);
    if((pReturnValue != NULL) && (this->GetMesh(rstrDestinationName) == NULL))
    {
      pReturnValue = new class Mesh(*pReturnValue, rstrDestinationName);
      this->mvMeshes.push_back(pReturnValue);
    }

    return pReturnValue;
  }

  //*************************************************************************//
  void Scene::DestroyMesh(const std::string& rstrName)
  {
    bool bReturnValue = false;

    vector<class Mesh*>::iterator itr = this->mvMeshes.begin();
    while(itr != this->mvMeshes.end())
    {
      if((*itr)->Name() == rstrName)
      {
        delete *itr;
        this->mvMeshes.erase(itr);
        bReturnValue = true;
        break;
      }
    }
  }
  //*************************************************************************//

  void Scene::DestroyMesh(class Mesh** ppMesh)
  {
  }

  //*************************************************************************//
  class Mesh* const Scene::GetMesh(const std::string& rstrName)
  {
    // TODO Make this quicker
    for(unsigned long i = 0; i < this->mvMeshes.size(); i++)
    {
      if(this->mvMeshes[i]->Name() == rstrName)
        return this->mvMeshes[i];
    }
    return NULL;
  }
  //*************************************************************************//

  //*************************************************************************//
  class Camera* const Scene::CreateCamera(const std::string& rstrName)
  {
    class Camera* pTempCamera = new class Camera(rstrName, this);
    this->mvCameras.push_back(pTempCamera);
    this->mpActiveCamera = pTempCamera;
    return pTempCamera;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Scene::DestroyCamera(const std::string& rstrName)
  {

  }
  //*************************************************************************//

  //*************************************************************************//
  class Camera* const Scene::GetCamera(const std::string& rstrName)
  {
    // TODO Make this quicker
    for(unsigned long i = 0; i < this->mvCameras.size(); i++)
    {
      if(this->mvCameras[i]->Name() == rstrName)
        return this->mvCameras[i];
    }
    return NULL;
  }
  //*************************************************************************//

  //*************************************************************************//
  class Camera* const Scene::GetActiveCamera()
  {
    return this->mpActiveCamera;
  }
  //*************************************************************************//

  //*************************************************************************//
  class Light* const Scene::CreateLight(const std::string& rstrName, enum LightID eLightID)
  {
    class Light* pTempLight = new class Light(rstrName, eLightID);
    this->mvLights.push_back(pTempLight);
    return pTempLight;
  }
  //*************************************************************************//

  //*************************************************************************//
  void Scene::DestroyLight(const std::string& rstrName)
  {

  }
  //*************************************************************************//

  //*************************************************************************//
  void Scene::DestroyLight(class Light** ppLight)
  {

  }
  //*************************************************************************//

  //*************************************************************************//
  class Light* const Scene::GetLight(const std::string& rstrName)
  {
    // TODO Make this quicker
    for(unsigned long i = 0; i < this->mvLights.size(); i++)
    {
      if(this->mvLights[i]->Name() == rstrName)
        return this->mvLights[i];
    }
    return NULL;
  }
  //*************************************************************************//

  //*************************************************************************//
  class Material* const Scene::GetMaterial(const std::string& rstrName)
  {
    // TODO Make this quicker
    for(unsigned long i = 0; i < this->mvMaterials.size(); i++)
    {
      if(this->mvMaterials[i]->Name() == rstrName)
        return this->mvMaterials[i];
    }
    return NULL;
  }
  //*************************************************************************//
  
  class Texture* const Scene::GetTexture(const std::string& rstrName)
  {
    for(unsigned long i = 0; i < this->mvTextures.size(); i++)
    {
      if(this->mvTextures[i]->Name() == rstrName)
        return this->mvTextures[i];
    }
    return NULL;
  }
  
}
//***************************************************************************//