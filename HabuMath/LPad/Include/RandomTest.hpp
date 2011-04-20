
#ifndef RANDOM_TEST_HPP
#define RANDOM_TEST_HPP

#include "HabuMath.hpp"

using namespace HabuTech;

void TestRandomNumberGeneration()
{
  const long interations_between_prints = 10000;
  const long interations_counts         = 10000;
  typedef long double random_type;

  class Random<random_type> oRandomFloat;

  unsigned long long ulNumberOfZeros = 0;
  unsigned long long ulNumberOfOnes  = 0;

  unsigned char* cpBuffer = new unsigned char[sizeof(random_type)];

  for(unsigned long k = 0; k < interations_between_prints; k++)
  {
    for(unsigned long i = 0; i < interations_counts; i++)
    {

      random_type random =  oRandomFloat.Generate(-1000000.0, 1000000.0);
      //random_type random =  oRandomFloat.GetRandom();
      assert((random <= 1000000.0) && (random >= -1000000.0));
      
      memcpy(cpBuffer, &random, sizeof(random_type));
      
      for(unsigned char j = 0; j < sizeof(random_type); j++)
      {
        unsigned char ucMask = 1;
        for(unsigned char m = 0; m < 8; m++)
        {
          
          if(ucMask & cpBuffer[j])
            ulNumberOfOnes++;
          else
            ulNumberOfZeros++;

          ucMask = ucMask << 1;
        }

      }
      
    }
    cout << "Zero Ratio: " << ulNumberOfZeros/((double)(k * interations_counts * 8 * sizeof(random_type))) << endl; 
    cout << "One Ratio: " << ulNumberOfOnes/((double)(k * interations_counts * 8 * sizeof(random_type))) << endl; 
  }
  delete [] cpBuffer;
}

#endif RANDOM_TEST_HPP
