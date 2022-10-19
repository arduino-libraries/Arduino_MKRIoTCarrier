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


// sets function called on slave write
EnvClass::EnvClass( getRev_t getRevision )
{
  //If board_revision = 1, IMU module is LSM6DSOX, otherwise is LSM6DS3
  board_revision = getRevision;
}

EnvClass::~EnvClass()
{
}

int EnvClass::begin()
{
  _revision = board_revision();
  if (_revision == BOARD_REVISION_2) {
   if (iaqSensor == nullptr) {
      iaqSensor = new Bsec();
    }
    iaqSensor->begin(BME680_I2C_ADDR_PRIMARY, Wire);
	  if (checkIaqSensorStatus() == STATUS_ERROR){
      return 0;
    }

    bsec_virtual_sensor_t sensorList[10] = {
      BSEC_OUTPUT_RAW_TEMPERATURE,
      BSEC_OUTPUT_RAW_PRESSURE,
      BSEC_OUTPUT_RAW_HUMIDITY,
      BSEC_OUTPUT_RAW_GAS,
      BSEC_OUTPUT_IAQ,
      BSEC_OUTPUT_STATIC_IAQ,
      BSEC_OUTPUT_CO2_EQUIVALENT,
      BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    };

    iaqSensor->updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_CONTINUOUS);
	  if (checkIaqSensorStatus() == STATUS_ERROR){
      return 0;
    }

    return 1;
  } else {
    if (HTS221 == nullptr) {
      HTS221 = new HTS221Class(Wire);
    }
    return HTS221->begin();
  }
}

int EnvClass::checkIaqSensorStatus(void)
{
  if (iaqSensor->status != BSEC_OK) {
    if (iaqSensor->status < BSEC_OK) {
        return 0;
    }
  }

  if (iaqSensor->bme680Status != BME680_OK) {
    if (iaqSensor->bme680Status < BME680_OK) {
      return 0;
    }
  }
  return 1;
}

void EnvClass::end()
{
  if (_revision == BOARD_REVISION_2) {
    delete iaqSensor;
    iaqSensor = nullptr;
  } else {
    HTS221->end();
    delete HTS221;
    HTS221 = nullptr;
  }
}

float EnvClass::readTemperature(int units /*= CELSIUS*/)
{
  if (_revision == BOARD_REVISION_2) {
    while(!iaqSensor->run()){ }
    return iaqSensor->temperature;
  }
  return HTS221->readTemperature(units);
}

float EnvClass::readHumidity()
{
  if (_revision == BOARD_REVISION_2) {
    while(!iaqSensor->run()){ }
    return iaqSensor->humidity;

  }
  return HTS221->readHumidity();
}
