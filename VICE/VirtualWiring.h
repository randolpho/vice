#pragma once
#include "VirtualConnection.h"
namespace VICE
{
  void BuildWires32(int val, VICE::Component::VirtualConnection * wires);
  int ReadWires32(const VICE::Component::VirtualConnection ** wires);
}