#include "mbed.h"

class ScrewEndEffectorInformatie { // Dit is de informatie die van de ScrewEndEffector naar de arm gaat
private:
// data
bool BitjesKlemOpen;
bool SchroefTouch; // Is de schroevendraaier vast in het systeem?
double RPMmotor; // De RPM van de motor
int SchroefAandrukStatus; // int 0 = default, int 1 = geen duk, int 2 = minimaale druk, int 3 = goede druk, 4 = maximale druk, 
int SchroefLengte; 
bool BitjeAanweezig, SchroefAanweezig;

public:
//data
int BitjesLengte = 5;
int VerwachteSchroefLengte = 15;

//setters
void set_BitjesKlemOpen( bool bitjesklemopen );
void set_SchroefTouch( bool schroeftouch );
void set_RPMmotor( double rpmmotoer );
void set_SchroefAandrukStatus( int schroefaandrukstatus );
void set_SchroefLengte(int schroeflengte);
void set_Schroefaanwezig(bool schroefaanweezig);
void set_BitjeAanweezig(bool bitjeaanweezig);


//getters
bool get_SchroefTouch() { return SchroefTouch; };
double get_RPMmotor(){ return RPMmotor; };
int get_SchroefAandrukStatus(){ return SchroefAandrukStatus; };
int get_SchroefLengte(){ return SchroefLengte; };
bool get_BitjeAanweezig(){ return BitjeAanweezig; };
bool get_SchroefAanweezig(){ return SchroefAanweezig; };

};