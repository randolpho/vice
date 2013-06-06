#include "TestFunctions.h"
#include "VirtualFlipFlop.h"
#include "VirtualConnection.h"
#include <iostream>
using namespace std;
using namespace VICE::Component;


void TestVirtualFlipFlop()
{
  cout << "Testing VirtualFlipFlop:" << endl;

  VirtualFlipFlop flipper;
  VirtualConnection Set(false);
  VirtualConnection Reset(false);
  flipper.Set_InputSet(&Set);
  flipper.Set_InputReset(&Reset);
  int testNum = 1;

  // test case 1 -- set
  bool pass = false;
  Set.On = true;
  Reset.On = false;
  flipper.Update();
  if(flipper.Get_Output()->On && !flipper.Get_NotOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(testNum++, pass);
  cout << "Set         -- ";
  PrintWireState(flipper.Get_WireState());
  cout << endl;

  // test case 2 -- reset
  pass = false;
  Set.On = false;
  Reset.On = true;
  flipper.Update();
  if(!flipper.Get_Output()->On && flipper.Get_NotOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(testNum++, pass);
  cout << "Reset       -- ";
  PrintWireState(flipper.Get_WireState());
  cout << endl;

  // test case 3 -- toggle
  pass = false;
  Set.On = true;
  Reset.On = true;
  flipper.Update();
  if(flipper.Get_Output()->On && !flipper.Get_NotOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(testNum++, pass);
  cout << "Toggle      -- ";
  PrintWireState(flipper.Get_WireState());
  cout << endl;

  // test case 4 -- toggle
  pass = false;
  Set.On = true;
  Reset.On = true;
  flipper.Update();
  if(!flipper.Get_Output()->On && flipper.Get_NotOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(testNum++, pass);
  cout << "Toggle Back -- ";
  PrintWireState(flipper.Get_WireState());
  cout << endl;

  // test case 5 -- do nothing
  pass = false;
  Set.On = false;
  Reset.On = false;
  flipper.Update();
  if(!flipper.Get_Output()->On && flipper.Get_NotOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(testNum++, pass);
  cout << "Nada        -- ";
  PrintWireState(flipper.Get_WireState());
  cout << endl;

  Set.On = true;
  Reset.On = true;
  flipper.Update();
  // test case 5 -- do nothing
  pass = false;
  Set.On = false;
  Reset.On = false;
  flipper.Update();
  if(flipper.Get_Output()->On && !flipper.Get_NotOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(testNum++, pass);
  cout << "Flip/Nada   -- ";
  PrintWireState(flipper.Get_WireState());
  cout << endl;
}
