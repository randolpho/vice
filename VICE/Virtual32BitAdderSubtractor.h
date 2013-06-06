
#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"
#include "VirtualBinaryAdder.h"
namespace VICE
{
  namespace Arithmetic
  {
    // The Virtual32BitAdderSubtractor adds or subtracts two 32-bit binary 
    // numbers. The Virtual32BitAdderSubtractor has 65 input VirtualConnections --
    // 32 for the augend bits, 32 for the addend bits, and a subtraction control input -- 
    // and 32 output VirtualConnections for the sum along with a 
    // carry/overflow output.
    // 
    // The 32-bit augend/minuend (InputA) and addend/subtrahend (InputB) are 
    // numbered from 0 to 31, with 0 being the least significant bit and 31 being 
    // the most significant or sign bit. For example, the number 56 (111000 in 
    // binary) is represented by:
    //
    // | 31 | 30 | 29 | ... | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
    // ----------------------------------------------------------
    // |  0 |  0 |  0 | ... | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 |
    //
    // This implementation extends the implementation of the 4-bit adder/subtractor
    // to 32 bits
    class Virtual32BitAdderSubtractor : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////
      VICE::Logic::VirtualXorGate Negater[32];
      VICE::Arithmetic::VirtualBinaryAdder Adder[32];
    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      Virtual32BitAdderSubtractor();
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //*********************************************************//
      //** A -- simulates the 32-bit augend/minuend of 32-bit  **//
      //**       adder/subtractor.                             **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff **//
      //*********************************************************//
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

      //***********************************************************//
      //** B -- simulates the 32-bit addend/subtrahend of 32-bit **//
      //**      adder/subtractor.                                **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff   **//
      //***********************************************************//
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

      //****************************************************************//
      //** SubtractionControl -- simulates the subtraction control    **//
      //**                       input of a 32-bit adder/subtractor.  **//
      //**   Defaults to VirtualConnection::AlwaysOff                 **//
      //****************************************************************//
    private:
      const VICE::Component::VirtualConnection * SubtractionControl;
    public:
      const VICE::Component::VirtualConnection * Get_SubtractionControl();
      void Set_SubtractionControl(const VICE::Component::VirtualConnection * input);

      //**********************************************************//
      //** Sum -- simulates the 32-bit sum/difference of 32-bit **//
      //**        adder/subtractor.                             **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff  **//
      //**********************************************************//
    private:      
      const VICE::Component::VirtualConnection * Sum[32];
    public:
      // returns the specified bit VirtualConnection for the Sum output
      const VICE::Component::VirtualConnection * Get_Sum(int bit);
      // returns the Sum output as an array of VirtualConnections (size 32)
      const VICE::Component::VirtualConnection ** Get_Sum();
       
      //************************************************************//
      //** OutputCarry  -- simulates the carry output of a 32-bit **//
      //**                 adder/subtractor.                      **//
      //**   Defaults to VirtualConnection::AlwaysOff             **//
      //************************************************************//
    private:
      const VICE::Component::VirtualConnection * OutputCarry;
    public:
      const VICE::Component::VirtualConnection * Get_OutputCarry();
    };
  }
}