#include "TestFunctions.h"
#include "Virtual4BitMultiplier.h"
#include "VirtualConnection.h"
#include <iostream>
#include <bitset>
using namespace std;
using namespace VICE::Arithmetic;
using namespace VICE::Component;
bool AnalyzeMultiplierState(Virtual4BitMultiplier & monty)
{
  int a = ReadWires(monty.Get_InputA());
  int b = ReadWires(monty.Get_InputB());
  int product = ReadWires8(monty.Get_Product());
  int expected = a*b;

  bitset<8> exp(expected);

  cout << "      A:     ";
  PrintWires(monty.Get_InputA());
  cout << " (" << a << ");" << endl;
  cout << "      B:     ";
  PrintWires(monty.Get_InputB());
  cout << " (" << b << ");" << endl;
  cout << "    A*B: ";
  PrintWires8(monty.Get_Product());
  cout << " (" << product << "); C(out): " << monty.Get_OutputCarry()->On << endl;
  cout << "   Ex'd: " << exp.to_string() << " (" << expected << ");" << endl;

  return exp.to_ulong() == product;
}

void Run4BitMultiplierTest(int testNum, int a, int b)
{
  Virtual4BitMultiplier monty;
  VirtualConnection aWires[4];
  VirtualConnection bWires[4];

  BuildWires(a, aWires);
  BuildWires(b, bWires);

  monty.Set_InputA(aWires);
  monty.Set_InputB(bWires);

  monty.Update();

  bool pass = AnalyzeMultiplierState(monty);
  PrintTestCaseHeader(testNum, pass);
  cout << endl;
}


void TestVirtual4BitMultiplier()
{
  cout << "Testing Virtual4BitMultiplier:" << endl;
  //Run4BitMultiplierTest(1, 13, 13);
  int testNum = 1;
  for(int i=0; i<16; i++)
  {
    for(int j=0; j<16; j++)
    {
      Run4BitMultiplierTest(testNum++, i, j);
    }
  }
}