#include "ArmInformatie.h"
#include <cmath>

void ArmInformatie::set_Gemeten_Positie(Positie positie) {
    oud = huidige;
    huidige = positie;
}

double ArmInformatie::PositieVerschil(Positie huidige, Positie oud) {
    // Hier wordt de afstand tussen de vorige en huidige meting gemeten
    double verschil = sqrt(pow(huidige.x - oud.x, 2) + pow(huidige.y - oud.y, 2) + pow(huidige.z - oud.z, 2));

    return verschil;
}

Positie ArmInformatie::get_Huidige_Positie() {
    return huidige;
}

Positie ArmInformatie::get_Vorige_Positie(Positie oud) {
    return oud;
}

void ArmInformatie::set_Request_Status(Status status) {
    Request_Status = status;
}

ArmInformatie::Status ArmInformatie::get_Actual_Status() {
    return Actual_Status;
}