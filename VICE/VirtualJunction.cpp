#include "StdAfx.h"
#include "VirtualJunction.h"
using namespace VICE::Component;
using namespace std;

VirtualJunction::VirtualJunction(void) : Output(false)
{
#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualJunction::UpdateWireState()
{
  int size = (int)Inputs.size();
  string name;
  bool on;
  for(int i=0 ; i < size; i++)
  {
    name = BuildWireStateName(i, "Input");
    on = Inputs[i]->On;
    WireState[name] = on;
  }
  WireState["Output"] = Output.On;
}
#endif



void VirtualJunction::Update()
{
  if(Inputs.size() == 0)
  {
    Output.On = false;
    return;
  }
  Output.On = false;
  vector<const VirtualConnection *>::const_iterator i = Inputs.begin();
  vector<const VirtualConnection *>::const_iterator end = Inputs.end(); 
  for( ; i != end; i++)
  {
    if((*i)->On)
    {
      Output.On = true;
#ifdef _DEBUG
      UpdateWireState();
#endif
      return;
    }
  }

#ifdef _DEBUG
  UpdateWireState();
#endif
}

const VirtualConnection * VirtualJunction::Get_Output()
{
  return &Output;
}

void VirtualJunction::Add_Input(const VirtualConnection *input)
{
  if(input == NULL)
  {
    throw invalid_argument("input cannot be null");
  }
  Inputs.push_back(input);
}
