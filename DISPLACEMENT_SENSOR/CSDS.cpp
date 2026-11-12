/* Filename: CSDS.cpp
 * Description: cpp file for the MML cell strain project. This file contains 
 * a class which assigns functions and variables to a status light object. 
 * The primary function declarations include those which perform a specific 
 * actions, getters and setters.
 * NOTES:
 *      1. "CSDS.h" is used instead of <CSDS.h> because the cpp and h files are located in the
 *         same folder.
 *      2. The SD card library should be installed prior before using the CSDS library
 *         or there will be a compilation error.
 *
 * v1.0
 * Author: Kevin Rivera
 */
////////////////////////////////////////////////////////////////////////////////////////////////

#include "CSDS.h"

CSDS *OBJ = new CSDS();


CSDS::CSDS(){}
CSDS::~CSDS(){}

/*!
  @brief   Function which sets the reference and sensor pins.
  @param   NONE
  @return  NONE
  @note    This is a public function that can be called by an object instantiated of this class.
*/
void CSDS::INITIATE(){
  
  Serial.begin(9600);
  pinMode(CSDS::getDISP_SENSOR_PIN(), INPUT);
  pinMode(CSDS::getREF_SENSOR_PIN(), INPUT);
  
}

/*!
  @brief   Function which determines the displacement value of the sensor in mm.
  @param   NONE
  @return  NONE
  @note    This is a public function that can be called by an object instantiated of this class.
*/
void CSDS::DISPLACEMENT(){
  CSDS::setREF_SENSOR_ADC_VALUE(analogRead(CSDS::getREF_SENSOR_PIN()));
  CSDS::setDISP_SENSOR_RESISTANCE(CSDS::getREF_SENSOR_RESISTANCE()*((1023.0 / CSDS::getREF_SENSOR_ADC_VALUE()) - 1.0));
  CSDS::setDISP_SENSOR_DISPLACEMENT(0.007505909117 * CSDS::getDISP_SENSOR_RESISTANCE() - 1.52373967);
}

/*!
  @brief   Function which prints the current displacement sensor value to be viewed 
           in the serial window or serial plotter.
  @param   NONE
  @return  NONE
  @note    This is a public function that can be called by an object instantiated of this class.
*/
void CSDS::SERIAL_PLOTTER(){
  Serial.println(CSDS::getDISP_SENSOR_DISPLACEMENT());
}

/*!
  @brief   Function which records the displacement sensor value to an SD card file.
  @param   NONE
  @return  NONE
  @note    This is a public function that can be called by an object instantiated of this class.
*/
void CSDS::SDCARD_RECORD(){
  
}

/*!
  @brief   Function which goes through an interactive calibration process for the
           displacement sensor.
  @param   NONE
  @return  NONE
  @note    This is a public function that can be called by an object instantiated of this class.
*/
void CSDS::CALIBRATION(){
  
}

/*!
  @brief   Functions which retrieve the values of the private member variables.
  @param   NONE
  @return  NONE
  @note    These are public function that can be called by an object instantiated of this class.
*/
int CSDS::getDISP_SENSOR_PIN(){
  return DISP_SENSOR_PIN;
}
int CSDS::getREF_SENSOR_PIN(){
  return REF_SENSOR_PIN;
}
float CSDS::getDISP_SENSOR_RESISTANCE(){
  return DISP_SENSOR_RESISTANCE;
}
float CSDS::getDISP_SENSOR_DISPLACEMENT(){
  return DISP_SENSOR_DISPLACEMENT;
}
int CSDS::getREF_SENSOR_ADC_VALUE(){
  return REF_SENSOR_ADC_VALUE;
}
float CSDS::getREF_SENSOR_RESISTANCE(){
  return REF_SENSOR_RESISTANCE;
}


/*!
  @brief   Functions which set the values of the private member variables.
  @param   DISP_SENSOR_PIN_, REF_SENSOR_PIN_, etc. are values that the private member variable 
           will be rewritten to.
  @return  NONE
  @note    These are public function that can be called by an object instantiated of this class.
*/
void CSDS::setDISP_SENSOR_PIN(int DISP_SENSOR_PIN_){
  DISP_SENSOR_PIN = DISP_SENSOR_PIN_;
}
void CSDS::setREF_SENSOR_PIN(int REF_SENSOR_PIN_){
  REF_SENSOR_PIN = REF_SENSOR_PIN_;
}
void CSDS::setDISP_SENSOR_RESISTANCE(float DISP_SENSOR_RESISTANCE_){
  DISP_SENSOR_RESISTANCE = DISP_SENSOR_RESISTANCE_;
}
void CSDS::setDISP_SENSOR_DISPLACEMENT(float DISP_SENSOR_DISPLACEMENT_){
  DISP_SENSOR_DISPLACEMENT = DISP_SENSOR_DISPLACEMENT_;
}
void CSDS::setREF_SENSOR_ADC_VALUE(int REF_SENSOR_ADC_VALUE_){
  REF_SENSOR_ADC_VALUE = REF_SENSOR_ADC_VALUE_;
}
void CSDS::setREF_SENSOR_RESISTANCE(float REF_SENSOR_RESISTANCE_){
  REF_SENSOR_RESISTANCE = REF_SENSOR_RESISTANCE_;
}
