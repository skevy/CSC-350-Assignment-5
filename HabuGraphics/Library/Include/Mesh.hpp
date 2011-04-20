//***************************************************************************//
// Mesh Class Interface
//
// Created: July 08, 2005
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

#ifndef HABU_GRAPHICS_MESH_HPP
#define HABU_GRAPHICS_MESH_HPP

//***************************************************************************//
// System includes
#include <string>
#include <vector>
//***************************************************************************//

//***************************************************************************//
// Local Includes
#include "Object.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  const unsigned char MAX_NUMBER_OF_LODS = 10;
  //*************************************************************************//

  class BoundingVolume
  {
  private:
    Point<float, 3> mUpperFrontRight;
    Point<float, 3> mLowerBackLeft;

    void Create();
    void Clone(const BoundingVolume &rSource);
    void Destroy();

  public:
    BoundingVolume();
    BoundingVolume(const BoundingVolume& rSource);
    ~BoundingVolume();

    void Examine(const class Vertex& rVertex);

    float Width() const;
    float Height() const;
    float Depth() const;
  };

  //*************************************************************************//
  // Mesh class manages polygons that describe the mesh.
  class Mesh : public Object
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    class Scene* mpScene;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long mulNumberOfFaces;
    unsigned long mulNumberOfVertices;
    unsigned long mulNumberOfIndices;
    unsigned long mulIndicesOffset;
    //-----------------------------------------------------------------------//

    class GeometryBuffer* mpGeometryBuffer;

    //-----------------------------------------------------------------------//
    class Surface* mpSurface;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    class Vertex* mpVertexArray;
    unsigned long* mpIndexArray;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    bool mbWireFrame;
    //-----------------------------------------------------------------------//
    
    BoundingVolume* mpBoundingVolume;

    void Create(const std::string& rstrName, class Scene* pScene);
    void Clone(const Mesh& rSource);
    void Destroy();
    
    //***********************************************************************//
  protected:
    //***********************************************************************//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // This constructor sets all member data to zero
    Mesh(const std::string& rstrName, class Scene* const pScene);
    Mesh(const Mesh& rSource);
    Mesh(const Mesh& rSource, const std::string& rstrDestinationName);
    virtual ~Mesh();
    //-----------------------------------------------------------------------//

    Mesh& Mesh::operator=(const Mesh& rSource)
    {
      if(this != &rSource)
      {
        Clone(rSource);
      }
      return *this;
    }

    //-----------------------------------------------------------------------//
    bool _cdecl Load(std::ifstream& ifs);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void _cdecl Position(float fX, float fY, float fZ);
    //-----------------------------------------------------------------------//

    class Vertex* VertexArray();
    unsigned long* IndexArray();

    unsigned long VertexCount() const;
    unsigned long IndexCount() const;

    void AssignBuffer(class GeometryBuffer* const pBuffer, unsigned long ulOffset);

    //-----------------------------------------------------------------------//
    // Renders the mesh
    virtual void _cdecl Render();
    //-----------------------------------------------------------------------//

    const BoundingVolume* const BoundVolume() { return this->mpBoundingVolume; }

    void SetLOD(unsigned long ulLOD);
    void SetWireframe(bool bWireframe) { mbWireFrame = bWireframe; }
    //***********************************************************************//
  }; // End of class Mesh : public Object
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//
#endif HABU_GRAPHICS_MESH_HPP