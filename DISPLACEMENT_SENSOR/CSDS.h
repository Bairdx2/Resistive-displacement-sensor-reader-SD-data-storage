/* Filename: CSDS.h
 * Description: h file for the MML cell strain project. This file contains 
 * a class which assigns functions and variables to a status light object. 
 * The primary function declarations include those which perform a specific 
 * actions, getters and setters.
 * NOTES:
 *      1. Function descriptions are located in the CSDS.cpp file.
 *
 * v1.0
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
    float getDISP_SENSOR_RESISTANCE();
    float getDISP_SENSOR_DISPLACEMENT();
    int getREF_SENSOR_ADC_VALUE();
    float getREF_SENSOR_RESISTANCE();

    void setDISP_SENSOR_PIN(int DISP_SENSOR_PIN_);
    void setREF_SENSOR_PIN(int REF_SENSOR_PIN_);
    void setDISP_SENSOR_RESISTANCE(float DISP_SENSOR_RESISTANCE_);
    void setDISP_SENSOR_DISPLACEMENT(float DISP_SENSOR_DISPLACEMENT_);
    void setREF_SENSOR_ADC_VALUE(int REF_SENSOR_ADC_VALUE_);
    void setREF_SENSOR_RESISTANCE(float REF_SENSOR_RESISTANCE_);
    


 private:

    int DISP_SENSOR_PIN = A0;
    int REF_SENSOR_PIN = A1;
    float DISP_SENSOR_RESISTANCE = 0;
    float DISP_SENSOR_DISPLACEMENT = 0;
    int REF_SENSOR_ADC_VALUE = 0;
    float REF_SENSOR_RESISTANCE = 1000.0;

};

#endif
