#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"

namespace VICE
{
  namespace Logic
  {
    // The VirtualInverters is a VirtualComponent that performs a logical "Not" 
    // function. It consists of a single Input and a single Output. It performs
    // the following conversion:
    //
    //  Input  |  Output
    // ------------------
    //    0    |    1
    //    1    |    0
    class VirtualInverter : public VICE::Component::VirtualComponent
    {
    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      VirtualInverter(void);
      // reads input and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////


      //**************************************************//
      //** Input -- simulates the input of an inverter. **//
      //**   Defaults to VirtualConnection::AlwaysOff   **//
      //**************************************************//
    private:
      const VICE::Component::VirtualConnection * Input;
    public:
      const VICE::Component::VirtualConnection * Get_Input();
      void Set_Input(const VICE::Component::VirtualConnection * input);

      //****************************************************//
      //** Output -- simulates the output of an inverter. **//
      //**   Defaults to VirtualConnection::AlwaysOff     **//
      //****************************************************//
    private:
      VICE::Component::VirtualConnection Output;
    public:
      const VICE::Component::VirtualConnection * Get_Output();
    };
  }
}