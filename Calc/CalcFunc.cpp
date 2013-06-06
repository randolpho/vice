#include "calcfunc.h"
#include "Virtual32BitAdderSubtractor.h"
#include "Virtual32BitMultiplier.h"
#include "VirtualConnection.h"
#include "VirtualWiring.h"
#include <bitset>
using namespace std;
using namespace VICE::Component;
using namespace VICE::Arithmetic;
using namespace VICE;

float DoOperation(char operation, float op1, float op2, int* isErr)
{
	switch (operation)
	{
	case '+':
		return DoAdd(op1, op2);
		break;
	case '-':
		return DoSub(op1, op2);
		break;	
	case '*':
		return DoMul(op1, op2);
		break;
	case '/':
		return DoDiv(op1, op2, isErr);
		break;
	}
	return op2;
}

float DoAdd(float op1, float op2)
{
  int a = (int)op1;
  int b = (int)op2;

  Virtual32BitAdderSubtractor adder;
  VirtualConnection aWires[32];
  VirtualConnection bWires[32];

  BuildWires32(a, aWires);
  BuildWires32(b, bWires);

  adder.Set_InputA(aWires);
  adder.Set_InputB(bWires);

  adder.Update();
  return (float)ReadWires32(adder.Get_Sum());
}

float DoSub(float op1, float op2)
{
  int a = (int)op1;
  int b = (int)op2;

  Virtual32BitAdderSubtractor adder;
  VirtualConnection aWires[32];
  VirtualConnection bWires[32];

  BuildWires32(a, aWires);
  BuildWires32(b, bWires);

  adder.Set_InputA(aWires);
  adder.Set_InputB(bWires);
  adder.Set_SubtractionControl(&VirtualConnection::AlwaysOn);

  adder.Update();
  return (float)ReadWires32(adder.Get_Sum());
}

float DoMul(float op1, float op2)
{
  int a = (int)op1;
  int b = (int)op2;

  Virtual32BitMultiplier multy;
  VirtualConnection aWires[32];
  VirtualConnection bWires[32];

  BuildWires32(a, aWires);
  BuildWires32(b, bWires);

  multy.Set_InputA(aWires);
  multy.Set_InputB(bWires);

  multy.Update();
  return (float)ReadWires32(multy.Get_Product());
}

float DoDiv(float op1, float op2, int *isErr)
{
  *isErr = 0;
  if(op2 == 0)
  {
    *isErr = 1;
  }
  return op1/op2;
}





