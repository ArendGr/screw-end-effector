#include "mbed.h"
#include "Bithandler.h"

bool Bithandler::get_pressure(int drukstatus)
{
    if (drukstatus != 0) // als de drukstatus niet nul is
    {
        return true;
    }
    
    else 
    {
        return false;
    }
}