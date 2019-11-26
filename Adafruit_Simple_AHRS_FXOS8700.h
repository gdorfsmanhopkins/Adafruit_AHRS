#ifndef __ADAFRUIT_SIMPLE_AHRS_FXOS8700_H__
#define __ADAFRUIT_SIMPLE_AHRS_FXOS8700_H__

#include <Adafruit_FXOS8700.h>

// Simple sensor fusion AHRS using an accelerometer and magnetometer.
class Adafruit_Simple_AHRS_FXOS8700
{
public:
  Adafruit_Simple_AHRS_FXOS8700(Adafruit_FXOS8700* accelmag);
  bool getOrientation(sensors_vec_t* orientation);

private:
  Adafruit_FXOS8700* _accelmag;

};

#endif
