#include "StdAfx.h"
#include "VirtualConnection.h"
using namespace VICE::Component;

VirtualConnection::VirtualConnection() : On(false)
{}

VirtualConnection::VirtualConnection(bool on) : On(on)
{}

const VirtualConnection VirtualConnection::AlwaysOff(false);

const VirtualConnection VirtualConnection::AlwaysOn(true);