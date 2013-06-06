#pragma once
#ifdef _DEBUG
#include <map>
#include <string>
#include <sstream>
#endif
namespace VICE
{
  namespace Component
  {
    // VirtualComponent is the base class of every component in a Virtual
    // Integrated Circuit. A VirtualComponent consists of a set of 
    // VirtualConnections as inputs and a set of VirtualConnections as outputs.
    // Because the number of inputs and outputs will vary wildly from VirtualComponent
    // to VirtualComponent, no specific interface is laid out here, other than the 
    // abstract Update() method telling the VirtualComponent to read its inputs and set its
    // outputs. 
    class VirtualComponent abstract
    {
#ifdef _DEBUG
    protected:
      // A mapping of input and output names to their current values.. 
      // Used for debug purposes. 
      std::map<std::string, bool> WireState;
      // Abstract method for updating WireState. It should be updated
      // by a VirtualComponent in the constructor and at the end of an Update()
      virtual void UpdateWireState() abstract;
      // Builds a numbered WireState name from the string and number passed.
      // for example, if called as follows:
      //
      //   BuildWireStateName(10, "InputA");
      // 
      // BuildWireStateName returns the string "InputA10"
      std::string BuildWireStateName(int num, std::string base)
      {
        std::stringstream s;
        s << base << num;
        return s.str();
      }
    public:
      // Returns the current WireState
      const std::map<std::string, bool> * Get_WireState()
      {
        return &WireState;
      }
      
#endif
    public:
      // Update is an abstract method. When called, it indicates that the VirtualComponent 
      // should read its input values and update its output values based upon those inputs. 
      // It is the responsibility of the implementing class to call Update() at the appropriate
      // time for any internal VirtualComponents it may use. 
      virtual void Update() abstract;
    };
  }
}
