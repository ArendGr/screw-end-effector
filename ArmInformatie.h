#include "mbed.h"

class ArmInformatie { // Dit is de informatie die van de arm naar de ScrewEndEffector
private:
bool BitLosLaten; // Moet de bit wel/niet losgelaten worden
bool StartDraaien; // Moet er beginnen worden met draaien

public:
//setters
void set_BitLosLaten( bool bitloslaten );
void set_StartDraaien( bool startdraaien );

//getters
bool get_BitLosLaten(){ return BitLosLaten; };
bool get_StartDraaien(){ return StartDraaien; }; 

};