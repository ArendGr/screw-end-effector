#include "ConductorSensor.h"

void ConductorSensor::calibrate(double positie)
{
    CalibrationValue = positie; // zet de calibratie waarde naar de plek van de arm
}

double ConductorSensor::calculate_Length(double positie)
{
    return positie - CalibrationValue; // return de lengte opbasis van de pizitie van de arm min de calibratie waarde
}

bool ConductorSensor::get_Touch()
{
    return Touch;
}


