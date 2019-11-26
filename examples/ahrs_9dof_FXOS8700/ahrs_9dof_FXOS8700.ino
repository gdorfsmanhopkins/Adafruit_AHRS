#include <Wire.h>
#include <Adafruit_Sensor.h>
//Include the sensor we have instead:
#include <Adafruit_FXOS8700.h>
//and our AHRS library we are modifying
#include <Adafruit_Simple_AHRS_FXOS8700.h>

// Create sensor instance.
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

// Create simple AHRS algorithm using the above sensor. 
Adafruit_Simple_AHRS_FXOS8700          ahrs(&accelmag);

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Adafruit 9 DOF Board AHRS Example")); Serial.println("");
  
  // Initialize the sensors.
  accelmag.begin();
}

void loop(void)
{
  sensors_vec_t   orientation;

  // Use the simple AHRS function to get the current orientation.
  if (ahrs.getOrientation(&orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
    Serial.print(F("Orientation: "));
    Serial.print(orientation.roll);
    Serial.print(F(" "));
    Serial.print(orientation.pitch);
    Serial.print(F(" "));
    Serial.print(orientation.heading);
    Serial.println(F(""));
  }
  
  delay(100);
}
