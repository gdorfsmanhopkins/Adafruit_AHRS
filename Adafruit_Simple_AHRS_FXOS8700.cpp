#include "Adafruit_Simple_AHRS_FXOS8700.h"

// Create a simple AHRS from an explicit accelerometer and magnetometer sensor.
Adafruit_Simple_AHRS_FXOS8700::Adafruit_Simple_AHRS_FXOS8700(Adafruit_FXOS8700* accelmag):
  _accelmag(accelmag)
{
}

// Compute orientation based on accelerometer and magnetometer data.
bool Adafruit_Simple_AHRS_FXOS8700::getOrientation(sensors_vec_t* orientation) {
  // Validate input and available sensors.
  if (orientation == NULL || _accelmag == NULL) return false;

  // Grab an acceleromter and magnetometer reading.
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  _accelmag->getEvent(&accel_event, &mag_event);

  float const PI_F = 3.14159265F;

  // roll: Rotation around the X-axis. -180 <= roll <= 180
  // a positive roll angle is defined to be a clockwise rotation about the positive X-axis
  //
  //                    y
  //      roll = atan2(---)
  //                    z
  //
  // where:  y, z are returned value from accelerometer sensor
  orientation->roll = (float)atan2(accel_event.acceleration.y, accel_event.acceleration.z);

  // pitch: Rotation around the Y-axis. -180 <= roll <= 180
  // a positive pitch angle is defined to be a clockwise rotation about the positive Y-axis
  //
  //                                 -x
  //      pitch = atan(-------------------------------)
  //                    y * sin(roll) + z * cos(roll)
  //
  // where:  x, y, z are returned value from accelerometer sensor
  if (accel_event.acceleration.y * sin(orientation->roll) + accel_event.acceleration.z * cos(orientation->roll) == 0)
    orientation->pitch = accel_event.acceleration.x > 0 ? (PI_F / 2) : (-PI_F / 2);
  else
    orientation->pitch = (float)atan(-accel_event.acceleration.x / (accel_event.acceleration.y * sin(orientation->roll) + \
                                                                     accel_event.acceleration.z * cos(orientation->roll)));

  // heading: Rotation around the Z-axis. -180 <= roll <= 180
  // a positive heading angle is defined to be a clockwise rotation about the positive Z-axis
  //
  //                                       z * sin(roll) - y * cos(roll)
  //   heading = atan2(--------------------------------------------------------------------------)
  //                    x * cos(pitch) + y * sin(pitch) * sin(roll) + z * sin(pitch) * cos(roll))
  //
  // where:  x, y, z are returned value from magnetometer sensor
  orientation->heading = (float)atan2(mag_event.magnetic.z * sin(orientation->roll) - mag_event.magnetic.y * cos(orientation->roll), \
                                      mag_event.magnetic.x * cos(orientation->pitch) + \
                                      mag_event.magnetic.y * sin(orientation->pitch) * sin(orientation->roll) + \
                                      mag_event.magnetic.z * sin(orientation->pitch) * cos(orientation->roll));


  // Convert angular data to degree
  orientation->roll = orientation->roll * 180 / PI_F;
  orientation->pitch = orientation->pitch * 180 / PI_F;
  orientation->heading = orientation->heading * 180 / PI_F;

  return true;
}
