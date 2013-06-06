#include "StdAfx.h"
#include "VirtualTransistor.h"
#include <stdexcept>
using namespace VICE::Component;

VirtualTransistor::VirtualTransistor() : Collector(&VirtualConnection::AlwaysOff), Base(&VirtualConnection::AlwaysOff)
{
#ifdef _DEBUG
  UpdateWireState();
#endif
}

#ifdef _DEBUG
void VirtualTransistor::UpdateWireState()
{
  WireState["Collector"] = Collector->On;
  WireState["Base"] = Base->On;
  WireState["Emitter"] = Emitter.On;
}
#endif

void VirtualTransistor::Update()
{
  if(Collector->On && Base->On)
  {
    Emitter.On = true;
  }
  else
  {
    Emitter.On = false;
  }

#ifdef _DEBUG
  UpdateWireState();
#endif
}

//*************//
//** Emitter **//
//*************//
const VirtualConnection * VirtualTransistor::Get_Emitter()
{
  return &Emitter;
}

//***************//
//** Collector **//
//***************//
const VirtualConnection * VirtualTransistor::Get_Collector()
{
  return Collector;
}

void VirtualTransistor::Set_Collector(const VirtualConnection * collector)
{
  if(collector == NULL)
  {
    throw std::invalid_argument("collector cannot be null");
  }
  Collector = collector;
}

//**********//
//** Base **//
//**********//
const VirtualConnection * VirtualTransistor::Get_Base()
{
  return Base;
}
void VirtualTransistor::Set_Base(const VirtualConnection * base)
{
  if(base == NULL)
  {
    throw std::invalid_argument("base cannot be null");
  }
  Base = base;
}
