#include "TestFunctions.h"
#include "VirtualInverter.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Component;
using namespace VICE::Logic;


void TestVirtualInverter()
{
  cout << "Testing VirtualInverter:" << endl;

  VirtualInverter inigo;

  // test case 1
  bool pass = false;
  inigo.Set_Input(&VirtualConnection::AlwaysOff);
  inigo.Update();
  if(inigo.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(1, pass);
  PrintWireState(inigo.Get_WireState());
  cout << endl;

  // test case 2
  pass = false;
  inigo.Set_Input(&VirtualConnection::AlwaysOn);
  inigo.Update();
  if(!inigo.Get_Output()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(2, pass);
  PrintWireState(inigo.Get_WireState());
  cout << endl;
  
}
