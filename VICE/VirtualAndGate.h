#pragma once
#include "VirtualComponent.h"
#include "VirtualTransistor.h"
#include "VirtualConnection.h"

namespace VICE
{
  namespace Logic
  {
    // The VirtualAndGate is a VirtualComponent that performs a logical "And" 
    // function. It consists of two inputs (InputA and InputB), and a single 
    // Output. It performs the following conversion:
    //
    //  A  |  B  |  Output
    // -------------------
    //  0  |  0  |   0
    //  0  |  1  |   0
    //  1  |  0  |   0
    //  1  |  1  |   1
    //
    // See http://hyperphysics.phy-astr.gsu.edu/hbase/electronic/trangate.html#c1 
    // for a schematic of an And gate. 
    class VirtualAndGate : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////
      VICE::Component::VirtualTransistor TransistorA;
      VICE::Component::VirtualTransistor TransistorB;
    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      VirtualAndGate();
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //*************************************************//
      //** A -- simulates the A input of an AND gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      const VICE::Component::VirtualConnection * InputA;
    public:
      const VICE::Component::VirtualConnection * Get_InputA();
      void Set_InputA(const VICE::Component::VirtualConnection * input);

      //*************************************************//
      //** B -- simulates the B input of an AND gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      const VICE::Component::VirtualConnection * InputB;
    public:
      const VICE::Component::VirtualConnection * Get_InputB();
      void Set_InputB(const VICE::Component::VirtualConnection * input);

      //******************************************************//
      //** Output  -- simulates the output of an AND gate.  **//
      //**   Defaults to VirtualConnection::AlwaysOff       **//
      //******************************************************//
    private:
      const VICE::Component::VirtualConnection * Output;
    public:
      const VICE::Component::VirtualConnection * Get_Output();
    };
  }
}