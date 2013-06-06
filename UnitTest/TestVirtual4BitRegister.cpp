#include "TestFunctions.h"
#include "Virtual4BitRegister.h"
#include "VirtualConnection.h"
#include <iostream>
#include <bitset>
using namespace std;
using namespace VICE::Memory;
using namespace VICE::Component;

void Run4BitRegisterTest(int testNum, int input, bool shiftValue)
{
  Virtual4BitRegister reggy;
  VirtualConnection inWires[4];
  VirtualConnection controlWires[2];
  VirtualConnection shift(shiftValue);
  reggy.Set_Input(inWires);
  reggy.Set_Control(controlWires);
  reggy.Set_Shift(&shift);

  bitset<4> expectedLeftShift(input);
  expectedLeftShift <<= 1;
  expectedLeftShift[0] = shiftValue;
  int exLeft = (int) expectedLeftShift.to_ulong();

  bitset<4> expectedRightShift(input);
  expectedRightShift >>= 1;
  expectedRightShift[3] = shiftValue;
  int exRight = (int) expectedRightShift.to_ulong();
  BuildWires(input, inWires);

  // load
  bool pass = false;
  BuildWires2(3, controlWires);
  reggy.Update();
  pass = input == ReadWires(reggy.Get_Output());
  PrintTestCaseHeader(testNum++, pass);
  cout << "Load:" << endl;
  cout << "       Input: ";
  PrintWires(reggy.Get_Input());
  cout << " (" << input << "); Shift: " << shiftValue << endl;
  cout << "      Output: ";
  PrintWires(reggy.Get_Output());
  cout << " (" << ReadWires(reggy.Get_Output()) << ");" << endl;
  cout << "    Expected: ";
  PrintWires(reggy.Get_Input());
  cout << " (" << input << ");" << endl;

  // do nothing
  BuildWires2(0, controlWires);
  reggy.Update();
  pass = input == ReadWires(reggy.Get_Output());
  PrintTestCaseHeader(testNum++, pass);
  cout << "Do Nothing:" << endl;
  cout << "       Input: ";
  PrintWires(reggy.Get_Input());
  cout << " (" << input << "); Shift: " << shiftValue << endl;
  cout << "      Output: ";
  PrintWires(reggy.Get_Output());
  cout << " (" << ReadWires(reggy.Get_Output()) << ");" << endl;
  cout << "    Expected: ";
  PrintWires(reggy.Get_Input());
  cout << " (" << input << ");" << endl;

  // right shift
  BuildWires2(1, controlWires);
  reggy.Update();
  pass = exRight == ReadWires(reggy.Get_Output());
  PrintTestCaseHeader(testNum++, pass);
  cout << "Right Shift:" << endl;
  cout << "       Input: ";
  PrintWires(reggy.Get_Input());
  cout << " (" << input << "); Shift: " << shiftValue << endl;
  cout << "      Output: ";
  PrintWires(reggy.Get_Output());
  cout << " (" << ReadWires(reggy.Get_Output()) << ");" << endl;
  cout << "    Expected: " << expectedRightShift.to_string() << " (" << exRight << ");" << endl;

  // left shift
  BuildWires2(3, controlWires); // first, reload old values
  reggy.Update();
  BuildWires2(2, controlWires);
  reggy.Update();
  pass = exLeft == ReadWires(reggy.Get_Output());
  PrintTestCaseHeader(testNum++, pass);
  cout << "Left Shift:" << endl;
  cout << "       Input: ";
  PrintWires(reggy.Get_Input());
  cout << " (" << input << "); Shift: " << shiftValue << endl;
  cout << "      Output: ";
  PrintWires(reggy.Get_Output());
  cout << " (" << ReadWires(reggy.Get_Output()) << ");" << endl;
  cout << "    Expected: " << expectedLeftShift.to_string() << " (" << exLeft << ");" << endl;

  
}

void TestVirtual4BitRegister()
{
  cout << "Testing Virtual4BitRegister" << endl;
  int testNum = 1;
  for(int i=0; i<16; i++)
  {
    Run4BitRegisterTest(testNum, i, false);
    testNum+=4;
    Run4BitRegisterTest(testNum, i, true);
    testNum+=4;
  }
}