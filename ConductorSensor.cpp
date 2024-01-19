#include "mbed.h"
#include "ConductorSensor.h"
#include <cstdio>
#pragma once

AnalogIn conductsensor(A0);

void ConductorSensor::calibrateversie1(double positie)
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

// Functie om de lengte te berekenen op basis van de kalibratiewaarden
double calculateLength(double voltage, const double calibrateLengths[], const double calibrateValues[], int numCalibrationPoints, bool Kallibratielengte) {
    // Hier moet je de formule invoegen op basis van je kalibratietabel
    // Bijvoorbeeld, een lineaire benadering:
    double m = (calibrateValues[0] - calibrateValues[numCalibrationPoints - 1]) / (calibrateLengths[0] - calibrateLengths[numCalibrationPoints - 1]);
    double b = calibrateValues[numCalibrationPoints - 1] - m * calibrateLengths[numCalibrationPoints - 1];

    // Afdrukken van de berekende formule
    if (Kallibratielengte) {
    printf("Berekende formule: length = %.4f * voltage + %.4f\n", m, b);
    }
    // Lengte berekenen
    double length = (voltage - b) / m;

    return length;
}

bool Kallibratie() {
    //AnalogIn conductsensor(A0);  // zorg dat de aansluiten op de Nucleo ook A0 is of pas deze functie aan
    AnalogIn conductsensor(A0);

    // Vervang deze lijn met de juiste methode voor het instellen van de referentiespanning
    // conductsensor.vref(3.3);

    ThisThread::sleep_for(100);

    const int numCalibrationPoints = 5;
    double calibrateLengths[numCalibrationPoints] = {0.0, 2.0, 5.0, 8.0, 10.0};  // Lengtes in centimeters
    double calibrateValues[numCalibrationPoints];

    float voltage;
    int i = 0;

    printf("Voer kalibratie uit voor bekende lengtes.\n");

    while (i < numCalibrationPoints) {
        printf("Plaats een schroef van %.2f cm en druk op Enter.", calibrateLengths[i]);
        getchar();  // Wacht op Enter

        float sumVoltage = 0.0;
        const int numSamples = 10;

        for (int j = 0; j < numSamples; ++j) {
            voltage = conductsensor.read();
            sumVoltage += voltage;
            ThisThread::sleep_for(100);
        }

        calibrateValues[i] = sumVoltage / numSamples;
        printf("Gemeten voltage: %.4f\n", calibrateValues[i]);

        i++;
    }

    printf("\nKalibratie voltooid. Gebruik deze waarden in je code:\n");

    for (int k = 0; k < numCalibrationPoints; ++k) {
        printf("Lengte: %.2f cm, Gemeten voltage: %.4f\n", calibrateLengths[k], calibrateValues[k]);
    }

    // Meet nu een spanning en bereken de geschatte lengte
    printf("\nTest: Plaats een schroef en druk op Enter om de lengte te meten.");
    getchar();  // Wacht op Enter

    // Meet de spanning voor de schroef
    voltage = conductsensor.read();
    printf("Gemeten voltage voor schroef: %.4f\n", voltage);

    // Bereken de geschatte lengte
    double estimatedLength = calculateLength(voltage, calibrateLengths, calibrateValues, numCalibrationPoints, true);
    printf("Geschatte lengte: %.2f cm\n", estimatedLength);

    return true;
}


