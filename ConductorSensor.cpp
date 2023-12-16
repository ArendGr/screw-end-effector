#include "ConductorSensor.h"

void ConductorSensor::calibrate(double positie)
{
    CalibrationValue = positie;
}

double ConductorSensor::calculate_Length(double positie)
{
    return positie - CalibrationValue;
}

bool ConductorSensor::get_Touch()
{
    return Touch;
}