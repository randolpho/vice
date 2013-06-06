#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"
#include "VirtualAndGate.h"
#include "VirtualOrGate.h"
#include "VirtualInverter.h"
namespace VICE
{
  namespace Control
  {
    // The VirtualMultiplexer_4_1 implements a single-bit 4-line multiplexer. It
    // takes six input VirtualConnections -- Input (the four lines to be multiplexed)
    // and Select (a two-bit selector that determines the currently switched line) -- 
    // and a single Output VirtualConnection representing the flowthrough of the
    // selected line. 
    // The Input connections are numbered 0 through 3. The Select connections represent
    // a two-bit binary number that determines which input line passes through to the output
    // 
    // The following truth table explains the conversion:
    //
    // Select0 | Select1 || Output
    // ---------------------------
    //    0    |    0    || Input0
    //    0    |    1    || Input1
    //    1    |    0    || Input2
    //    1    |    1    || Input3
    //
    // I was unable to find the particular schematic of a 4-line multiplexer that I 
    // am using here online, but alternate schematics can be seen here:
    // 
    // http://en.wikipedia.org/wiki/Multiplexer
    class VirtualMultiplexer_4_1 : public VICE::Component::VirtualComponent
    {
    private:
      ////////////////////
      // sub-components //
      ////////////////////
      // Ands Input lines with the result of the SelectionAnders
      VICE::Logic::VirtualAndGate InputAnders[4];
      // Wired to selection lines; result goes to InputAnders to determine
      // if the line was selected
      VICE::Logic::VirtualAndGate SelectAnders[4];
      // inverts each selection line
      VICE::Logic::VirtualInverter SelectInverters[2];
      // ors the results of the InputAnders 0 and 1, passing
      // it on to the output accumulator
      VICE::Logic::VirtualOrGate InputAccumulator_0_1;
      // ors the results of the InputAnders 2 and 3, passing 
      // it on to the output accumulator
      VICE::Logic::VirtualOrGate InputAccumulator_2_3;
      // ors the result of the InputAccumulators 
      VICE::Logic::VirtualOrGate OutputAccumulator;

    public:
      /////////////
      // Methods //
      /////////////

      // Default Constructor
      VirtualMultiplexer_4_1();
      // reads inputs and calculates output
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //**********************************************************//
      //** Input -- the 4 input lines to be multiplexed.        **//
      //**   Each line defaults to VirtualConnection::AlwaysOff **//
      //**********************************************************//
    private:      
      const VICE::Component::VirtualConnection * Input[4];
    public:
      // returns the specified line VirtualConnection of the Input 
      const VICE::Component::VirtualConnection * Get_Input(int line);
      // returns the Input lines as an array of VirtualConnections (size 4)
      const VICE::Component::VirtualConnection ** Get_Input();
      // sets the specified line VirtualConnection of the Input
      void Set_Input(const VICE::Component::VirtualConnection * input, int line);
      // sets the Input lines as an array of VirtualConnections (size 4)
      // NOTE: This method considers input to be an array of const 
      // VirtualConnections of size 4. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_Input(const VICE::Component::VirtualConnection * input);
      // sets the Input lines as an array of VirtualConnections (size 4)
      // NOTE: This method considers input to be an array of pointers to
      // const VirtualConnections of size 4. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_Input(const VICE::Component::VirtualConnection ** input);

      //**********************************************************//
      //** Select -- the 2-bit selection input lines            **//
      //**   Each line defaults to VirtualConnection::AlwaysOff **//
      //**********************************************************//
    private:      
      const VICE::Component::VirtualConnection * Select[2];
    public:
      // returns the specified bit VirtualConnection of the Select 
      const VICE::Component::VirtualConnection * Get_Select(int bit);
      // returns the Select bits as an array of VirtualConnections (size 2)
      const VICE::Component::VirtualConnection ** Get_Select();
      // sets the specified bit VirtualConnection of Select
      void Set_Select(const VICE::Component::VirtualConnection * input, int bit);
      // sets the Select bits as an array of VirtualConnections (size 2)
      // NOTE: This method considers input to be an array of const 
      // VirtualConnections of size 2. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_Select(const VICE::Component::VirtualConnection * input);
      // sets the Select bits as an array of VirtualConnections (size 2)
      // NOTE: This method considers input to be an array of pointers to
      // const VirtualConnections of size 2. Unexpected results can occur
      // if an array of a smaller size is passed. 
      void Set_Select(const VICE::Component::VirtualConnection ** input);

      //************************************************//
      //** Output -- The multiplexed input line.      **//
      //**   Defaults to VirtualConnection::AlwaysOff **//
      //************************************************//
    private:
      const VICE::Component::VirtualConnection * Output;
    public:
      const VICE::Component::VirtualConnection * Get_Output();
    };
  }
}