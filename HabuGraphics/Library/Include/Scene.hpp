//***************************************************************************//
// Scene Class Interface
//
// Created Sept 4, 2005
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

#ifndef HABU_GRAPHICS_SCENE_HPP
#define HABU_GRAPHICS_SCENE_HPP

//***************************************************************************//
// System Includes
#include <fstream>
#include <vector>
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  class GeometryBuffer
  {
    const class Graphics* mpGraphics;

    unsigned int muiVertexBufferID;
    unsigned int muiIndexBufferID;

    unsigned long mulVertexFreeElements;
    unsigned long mulIndexFreeElements;

    unsigned int muiMaxVertexSize;
    unsigned int muiMaxIndexSize;

    void Create(const class Graphics* const pGraphics);
    void Clone(const GeometryBuffer& rSource);
    void Destroy();

  public:
    GeometryBuffer(const class Graphics* const pGraphics);
    GeometryBuffer(const GeometryBuffer& rSource);
    ~GeometryBuffer();

    unsigned long _cdecl VertexFreeElements() const;
    unsigned long _cdecl IndexFreeElements() const;

    unsigned long _cdecl MaxVertexElements() const;
    unsigned long _cdecl MaxIndexElements() const;

    unsigned long _cdecl UsedVertexElements() const;
    unsigned long _cdecl UsedIndexElements() const;

    unsigned long _cdecl Allocate(const class Vertex* const pVerticies, unsigned long ulVerticiesLength, const unsigned long* const pIndicies, unsigned long ulIndiciesLength);

    void _cdecl Bind();
    void _cdecl UnBind();
  };

  //*************************************************************************//
  class Scene
  {
  private:
    //***********************************************************************//
    std::string mstrSceneName;
    class Graphics* mpGraphics;

    std::vector<class Mesh*> mvMeshes;
    std::vector<class Light*> mvLights;
    std::vector<class Camera*> mvCameras;
    std::vector<class Material*> mvMaterials;
    std::vector<class Texture*> mvTextures;
    std::vector<class GeometryBuffer*> mvGeometryBuffers;
    class Camera* mpActiveCamera;
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Scene(class Graphics* const pGraphics);
    ~Scene();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void Render();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool SetupCamera();
    bool SetupLight();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Mesh* const CreateMesh(const std::string& rstrName);
    Mesh* const CloneMesh(const std::string& rstrSourceName, const std::string& rstrDestinationName);
    void DestroyMesh(const std::string& rstrName);
    void DestroyMesh(class Mesh** ppMesh);
    class Mesh* const GetMesh(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Camera* const CreateCamera(const std::string& rstrName);
    void DestroyCamera(const std::string& rstrName);
    void DestroyCamera(class Camera** ppCamera);
    class Camera* const GetCamera(const std::string& rstrName);
    class Camera* const GetActiveCamera();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Light* const CreateLight( const std::string& rstrName, enum LightID eLightID);
    void DestroyLight(const std::string& rstrName);
    void DestroyLight(class Light** ppLight);
    class Light* const GetLight(const std::string& rstrName);
    //-----------------------------------------------------------------------//

    class Material* const GetMaterial(const std::string& rstrName);
    
    class Texture* const GetTexture(const std::string& rstrName);

    //-----------------------------------------------------------------------//
    class Graphics* const GetGraphics() const { return mpGraphics; }
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Scene
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_GRAPHICS_SCENE_HPP