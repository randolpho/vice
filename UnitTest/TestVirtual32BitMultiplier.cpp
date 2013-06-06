#include "TestFunctions.h"
#include "Virtual32BitMultiplier.h"
#include "VirtualConnection.h"
#include <iostream>
#include <bitset>
using namespace std;
using namespace VICE::Arithmetic;
using namespace VICE::Component;
bool AnalyzeMultiplier32State(Virtual32BitMultiplier & monty)
{
  int a = ReadWires32(monty.Get_InputA());
  int b = ReadWires32(monty.Get_InputB());
  int product = ReadWires32(monty.Get_Product());
  int expected = a*b;

  bitset<32> exp(expected);

  cout << "      A: ";
  PrintWires32(monty.Get_InputA());
  cout << " (" << a << ");" << endl;
  cout << "      B: ";
  PrintWires32(monty.Get_InputB());
  cout << " (" << b << ");" << endl;
  cout << "    A*B: ";
  PrintWires32(monty.Get_Product());
  cout << " (" << product << "); C(out): " << monty.Get_OutputCarry()->On << endl;
  cout << "   Ex'd: " << exp.to_string() << " (" << expected << ");" << endl;

  return exp.to_ulong() == product;
}

void Run32BitMultiplierTest(int testNum, int a, int b, Virtual32BitMultiplier & monty)
{
  VirtualConnection aWires[32];
  VirtualConnection bWires[32];

  BuildWires32(a, aWires);
  BuildWires32(b, bWires);

  monty.Set_InputA(aWires);
  monty.Set_InputB(bWires);

  monty.Update();

  bool pass = AnalyzeMultiplier32State(monty);
  PrintTestCaseHeader(testNum, pass);
  cout << endl;
}


void TestVirtual32BitMultiplier()
{
  Virtual32BitMultiplier monty;
  cout << "Testing Virtual32BitMultiplier:" << endl;
  //Run4BitMultiplierTest(1, 13, 13);
  int testNum = 1;

  // no time for exhaustive tests... let's test the test cases!
  Run32BitMultiplierTest(testNum++, 1, 2, monty);
  Run32BitMultiplierTest(testNum++, 4107, 3, monty);
  Run32BitMultiplierTest(testNum++, 3649, 55, monty);
  Run32BitMultiplierTest(testNum++, 29384, 7, monty);
  Run32BitMultiplierTest(testNum++, 500, 75, monty);
  Run32BitMultiplierTest(testNum++, 45368, 2, monty);
  Run32BitMultiplierTest(testNum++, 999999, 0, monty);
}