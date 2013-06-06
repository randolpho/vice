#include "StdAfx.h"
#include "VirtualInverter.h"
#include <stdexcept>
using namespace VICE::Logic;
using namespace VICE::Component;

VirtualInverter::VirtualInverter(void) : Output(false), Input(&VirtualConnection::AlwaysOff)
{
#ifdef _DEBUG
  UpdateWireState();
#endif
}

void VirtualInverter::Update()
{
  Output.On = !Input->On;
#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualInverter::UpdateWireState()
{
  WireState["Input"] = Input->On;
  WireState["Output"] = Output.On;
}
#endif

//***********//
//** Input **//
//***********//
const VICE::Component::VirtualConnection * VirtualInverter::Get_Input()
{
  return Input;
}
void VirtualInverter::Set_Input(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  Input = input;
}

//************//
//** Output **//
//************//
const VirtualConnection * VirtualInverter::Get_Output()
{
  return &Output;
}
