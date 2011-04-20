#ifndef NORMALIZE_TEST_HPP
#define NORMALIZE_TEST_HPP

#include "HabuMath.hpp"
#include <d3dx9math.h> // for testing

using namespace HabuTech;
// Note that also tests Vector::Magnitude();
void TestNormalizeVector()
{
  // TEST 2D
  D3DXVECTOR2 DX_VECTOR2;
  Vector<double, 2> Habu_VECTOR2;
  cout.precision(10);
  cout << "Running Normalize Vector Test" << endl;

  float fxDiffTotal = 0.0F;
  float fyDiffTotal = 0.0F;

  for(unsigned long i = 0; i < ULONG_MAX; i++)
  {
    DX_VECTOR2.x = rand()/(float(RAND_MAX)+1) * 1000000.0F; 
    DX_VECTOR2.y = rand()/(float(RAND_MAX)+1) * 1000000.0F;

    Habu_VECTOR2.X(DX_VECTOR2.x);
    Habu_VECTOR2.Y(DX_VECTOR2.y);
    // test normalize

    D3DXVECTOR2 DX_VECTOR2_NORMAL;
    D3DXVec2Normalize(&DX_VECTOR2_NORMAL, &DX_VECTOR2);
    Habu_VECTOR2.Normalize();

    float xDiff = DX_VECTOR2_NORMAL.x - Habu_VECTOR2.X();
    float yDiff = DX_VECTOR2_NORMAL.y - Habu_VECTOR2.Y();

    xDiff = fabs(xDiff);
    yDiff = fabs(yDiff);
    fxDiffTotal += xDiff;
    fyDiffTotal += yDiff;
    if(xDiff > EPSILION || yDiff > EPSILION)
    {
      cout << "Error: X: " <<  DX_VECTOR2.x << " Y: " << DX_VECTOR2.y << endl
        << " X Diff: " << xDiff << " Y Diff: " << yDiff << " E: " << EPSILION << endl
        << "Press any key to close...";
      cin.get();

      exit(1);
    }

    if((i % 100000) == 0)
    {
      cout << "i: " << i << endl 
        << " X Diff Total: " << fxDiffTotal << " Y Diff Total: " << fyDiffTotal << endl
        << " X Diff Avg: " << fxDiffTotal / (float)100000 << " Y Diff Total: " << fyDiffTotal / (float)100000 << endl;
      fyDiffTotal = 0.0;
      fxDiffTotal = 0.0;
    }
  }
}

#endif NORMALIZE_TEST_HPP