#include "TestFunctions.h"
#include "VirtualOrGate.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Logic;
using namespace VICE::Component;


void TestVirtualOrGate()
{
  cout << "Testing VirtualOrGate:" << endl;

  VirtualOrGate orrell;

  // test case 1
  bool pass = false;
  orrell.Update();
  if(!orrell.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(1, pass);
  PrintWireState(orrell.Get_WireState());
  cout << endl;

  // test case 2
  pass = false;
  orrell.Set_InputA(&VirtualConnection::AlwaysOn);
  orrell.Set_InputB(&VirtualConnection::AlwaysOff);
  orrell.Update();
  if(orrell.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(2, pass);
  PrintWireState(orrell.Get_WireState());
  cout << endl;

  // test case 3
  pass = false;
  orrell.Set_InputA(&VirtualConnection::AlwaysOff);
  orrell.Set_InputB(&VirtualConnection::AlwaysOn);
  orrell.Update();
  if(orrell.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(3, pass);
  PrintWireState(orrell.Get_WireState());
  cout << endl;

  // test case 4
  pass = false;
  orrell.Set_InputA(&VirtualConnection::AlwaysOn);
  orrell.Set_InputB(&VirtualConnection::AlwaysOn);
  orrell.Update();
  if(orrell.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(4, pass);
  PrintWireState(orrell.Get_WireState());
  cout << endl;
  
}
