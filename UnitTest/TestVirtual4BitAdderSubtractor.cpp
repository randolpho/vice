#include "TestFunctions.h"
#include "Virtual4BitAdderSubtractor.h"
#include "VirtualConnection.h"
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
using namespace VICE::Arithmetic;
using namespace VICE::Component;

void PrintWires(const VirtualConnection ** wires);
int ReadWires(const VirtualConnection ** wires);
void BuildWires(int val, VirtualConnection * wires);

bool AnalyzeAdderSubtractorState(Virtual4BitAdderSubtractor & adder)
{
  int a = ReadWires(adder.Get_InputA());
  int b = ReadWires(adder.Get_InputB());
  int sum = ReadWires(adder.Get_Sum());
  int expected = a+b;
  char op = '+';
  if(adder.Get_SubtractionControl()->On)
  {
    expected = a-b;
    op = '-';
  }
  bool carry = false;
  if(expected > 15 || expected < -15)
  {
    carry = true;
  }
  bitset<4> exp(expected);
  cout << "      A: ";
  PrintWires(adder.Get_InputA());
  cout << " (" << a << "); C(in): " << adder.Get_SubtractionControl()->On << endl;
  cout << "      B: ";
  PrintWires(adder.Get_InputB());
  cout << " (" << b << ")" << endl;
  cout << "    A" << op << "B: ";
  PrintWires(adder.Get_Sum());
  cout << " (" << sum << "); C(out): " << adder.Get_OutputCarry()->On << endl;
  cout << "   Ex'd: " << exp.to_string() << " (" << expected << "); C(out): " << carry << endl;

  return exp.to_ulong() == sum;
}


void Run4BitAdderSubtractorTest(int testNum, int a, int b, bool subtract)
{
  Virtual4BitAdderSubtractor adder;

  VirtualConnection aWires[4];
  VirtualConnection bWires[4];
  VirtualConnection subtractWire(subtract);

  BuildWires(a, aWires);
  BuildWires(b, bWires);

  adder.Set_InputA(aWires);
  adder.Set_InputB(bWires);
  adder.Set_SubtractionControl(&subtractWire);

  adder.Update();
  bool pass = AnalyzeAdderSubtractorState(adder);
  PrintTestCaseHeader(testNum, pass);
  cout << endl;
}

void TestVirtual4BitAdderSubtractor()
{
  cout << "Testing Virtual4BitAdderSubtractor:" << endl;
  int testNum = 1;
  for(int i=0; i<16; i++)
  {
    for(int j=0; j<16; j++)
    {
      Run4BitAdderSubtractorTest(testNum++, i, j, false);
      Run4BitAdderSubtractorTest(testNum++, i, j, true);
    }
  }
}