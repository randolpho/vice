#include "TestFunctions.h"
#include "VirtualBinaryAdder.h"
#include <iostream>
using namespace std;
using namespace VICE::Arithmetic;
using namespace VICE::Component;
void TestVirtualBinaryAdder()
{
  cout << "Testing VirtualBinaryAdder:" << endl;
  VirtualBinaryAdder binaka;

  // test case 1
  bool pass = false;
  binaka.Set_InputA(&VirtualConnection::AlwaysOff);
  binaka.Set_InputB(&VirtualConnection::AlwaysOff);
  binaka.Set_InputCarry(&VirtualConnection::AlwaysOff);
  binaka.Update();
  if(!binaka.Get_Sum()->On && !binaka.Get_CarryOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(1, pass);
  PrintWireState(binaka.Get_WireState());
  cout << endl;
  //cout << "A: 0; B: 0; C In: 0; Sum: " << binaka.Get_Sum()->On << "; C Out: " << binaka.Get_CarryOutput()->On << endl;

  // test case 2
  pass = false;
  binaka.Set_InputA(&VirtualConnection::AlwaysOff);
  binaka.Set_InputB(&VirtualConnection::AlwaysOff);
  binaka.Set_InputCarry(&VirtualConnection::AlwaysOn);
  binaka.Update();
  if(binaka.Get_Sum()->On && !binaka.Get_CarryOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(2, pass);
  PrintWireState(binaka.Get_WireState());
  cout << endl;
  //cout << "A: 0; B: 0; C In: 1; Sum: " << binaka.Get_Sum()->On << "; C Out: " << binaka.Get_CarryOutput()->On << endl;

  // test case 3
  pass = false;
  binaka.Set_InputA(&VirtualConnection::AlwaysOff);
  binaka.Set_InputB(&VirtualConnection::AlwaysOn);
  binaka.Set_InputCarry(&VirtualConnection::AlwaysOff);
  binaka.Update();
  if(binaka.Get_Sum()->On && !binaka.Get_CarryOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(3, pass);
  PrintWireState(binaka.Get_WireState());
  cout << endl;
  //cout << "A: 0; B: 1; C In: 0; Sum: " << binaka.Get_Sum()->On << "; C Out: " << binaka.Get_CarryOutput()->On << endl;

  // test case 4
  pass = false;
  binaka.Set_InputA(&VirtualConnection::AlwaysOff);
  binaka.Set_InputB(&VirtualConnection::AlwaysOn);
  binaka.Set_InputCarry(&VirtualConnection::AlwaysOn);
  binaka.Update();
  if(!binaka.Get_Sum()->On && binaka.Get_CarryOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(4, pass);
  PrintWireState(binaka.Get_WireState());
  cout << endl;
  //cout << "A: 0; B: 1; C In: 1; Sum: " << binaka.Get_Sum()->On << "; C Out: " << binaka.Get_CarryOutput()->On << endl;

  // test case 5
  pass = false;
  binaka.Set_InputA(&VirtualConnection::AlwaysOn);
  binaka.Set_InputB(&VirtualConnection::AlwaysOff);
  binaka.Set_InputCarry(&VirtualConnection::AlwaysOff);
  binaka.Update();
  if(binaka.Get_Sum()->On && !binaka.Get_CarryOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(5, pass);
  PrintWireState(binaka.Get_WireState());
  cout << endl;
  //cout << "A: 1; B: 0; C In: 0; Sum: " << binaka.Get_Sum()->On << "; C Out: " << binaka.Get_CarryOutput()->On << endl;

  // test case 6
  pass = false;
  binaka.Set_InputA(&VirtualConnection::AlwaysOn);
  binaka.Set_InputB(&VirtualConnection::AlwaysOff);
  binaka.Set_InputCarry(&VirtualConnection::AlwaysOn);
  binaka.Update();
  if(!binaka.Get_Sum()->On && binaka.Get_CarryOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(6, pass);
  PrintWireState(binaka.Get_WireState());
  cout << endl;
  //cout << "A: 1; B: 0; C In: 1; Sum: " << binaka.Get_Sum()->On << "; C Out: " << binaka.Get_CarryOutput()->On << endl;

  // test case 7
  pass = false;
  binaka.Set_InputA(&VirtualConnection::AlwaysOn);
  binaka.Set_InputB(&VirtualConnection::AlwaysOn);
  binaka.Set_InputCarry(&VirtualConnection::AlwaysOff);
  binaka.Update();
  if(!binaka.Get_Sum()->On && binaka.Get_CarryOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(7, pass);
  PrintWireState(binaka.Get_WireState());
  cout << endl;
  //cout << "A: 1; B: 1; C In: 0; Sum: " << binaka.Get_Sum()->On << "; C Out: " << binaka.Get_CarryOutput()->On << endl;

  // test case 8
  pass = false;
  binaka.Set_InputA(&VirtualConnection::AlwaysOn);
  binaka.Set_InputB(&VirtualConnection::AlwaysOn);
  binaka.Set_InputCarry(&VirtualConnection::AlwaysOn);
  binaka.Update();
  if(binaka.Get_Sum()->On && binaka.Get_CarryOutput()->On)
  {
    pass = true;
  }
  PrintTestCaseHeader(8, pass);
  PrintWireState(binaka.Get_WireState());
  cout << endl;
  //cout << "A: 1; B: 1; C In: 1; Sum: " << binaka.Get_Sum()->On << "; C Out: " << binaka.Get_CarryOutput()->On << endl;

}