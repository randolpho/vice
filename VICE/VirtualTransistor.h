#pragma once
#include "VirtualComponent.h"
#include "VirtualConnection.h"

namespace VICE
{
  namespace Component
  {
    // The VirtualTransistor is the heart of the VICE system. Although itself 
    // a VirtualComponent, nearly all other VirtualComponents are built from a 
    // VirtualTransistor or from other VirtualComponents that (at some point) 
    // utilize a VirtualTransistor. 
    //
    // A VirtualTransistor models an NPN transistor which is, essentially, a 
    // switch. It sends current through its output (typically called 
    // an "Emitter" on NPN transistors), only if it both receives current from 
    // its input ("Collector") and receives a small amount of current from 
    // its switch input ("Base"). 
    //
    // Because both current and voltage have been abstracted away for Virtual 
    // Integrated Circuits, the difference between NPN and PNP transistors 
    // (essentially a matter of current direction and whether a connected base 
    // adds to or subtracts from the current flowing through the transistor) 
    // becomes moot. In a VirtualTransistor, "current" flows from the Collector
    // to the Emitter. 
    class VirtualTransistor : public VirtualComponent
    {
    public:
      /////////////////
      //// Methods ////
      /////////////////

      // default constructor
      VirtualTransistor();
      // Causes the VirtualTransistor to update its output based
      // on its inputs. 
      void Update();
#ifdef _DEBUG
      void UpdateWireState();
#endif

      ////////////////////////////
      //// Inputs and Outputs ////
      ////////////////////////////

      //*****************************************************//
      //** Collector -- simulates a transistor's collector **//
      //**              or "power input"                   **//
      //**   Defaults to VirtualConnection::AlwaysOff      **//
      //*****************************************************//
    private:
      const VirtualConnection * Collector;
    public:
      const VirtualConnection * Get_Collector();
      void Set_Collector(const VirtualConnection * collector);

      //************************************************//
      //** Base -- Simulates a transistor's base      **//
      //**         or "switch input"                  **//
      //**   Defaults to VirtualConnection::AlwaysOff **//
      //************************************************//
    private:
      const VirtualConnection * Base;
    public:
      const VirtualConnection * Get_Base();
      void Set_Base(const VirtualConnection * base);

      //*************************************************//
      //** Emitter -- Simulates a transistor's emitter **//
      //**            or "result output"               **//
      //**   Defaults to VirtualConnection::AlwaysOff  **//
      //*************************************************//
    private:
      VirtualConnection Emitter;
    public:
      const VirtualConnection * Get_Emitter();
    };
  }
}
