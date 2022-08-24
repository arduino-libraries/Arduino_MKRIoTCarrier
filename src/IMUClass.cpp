/*
  This file is part of the Arduino_LSM6DSOX library.
  Copyright (c) 2021 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "IMUClass.h"

// sets function called on slave write
IMUClass::IMUClass( getRev_t getRevision)
{
  //If board_revision = 0, IMU module is LSM6DSOX, otherwhise is LSM6DS3
  board_revision = getRevision;
}

IMUClass::~IMUClass()
{
}

int IMUClass::begin()
{
  _revision = board_revision();
  LSM6DSOX = new LSM6DSOXClass(Wire, LSM6DSOX_ADDRESS);
  if (LSM6DSOX == nullptr) return 0;
  return LSM6DSOX->begin();
}

void IMUClass::end()
{
  LSM6DSOX->end();
  delete LSM6DSOX;
}

int IMUClass::readAcceleration(float& x, float& y, float& z)
{
  return LSM6DSOX->readAcceleration(x,y,z);
}

int IMUClass::accelerationAvailable()
{
  return LSM6DSOX->accelerationAvailable();
}

float IMUClass::accelerationSampleRate()
{
  return LSM6DSOX->accelerationSampleRate();
}

int IMUClass::readGyroscope(float& x, float& y, float& z)
{
  return LSM6DSOX->readGyroscope(x,y,z);
}

int IMUClass::gyroscopeAvailable()
{
  return LSM6DSOX->gyroscopeAvailable();
}

float IMUClass::gyroscopeSampleRate()
{
  return LSM6DSOX->gyroscopeSampleRate();
}