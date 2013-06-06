#include "TestFunctions.h"
#include "VirtualJunction.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Component;


void TestVirtualJunction()
{
  cout << "Testing VirtualJunction:" << endl;

  VirtualJunction junky;

  // test case 1
  bool pass = false;
  junky.Update();
  if(!junky.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(1, pass);
  //cout << "No Inputs Added; Output: " << junky.Get_Output()->On << endl;
  PrintWireState(junky.Get_WireState());
  cout << endl;

  // test case 2
  pass = false;
  VirtualJunction junky2;
  junky2.Add_Input(&VirtualConnection::AlwaysOff);
  junky2.Add_Input(&VirtualConnection::AlwaysOff);
  junky2.Add_Input(&VirtualConnection::AlwaysOff);
  junky2.Update();
  if(!junky2.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(2, pass);
  //cout << "Input 1: 0; Input 2: 0; Input 3: 0; Output: " << junky2.Get_Output()->On << endl;
  PrintWireState(junky2.Get_WireState());
  cout << endl;
  
  // test case 3
  pass = false;
  VirtualJunction junky3;
  junky3.Add_Input(&VirtualConnection::AlwaysOff);
  junky3.Add_Input(&VirtualConnection::AlwaysOn);
  junky3.Add_Input(&VirtualConnection::AlwaysOff);
  junky3.Update();
  if(junky3.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(3, pass);
  //cout << "Input 1: 0; Input 2: 1; Input 3: 0; Output: " << junky3.Get_Output()->On << endl;
  PrintWireState(junky3.Get_WireState());
  cout << endl;

  // test case 4
  pass = false;
  VirtualJunction junky4;
  junky4.Add_Input(&VirtualConnection::AlwaysOn);
  junky4.Add_Input(&VirtualConnection::AlwaysOn);
  junky4.Add_Input(&VirtualConnection::AlwaysOn);
  junky4.Update();
  if(junky4.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(4, pass);
  //cout << "Input 1: 1; Input 2: 1; Input 3: 1; Output: " << junky4.Get_Output()->On << endl;
  PrintWireState(junky4.Get_WireState());
  cout << endl;
}
