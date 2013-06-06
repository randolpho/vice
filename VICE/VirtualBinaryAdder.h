#pragma once
#include "VirtualComponent.h"
#include "VirtualXorGate.h"
#include "VirtualAndGate.h"
#include "VirtualOrGate.h"

namespace VICE
{
  namespace Arithmetic
  {
    // The VirtualBinaryAdder is a VirtualComponent that performs a full binary 
    // addition (including carry) of two binary digits. It consists of three 
    // inputs (the digits A and B to be added, plus an optional carry digit) and two
    // outputs (the sum of the three inputs, plus a carry)
    //
    // The following truth table lays out the full mapping of inputs to outputs
    //
    //  A  |  B  |  C In  ||  Sum  |  C Out
    // ------------------------------------
    //  0  |  0  |    0   ||   0   |   0 
    //  0  |  0  |    1   ||   1   |   0
    //  0  |  1  |    0   ||   1   |   0 
    //  0  |  1  |    1   ||   0   |   1 
    //  1  |  0  |    0   ||   1   |   0 
    //  1  |  0  |    1   ||   0   |   1
    //  1  |  1  |    0   ||   0   |   1 
    //  1  |  1  |    1   ||   1   |   1 
    //
    // See http://en.wikipedia.org/wiki/Adder_%28electronics%29 
    // for a schematic of a full binary adder
    class VirtualBinaryAdder : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////

      // Calculates the sum (XOR) of A and B 
      VICE::Logic::VirtualXorGate SumAdder;
      // Adds the carry input to the sum
      VICE::Logic::VirtualXorGate CarryAdder;
      // Ands the result of SumAdder with the carry input
      VICE::Logic::VirtualAndGate SumAndCarry;
      // Ands the A and B inputs
      VICE::Logic::VirtualAndGate A_And_B;
      // Ors SumAndCarry with A_And_b -- determines whether a carry occurred. 
      VICE::Logic::VirtualOrGate CarryOut;

    public:
      /////////////
      // Methods //
      /////////////
      // Default Constructor
      VirtualBinaryAdder();
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //*************************************************//
      //** A -- simulates the A input of a full adder. **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      const VICE::Component::VirtualConnection * InputA;
    public:
      const VICE::Component::VirtualConnection * Get_InputA();
      void Set_InputA(const VICE::Component::VirtualConnection * input);

      //*************************************************//
      //** B -- simulates the B input of a full adder. **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      const VICE::Component::VirtualConnection * InputB;
    public:
      const VICE::Component::VirtualConnection * Get_InputB();
      void Set_InputB(const VICE::Component::VirtualConnection * input);

      //***************************************************************//
      //** InputCarry  -- simulates the carry input of a full adder. **//
      //**   Defaults to VirtualConnection::AlwaysOff                **//
      //***************************************************************//
    private:
      const VICE::Component::VirtualConnection * InputCarry;
    public:
      void Set_InputCarry(const VICE::Component::VirtualConnection * input);
      const VICE::Component::VirtualConnection * Get_InputCarry();

      //******************************************************************//
      //** CarryOutput  -- simulates the carry output of a full adder.  **//
      //**   Defaults to VirtualConnection::AlwaysOff                   **//
      //******************************************************************//
    private:
      const VICE::Component::VirtualConnection * CarryOutput;
    public:
      const VICE::Component::VirtualConnection * Get_CarryOutput();

      //*******************************************************//
      //** Sum  -- simulates the sum output of a full adder. **//
      //**   Defaults to VirtualConnection::AlwaysOff        **//
      //*******************************************************//
    private:
      const VICE::Component::VirtualConnection * Sum;
    public:
      const VICE::Component::VirtualConnection * Get_Sum();
    };
  }
}