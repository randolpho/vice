#include "TestFunctions.h"
#include "VirtualXorGate.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Logic;
using namespace VICE::Component;

void TestVirtualXorGate()
{
  cout << "Testing VirtualXorGate:" << endl;

  VirtualXorGate xoran;

  // test case 1
  bool pass = false;
  xoran.Update();
  if(!xoran.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(1, pass);
  PrintWireState(xoran.Get_WireState());
  cout << endl;

  // test case 2
  pass = false;
  xoran.Set_InputA(&VirtualConnection::AlwaysOn);
  xoran.Set_InputB(&VirtualConnection::AlwaysOff);
  xoran.Update();
  if(xoran.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(2, pass);
  PrintWireState(xoran.Get_WireState());
  cout << endl;

  // test case 3
  pass = false;
  xoran.Set_InputA(&VirtualConnection::AlwaysOff);
  xoran.Set_InputB(&VirtualConnection::AlwaysOn);
  xoran.Update();
  if(xoran.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(3, pass);
  PrintWireState(xoran.Get_WireState());
  cout << endl;

  // test case 4
  pass = false;
  xoran.Set_InputA(&VirtualConnection::AlwaysOn);
  xoran.Set_InputB(&VirtualConnection::AlwaysOn);
  xoran.Update();
  if(!xoran.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(4, pass);
  PrintWireState(xoran.Get_WireState());
  cout << endl;
}