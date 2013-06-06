#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"
#include "Virtual32BitAdderSubtractor.h"
#include "Virtual32BitRegister.h"
#include "Virtual32BitRegister.h"

namespace VICE
{
  namespace Arithmetic
  {
    // The Virtual32BitMultiplier multiplies two 32-bit binary numbers.
    // The Virtual32BitMultiplier has 64 input VirtualConnections -- 
    // 32 for the multiplicand and 32 for the multiplier -- and 64 output
    // VirtualConnections for the product along with a carry/overflow
    // output. 
    //
    // The 32-bit multiplicand (InputA) and multiplier (InputB) are 
    // numbered from 0 to 31, with 0 being the least significant bit and 31 being 
    // the most significant or sign bit. For example, the number 56 (111000 in 
    // binary) is represented by:
    //
    // | 31 | 30 | 29 | ... | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    // ----------------------------------------------------------
    // |  0 |  0 |  0 | ... | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 |
    //
    // Note that because I am running out of time for the contest, I 
    // am "hacking" this class; rather than create an algorithmic
    // state machine virtual circuit for the control of the multiplication, 
    // I am controlling the multiplication programmatically. I am 
    // saddened that I must resort to this -- I had hoped to build a 
    // Turing complete VirtualCPU with 4 MB of VirtualRAM for the contest.
    // Alas, I had not enough time. 
    class Virtual32BitMultiplier : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////
      VICE::Memory::Virtual32BitRegister Multiplicand;
      VICE::Memory::Virtual32BitRegister Multiplier;
      VICE::Memory::Virtual32BitRegister Accumulator;
      VICE::Arithmetic::Virtual32BitAdderSubtractor Adder;
      // If on, allows Adder's carry output to be propagated to the Accumulator's shift input
      VICE::Component::VirtualConnection CarryAllower;
      // merges CarryAllower with the Adder's carry output. 
      VICE::Logic::VirtualAndGate Carry;

      VICE::Component::VirtualConnection MultiplicandControl[2];
      VICE::Component::VirtualConnection MultiplierControl[2];
      VICE::Component::VirtualConnection AccumulatorControl[2];

    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      Virtual32BitMultiplier();
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif
    private:
      //  sets a 2-bit control word to the command specified.
      void SetControl(int command, VICE::Component::VirtualConnection * control);

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //********************************************************************//
      //** A -- simulates the 32-bit multiplicand of 32-bit multiplier.     **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff            **//
      //********************************************************************//
    private:      
      const VICE::Component::VirtualConnection * InputA[32];
    public:
      // returns the spcified bit VirtualConnection of the A input 
      const VICE::Component::VirtualConnection * Get_InputA(int bit);
      // returns the A input as an array of VirtualConnections (size 32)
      const VICE::Component::VirtualConnection ** Get_InputA();
      // sets the specified bit VirtualConnection of the A input
      void Set_InputA(const VICE::Component::VirtualConnection * input, int bit);
      // sets the A input as an array of VirtualConnections (size 32)
      // NOTE: This method considers input to be an array of const 
      // VirtualConnections of size 32. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_InputA(const VICE::Component::VirtualConnection * input);
      // sets the A input as an array of VirtualConnections (size 32)
      // NOTE: This method considers input to be an array of pointers to
      // const VirtualConnections of size 32. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_InputA(const VICE::Component::VirtualConnection ** input);

      //********************************************************************//
      //** B -- simulates the 32-bit multiplier of a 32-bit multiplier.     **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff            **//
      //********************************************************************//
    private:      
      const VICE::Component::VirtualConnection * InputB[32];
    public:
      // returns the spcified bit VirtualConnection of the B input
      const VICE::Component::VirtualConnection * Get_InputB(int bit);
      // returns the B input as an array of VirtualConnections (size 32)
      const VICE::Component::VirtualConnection ** Get_InputB();
      // sets the specified bit VirtualConnection of the B input
      void Set_InputB(const VICE::Component::VirtualConnection * input, int bit);
      // sets the B input as an array of VirtualConnections (size 32)
      // NOTE: This method considers input to be an array of const 
      // VirtualConnections of size 32. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_InputB(const VICE::Component::VirtualConnection * input);
      // sets the B input as an array of pointers to VirtualConnections (size 32)
      // NOTE: This method considers input to be an array of pointers to
      // const VirtualConnections of size 32. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_InputB(const VICE::Component::VirtualConnection ** input);

      //*******************************************************************//
      //** Product -- simulates the 8-bit product of a 32-bit multiplier. **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff           **//
      //*******************************************************************//
    private:      
      const VICE::Component::VirtualConnection * Product[64];
    public:
      // returns the specified bit VirtualConnection for the Sum output
      const VICE::Component::VirtualConnection * Get_Product(int bit);
      // returns the Sum output as an array of VirtualConnections (size 8)
      const VICE::Component::VirtualConnection ** Get_Product();
       
      //***********************************************************************//
      //** OutputCarry  -- simulates the carry output of a 32-bit multiplier. **//
      //**   Defaults to VirtualConnection::AlwaysOff                        **//
      //***********************************************************************//
    private:
      const VICE::Component::VirtualConnection * OutputCarry;
    public:
      const VICE::Component::VirtualConnection * Get_OutputCarry();
    };
  }
}