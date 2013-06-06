#pragma once

namespace VICE
{
  namespace Component
  {
    // A Virtual Connection represents a wire or connection between VirtualComponents in a Virtual
    // Integrated Circuit. Every VirtualComponent in a Virtual Integrated Circuit
    // offers a pointer to a const VirtualConnection object as its output(s) and accepts a 
    // pointer to a const VirtualConnection object as its input(s).
    //
    // Because VICE has abstracted away such annoying problems as current and 
    // and voltage in an integrated circuit, a VirtualConnection represents, as it were,
    // the current that flows through an integrated circuit. It is either "on" when 
    // "current" is flowing from one VirtualComponent to another, or "off" when it is not. 
    class VirtualConnection
    {
    public:
      // True if the connection is currently "on", that is if the connection 
      // currently has "current" flowing through it.
      bool On;
      // Default constructor -- sets On to false. 
      VirtualConnection();
      // Sets On to the value specified. 
      VirtualConnection(bool on);
      // Quick-access to a VirtualConnection that is on. Useful for VirtualComponents
      // that require constant power in addition to its inputs. 
      static const VirtualConnection AlwaysOn;
      // Quick-access to a VirtualConnection that is off. Useful as a default input for
      // VirtualComponents. 
      static const VirtualConnection AlwaysOff;
    };
  }
}