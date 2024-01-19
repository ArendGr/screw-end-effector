#include "mbed.h"
#pragma once
class ConductorSensor
{
    private:

   // DigitalIn Touch(p10); <-- defineer een pin voor de druk sensor
    double CalibrationValue; // data van de calibratie
    bool Touch;


    public:
    ConductorSensor() : CalibrationValue(0.0), Touch(false) {}
    bool get_Touch(); // fuctie die controleerd of er stroom loopt naar de gedefineerde pin

    void calibrateversie1(double positie); // functie die de calibratie uitvoert

    double calculate_Length(double positie); // functie die de lengte van een object vaststeld
    bool kallibratie();
};


