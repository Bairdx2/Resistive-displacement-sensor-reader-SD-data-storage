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
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

CSDS *OBJ = new CSDS();

char DATA[100];
char DISP[10];
char TIME_[50];
char filename[] = "mll00.txt";
File DATAFILE;


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

  // Conditional to see if the SD card is connected.
  if (!SD.begin(CSDS::getCS())) {
    //Serial.println("Not initiated");
    return;
  }

  // Loops and changes the last portion of the file until the name is unique.
  for (uint8_t i = 0; i < 100; i++) {
    filename[3] = i/10 + '0';
    filename[4] = i%10 + '0';
    if (! SD.exists(filename)) {
      DATAFILE = SD.open(filename, FILE_WRITE);
      break;
    }
  }
  
  DATAFILE.println("Time(ms), Displacement(mm)");// Prints the column header for the .txt file
  DATAFILE.close(); 
  
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
  //CSDS::setDISP_SENSOR_DISPLACEMENT(0.007505909117 * CSDS::getDISP_SENSOR_RESISTANCE() - 1.52373967);
  CSDS::setDISP_SENSOR_DISPLACEMENT(CSDS::getDISP_EQN_SLOPE() * CSDS::getDISP_SENSOR_RESISTANCE() + CSDS::getDISP_EQN_OFFSET());
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
  
  File DATAFILE = SD.open(filename, FILE_WRITE);
  dtostrf(CSDS::getDISP_SENSOR_DISPLACEMENT(), 6, 4, DISP);
  
  strcat(DATA,itoa(CSDS::getTIME(),TIME_,10));
  strcat(DATA,",");
  strcat(DATA,DISP);

  
  
  CSDS::setTIME(CSDS::getTIME() + 10);
  
  if (DATAFILE){                           // Checks to see if the file was opened and writes
    DATAFILE.println(DATA);                // the combined data to it.
    DATAFILE.close();
    //Serial.println(DATA);
  }
  else {}

  //Serial.println(DISP);

  memset(DATA, 0, sizeof(DATA));           // Clearing the contents of the data array.
  memset(TIME_, 0, sizeof(TIME_));
  memset(DISP, 0, sizeof(DISP));
  delay(10);
}

