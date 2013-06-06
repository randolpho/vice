#include "TestFunctions.h"
#include "VirtualNandGate.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Logic;
using namespace VICE::Component;

void TestVirtualNandGate()
{
  cout << "Testing VirtualNandGate:" << endl;

  VirtualNandGate nancy;

  // test case 1
  bool pass = false;
  nancy.Update();
  if(nancy.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(1, pass);
  PrintWireState(nancy.Get_WireState());
  cout << endl;

  // test case 2
  pass = false;
  nancy.Set_InputA(&VirtualConnection::AlwaysOn);
  nancy.Set_InputB(&VirtualConnection::AlwaysOff);
  nancy.Update();
  if(nancy.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(2, pass);
  PrintWireState(nancy.Get_WireState());
  cout << endl;

  // test case 3
  pass = false;
  nancy.Set_InputA(&VirtualConnection::AlwaysOff);
  nancy.Set_InputB(&VirtualConnection::AlwaysOn);
  nancy.Update();
  if(nancy.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(3, pass);
  PrintWireState(nancy.Get_WireState());
  cout << endl;

  // test case 4
  pass = false;
  nancy.Set_InputA(&VirtualConnection::AlwaysOn);
  nancy.Set_InputB(&VirtualConnection::AlwaysOn);
  nancy.Update();
  if(!nancy.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(4, pass);
  PrintWireState(nancy.Get_WireState());
  cout << endl;

}