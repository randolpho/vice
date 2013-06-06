#include "StdAfx.h"
#include "VirtualAndGate.h"
#include <stdexcept>
using namespace VICE::Logic;
using namespace VICE::Component;


VirtualAndGate::VirtualAndGate() : InputA(&VirtualConnection::AlwaysOff), InputB(&VirtualConnection::AlwaysOff)
{
  TransistorA.Set_Collector(&VirtualConnection::AlwaysOn);
  TransistorB.Set_Collector(TransistorA.Get_Emitter());
  Output = TransistorB.Get_Emitter();
#ifdef _DEBUG
  UpdateWireState();
#endif
}
void VirtualAndGate::Update()
{
  TransistorA.Update();
  TransistorB.Update();
#ifdef _DEBUG
  UpdateWireState();
#endif
}
#ifdef _DEBUG
void VirtualAndGate::UpdateWireState()
{
  WireState["A"] = InputA->On;
  WireState["B"] = InputB->On;
  WireState["Output"] = Output->On;
}
#endif

//*******//
//** A **//
//*******//
const VICE::Component::VirtualConnection * VirtualAndGate::Get_InputA()
{
  return InputA;
}
void VirtualAndGate::Set_InputA(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputA = input;
  TransistorA.Set_Base(input);
}

//*******//
//** B **//
//*******//
const VICE::Component::VirtualConnection * VirtualAndGate::Get_InputB()
{
  return InputB;
}
void VirtualAndGate::Set_InputB(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputB = input;
  TransistorB.Set_Base(input);
}

//************//
//** Output **//
//************//
const VirtualConnection * VirtualAndGate::Get_Output()
{
  return Output;
}