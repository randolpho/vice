#pragma once
#include "VirtualComponent.h"
#include "VirtualFlipFlop.h"
#include "VirtualMultiplexer_4_1.h"
#include "VirtualConnection.h"
namespace VICE
{
  namespace Memory
  {
    // The Virtual32BitRegister implements a 32-bit universal (shift-left/shift-right
    // parallel in/out) register. It takes seven input VirtualConnections -- four input
    // bits (Input), a shift input value bit (Shift), and two control input connections 
    // (Control)-- and four output bits (Output) that contain the current state of the 
    // register.
    //
    // The Input and Output connections are numbered 0 - 3, with 0 being the least
    // significant bit and 3 being the most significant or sign bit. 
    // 
    // The combination of Control input connections determines the action that the
    // Virtual32BitRegister takes during update. The following truth table shows the
    // control codes and their corresponding actions:
    // 
    // Control0 | Control1 || Action
    // ---------------------------
    //     0    |     0    || No Action
    //     0    |     1    || Shift Right
    //     1    |     0    || Shift Left
    //     1    |     1    || Paralell Load
    //
    // Information on shift registers can be found here:
    // http://en.wikipedia.org/wiki/Shift_register
    class Virtual32BitRegister : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////
      // they store the bits, surprise!
      VICE::Component::VirtualFlipFlop Bits[32];
      // input/action controllers
      VICE::Control::VirtualMultiplexer_4_1 BitControl[32];
      // inverts the output of BitControl; necessary because of the
      // way VirtualFlipFlops set bits. 
      VICE::Logic::VirtualInverter MuxInverters[32]; 
    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      Virtual32BitRegister();
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif
      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //*********************************************************//
      //** Input -- the input to load into the register.       **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff **//
      //*********************************************************//
    private:      
      const VICE::Component::VirtualConnection * Input[32];
    public:
      // returns the specified bit VirtualConnection of the Input 
      const VICE::Component::VirtualConnection * Get_Input(int bit);
      // returns the Input bits as an array of VirtualConnections (size 32)
      const VICE::Component::VirtualConnection ** Get_Input();
      // sets the specified bit VirtualConnection of the Input
      void Set_Input(const VICE::Component::VirtualConnection * input, int bit);
      // sets the Input bits as an array of VirtualConnections (size 32)
      // NOTE: This method considers input to be an array of const 
      // VirtualConnections of size 32. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_Input(const VICE::Component::VirtualConnection * input);
      // sets the Input lines as an array of VirtualConnections (size 32)
      // NOTE: This method considers input to be an array of pointers to
      // const VirtualConnections of size 32. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_Input(const VICE::Component::VirtualConnection ** input);

      //***********************************************************//
      //** Control -- the 2-bit action control input connections **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff   **//
      //***********************************************************//
    private:      
      const VICE::Component::VirtualConnection * Control[2];
    public:
      // returns the specified bit VirtualConnection of the Control 
      const VICE::Component::VirtualConnection * Get_Control(int bit);
      // returns the Control bits as an array of VirtualConnections (size 2)
      const VICE::Component::VirtualConnection ** Get_Control();
      // sets the specified bit VirtualConnection of Control
      void Set_Control(const VICE::Component::VirtualConnection * input, int bit);
      // sets the Control bits as an array of VirtualConnections (size 2)
      // NOTE: This method considers input to be an array of const 
      // VirtualConnections of size 2. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_Control(const VICE::Component::VirtualConnection * input);
      // sets the Control bits as an array of VirtualConnections (size 2)
      // NOTE: This method considers input to be an array of pointers to
      // const VirtualConnections of size 2. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_Control(const VICE::Component::VirtualConnection ** input);

      //****************************************************************//
      //** Shift -- the value to be shifted, if a shift occurs.       **//
      //**   Defaults to VirtualConnection::AlwaysOff                 **//
      //****************************************************************//
    private:
      const VICE::Component::VirtualConnection * Shift;
    public:
      const VICE::Component::VirtualConnection * Get_Shift();
      void Set_Shift(const VICE::Component::VirtualConnection * input);

      //*********************************************************//
      //** Output -- the 32-bit current value of the register  **//
      //**   Each bit defaults to VirtualConnection::AlwaysOff **//
      //*********************************************************//
    private:      
      const VICE::Component::VirtualConnection * Output[32];
    public:
      // returns the specified bit VirtualConnection for the Sum output
      const VICE::Component::VirtualConnection * Get_Output(int bit);
      // returns the Sum output as an array of VirtualConnections (size 32)
      const VICE::Component::VirtualConnection ** Get_Output();
    };
  }
}