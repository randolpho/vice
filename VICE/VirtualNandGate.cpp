#include "StdAfx.h"
#include "VirtualNandGate.h"
#include <stdexcept>
using namespace VICE::Logic;
using namespace VICE::Component;

VirtualNandGate::VirtualNandGate() : InputA(&VirtualConnection::AlwaysOff), InputB(&VirtualConnection::AlwaysOff)
{
  Inverter.Set_Input(And.Get_Output());
  Output = Inverter.Get_Output();
#ifdef _DEBUG
  UpdateWireState();
#endif
}

void VirtualNandGate::Update()
{
  And.Update();
  Inverter.Update();
#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualNandGate::UpdateWireState()
{
  WireState["A"] = InputA->On;
  WireState["B"] = InputB->On;
  WireState["Output"] = Output->On;
}
#endif

//*******//
//** A **//
//*******//
const VICE::Component::VirtualConnection * VirtualNandGate::Get_InputA()
{
  return InputA;
}
void VirtualNandGate::Set_InputA(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputA = input;
  And.Set_InputA(input);
}

//*******//
//** B **//
//*******//
const VICE::Component::VirtualConnection * VirtualNandGate::Get_InputB()
{
  return InputB;
}
void VirtualNandGate::Set_InputB(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputB = input;
  And.Set_InputB(input);
}
//************//
//** Output **//
//************//
const VirtualConnection * VirtualNandGate::Get_Output()
{
  return Output;
}