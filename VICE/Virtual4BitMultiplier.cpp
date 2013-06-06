#include "StdAfx.h"
#include "Virtual4BitMultiplier.h"
#include <stdexcept>
using namespace VICE::Logic;
using namespace VICE::Component;
using namespace VICE::Arithmetic;
using namespace VICE::Arithmetic;

Virtual4BitMultiplier::Virtual4BitMultiplier() : CarryAllower(true)
{
  for(int i=0; i<4; i++)
  {
    InputA[i] = &VirtualConnection::AlwaysOff;
    InputB[i] = &VirtualConnection::AlwaysOff;
    Product[i] = Multiplier.Get_Output(i);
    Product[i+4] = Accumulator.Get_Output(i);
  }

  OutputCarry = Carry.Get_Output();
  Carry.Set_InputA(&CarryAllower);
  Carry.Set_InputB(Adder.Get_OutputCarry());

  Multiplier.Set_Shift(Accumulator.Get_Output(0));
  Multiplier.Set_Control(MultiplierControl);

  Multiplicand.Set_Control(MultiplicandControl);

  Accumulator.Set_Shift(Carry.Get_Output());
  Accumulator.Set_Input(Adder.Get_Sum());
  Accumulator.Set_Control(AccumulatorControl);

  Adder.Set_InputA(Accumulator.Get_Output());
  Adder.Set_InputB(Multiplicand.Get_Output());

#ifdef _DEBUG
  UpdateWireState();
#endif
}

void Virtual4BitMultiplier::Update()
{
  // first, load the registers (Accumulator should have default 0 value)
  SetControl(3, MultiplicandControl);
  Multiplicand.Update();
  SetControl(3, MultiplierControl);
  Multiplier.Update();

  // multiplier will only ever right shift from now on. 
  SetControl(1, MultiplierControl);
  for(int i=0; i<4; i++)
  {
    if(Multiplier.Get_Output(0)->On)
    {
      // add
      Adder.Update();
      SetControl(3, AccumulatorControl);
      Accumulator.Update();
      CarryAllower.On = true;
    }
    else
    {
      CarryAllower.On = false;
    }
    Carry.Update();

    // shift right
    Multiplier.Update();
    SetControl(1, AccumulatorControl);
    Accumulator.Update();
  }

#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void Virtual4BitMultiplier::UpdateWireState()
{
  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "A")] = InputA[i]->On;
  }

  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "B")] = InputB[i]->On;
  }

  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "Product")] = Product[i]->On;
  }

  WireState["C(out)"] = OutputCarry->On;
}
#endif

void Virtual4BitMultiplier::SetControl(int command, VirtualConnection * control)
{
  switch(command)
  {
  default:
  case 0:
    control[0].On = false;
    control[1].On = false;
    break;
  case 1:
    control[0].On = true;
    control[1].On = false;
    break;
  case 2:
    control[0].On = false;
    control[1].On = true;
    break;
  case 3:
    control[0].On = true;
    control[1].On = true;
    break;
  }
}

//*******//
//** A **//
//*******//
const VirtualConnection * Virtual4BitMultiplier::Get_InputA(int bit)
{
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  return InputA[bit];
}
const VirtualConnection ** Virtual4BitMultiplier::Get_InputA()
{
  return InputA;
}
void Virtual4BitMultiplier::Set_InputA(const VirtualConnection * input, int bit)
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
  Multiplicand.Set_Input(input, bit);
}
void Virtual4BitMultiplier::Set_InputA(const VirtualConnection * input)
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
void Virtual4BitMultiplier::Set_InputA(const VirtualConnection ** input)
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
const VirtualConnection * Virtual4BitMultiplier::Get_InputB(int bit)
{
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  return InputB[bit];
}
const VirtualConnection ** Virtual4BitMultiplier::Get_InputB()
{
  return InputB;
}
void Virtual4BitMultiplier::Set_InputB(const VirtualConnection * input, int bit)
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
  Multiplier.Set_Input(input, bit);
}
void Virtual4BitMultiplier::Set_InputB(const VirtualConnection * input)
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
void Virtual4BitMultiplier::Set_InputB(const VirtualConnection ** input)
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

//*************//
//** Product **//
//*************//
const VICE::Component::VirtualConnection * Virtual4BitMultiplier::Get_Product(int bit)
{
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  return Product[bit];
}
const VICE::Component::VirtualConnection ** Virtual4BitMultiplier::Get_Product()
{
  return Product;
}

//*****************//
//** OutputCarry **//
//*****************//
const VICE::Component::VirtualConnection * Virtual4BitMultiplier::Get_OutputCarry()
{
  return OutputCarry;
}
