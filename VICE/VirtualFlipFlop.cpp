#include "StdAfx.h"
#include "VirtualFlipFlop.h"
#include <stdexcept>
using namespace VICE::Component;

VirtualFlipFlop::VirtualFlipFlop() : InputSet(&VirtualConnection::AlwaysOff), InputReset(&VirtualConnection::AlwaysOff), Output(false), NotOutput(true)
{
#ifdef _DEBUG
  UpdateWireState();
#endif
}

void VirtualFlipFlop::Update()
{
  if(InputSet->On && InputReset->On)
  {
    // toggle
    Output.On = !Output.On;
  }
  else
  {
    if(InputSet->On)
    {
      Output.On = true;
    }
    if(InputReset->On)
    {
      Output.On = false;
    }
  }
  NotOutput.On = !Output.On;
#ifdef _DEBUG
  UpdateWireState();
#endif
}
#ifdef _DEBUG
void VirtualFlipFlop::UpdateWireState()
{
  WireState["J"] = InputSet->On;
  WireState["K"] = InputReset->On;
  WireState["Q"] = Output.On;
  WireState["Q'"] = NotOutput.On;
}
#endif

//**************//
//** InputSet **//
//**************//
const VICE::Component::VirtualConnection * VirtualFlipFlop::Get_InputSet()
{
  return InputSet;
}
void VirtualFlipFlop::Set_InputSet(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputSet = input;
}

//****************//
//** InputReset **//
//****************//
const VICE::Component::VirtualConnection * VirtualFlipFlop::Get_InputReset()
{
  return InputReset;
}
void VirtualFlipFlop::Set_InputReset(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  InputReset = input;
}

//************//
//** Output **//
//************//
const VirtualConnection * VirtualFlipFlop::Get_Output()
{
  return &Output;
}

//***************//
//** NotOutput **//
//***************//
const VirtualConnection * VirtualFlipFlop::Get_NotOutput()
{
  return &NotOutput;
}