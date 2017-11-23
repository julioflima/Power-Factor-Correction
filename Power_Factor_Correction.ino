#include <math.h>


//digitals
const static int relay_1 = 53;
const static int relay_2 = 51;
const static int relay_3 = 49;
const static int relay_4 = 47;
const static int relay_5 = 45;
const static int relay_6 = 43;
const static int relay_7 = 41;
const static int relay_8 = 39;


//analogics
const int anlg_voltage = 54; //A0
const int anlg_current = 55; //A1
const int anlg_reference = 56; //A2

//constants
const int time_reset = 10000;
const double shunt_resistor = 0.47;
const double big_voltage_resistor = 148000;
const double small_voltage_resistor = 668;
const double big_current_resistor = 32580;
const double small_current_resistor = 9080;
const double anti_gain_Voltage = big_voltage_resistor / small_voltage_resistor;
const double anti_gain_Current = big_current_resistor / small_current_resistor;



// constant for settings of prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

//variables
double voltages[600];
double currents[600];
double last_v=1;
int received;
int count = 0;
int passed = 1;
int relays = 0;
double v_Peak;
double c_Peak;
double v_RMS;
double c_RMS;
double sum_V_RMS;
double sum_C_RMS;
double power_S;
double sum_power_P;
double power_P;
double power_Factor;


/*
 * ((read_Current() - read_Refence())*anti_gain_Current - read_Refence())/shunt_resistor
 * 
 * ((read_Voltage() - read_Refence())*anti_gain_Voltage - read_Refence())
*/

