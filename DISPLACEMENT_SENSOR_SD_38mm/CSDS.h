/* Filename: CSDS.h
 * Description: h file for the MML cell strain project. This file contains 
 * a class which assigns functions and variables to a displacement sensor object. 
 * The primary function declarations include those which perform a specific 
 * actions, getters and setters.
 * NOTES:
 *      1. Function descriptions are located in the CSDS.cpp file.
 *
 * v1.1
 * Author: Kevin Rivera
 */
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CSDS_H
#define CSDS_H
#include <Arduino.h>



class CSDS{

  public:
    CSDS();
    ~CSDS();

    void INITIATE();
    void DISPLACEMENT();
    void SERIAL_PLOTTER();
    void SDCARD_RECORD();
    void CALIBRATION();

    int getDISP_SENSOR_PIN();
    int getREF_SENSOR_PIN();
    int getREF_SENSOR_ADC_VALUE();
    int getCS();
    //int getTIME();
	  float getTIME();
    float getDISP_SENSOR_RESISTANCE();
    float getDISP_SENSOR_DISPLACEMENT();
    float getREF_SENSOR_RESISTANCE();
    float getDISP_EQN_SLOPE();
    float getDISP_EQN_OFFSET();

    void setDISP_SENSOR_PIN(int DISP_SENSOR_PIN_);
    void setREF_SENSOR_PIN(int REF_SENSOR_PIN_);
    void setREF_SENSOR_ADC_VALUE(int REF_SENSOR_ADC_VALUE_);
    void setCS(int CS_);
    void setTIME(int TIME_);
    void setDISP_SENSOR_RESISTANCE(float DISP_SENSOR_RESISTANCE_);
    void setDISP_SENSOR_DISPLACEMENT(float DISP_SENSOR_DISPLACEMENT_);
    void setREF_SENSOR_RESISTANCE(float REF_SENSOR_RESISTANCE_);
    void setDISP_EQN_SLOPE(float DISP_EQN_SLOPE_);
    void setDISP_EQN_OFFSET(float DISP_EQN_OFFSET_);
    


 private:

    int DISP_SENSOR_PIN = A0;
    int REF_SENSOR_PIN = A1;
    int REF_SENSOR_ADC_VALUE = 0;
    int CS = 10;
    //int TIME = 0;
	  float TIME = 0;
    float DISP_SENSOR_RESISTANCE = 0;
    float DISP_SENSOR_DISPLACEMENT = 0;
    float REF_SENSOR_RESISTANCE = 1000.0;
	
	//Equation parameters updated for 38.1mm displacement sensor
    float DISP_EQN_SLOPE = 0.008039670817;
    float DISP_EQN_OFFSET = -1.889322641908;

};

#endif
