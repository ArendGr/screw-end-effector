#include "mbed.h"
#include "Bithandler.h"

bool Bithandler::is_pressure(int drukstatus)
{
    if (drukstatus == 0) // als de drukstatus niet nul is
    {
        return false;
    }
    else 
    {
        return true;
    }
}