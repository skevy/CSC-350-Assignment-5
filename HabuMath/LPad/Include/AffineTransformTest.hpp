
#ifndef AFFINE_TRANFORM_TEST_HPP
#define AFFINE_TRANFORM_TEST_HPP
#include "HabuMath.hpp"
#include <d3dx9math.h> // for testing

using namespace HabuTech;

#define INTERATIONS 1000000

void TestAffineTransforms()
{

  long double fXdiff = 0.0;
  long double fYdiff = 0.0;
  long double fZdiff = 0.0;

  cout << "*************START AFFINE TRANSFORMS TEST************" << endl;
  cout << "*****************START ROTATION TEST*****************" << endl;
  D3DXMATRIX D3DX_XRotationMatrix;
  D3DXMATRIX D3DX_YRotationMatrix;
  D3DXMATRIX D3DX_ZRotationMatrix; 

  Matrix<float, 4> HM_XRotationMatrix;
  Matrix<float, 4> HM_YRotationMatrix;
  Matrix<float, 4> HM_ZRotationMatrix;

  Random<float> oRandomFloat;

  for(unsigned long long i = 0; i < INTERATIONS; i++)
  {

    D3DXMatrixIdentity(&D3DX_XRotationMatrix);
    D3DXMatrixIdentity(&D3DX_YRotationMatrix);
    D3DXMatrixIdentity(&D3DX_ZRotationMatrix);

    HM_XRotationMatrix.Identity();
    HM_YRotationMatrix.Identity();
    HM_ZRotationMatrix.Identity();

    float fXangle = oRandomFloat.Generate(0.0F, 2*3.14F);
    float fYangle = oRandomFloat.Generate(0.0F, 2*3.14F);
    float fZangle = oRandomFloat.Generate(0.0F, 2*3.14F);


    D3DXMatrixRotationX(&D3DX_XRotationMatrix, fXangle);
    D3DXMatrixRotationY(&D3DX_YRotationMatrix, fYangle);
    D3DXMatrixRotationZ(&D3DX_ZRotationMatrix, fZangle);

    HM_XRotationMatrix.RotateAboutX(fXangle);
    HM_YRotationMatrix.RotateAboutY(fYangle);
    HM_ZRotationMatrix.RotateAboutZ(fZangle);

    for(unsigned char r = 0; r < 4; r++)
    {
      for(unsigned char c = 0; c < 4; c++)
      {
        fXdiff += (D3DX_XRotationMatrix(r,c) - HM_XRotationMatrix(c,r));
      }
    }

    for(unsigned char r = 0; r < 4; r++)
    {
      for(unsigned char c = 0; c < 4; c++)
      {
        fYdiff += (D3DX_YRotationMatrix(r,c) - HM_YRotationMatrix(c,r));
      }
    }

    for(unsigned char r = 0; r < 4; r++)
    {
      for(unsigned char c = 0; c < 4; c++)
      {
        fZdiff += (D3DX_ZRotationMatrix(r,c) - HM_ZRotationMatrix(c,r));
      }
    }

    if(!(i%10000))
    {
      cout << "XDiff Average: " << fXdiff/(float)(INTERATIONS * 16) << endl
        << "YDiff Average: " << fYdiff/(float)(INTERATIONS * 16) << endl
        << "ZDiff Average: " << fZdiff/(float)(INTERATIONS * 16) << endl;
    }
  }


  cout << "Final Result for Rotation Test" << endl
    << "XDiff Average: " << fXdiff/(float)(INTERATIONS * 16) << endl
    << "YDiff Average: " << fYdiff/(float)(INTERATIONS * 16) << endl
    << "ZDiff Average: " << fZdiff/(float)(INTERATIONS * 16) << endl;
  cout << "*****************END ROTATION TEST*****************" << endl;


  cout << "************END AFFINE TRANSFORMS TEST**********" << endl;
}

#endif AFFINE_TRANFORM_TEST_HPP