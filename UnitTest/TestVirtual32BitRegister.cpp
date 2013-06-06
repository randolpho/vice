#include "TestFunctions.h"
#include "Virtual32BitRegister.h"
#include "VirtualConnection.h"
#include <iostream>
#include <bitset>
using namespace std;
using namespace VICE::Memory;
using namespace VICE::Component;

void Run32BitRegisterTest(int testNum, int input, bool shiftValue)
{
  Virtual32BitRegister reggy;
  VirtualConnection inWires[32];
  VirtualConnection controlWires[2];
  VirtualConnection shift(shiftValue);
  reggy.Set_Input(inWires);
  reggy.Set_Control(controlWires);
  reggy.Set_Shift(&shift);

  bitset<32> expectedLeftShift(input);
  expectedLeftShift <<= 1;
  expectedLeftShift[0] = shiftValue;
  int exLeft = (int) expectedLeftShift.to_ulong();

  bitset<32> expectedRightShift(input);
  expectedRightShift >>= 1;
  expectedRightShift[31] = shiftValue;
  int exRight = (int) expectedRightShift.to_ulong();
  BuildWires32(input, inWires);

  // load
  bool pass = true;
  BuildWires2(3, controlWires);
  reggy.Update();
  pass = input == ReadWires32(reggy.Get_Output());
  PrintTestCaseHeader(testNum++, pass);
  cout << "Load:" << endl;
  cout << "       Input: ";
  PrintWires32(reggy.Get_Input());
  cout << " (" << input << "); Shift: " << shiftValue << endl;
  cout << "      Output: ";
  PrintWires32(reggy.Get_Output());
  cout << " (" << ReadWires32(reggy.Get_Output()) << ");" << endl;
  cout << "    Expected: ";
  PrintWires32(reggy.Get_Input());
  cout << " (" << input << ");" << endl;

  // do nothing
  BuildWires2(0, controlWires);
  reggy.Update();
  pass = input == ReadWires32(reggy.Get_Output());
  PrintTestCaseHeader(testNum++, pass);
  cout << "Do Nothing:" << endl;
  cout << "       Input: ";
  PrintWires32(reggy.Get_Input());
  cout << " (" << input << "); Shift: " << shiftValue << endl;
  cout << "      Output: ";
  PrintWires32(reggy.Get_Output());
  cout << " (" << ReadWires32(reggy.Get_Output()) << ");" << endl;
  cout << "    Expected: ";
  PrintWires32(reggy.Get_Input());
  cout << " (" << input << ");" << endl;

  // right shift
  BuildWires2(1, controlWires);
  reggy.Update();
  pass = exRight == ReadWires32(reggy.Get_Output());
  PrintTestCaseHeader(testNum++, pass);
  cout << "Right Shift:" << endl;
  cout << "       Input: ";
  PrintWires32(reggy.Get_Input());
  cout << " (" << input << "); Shift: " << shiftValue << endl;
  cout << "      Output: ";
  PrintWires32(reggy.Get_Output());
  cout << " (" << ReadWires32(reggy.Get_Output()) << ");" << endl;
  cout << "    Expected: " << expectedRightShift.to_string() << " (" << exRight << ");" << endl;

  // left shift
  BuildWires2(3, controlWires); // first, reload old values
  reggy.Update();
  BuildWires2(2, controlWires);
  reggy.Update();
  pass = exLeft == ReadWires32(reggy.Get_Output());
  PrintTestCaseHeader(testNum++, pass);
  cout << "Left Shift:" << endl;
  cout << "       Input: ";
  PrintWires32(reggy.Get_Input());
  cout << " (" << input << "); Shift: " << shiftValue << endl;
  cout << "      Output: ";
  PrintWires32(reggy.Get_Output());
  cout << " (" << ReadWires32(reggy.Get_Output()) << ");" << endl;
  cout << "    Expected: " << expectedLeftShift.to_string() << " (" << exLeft << ");" << endl;

  
}

void TestVirtual32BitRegister()
{
  cout << "Testing Virtual32BitRegister" << endl;
  int testNum = 1;
  Run32BitRegisterTest(testNum, 2340987238, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 983987293, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 98793482, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 341, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 1687, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 56233, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 87475495, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 98754, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 78934, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 565, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, -453, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 54356, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, -76575, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, -542, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 56982, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 98765, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 13568, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 632667, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 76532, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 5235, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 67645, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 9876, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 342, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 567857, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 23479, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 48289, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 349406, false);
  testNum+=4;
  Run32BitRegisterTest(testNum, 1234, false);
  testNum+=4;

  
  Run32BitRegisterTest(testNum, 2340987238, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 983987293, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 98793482, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 341, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 1687, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 56233, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 87475495, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 98754, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 78934, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 565, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, -453, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 54356, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, -76575, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, -542, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 56982, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 98765, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 13568, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 632667, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 76532, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 5235, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 67645, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 9876, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 342, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 567857, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 23479, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 48289, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 349406, true);
  testNum+=4;
  Run32BitRegisterTest(testNum, 1234, true);
  testNum+=4;
  
}