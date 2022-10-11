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

#include "PressureClass.h"

Bme68x* BME;

// sets function called on slave write
PressureClass::PressureClass( getRev_t getRevision)
{
  //If board_revision = 1, IMU module is LSM6DSOX, otherwise is LSM6DS3
  board_revision = getRevision;
}

PressureClass::~PressureClass()
{
}

int PressureClass::begin()
{
  _revision = board_revision();
  if (_revision == BOARD_REVISION_2) {
    if (BME == nullptr) {
      BME = new Bme68x();
    }
    BME->begin(BME_SLAVE_ADDRESS, Wire);

    if (BME->checkStatus() == BME68X_ERROR)
    {
      return 0;
    }

	  /* Set the default configuration for temperature, pressure and humidity */
    BME->setTPH();

    BME->setSeqSleep(BME68X_ODR_250_MS);
    BME->setOpMode(BME68X_SEQUENTIAL_MODE);
    return 1;
  } else {
    if (LPS22HB == nullptr) {
      LPS22HB = new LPS22HBClass(Wire);
    }
    if (LPS22HB == nullptr) return 0;
    return LPS22HB->begin();
  }
}

void PressureClass::end()
{
  if (_revision == BOARD_REVISION_2) {
    delete BME;
    BME = nullptr;
  } else {
    LPS22HB->end();
    delete LPS22HB;
    LPS22HB = nullptr;
  }
}

float PressureClass::readPressure(int units)
{
  if (_revision == BOARD_REVISION_2) {
    bme68xData data;
    uint8_t nFieldsLeft = 0;
    BME->fetchData();
    nFieldsLeft = BME->getData(data);
    return data.pressure/1000;
    
  }
  return LPS22HB->readPressure(units);
}

float PressureClass::readTemperature()
{
  if (_revision == BOARD_REVISION_2) {
    bme68xData data;
    uint8_t nFieldsLeft = 0;
    BME->fetchData();
    nFieldsLeft = BME->getData(data);
    return data.temperature;
    
  }
  return LPS22HB->readTemperature();
}

