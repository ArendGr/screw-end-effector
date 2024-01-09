#include "mbed.h"
#include "ArmInformatie.h"
class DraaiSchroefAaninformatie {
private:

    int staat;
    bool juist;
    bool aangeraakt;
    double schroeflengte;
    bool SchroefIsErin;

public:

    void set_start();
    void set_einde();

    int get_laatstestaat() {return staat;};
    bool get_laatstejuist() {return juist;};
    bool get_laatsteaangeraakt() {return aangeraakt;};
    double get_laatsteschroeflengte() {return schroeflengte;};
    bool get_SchroefIsErin() {return SchroefIsErin;};

    void set_laatstestaat(int a) {staat = a;};
    void set_laatstejuist(bool b) {juist = b;};
    void set_laatsteaangeraakt(bool c) {aangeraakt = c;};
    void set_laatsteschroeflengte(double d) {schroeflengte = d;};
    void set_SchroefIsErin(bool e) {SchroefIsErin = e;};
    
    bool Schroefmoment();
    bool DraaiSchroefAan();
};