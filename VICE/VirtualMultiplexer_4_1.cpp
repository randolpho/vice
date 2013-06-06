#include "StdAfx.h"
#include "VirtualMultiplexer_4_1.h"
#include <stdexcept>

using namespace VICE::Control;
using namespace VICE::Component;

VirtualMultiplexer_4_1::VirtualMultiplexer_4_1()
{
  for(int i=0; i<4; i++)
  {
    Input[i] = &VirtualConnection::AlwaysOff;
    InputAnders[i].Set_InputB(SelectAnders[i].Get_Output());
  }
  for(int i=0; i<2; i++)
  {
    Select[i] = &VirtualConnection::AlwaysOff;
  }
  Output = OutputAccumulator.Get_Output();
  OutputAccumulator.Set_InputA(InputAccumulator_0_1.Get_Output());
  OutputAccumulator.Set_InputB(InputAccumulator_2_3.Get_Output());
  InputAccumulator_0_1.Set_InputA(InputAnders[0].Get_Output());
  InputAccumulator_0_1.Set_InputB(InputAnders[1].Get_Output());
  InputAccumulator_2_3.Set_InputA(InputAnders[2].Get_Output());
  InputAccumulator_2_3.Set_InputB(InputAnders[3].Get_Output());

  SelectAnders[0].Set_InputA(SelectInverters[1].Get_Output());
  SelectAnders[1].Set_InputA(SelectInverters[1].Get_Output());
  SelectAnders[0].Set_InputB(SelectInverters[0].Get_Output());
  SelectAnders[2].Set_InputB(SelectInverters[0].Get_Output());


#ifdef _DEBUG
  UpdateWireState();
#endif
}

void VirtualMultiplexer_4_1::Update()
{
  for(int i=0; i<2; i++)
  {
    SelectInverters[i].Update();
  }
  for(int i=0; i<4; i++)
  {
    SelectAnders[i].Update();
    InputAnders[i].Update();
  }
  InputAccumulator_0_1.Update();
  InputAccumulator_2_3.Update();
  OutputAccumulator.Update();

#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualMultiplexer_4_1::UpdateWireState()
{
  for(int i=0; i<4; i++)
  {
    WireState[BuildWireStateName(i, "I")] = Input[i]->On;
  }

  for(int i=0; i<2; i++)
  {
    WireState[BuildWireStateName(i, "S")] = Select[i]->On;
  }

  WireState["Output"] = Output->On;
}
#endif

//***********//
//** Input **//
//***********//
const VICE::Component::VirtualConnection * VirtualMultiplexer_4_1::Get_Input(int line)
{
  if(line < 0 || line > 3)
  {
    throw std::invalid_argument("line must be between 0 and 3");
  }
  return Input[line];
}
const VICE::Component::VirtualConnection ** VirtualMultiplexer_4_1::Get_Input()
{
  return Input;
}
void VirtualMultiplexer_4_1::Set_Input(const VirtualConnection * input, int line)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  if(line < 0 || line > 3)
  {
    throw std::invalid_argument("line must be between 0 and 3");
  }
  Input[line] = input;
  InputAnders[line].Set_InputA(input);
}
void VirtualMultiplexer_4_1::Set_Input(const VirtualConnection * input)
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
void VirtualMultiplexer_4_1::Set_Input(const VirtualConnection ** input)
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

//************//
//** Select **//
//************//
const VICE::Component::VirtualConnection * VirtualMultiplexer_4_1::Get_Select(int bit)
{
  if(bit < 0 || bit > 1)
  {
    throw std::invalid_argument("bit must be between 0 and 1");
  }
  return Select[bit];
}
const VICE::Component::VirtualConnection ** VirtualMultiplexer_4_1::Get_Select()
{
  return Select;
}
void VirtualMultiplexer_4_1::Set_Select(const VirtualConnection * input, int bit)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  if(bit < 0 || bit > 1)
  {
    throw std::invalid_argument("bit must be between 0 and 1");
  }
  Select[bit] = input;
  SelectInverters[bit].Set_Input(input);
  if(bit == 0)
  {
    SelectAnders[1].Set_InputB(input);
    SelectAnders[3].Set_InputB(input);
  }
  else
  {
    SelectAnders[2].Set_InputA(input);
    SelectAnders[3].Set_InputA(input);
  }
}
void VirtualMultiplexer_4_1::Set_Select(const VirtualConnection * input)
{
  if(input == NULL)
  {
    throw std::invalid_argument("input cannot be null");
  }
  for(int i=0; i<2; i++)
  {
    Set_Select(&input[i], i);
  }
}
void VirtualMultiplexer_4_1::Set_Select(const VirtualConnection ** input)
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
    Set_Select(input[i], i);
  }
}
//************//
//** Output **//
//************//
const VICE::Component::VirtualConnection * VirtualMultiplexer_4_1::Get_Output()
{
  return Output;
}