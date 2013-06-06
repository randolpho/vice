#include "VirtualWiring.h"
#include <bitset>
using namespace std;
using namespace VICE;
using namespace VICE::Component;

void VICE::BuildWires32(int val, VirtualConnection * wires)
{
  bitset<32> bits(val);
  for(int i=0; i<32; i++)
  {
    wires[i].On = bits[i];
  }
}

int VICE::ReadWires32(const VirtualConnection ** wires)
{
  bitset<32> bits;
  for(int i=0; i<32; i++)
  {
    bits[i] = wires[i]->On;
  }
  return (int)bits.to_ulong();
}