#include "mbed.h"

class ConductorSensor
{
    private:

    DigitalIn Touch(p10);

    double CalibrationValue;

    public:

    bool get_Touch();

    void calibrate(double positie);

    double calculate_Length(double positie);
};