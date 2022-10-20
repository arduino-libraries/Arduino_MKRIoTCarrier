/*
  This file is part of the Arduino_MKRIoTCarrier library.
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
  board_revision = getRevision;
}

IMUClass::~IMUClass()
{
}

int IMUClass::begin()
{
  _revision = board_revision();
  // If board_revision = BOARD_REVISION_2, IMU module is LSM6DSOX, otherwise is LSM6DS3
  if (_revision == BOARD_REVISION_2) {
    LSM6DSOX = new LSM6DSOXClass(Wire, LSM6DSOX_ADDRESS);
    if (LSM6DSOX == nullptr) return 0;
    return LSM6DSOX->begin();
  } else {
    LSM6DS3 = new LSM6DS3Class(Wire, LSM6DS3_ADDRESS);
    if (LSM6DS3 == nullptr) return 0;
    return LSM6DS3->begin();
  }

}

void IMUClass::end()
{
  if (_revision == BOARD_REVISION_2) {
    LSM6DSOX->end();
    delete LSM6DSOX;
    LSM6DSOX = nullptr;
  } else {
    LSM6DS3->end();
    delete LSM6DS3;
    LSM6DS3 = nullptr;
  }
}

int IMUClass::readAcceleration(float& x, float& y, float& z)
{
  if (_revision == BOARD_REVISION_2) {
    return LSM6DSOX->readAcceleration(x,y,z);
  } else {
    return LSM6DS3->readAcceleration(x,y,z);
  }
}

int IMUClass::accelerationAvailable()
{
  if (_revision == BOARD_REVISION_2) {
    return LSM6DSOX->accelerationAvailable();
  } else {
    return LSM6DS3->accelerationAvailable();
  }

}

float IMUClass::accelerationSampleRate()
{
  if (_revision == BOARD_REVISION_2) {
    return LSM6DSOX->accelerationSampleRate();
  } else {
    return LSM6DS3->accelerationSampleRate();
  }
}

int IMUClass::readGyroscope(float& x, float& y, float& z)
{
  if (_revision == BOARD_REVISION_2) {
    return LSM6DSOX->readGyroscope(x,y,z);
  } else {
    return LSM6DS3->readGyroscope(x,y,z);
  }
}

int IMUClass::gyroscopeAvailable()
{
  if (_revision == BOARD_REVISION_2) {
    return LSM6DSOX->gyroscopeAvailable();
  } else {
    return LSM6DS3->gyroscopeAvailable();
  }
}

float IMUClass::gyroscopeSampleRate()
{
  if (_revision == BOARD_REVISION_2) {
    return LSM6DSOX->gyroscopeSampleRate();
  } else {
    return LSM6DS3->gyroscopeSampleRate();
  }
}
