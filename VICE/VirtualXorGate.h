#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"
#include "VirtualNandGate.h"

namespace VICE
{
  namespace Logic
  {
    // The VirtualNorGate is a VirtualComponent that performs a logical "Not Or" 
    // function. It consists of two inputs (InputA and InputB), and a single 
    // Output. It performs the following conversion:
    //
    //  A  |  B  |  Output
    // -------------------
    //  0  |  0  |   0
    //  0  |  1  |   1
    //  1  |  0  |   1
    //  1  |  1  |   0
    //
    // See http://en.wikipedia.org/wiki/Image:XOR_Using_NAND.jpg for a schematic
    // for an XOR gate.
    class VirtualXorGate : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////

      // Nands the A and B inputs
      VICE::Logic::VirtualNandGate A_B;
      // Nands the A input with the result of A_B
      VICE::Logic::VirtualNandGate A__A_B;
      // Nands the B input with the result of A_B
      VICE::Logic::VirtualNandGate B__A_B;
      // Nands the results of A__A_B and B__A_B
      VICE::Logic::VirtualNandGate AAB_BAB;
    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      VirtualXorGate();
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //*************************************************//
      //** A -- simulates the A input of an XOR gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      const VICE::Component::VirtualConnection * InputA;
    public:
      const VICE::Component::VirtualConnection * Get_InputA();
      void Set_InputA(const VICE::Component::VirtualConnection * input);

      //*************************************************//
      //** B -- simulates the B input of an XOR gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      const VICE::Component::VirtualConnection * InputB;
    public:
      const VICE::Component::VirtualConnection * Get_InputB();
      void Set_InputB(const VICE::Component::VirtualConnection * input);

      //******************************************************//
      //** Output  -- simulates the output of an XOR gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff       **//
      //******************************************************//
    private:
      const VICE::Component::VirtualConnection * Output;
    public:
      const VICE::Component::VirtualConnection * Get_Output();
    };
  }
}
