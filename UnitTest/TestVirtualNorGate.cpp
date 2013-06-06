#include "TestFunctions.h"
#include "VirtualNorGate.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Logic;
using namespace VICE::Component;

void TestVirtualNorGate()
{
  cout << "Testing VirtualNorGate:" << endl;

  VirtualNorGate norbert;

  // test case 1
  bool pass = false;
  norbert.Update();
  if(norbert.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(1, pass);
  PrintWireState(norbert.Get_WireState());
  cout << endl;

  // test case 2
  pass = false;
  norbert.Set_InputA(&VirtualConnection::AlwaysOn);
  norbert.Set_InputB(&VirtualConnection::AlwaysOff);
  norbert.Update();
  if(!norbert.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(2, pass);
  PrintWireState(norbert.Get_WireState());
  cout << endl;

  // test case 3
  pass = false;
  norbert.Set_InputA(&VirtualConnection::AlwaysOff);
  norbert.Set_InputB(&VirtualConnection::AlwaysOn);
  norbert.Update();
  if(!norbert.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(3, pass);
  PrintWireState(norbert.Get_WireState());
  cout << endl;

  // test case 4
  pass = false;
  norbert.Set_InputA(&VirtualConnection::AlwaysOn);
  norbert.Set_InputB(&VirtualConnection::AlwaysOn);
  norbert.Update();
  if(!norbert.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(4, pass);
  PrintWireState(norbert.Get_WireState());
  cout << endl;
}