#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"

namespace VICE
{
  namespace Component
  {
    // The VirtualFlipFlop simulates the implementation of a 
    // standard J/K flipflop. It consists of two inputs -- 
    // InputSet (J) which forces the flipflop to a "1" value, and
    // InputReset (K) which forces the flipflop to a "0" value -- 
    // and two outputs -- Output (Q), which contains the current
    // value of the flipflop, and NotOutput (Q') which contains the 
    // opposite value. 
    //
    // The VirtualFlipFlop simulates a J/K flipflop, so the 
    // "undefined" condition of J and K both being set in an SR flipflop
    // is defined as a "toggle" of the current value. The following
    // truth table explains all possible input/output combinations:
    //
    // | J | K | Q | Q' |
    // ------------------
    // | 0 | 0 | 0 | 1  |    -- do nothing, retain current Q=0
    // | 0 | 0 | 1 | 0  |    -- do nothing, retain current Q=1
    // | 1 | 0 | 1 | 0  |   
    // | 0 | 1 | 0 | 1  | 
    // | 1 | 1 | 0 | 1  |    -- toggle from Q=1 to Q=0
    // | 1 | 1 | 1 | 0  |    -- toggle from Q=0 to Q=1
    class VirtualFlipFlop : public VICE::Component::VirtualComponent
    {
    public:
      /////////////////
      //// Methods ////
      /////////////////

      // default constructor
      VirtualFlipFlop();
      // reads inputs and updates outputs 
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //************************************************//
      //** InputSet -- simulates a flipflop's Set (to **//
      //**             value 1) input                 **//
      //**   Defaults to VirtualConnection::AlwaysOff **//
      //************************************************//
    private:
      const VirtualConnection * InputSet;
    public:
      const VirtualConnection * Get_InputSet();
      void Set_InputSet(const VirtualConnection * collector);

      //************************************************//
      //** InputReset -- Simulates a flipflop's Reset **//
      //**               (to value 0) input           **//
      //**   Defaults to VirtualConnection::AlwaysOff **//
      //************************************************//
    private:
      const VirtualConnection * InputReset;
    public:
      const VirtualConnection * Get_InputReset();
      void Set_InputReset(const VirtualConnection * base);

      //************************************************//
      //** Output -- Simulates a flipflops's "current **//
      //**           value" output.                   **//
      //**   Defaults to VirtualConnection::AlwaysOff **//
      //*************************************************//
    private:
      VirtualConnection Output;
    public:
      const VirtualConnection * Get_Output();

      //****************************************************//
      //** NotOutput -- Simulates a flipflops's "opposite **//
      //**           value" output.                       **//
      //**   Defaults to VirtualConnection::AlwaysOff     **//
      //****************************************************//
    private:
      VirtualConnection NotOutput;
    public:
      const VirtualConnection * Get_NotOutput();
    };
  }
}