/* Filename: DISPLACEMENT_SENSOR.ino
 * Description: cpp file for the MML cell strain project. This file contains 
 * a class which assigns functions and variables to a status light object. 
 * The primary function declarations include those which perform a specific 
 * actions, getters and setters.
 * NOTES:
 *      1. "CSDS.h" is used instead of <CSDS.h> because the cpp, h and ino files are 
 *         located in thesame folder.If the cpp and h files are moved to the Arduino 
 *         library folder (i.e. C:\Users\person\Documents\Arduino\libraries or 
 *         C:\Program Files (x86)\Arduino\libraries), the "SLI.h" should be changed 
 *         to <CSDS.h> because the library files will no longer be local and a compilation 
 *         error will result.
 *      2. This code can be used to determine the displacement of at least one displacement
 *         sensor. Multiple sensors may be measured and recorded by connecting more sensors
 *         to the microcontroller and instantiating additional objects.
 *
 * v1.0
 * Author: Kevin Rivera
 */
////////////////////////////////////////////////////////////////////////////////////////////////

#include "CSDS.h"

CSDS DISP_SENS;


void setup(){

  DISP_SENS.INITIATE();
}

void loop(){

  DISP_SENS.DISPLACEMENT();
  DISP_SENS.SERIAL_PLOTTER();
}
