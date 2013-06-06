#pragma once
#include <map>
#include <string>
#include "VirtualConnection.h"
void PrintTestCaseHeader(int testNum, bool pass);
void PrintWireState(const std::map<std::string, bool> * state);
int ReadWires(const VICE::Component::VirtualConnection ** wires);
void BuildWires(int val, VICE::Component::VirtualConnection * wires);
void PrintWires(const VICE::Component::VirtualConnection ** wires);
void BuildWires2(int val, VICE::Component::VirtualConnection * wires);
void PrintWires32(const VICE::Component::VirtualConnection ** wires);
int ReadWires32(const VICE::Component::VirtualConnection ** wires);
void BuildWires32(int val, VICE::Component::VirtualConnection * wires);
void PrintWires64(const VICE::Component::VirtualConnection ** wires);
int ReadWires64(const VICE::Component::VirtualConnection ** wires);
void BuildWires64(long val, VICE::Component::VirtualConnection * wires);
int ReadWires8(const VICE::Component::VirtualConnection ** wires);
void PrintWires8(const VICE::Component::VirtualConnection ** wires);

void TestVirtualTransistor();
void TestVirtualJunction();
void TestVirtualAndGate();
void TestVirtualOrGate();
void TestVirtualInverter();
void TestVirtualNandGate();
void TestVirtualNorGate();
void TestVirtualXorGate();
void TestVirtualBinaryAdder();
void TestVirtual4BitAdder();
void TestVirtual4BitAdderSubtractor();
void TestVirtual32BitAdderSubtractor();
void TestVirtualFlipFlop();
void TestVirtualMultiplexer_4_1();
void TestVirtual4BitRegister();
void TestVirtual32BitRegister();
void TestVirtual64BitRegister();
void TestVirtual4BitMultiplier();
void TestVirtual32BitMultiplier();