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

#include "EnvClass.h"

extern Bme68x* BME;

// sets function called on slave write
EnvClass::EnvClass( getRev_t getRevision )
{
  //If board_revision = 1, IMU module is LSM6DSOX, otherwhise is LSM6DS3
  board_revision = getRevision;
}

EnvClass::~EnvClass()
{
}

int EnvClass::begin()
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
    HTS221 = new HTS221Class(Wire);
    return HTS221->begin();
  }
}

void EnvClass::end()
{
  if (_revision == BOARD_REVISION_2) {
    delete BME;
  } else {
    HTS221->end();
    delete HTS221;
  }
}

float EnvClass::readTemperature(int units /*= CELSIUS*/)
{
  if (_revision == BOARD_REVISION_2) {
    bme68xData data;
    uint8_t nFieldsLeft = 0;
    uint8_t fetchDataResult = BME->fetchData();
    nFieldsLeft = BME->getData(data);
    return data.temperature;
  }
  else {
    return HTS221->readTemperature(units);
  }
}

float EnvClass::readHumidity()
{
  if (_revision == BOARD_REVISION_2) {
    bme68xData data;
    uint8_t nFieldsLeft = 0;
    uint8_t fetchDataResult = BME->fetchData();
    nFieldsLeft = BME->getData(data); 
    return data.humidity;
    
  }
  return HTS221->readHumidity();
}