/*!
  @brief   Function which goes through an interactive calibration process for the
           displacement sensor.
  @param   NONE
  @return  NONE
  @note    This is a public function that can be called by an object instantiated of this class.
*/
void CSDS::CALIBRATION(){

  float R_LONG;
  float R_SHORT;
  const int RLED = 3;
  const int GLED = 5;
  const int BLED = 6;

  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  
  CSDS::setREF_SENSOR_ADC_VALUE(analogRead(CSDS::getREF_SENSOR_PIN()));
  CSDS::setDISP_SENSOR_RESISTANCE(CSDS::getREF_SENSOR_RESISTANCE()*((1023.0 / CSDS::getREF_SENSOR_ADC_VALUE()) - 1.0));
  
  /*
  //RED_LED_ON
  Serial.println("Leave the sensor in the extended position to aquire the first calibration point");
  delay(5000);
  R_LONG = CSDS::getDISP_SENSOR_RESISTANCE();
  Serial.println("First calibration point aquired");
  delay(5000);
  
  //BLUE_LED_ON
  Serial.println("Depress the sensor pin all the way to aquire the second calibration point");
  delay(5000);
  CSDS::setREF_SENSOR_ADC_VALUE(analogRead(CSDS::getREF_SENSOR_PIN()));
  CSDS::setDISP_SENSOR_RESISTANCE(CSDS::getREF_SENSOR_RESISTANCE()*((1023.0 / CSDS::getREF_SENSOR_ADC_VALUE()) - 1.0));
  R_SHORT = CSDS::getDISP_SENSOR_RESISTANCE();
  Serial.println("First calibration point aquired");
  Serial.println("Calibration complete");
  */


  //RED_LED_ON
  for(int i = 255; i >= 0; i--){
    analogWrite(RLED, i);
    analogWrite(GLED, 0);
    analogWrite(BLED, 0);
    delay(20);
  }
  delay(2000);
  R_LONG = CSDS::getDISP_SENSOR_RESISTANCE();
  //delay(5000);
  
  //BLUE_LED_ON
  for(int i = 255; i >= 0; i--){
    analogWrite(RLED, 0);
    analogWrite(GLED, 0);
    analogWrite(BLED, i);
    delay(20);
  }
  delay(2000);
  CSDS::setREF_SENSOR_ADC_VALUE(analogRead(CSDS::getREF_SENSOR_PIN()));
  CSDS::setDISP_SENSOR_RESISTANCE(CSDS::getREF_SENSOR_RESISTANCE()*((1023.0 / CSDS::getREF_SENSOR_ADC_VALUE()) - 1.0));
  R_SHORT = CSDS::getDISP_SENSOR_RESISTANCE();  

  CSDS::setDISP_EQN_SLOPE((25.4 - 0)/(R_LONG - R_SHORT));
  CSDS::setDISP_EQN_OFFSET(-1 * (R_SHORT * CSDS::getDISP_EQN_SLOPE()));
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, HIGH);
  digitalWrite(BLED, LOW);
  delay(500);
  digitalWrite(GLED, LOW);
  delay(500);
  digitalWrite(GLED, HIGH);
  delay(500);
  digitalWrite(GLED, LOW);
  delay(500);
  delay(1000);
  
  CSDS::setDISP_SENSOR_DISPLACEMENT(CSDS::getDISP_EQN_SLOPE() * CSDS::getDISP_SENSOR_RESISTANCE() + CSDS::getDISP_EQN_OFFSET());
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
int CSDS::getREF_SENSOR_ADC_VALUE(){
  return REF_SENSOR_ADC_VALUE;
}
int CSDS::getCS(){
  return CS;
}
int CSDS::getTIME(){
  return TIME;
}
float CSDS::getDISP_SENSOR_RESISTANCE(){
  return DISP_SENSOR_RESISTANCE;
}
float CSDS::getDISP_SENSOR_DISPLACEMENT(){
  return DISP_SENSOR_DISPLACEMENT;
}
float CSDS::getREF_SENSOR_RESISTANCE(){
  return REF_SENSOR_RESISTANCE;
}
float CSDS::getDISP_EQN_SLOPE(){
  return DISP_EQN_SLOPE;
}
float CSDS::getDISP_EQN_OFFSET(){
  return DISP_EQN_OFFSET;
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
void CSDS::setREF_SENSOR_ADC_VALUE(int REF_SENSOR_ADC_VALUE_){
  REF_SENSOR_ADC_VALUE = REF_SENSOR_ADC_VALUE_;
}
void CSDS::setCS(int CS_){
  CS = CS_;
}
void CSDS::setTIME(int TIME_){
  TIME = TIME_;
}
void CSDS::setDISP_SENSOR_RESISTANCE(float DISP_SENSOR_RESISTANCE_){
  DISP_SENSOR_RESISTANCE = DISP_SENSOR_RESISTANCE_;
}
void CSDS::setDISP_SENSOR_DISPLACEMENT(float DISP_SENSOR_DISPLACEMENT_){
  DISP_SENSOR_DISPLACEMENT = DISP_SENSOR_DISPLACEMENT_;
}
void CSDS::setREF_SENSOR_RESISTANCE(float REF_SENSOR_RESISTANCE_){
  REF_SENSOR_RESISTANCE = REF_SENSOR_RESISTANCE_;
}
void CSDS::setDISP_EQN_SLOPE(float DISP_EQN_SLOPE_){
  DISP_EQN_SLOPE = DISP_EQN_SLOPE_;
}
void CSDS::setDISP_EQN_OFFSET(float DISP_EQN_OFFSET_){
  DISP_EQN_OFFSET = DISP_EQN_OFFSET_;
}
