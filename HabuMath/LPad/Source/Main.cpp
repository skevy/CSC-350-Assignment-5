
//#include <iostream>
//#include <stdlib.h>



#include <iostream>

using namespace std;

#define EPSILION 0.000001

#include "AffineTransformTest.hpp"
#include "NormalizeTest.hpp"
#include "RandomTest.hpp"


int main(int argc, char** argv)
{
  //TestNormalizeVector();
  //TestRandomNumberGeneration();
  TestAffineTransforms();


  cout << "Press any key to close...";
  cin.get();

  exit(1);
  return 0;
}