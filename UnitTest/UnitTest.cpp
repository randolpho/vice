#include "TestFunctions.h"
#include <iostream>
#include <map>
#include <bitset>
using namespace std;
using namespace VICE::Component;

void PrintTestCaseHeader(int testNum, bool pass)
{
  cout << "  Test Case " << testNum << " ";
  if(pass)
  {
    cout << "{PASSED}";
  }
  else
  {
    cout << "{FAILED}";
  }
  cout << " --  ";
}

void PrintWireState(const map<string, bool> * state)
{
  map<string, bool>::const_iterator i = state->begin();
  map<string, bool>::const_iterator end = state->end();
  while(i!= end)
  {
    cout << i->first << ": " << i->second << "; ";
    i++;
  }
}

void BuildWires64(long val, VirtualConnection * wires)
{
  bitset<64> bits(val);
  for(int i=0; i<64; i++)
  {
    wires[i].On = bits[i];
  }
}

int ReadWires64(const VirtualConnection ** wires)
{
  bitset<64> bits;
  for(int i=0; i<64; i++)
  {
    bits[i] = wires[i]->On;
  }
  return (int)bits.to_ulong();
}

void PrintWires64(const VirtualConnection ** wires)
{
  for(int i=63; i>=0; i--)
  {
    cout << wires[i]->On;
  }
}

void BuildWires32(int val, VirtualConnection * wires)
{
  bitset<32> bits(val);
  for(int i=0; i<32; i++)
  {
    wires[i].On = bits[i];
  }
}

int ReadWires32(const VirtualConnection ** wires)
{
  bitset<32> bits;
  for(int i=0; i<32; i++)
  {
    bits[i] = wires[i]->On;
  }
  return (int)bits.to_ulong();
}

void PrintWires32(const VirtualConnection ** wires)
{
  for(int i=31; i>=0; i--)
  {
    cout << wires[i]->On;
  }
}
void BuildWires(int val, VirtualConnection * wires)
{
  bitset<4> bits(val);
  for(int i=0; i<4; i++)
  {
    wires[i].On = bits[i];
  }
}

void BuildWires2(int val, VirtualConnection * wires)
{
  bitset<2> bits(val);
  for(int i=0; i<2; i++)
  {
    wires[i].On = bits[i];
  }
}

int ReadWires(const VirtualConnection ** wires)
{
  bitset<4> bits;
  for(int i=0; i<4; i++)
  {
    bits[i] = wires[i]->On;
  }
  return (int)bits.to_ulong();
}

void PrintWires(const VirtualConnection ** wires)
{
  for(int i=3; i>=0; i--)
  {
    cout << wires[i]->On;
  }
}

int ReadWires8(const VirtualConnection ** wires)
{
  bitset<8> bits;
  for(int i=0; i<8; i++)
  {
    bits[i] = wires[i]->On;
  }
  return (int)bits.to_ulong();
}

void PrintWires8(const VirtualConnection ** wires)
{
  for(int i=7; i>=0; i--)
  {
    cout << wires[i]->On;
  }
}

void main()
{
  TestVirtualTransistor();
  TestVirtualJunction();
  TestVirtualAndGate();
  TestVirtualOrGate();
  TestVirtualInverter();
  TestVirtualNandGate();
  TestVirtualNorGate();
  TestVirtualXorGate();
  TestVirtualBinaryAdder();
  TestVirtual4BitAdder();
  TestVirtual4BitAdderSubtractor();
  TestVirtual32BitAdderSubtractor();
  TestVirtualFlipFlop();
  TestVirtualMultiplexer_4_1();
  TestVirtual4BitRegister();
  TestVirtual32BitRegister();
  TestVirtual64BitRegister();
  TestVirtual4BitMultiplier();
  TestVirtual32BitMultiplier();

  //cout << "Testing concluded. Press Enter to continue..." << endl;
  //char c;
  //cin >> c;
}