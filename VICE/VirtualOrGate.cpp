#include "StdAfx.h"
#include "VirtualOrGate.h"
#include <stdexcept>
using namespace VICE::Logic;
using namespace VICE::Component;

VirtualOrGate::VirtualOrGate() : InputA(&VirtualConnection::AlwaysOff), InputB(&VirtualConnection::AlwaysOff)
{
  TransistorA.Set_Collector(&VirtualConnection::AlwaysOn);
  TransistorB.Set_Collector(&VirtualConnection::AlwaysOn);
  OutputJunction.Add_Input(TransistorA.Get_Emitter());
  OutputJunction.Add_Input(TransistorB.Get_Emitter());
  Output = OutputJunction.Get_Output();
#ifdef _DEBUG
  UpdateWireState();
#endif
}

void VirtualOrGate::Update()
{
  TransistorA.Update();
  TransistorB.Update();
  OutputJunction.Update();
#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualOrGate::UpdateWireState()
{
  WireState["A"] = InputA->On;
  WireState["B"] = InputB->On;
  WireState["Output"] = Output->On;
}
#endif

//*******//
//** A **//
//*******//
const VICE::Component::VirtualConnection * VirtualOrGate::Get_InputA()
{
  return InputA;
}
void VirtualOrGate::Set_InputA(const VirtualConnection * input)
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
const VICE::Component::VirtualConnection * VirtualOrGate::Get_InputB()
{
  return InputB;
}
void VirtualOrGate::Set_InputB(const VirtualConnection * input)
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
const VirtualConnection * VirtualOrGate::Get_Output()
{
  return Output;
}


