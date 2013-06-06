#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"
#include "VirtualAndGate.h"
#include "VirtualInverter.h"

namespace VICE
{
  namespace Logic
  {
    // The VirtualNandGate is a VirtualComponent that performs a logical "Not And" 
    // function. It consists of two inputs (InputA and InputB), and a single 
    // Output. It performs the following conversion:
    //
    //  A  |  B  |  Output
    // -------------------
    //  0  |  0  |   1
    //  0  |  1  |   1
    //  1  |  0  |   1
    //  1  |  1  |   0
    //
    class VirtualNandGate : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////
      // ands the A and B inputs
      VICE::Logic::VirtualAndGate And;
      // inverts the output of A and B. 
      VICE::Logic::VirtualInverter Inverter;      
    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      VirtualNandGate(void);
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //*************************************************//
      //** A -- simulates the A input of a NAND gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      const VICE::Component::VirtualConnection * InputA;
    public:
      const VICE::Component::VirtualConnection * Get_InputA();
      void Set_InputA(const VICE::Component::VirtualConnection * input);

      //*************************************************//
      //** B -- simulates the B input of a NAND gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      const VICE::Component::VirtualConnection * InputB;
    public:
      const VICE::Component::VirtualConnection * Get_InputB();
      void Set_InputB(const VICE::Component::VirtualConnection * input);

      //******************************************************//
      //** Output  -- simulates the output of a NAND gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff       **//
      //******************************************************//
    private:
      const VICE::Component::VirtualConnection * Output;
    public:
      const VICE::Component::VirtualConnection * Get_Output();
    };
  }
}