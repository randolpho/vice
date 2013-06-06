#pragma once
#include <vector>
#include "VirtualComponent.h"
#include "VirtualConnection.h"

namespace VICE
{
  namespace Component
  {
    // A VirtualJunction represents the connection of two or more virtual "wires" 
    // in a Virtual Integrated Circuit. 
    // 
    // Because current and voltage have been abstracted away in VICE to a simple
    // question of "is current flowing, yes or no?" the issue of how current flows
    // when a "wire" splits into two wires or when two wires join together to
    // form a single wire has been simplified. 
    //
    // In the case of two wires splitting, current flows in both wires dependent 
    // on whether or not current was flowing immediately before the split. In 
    // VICE, when two VirtualComponents are connected to the same "wire", 
    // one simply sets the appropriate inputs of both VirtualComponents to the 
    // same VirtualConnection that represents that wire.  
    // 
    // When two wires *join*, however, current flows in the joined wire if it 
    // flows in any of the joining wires. There is no easy way to wire 
    // VirtualComponents to appropriate VirtualConnections in such a case. 
    //
    // The VirtualJunction provides that missing "easy way" -- it provides a 
    // "joining" of virtual "wires" in the standard VICE wiring way. It can take 
    // any number of VirtualConnections as input, and provides a single 
    // VirtualConnection output that is "on" if any of the corresponding inputs 
    // are "on". 
    class VirtualJunction : public VICE::Component::VirtualComponent
    {
    private:
      // collection of VirtualConnection inputs
      std::vector<const VICE::Component::VirtualConnection *> Inputs;
      // output VirtualConnection
      VICE::Component::VirtualConnection Output;
    public:
      // adds a VirtualConnection to the Inputs collection
      void Add_Input(const VICE::Component::VirtualConnection * input);
      // obtains a VirtualConnection as the output
      const VICE::Component::VirtualConnection * Get_Output();
      // default constructor
      VirtualJunction();
      // tells the VirtualJunction to read its input virtualConnections and
      // update is output VirtualConnection.
      // Note that Update() is worst-case order(n), where n is the number of inputs
      // specified. Worst case is defined as all inputs being "off"
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif
    };
  }
}