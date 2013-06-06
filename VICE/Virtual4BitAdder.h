#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"
#include "VirtualBinaryAdder.h"
namespace VICE
{
  namespace Arithmetic
  {
    // The Virtual4BitAdder adds two 4-bit binary 
    // numbers. The Virtual4BitAdder has 9 input VirtualConnections --
    // 4 for the augend bits, 4 for the addend bits, and a carry input -- 
    // and 4 output VirtualConnections for the sum along with a 
    // carry/overflow output.
    // 
    // The 4-bit augend (InputA) and addend (InputB) are 
    // numbered from 0 to 3, with 0 being the least significant bit and 3 being 
    // the most significant or sign bit. For example, the number 6 (110 in 
    // binary) is represented by:
    //
    // | 3 | 2 | 1 | 0 |
    // -----------------
    // | 0 | 1 | 1 | 0 |
    //
    // An example schematic of a four-bit adder can be viewed at
    // http://en.wikipedia.org/wiki/Adder_%28electronics%29 
    // 
    // Note that because propagation delay is not an issue in the
    // abstracted world of VICE, look-ahead carry generators are not 
    // necessary
    class Virtual4BitAdder : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////
      VICE::Arithmetic::VirtualBinaryAdder Adder[4];
    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      Virtual4BitAdder();
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //*********************************************************//
      //** A -- simulates the 4-bit augend of 4-bit adder.     **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff **//
      //*********************************************************//
    private:      
      const VICE::Component::VirtualConnection * InputA[4];
    public:
      // returns the spcified bit VirtualConnection of the A input 
      const VICE::Component::VirtualConnection * Get_InputA(int bit);
      // returns the A input as an array of VirtualConnections (size 4)
      const VICE::Component::VirtualConnection ** Get_InputA();
      // sets the specified bit VirtualConnection of the A input
      void Set_InputA(const VICE::Component::VirtualConnection * input, int bit);
      // sets the A input as an array of VirtualConnections (size 4)
      // NOTE: This method considers input to be an array of const 
      // VirtualConnections of size 4. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_InputA(const VICE::Component::VirtualConnection * input);
      // sets the A input as an array of VirtualConnections (size 4)
      // NOTE: This method considers input to be an array of pointers to
      // const VirtualConnections of size 4. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_InputA(const VICE::Component::VirtualConnection ** input);

      //*********************************************************//
      //** B -- simulates the 4-bit addend of 4-bit adder.     **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff **//
      //*********************************************************//
    private:      
      const VICE::Component::VirtualConnection * InputB[4];
    public:
      // returns the spcified bit VirtualConnection of the B input
      const VICE::Component::VirtualConnection * Get_InputB(int bit);
      // returns the B input as an array of VirtualConnections (size 4)
      const VICE::Component::VirtualConnection ** Get_InputB();
      // sets the specified bit VirtualConnection of the B input
      void Set_InputB(const VICE::Component::VirtualConnection * input, int bit);
      // sets the B input as an array of VirtualConnections (size 4)
      // NOTE: This method considers input to be an array of const 
      // VirtualConnections of size 4. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_InputB(const VICE::Component::VirtualConnection * input);
      // sets the B input as an array of pointers to VirtualConnections (size 4)
      // NOTE: This method considers input to be an array of pointers to
      // const VirtualConnections of size 4. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_InputB(const VICE::Component::VirtualConnection ** input);

      //****************************************************************//
      //** InputCarry -- simulates the carry input of a 4-bit adder.  **//
      //**   Defaults to VirtualConnection::AlwaysOff                 **//
      //****************************************************************//
    private:
      const VICE::Component::VirtualConnection * InputCarry;
    public:
      const VICE::Component::VirtualConnection * Get_InputCarry();
      void Set_InputCarry(const VICE::Component::VirtualConnection * input);

      //*********************************************************//
      //** Sum -- simulates the 4-bit sum of 4-bit adder.      **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff **//
      //*********************************************************//
    private:      
      const VICE::Component::VirtualConnection * Sum[4];
    public:
      // returns the specified bit VirtualConnection for the Sum output
      const VICE::Component::VirtualConnection * Get_Sum(int bit);
      // returns the Sum output as an array of VirtualConnections (size 4)
      const VICE::Component::VirtualConnection ** Get_Sum();
       
      //******************************************************************//
      //** OutputCarry  -- simulates the carry output of a 4-bit adder. **//
      //**   Defaults to VirtualConnection::AlwaysOff                   **//
      //******************************************************************//
    private:
      const VICE::Component::VirtualConnection * OutputCarry;
    public:
      const VICE::Component::VirtualConnection * Get_OutputCarry();
    };
  }
}