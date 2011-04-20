xof 0303txt 0032


template VertexDuplicationIndices { 
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}
template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array float weights[nWeights];
 Matrix4x4 matrixOffset;
}

Frame RootFrame {

  FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,
    0.000000,0.000000,1.000000,0.000000,
    0.000000,1.000000,0.000000,0.000000,
    0.000000,0.000000,0.000000,1.000000;;
  }
  Frame Plane {

    FrameTransformMatrix {
      -65.448600,0.000000,0.000000,0.000000,
      0.000000,-65.448600,0.000000,0.000000,
      0.000000,0.000000,-65.448600,0.000000,
      0.000000,0.000000,0.000000,1.000000;;
    }
Mesh {
6;
1.000000; 1.000000; 0.000000;,
-1.000000; 1.000000; 0.000000;,
-1.000000; -1.000000; 0.000000;,
1.000000; 1.000000; 0.000000;,
-1.000000; -1.000000; 0.000000;,
1.000000; -1.000000; 0.000000;;
2;
3; 0, 2, 1;,
3; 3, 5, 4;;
  MeshMaterialList {
    1;
    2;
    0,
    0;;
  Material Material_001 {
    0.420000; 0.420000; 0.420000;1.0;;
    0.500000;
    1.000000; 1.000000; 1.000000;;
    0.0; 0.0; 0.0;;
  }  //End of Material
    }  //End of MeshMaterialList
  MeshNormals {
6;
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;,
    0.000000; 0.000000; 1.000000;;
2;
3; 0, 2, 1;,
3; 3, 5, 4;;
}  //End of MeshNormals
  }  // End of the Mesh Plane 
  }  // SI End of the Object Plane 
}  // End of the Root Frame
