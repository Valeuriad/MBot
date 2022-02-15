/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    MeLightSensorTest.ino
 * @author  MakeBlock
 * @version V1.0.1
 * @date    2015/09/10
 * @brief   Description: this file is sample program for Me Light Sensor module.
 *
 * Function List:
 *    1. int16_t MeLightSensor::read();
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2015/07/24     1.0.0            Rebuild the old lib.
 * Rafael Lee       2015/09/10     1.0.1            Added some comments and macros.
 * </pre>
 */

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

/* Private variables ---------------------------------------------------------*/
MeLightSensor lightSensor1(PORT_12);
MeLightSensor lightSensor2(PORT_11);
int value = 0;      /* a variable for the lightSensor's value */

MeRGBLed led(0, 12);
/* Private functions ---------------------------------------------------------*/
/**
 * \par Function
 *    setup
 * \par Description
 *    Run once, initialize serial port.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None.
 * \par Others
 *    None
 */
void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(115200);
  led.setpin(44);
  led.fillPixelsBak(0, 2, 1);
}

void colorer_leds(int rouge, int vert, int bleu, int nombreDeLeds) {
  for(int numeroLed = 0; numeroLed < nombreDeLeds; numeroLed++) {
    led.setColor(numeroLed, rouge, vert, bleu);
  }
  for(int numeroLed = nombreDeLeds; numeroLed < 12; numeroLed++) {
    led.setColor(numeroLed, 0, 0, 0);
  }
  led.show();
}

/**
 * \par Function
 *    loop
 * \par Description
 *    Run continuously, print if light sensor's DAC value.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None.
 * \par Others
 *    None
 */
void loop()
{
  // read the lightSensor value:
    colorer_leds(255, 255, 255, 12);
  value = lightSensor1.read();

  // print the results to the serial monitor
  Serial.println(value);
  // wait 100 milliseconds before the next loop
}
