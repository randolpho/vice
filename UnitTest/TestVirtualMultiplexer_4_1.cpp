#include "VirtualMultiplexer_4_1.h"
#include "TestFunctions.h"
#include <bitset>
#include <iostream>
using namespace std;
using namespace VICE::Control;
using namespace VICE::Component;
using namespace VICE::Logic;

void RunMultiplexerTest(int testNum, int input, int select)
{
  VirtualMultiplexer_4_1 mxyzptlk;
  bitset<4> inBits(input);
  VirtualConnection inputWires[4];
  VirtualConnection selectWires[2];

  BuildWires(input, inputWires);
  BuildWires2(select, selectWires);

  bool expected = inBits[select];

  mxyzptlk.Set_Select(selectWires);
  mxyzptlk.Set_Input(inputWires);

  mxyzptlk.Update();

  bool pass = mxyzptlk.Get_Output()->On == expected;
  PrintTestCaseHeader(testNum, pass);
  cout << "Input: ";
  PrintWires(mxyzptlk.Get_Input());
  cout << "; Select: " << mxyzptlk.Get_Select(1)->On 
    << mxyzptlk.Get_Select(0)->On << " (" << select << "); Output: "
    << mxyzptlk.Get_Output()->On << endl;
}

void TestVirtualMultiplexer_4_1()
{
  cout << "Testing VirtualMultiplexer_4_1:" << endl;
  int testNum = 1;
  for(int i=0; i<16; i++)
  {
    for(int j=0; j<4; j++)
    {
      RunMultiplexerTest(testNum++, i, j);
    }
  }
}