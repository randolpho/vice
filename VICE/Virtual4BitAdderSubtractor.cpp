#include "StdAfx.h"
#include "Virtual4BitAdderSubtractor.h"
#include <stdexcept>
#include <sstream>
using namespace VICE::Logic;
using namespace VICE::Component;
using namespace VICE::Arithmetic;

Virtual4BitAdderSubtractor::Virtual4BitAdderSubtractor() : SubtractionControl(&VirtualConnection::AlwaysOff)
{
  for(int i=0; i<4; i++)
  {
    InputA[i] = &VirtualConnection::AlwaysOff;
    InputB[i] = &VirtualConnection::AlwaysOff;
    Adder[i].Set_InputB(Negater[i].Get_Output());
    Sum[i] = Adder[i].Get_Sum();
  }

  OutputCarry = Adder[3].Get_CarryOutput();

  for(int i=1; i<4; i++)
  {
    Adder[i].Set_InputCarry(Adder[i-1].Get_CarryOutput());
  }

#ifdef _DEBUG
  UpdateWireState();
#endif
}

void Virtual4BitAdderSubtractor::Update()
{
  for(int i=0; i<4; i++)
  {
    Negater[i].Update();
    Adder[i].Update();
  }
#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void Virtual4BitAdderSubtractor::UpdateWireState()
{
  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "A")] = InputA[i]->On;
  }

  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "B")] = InputB[i]->On;
  }

  WireState["C(in)"] = SubtractionControl->On;

  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "Sum")] = Sum[i]->On;
  }

  WireState["C(out)"] = OutputCarry->On;
}
#endif

//*******//
//** A **//
//*******//
const VICE::Component::VirtualConnection * Virtual4BitAdderSubtractor::Get_InputA(int bit)
{
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  return InputA[bit];
}
const VICE::Component::VirtualConnection ** Virtual4BitAdderSubtractor::Get_InputA()
{
  return InputA;
}
void Virtual4BitAdderSubtractor::Set_InputA(const VirtualConnection * input, int bit)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  InputA[bit] = input;
  Adder[bit].Set_InputA(input);
}
void Virtual4BitAdderSubtractor::Set_InputA(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  for(int i=0; i<4; i++)
  {
    Set_InputA(&input[i], i);
  }
}
void Virtual4BitAdderSubtractor::Set_InputA(const VirtualConnection ** input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  for(int i=0; i<4; i++)
  {
    if(input[i] == NULL)
    {
      throw std::invalid_argument("input cannot contain a null pointer");
    }
    Set_InputA(input[i], i);
  }
}

//*******//
//** B **//
//*******//
const VICE::Component::VirtualConnection * Virtual4BitAdderSubtractor::Get_InputB(int bit)
{
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  return InputB[bit];
}
const VICE::Component::VirtualConnection ** Virtual4BitAdderSubtractor::Get_InputB()
{
  return InputB;
}
void Virtual4BitAdderSubtractor::Set_InputB(const VirtualConnection * input, int bit)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  InputB[bit] = input;
  Negater[bit].Set_InputB(input);
}
void Virtual4BitAdderSubtractor::Set_InputB(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  for(int i=0; i<4; i++)
  {
    Set_InputB(&input[i], i);
  }
}
void Virtual4BitAdderSubtractor::Set_InputB(const VirtualConnection ** input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  for(int i=0; i<4; i++)
  {
    if(input[i] == NULL)
    {
      throw std::invalid_argument("input cannot contain a null pointer");
    }
    Set_InputB(input[i], i);
  }
}

//************************//
//** SubtractionControl **//
//************************//
const VICE::Component::VirtualConnection * Virtual4BitAdderSubtractor::Get_SubtractionControl()
{
  return SubtractionControl;
}
void Virtual4BitAdderSubtractor::Set_SubtractionControl(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  SubtractionControl = input;
  Adder[0].Set_InputCarry(input);
  for(int i=0; i<4; i++)
  {
    Negater[i].Set_InputA(input);
  }
}

//*********//
//** Sum **//
//*********//
const VICE::Component::VirtualConnection * Virtual4BitAdderSubtractor::Get_Sum(int bit)
{
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  return Sum[bit];
}
const VICE::Component::VirtualConnection ** Virtual4BitAdderSubtractor::Get_Sum()
{
  return Sum;
}

//*****************//
//** OutputCarry **//
//*****************//
const VICE::Component::VirtualConnection * Virtual4BitAdderSubtractor::Get_OutputCarry()
{
  return OutputCarry;
}