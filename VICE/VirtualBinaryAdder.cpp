#include "StdAfx.h"
#include "VirtualBinaryAdder.h"
#include <stdexcept>
using namespace VICE::Logic;
using namespace VICE::Component;
using namespace VICE::Arithmetic;

VirtualBinaryAdder::VirtualBinaryAdder() : InputA(&VirtualConnection::AlwaysOff), InputB(&VirtualConnection::AlwaysOff), InputCarry(&VirtualConnection::AlwaysOff)
{
  CarryAdder.Set_InputA(SumAdder.Get_Output());
  SumAndCarry.Set_InputA(SumAdder.Get_Output());
  CarryOut.Set_InputA(SumAndCarry.Get_Output());
  CarryOut.Set_InputB(A_And_B.Get_Output());

  CarryOutput = CarryOut.Get_Output();
  Sum = CarryAdder.Get_Output();

#ifdef _DEBUG
  UpdateWireState();
#endif
}

void VirtualBinaryAdder::Update()
{
  SumAdder.Update();
  CarryAdder.Update();
  SumAndCarry.Update();
  A_And_B.Update();
  CarryOut.Update();

#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualBinaryAdder::UpdateWireState()
{
  WireState["A"] = InputA->On;
  WireState["B"] = InputB->On;
  WireState["C(in)"] = InputCarry->On;
  WireState["Sum"] = Sum->On;
  WireState["C(out)"] = CarryOutput->On;
}
#endif

//*******//
//** A **//
//*******//
const VICE::Component::VirtualConnection * VirtualBinaryAdder::Get_InputA()
{
  return InputA;
}
void VirtualBinaryAdder::Set_InputA(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputA = input;
  SumAdder.Set_InputA(input);
  A_And_B.Set_InputA(input);
}

//*******//
//** B **//
//*******//
const VICE::Component::VirtualConnection * VirtualBinaryAdder::Get_InputB()
{
  return InputB;
}
void VirtualBinaryAdder::Set_InputB(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputB = input;
  SumAdder.Set_InputB(input);
  A_And_B.Set_InputB(input);
}

//***********//
//** C(in) **//
//***********//
const VICE::Component::VirtualConnection * VirtualBinaryAdder::Get_InputCarry()
{
  return InputCarry;
}
void VirtualBinaryAdder::Set_InputCarry(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputCarry = input;
  CarryAdder.Set_InputB(input);
  SumAndCarry.Set_InputB(input);
}

//************//
//** C(out) **//
//************//
const VirtualConnection * VirtualBinaryAdder::Get_CarryOutput()
{
  return CarryOutput;
}

//*********//
//** Sum **//
//*********//
const VirtualConnection * VirtualBinaryAdder::Get_Sum()
{
  return Sum;
}