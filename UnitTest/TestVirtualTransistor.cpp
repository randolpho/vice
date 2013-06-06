#include "TestFunctions.h"
#include "VirtualTransistor.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Component;


void TestVirtualTransistor()
{
  cout << "Testing VirtualTransistor:" << endl;

  VirtualTransistor tranny;

  // test case 1
  bool pass = false;
  tranny.Update();
  if(!tranny.Get_Emitter()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(1, pass);
  PrintWireState(tranny.Get_WireState());
  cout << endl;

  // test case 2
  pass = false;
  tranny.Set_Base(&VirtualConnection::AlwaysOn);
  tranny.Set_Collector(&VirtualConnection::AlwaysOff);
  tranny.Update();
  if(!tranny.Get_Emitter()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(2, pass);
  PrintWireState(tranny.Get_WireState());
  cout << endl;

  // test case 3
  pass = false;
  tranny.Set_Base(&VirtualConnection::AlwaysOff);
  tranny.Set_Collector(&VirtualConnection::AlwaysOn);
  tranny.Update();
  if(!tranny.Get_Emitter()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(3, pass);
  PrintWireState(tranny.Get_WireState());
  cout << endl;

  // test case 4
  pass = false;
  tranny.Set_Base(&VirtualConnection::AlwaysOn);
  tranny.Set_Collector(&VirtualConnection::AlwaysOn);
  tranny.Update();
  if(tranny.Get_Emitter()->On)
  {
    pass = true;
  };
  PrintTestCaseHeader(4, pass);
  PrintWireState(tranny.Get_WireState());
  cout << endl;
  
}
