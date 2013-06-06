#include "TestFunctions.h"
#include "VirtualAndGate.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Logic;
using namespace VICE::Component;


void TestVirtualAndGate()
{
  cout << "Testing VirtualAndGate:" << endl;

  VirtualAndGate andy;

  // test case 1
  bool pass = false;
  andy.Update();
  if(!andy.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(1, pass);
  PrintWireState(andy.Get_WireState());
  cout << endl;

  // test case 2
  pass = false;
  andy.Set_InputA(&VirtualConnection::AlwaysOn);
  andy.Set_InputB(&VirtualConnection::AlwaysOff);
  andy.Update();
  if(!andy.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(2, pass);
  PrintWireState(andy.Get_WireState());
  cout << endl;

  // test case 3
  pass = false;
  andy.Set_InputA(&VirtualConnection::AlwaysOff);
  andy.Set_InputB(&VirtualConnection::AlwaysOn);
  andy.Update();
  if(!andy.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(3, pass);
  PrintWireState(andy.Get_WireState());
  cout << endl;

  // test case 4
  pass = false;
  andy.Set_InputA(&VirtualConnection::AlwaysOn);
  andy.Set_InputB(&VirtualConnection::AlwaysOn);
  andy.Update();
  if(andy.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(4, pass);
  PrintWireState(andy.Get_WireState());
  cout << endl;
  
}
