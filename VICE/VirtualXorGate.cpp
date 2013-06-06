#include "StdAfx.h"
#include "VirtualXorGate.h"
#include <stdexcept>
using namespace VICE::Logic;
using namespace VICE::Component;

VirtualXorGate::VirtualXorGate() : InputA(&VirtualConnection::AlwaysOff), InputB(&VirtualConnection::AlwaysOff)
{
  A__A_B.Set_InputB(A_B.Get_Output());
  B__A_B.Set_InputA(A_B.Get_Output());
  AAB_BAB.Set_InputA(A__A_B.Get_Output());
  AAB_BAB.Set_InputB(B__A_B.Get_Output());
  Output = AAB_BAB.Get_Output();
#ifdef _DEBUG
  UpdateWireState();
#endif
}

void VirtualXorGate::Update()
{
  A_B.Update();
  A__A_B.Update();
  B__A_B.Update();
  AAB_BAB.Update();
#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualXorGate::UpdateWireState()
{
  WireState["A"] = InputA->On;
  WireState["B"] = InputB->On;
  WireState["Output"] = Output->On;
}
#endif

//*******//
//** A **//
//*******//
const VICE::Component::VirtualConnection * VirtualXorGate::Get_InputA()
{
  return InputA;
}
void VirtualXorGate::Set_InputA(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputA = input;
  A_B.Set_InputA(input);
  A__A_B.Set_InputA(input);
}

//*******//
//** B **//
//*******//
const VICE::Component::VirtualConnection * VirtualXorGate::Get_InputB()
{
  return InputB;
}
void VirtualXorGate::Set_InputB(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputB = input;
  A_B.Set_InputB(input);
  B__A_B.Set_InputB(input);
}

//************//
//** Output **//
//************//
const VirtualConnection * VirtualXorGate::Get_Output()
{
  return Output;
}
