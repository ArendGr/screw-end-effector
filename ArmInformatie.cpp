#include "ArmInformatie.h"
// Dit is het tweede gedeelte van de setters

void ArmInformatie::set_Request_Status(Status status) 
{
    Request_Status = status;
}

ArmInformatie::Status ArmInformatie::get_Actual_Status()
{
    return Actual_Status;
}