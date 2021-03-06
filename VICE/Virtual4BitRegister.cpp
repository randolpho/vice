#include "StdAfx.h"
#include "Virtual4BitRegister.h"
using namespace VICE::Memory;
using namespace VICE::Component;

Virtual4BitRegister::Virtual4BitRegister(void) : Shift(&VirtualConnection::AlwaysOff)
{
  for(int i=0; i<4; i++)
  {
    Output[i] = Bits[i].Get_Output();
    Input[i] = &VirtualConnection::AlwaysOff;
    MuxInverters[i].Set_Input(BitControl[i].Get_Output());
    Bits[i].Set_InputSet(BitControl[i].Get_Output());
    Bits[i].Set_InputReset(MuxInverters[i].Get_Output());
    // set the output of each bit to the 0 control input of its multiplexer
    BitControl[i].Set_Input(Bits[i].Get_Output(), 0);
    // set the output of each bit to the 2 control input of the bit to the left
    if(i < 3)
    {
      BitControl[i+1].Set_Input(Bits[i].Get_Output(), 2);
    }
    // set the output of each bit to the 1 control input of the bit to the right
    if(i > 0)
    {
      BitControl[i-1].Set_Input(Bits[i].Get_Output(), 1);
    }
  }
  for(int i=0; i<2; i++)
  {
    Control[i] = &VirtualConnection::AlwaysOff;
  }
#ifdef _DEBUG
  UpdateWireState();
#endif
}

void Virtual4BitRegister::Update()
{
  // NOTE: I cannot merge these into a single loop because 
  // the BitControl during shifting depends upon the 
  // current state a separate Bit -- all BitControls have
  // to be updated before any of the Bits are updated. 
  for(int i=0; i<4; i++)
  {
    BitControl[i].Update();
  }
  for(int i=0; i<4; i++)
  {
    MuxInverters[i].Update();
  }
  for(int i=0; i<4; i++)
  {
    Bits[i].Update();
  }

#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void Virtual4BitRegister::UpdateWireState()
{
  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "Input")] = Input[i]->On;
  }
  for(int i=0; i<2; i++)
  {
    WireState[BuildWireStateName(i, "Control")] = Control[i]->On;
  }
  WireState["Shift"] = Shift->On;
  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "Output")] = Output[i]->On;
  }
}
#endif

//***********//
//** Input **//
//***********//
const VirtualConnection * Virtual4BitRegister::Get_Input(int bit)
{
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  return Input[bit];
}
const VirtualConnection ** Virtual4BitRegister::Get_Input()
{
  return Input;
}
void Virtual4BitRegister::Set_Input(const VirtualConnection * input, int bit)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  Input[bit] = input;
  BitControl[bit].Set_Input(input, 3);
}
void Virtual4BitRegister::Set_Input(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  for(int i=0; i<4; i++)
  {
    Set_Input(&input[i], i);
  }
}
void Virtual4BitRegister::Set_Input(const VirtualConnection ** input)
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
    Set_Input(input[i], i);
  }
}

//*************//
//** Control **//
//*************//
const VirtualConnection * Virtual4BitRegister::Get_Control(int bit)
{
  if(bit < 0 || bit > 1)
  {
    throw std::invalid_argument("bit must be between 0 and 1");
  }
  return Control[bit];
}
const VirtualConnection ** Virtual4BitRegister::Get_Control()
{
  return Control;
}
void Virtual4BitRegister::Set_Control(const VirtualConnection * input, int bit)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  if(bit < 0 || bit > 1)
  {
    throw std::invalid_argument("bit must be between 0 and 1");
  }
  Control[bit] = input;
  for(int i=0; i<4; i++)
  {
    BitControl[i].Set_Select(input, bit);
  }
}
void Virtual4BitRegister::Set_Control(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  for(int i=0; i<2; i++)
  {
    Set_Control(&input[i], i);
  }
}
void Virtual4BitRegister::Set_Control(const VirtualConnection ** input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  for(int i=0; i<2; i++)
  {
    if(input[i] == NULL)
    {
      throw std::invalid_argument("input cannot contain a null pointer");
    }
    Set_Control(input[i], i);
  }
}

//***********//
//** Shift **//
//***********//
const VirtualConnection * Virtual4BitRegister::Get_Shift()
{
  return Shift;
}
void Virtual4BitRegister::Set_Shift(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  Shift = input;
  BitControl[0].Set_Input(input, 2);
  BitControl[3].Set_Input(input, 1);
}

//************//
//** Output **//
//************//
const VirtualConnection * Virtual4BitRegister::Get_Output(int bit)
{
  if(bit < 0 || bit > 3)
  {
    throw std::invalid_argument("bit must be between 0 and 3");
  }
  return Output[bit];
}
const VirtualConnection ** Virtual4BitRegister::Get_Output()
{
  return Output;
}