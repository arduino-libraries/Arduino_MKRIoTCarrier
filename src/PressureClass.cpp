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

#include "PressureClass.h"

// sets function called on slave write
PressureClass::PressureClass( getRev_t getRevision)
{
  board_revision = getRevision;
}

PressureClass::~PressureClass()
{
}

int PressureClass::begin()
{
  _revision = board_revision();
  if (_revision == BOARD_REVISION_2) {
    if (mkr_iot_carrier_rev2::iaqSensor == nullptr) {
      iaqSensor = new Bsec();
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
      mkr_iot_carrier_rev2::iaqSensor = iaqSensor;
    } else {
      iaqSensor = mkr_iot_carrier_rev2::iaqSensor;
    }
    return 1;
  } else {
    if (LPS22HB == nullptr) {
      LPS22HB = new LPS22HBClass(Wire);
    }
    if (LPS22HB == nullptr) return 0;
    return LPS22HB->begin();
  }
}

int PressureClass::checkIaqSensorStatus(void)
{
  if (iaqSensor->status != BSEC_OK) {
    if (iaqSensor->status < BSEC_OK) {
     return STATUS_ERROR;
    }
  }

  if (iaqSensor->bme680Status != BME680_OK) {
    if (iaqSensor->bme680Status < BME680_OK) {
     return STATUS_ERROR;
    }
  }
  return STATUS_OK;
}

void PressureClass::end()
{
  if (_revision == BOARD_REVISION_2) {
    delete iaqSensor;
    iaqSensor = nullptr;
  } else {
    LPS22HB->end();
    delete LPS22HB;
    LPS22HB = nullptr;
  }
}

float PressureClass::readPressure(int units)
{
  if (_revision == BOARD_REVISION_2) {
    while(!iaqSensor->run()){ }
    float reading = iaqSensor->pressure/1000;
    if (units == MILLIBAR) { // 1 kPa = 10 millibar
      return reading * 10;
    } else if (units == PSI) {  // 1 kPa = 0.145038 PSI
      return reading * 0.145038;
    } else {
      return reading;
    }
  }
  return LPS22HB->readPressure(units);
}

float PressureClass::readTemperature(int units /*= CELSIUS*/)
{
  if (_revision == BOARD_REVISION_2) {
    while(!iaqSensor->run()){}
    float reading = iaqSensor->temperature;
    if (units == FAHRENHEIT){
      return (reading * 9.0 / 5.0) + 32.0;
    } else {
      return reading;
    }
  }
  return LPS22HB->readTemperature();
}

