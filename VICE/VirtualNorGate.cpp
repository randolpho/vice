#include "StdAfx.h"
#include "VirtualNorGate.h"
#include <stdexcept>
using namespace VICE::Logic;
using namespace VICE::Component;

VirtualNorGate::VirtualNorGate() : InputA(&VirtualConnection::AlwaysOff), InputB(&VirtualConnection::AlwaysOff)
{
  Inverter.Set_Input(Or.Get_Output());
  Output = Inverter.Get_Output();
#ifdef _DEBUG
  UpdateWireState();
#endif
}

void VirtualNorGate::Update()
{
  Or.Update();
  Inverter.Update();
#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualNorGate::UpdateWireState()
{
  WireState["A"] = InputA->On;
  WireState["B"] = InputB->On;
  WireState["Output"] = Output->On;
}
#endif


//*******//
//** A **//
//*******//
const VICE::Component::VirtualConnection * VirtualNorGate::Get_InputA()
{
  return InputA;
}
void VirtualNorGate::Set_InputA(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputA = input;
  Or.Set_InputA(input);
}

//*******//
//** B **//
//*******//
const VICE::Component::VirtualConnection * VirtualNorGate::Get_InputB()
{
  return InputB;
}
void VirtualNorGate::Set_InputB(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputB = input;
  Or.Set_InputB(input);
}

//************//
//** Output **//
//************//
const VirtualConnection * VirtualNorGate::Get_Output()
{
  return Output;
}