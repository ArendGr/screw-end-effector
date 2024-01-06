#include "ArmInformatie.h"
#include <cmath>

void ArmInformatie::set_Gemeten_Positie(Positie positie) {
    // bij het meten van een nieuwe positie wordt eerst de vorig 'huidige' positie als oud neergezet
    oud = huidige;
    huidige = positie;
    // Dit blok zou langer zijn mits er een daadwerkelijke robotarm is om mee te werken
}

void ArmInformatie::set_Start() {
    // de huidige positie wordt als startpositie neergezet
    Start = huidige;
}

double ArmInformatie::PositieVerschil(Positie huidige, Positie oud) {
    // Hier wordt de afstand tussen de vorige en huidige meting gemeten
    double verschil = sqrt(pow(huidige.x - oud.x, 2) + pow(huidige.y - oud.y, 2) + pow(huidige.z - oud.z, 2));

    return verschil;
}

Positie ArmInformatie::get_Start() {
    // hier wordt de startpositie teruggegeven
    return Start;
}

Positie ArmInformatie::get_Huidige_Positie() {
    // hier wordt de huidige positie teruggegeven
    return huidige;
}

Positie ArmInformatie::get_Vorige_Positie(Positie oud) {
    // hier wordt de vorige positie teruggegeven
    return oud;
}

void ArmInformatie::set_Request_Status(Status status) {
    // het setten van de opgevraagde status
    Request_Status = status;
}

ArmInformatie::Status ArmInformatie::get_Actual_Status() {
    // hier wordt de actuele status teruggegeven
    return Actual_Status;
}