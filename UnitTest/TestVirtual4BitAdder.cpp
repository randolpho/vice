#include "TestFunctions.h"
#include "Virtual4BitAdder.h"
#include "VirtualConnection.h"
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
using namespace VICE::Arithmetic;
using namespace VICE::Component;

bool AnalyzeAdderState(Virtual4BitAdder & adder)
{
  int a = ReadWires(adder.Get_InputA());
  int b = ReadWires(adder.Get_InputB());
  int sum = ReadWires(adder.Get_Sum());
  int expected = a+b;
  if(adder.Get_InputCarry()->On)
  {
    expected++;
  }
  bool carry = false;
  if(expected > 15)
  {
    carry = true;
  }
  bitset<4> exp(expected);
  cout << "      A: ";
  PrintWires(adder.Get_InputA());
  cout << " (" << a << "); C(in): " << adder.Get_InputCarry()->On << endl;
  cout << "      B: ";
  PrintWires(adder.Get_InputB());
  cout << " (" << b << ")" << endl;
  cout << "    A+B: ";
  PrintWires(adder.Get_Sum());
  cout << " (" << sum << "); C(out): " << adder.Get_OutputCarry()->On << endl;
  cout << "   Ex'd: " << exp.to_string() << " (" << expected << "); C(out): " << carry << endl;

  bool pass = false;
  bool passCarry = adder.Get_OutputCarry()->On == carry;
  bool passExp = exp.to_ulong() == sum;
  pass = passCarry && passExp;
  return pass;
}


void RunTest(int testNum, int a, int b, bool carry)
{
  Virtual4BitAdder adder;

  VirtualConnection aWires[4];
  VirtualConnection bWires[4];
  VirtualConnection carryWire(carry);

  BuildWires(a, aWires);
  BuildWires(b, bWires);

  adder.Set_InputA(aWires);
  adder.Set_InputB(bWires);
  adder.Set_InputCarry(&carryWire);

  adder.Update();
  bool pass = AnalyzeAdderState(adder);
  PrintTestCaseHeader(testNum, pass);
  cout << endl;
}

void TestVirtual4BitAdder()
{
  cout << "Testing Virtual4BitAdder:" << endl;
  int testNum = 1;
  for(int i=0; i<16; i++)
  {
    for(int j=0; j<16; j++)
    {
      RunTest(testNum++, i, j, false);
      RunTest(testNum++, i, j, true);
    }
  }
}