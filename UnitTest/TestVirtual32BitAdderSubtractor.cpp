#include "TestFunctions.h"
#include "Virtual32BitAdderSubtractor.h"
#include "VirtualConnection.h"
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
using namespace VICE::Arithmetic;
using namespace VICE::Component;

bool AnalyzeAdderSubtractorState(Virtual32BitAdderSubtractor & adder)
{
  int a = ReadWires32(adder.Get_InputA());
  int b = ReadWires32(adder.Get_InputB());
  int sum = ReadWires32(adder.Get_Sum());
  int expected = a+b;
  char op = '+';
  if(adder.Get_SubtractionControl()->On)
  {
    expected = a-b;
    op = '-';
  }
  bitset<32> exp(expected);
  cout << "      A: ";
  PrintWires32(adder.Get_InputA());
  cout << " (" << a << "); C(in): " << adder.Get_SubtractionControl()->On << endl;
  cout << "      B: ";
  PrintWires32(adder.Get_InputB());
  cout << " (" << b << ")" << endl;
  cout << "    A" << op << "B: ";
  PrintWires32(adder.Get_Sum());
  cout << " (" << sum << "); C(out): " << adder.Get_OutputCarry()->On << endl;
  cout << "   Ex'd: " << exp.to_string() << " (" << expected << ")" << endl;

  return exp.to_ulong() == sum;
}


void Run32BitAdderSubtractorTest(int testNum, int a, int b, bool subtract)
{
  Virtual32BitAdderSubtractor adder;

  VirtualConnection aWires[32];
  VirtualConnection bWires[32];
  VirtualConnection subtractWire(subtract);

  BuildWires32(a, aWires);
  BuildWires32(b, bWires);

  adder.Set_InputA(aWires);
  adder.Set_InputB(bWires);
  adder.Set_SubtractionControl(&subtractWire);

  adder.Update();
  bool pass = AnalyzeAdderSubtractorState(adder);
  PrintTestCaseHeader(testNum, pass);
  cout << endl;
}

void TestVirtual32BitAdderSubtractor()
{
  cout << "Testing Virtual32BitAdderSubtractor:" << endl;
  int testNum = 1;
  // Testing note: An exhaustive test of the 32-bit adder/subtractor
  // could take a *very* long time to test, there being, what, 4 billion 
  // possible combinations? Add subtraction to that, and I'll be here all
  // month! Let's just test against the contest test cases, shall we? 
  Run32BitAdderSubtractorTest(testNum++, 1, 1, false);
  Run32BitAdderSubtractorTest(testNum++, 2, 1, true);
  Run32BitAdderSubtractorTest(testNum++, 1, 2, true);
  Run32BitAdderSubtractorTest(testNum++, 10, 1, false);
  Run32BitAdderSubtractorTest(testNum++, 435, 231, false);
  Run32BitAdderSubtractorTest(testNum++, 881, 456, false);
  Run32BitAdderSubtractorTest(testNum++, 110101, 10001, true);
  Run32BitAdderSubtractorTest(testNum++, 9876, 1234, false);
  Run32BitAdderSubtractorTest(testNum++, 400000, 500000, true);
  Run32BitAdderSubtractorTest(testNum++, 28, 72, false);
  Run32BitAdderSubtractorTest(testNum++, 123, 456, false);
  Run32BitAdderSubtractorTest(testNum++, 567347, 43578, true);
  Run32BitAdderSubtractorTest(testNum++, 2222, 888, false);
  Run32BitAdderSubtractorTest(testNum++, 56723, 73465, true);
  Run32BitAdderSubtractorTest(testNum++, 3456, 4578, false);
}
