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

#include "EnvClass.h"


// sets function called on slave write
EnvClass::EnvClass( getRev_t getRevision )
{
  board_revision = getRevision;
}

EnvClass::~EnvClass()
{
}

extern const uint8_t bsec_config_iaq[];

int EnvClass::begin()
{
  _revision = board_revision();
  if (_revision == BOARD_REVISION_2) {
    if (mkr_iot_carrier_rev2::iaqSensor == nullptr) {
      iaqSensor = new Bsec();
      iaqSensor->begin(BME68X_I2C_ADDR_LOW, Wire);
      if (checkIaqSensorStatus() == STATUS_ERROR){
        return 0;
      }
      iaqSensor->setConfig(bsec_config_iaq);

      bsec_virtual_sensor_t sensorList[13] = {
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_STATIC_IAQ,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
        BSEC_OUTPUT_RAW_TEMPERATURE,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_RAW_HUMIDITY,
        BSEC_OUTPUT_RAW_GAS,
        BSEC_OUTPUT_STABILIZATION_STATUS,
        BSEC_OUTPUT_RUN_IN_STATUS,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
        BSEC_OUTPUT_GAS_PERCENTAGE
      };

      iaqSensor->updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
      if (checkIaqSensorStatus() == STATUS_ERROR){
        return 0;
      }
      mkr_iot_carrier_rev2::iaqSensor = iaqSensor;
    } else {
      iaqSensor = mkr_iot_carrier_rev2::iaqSensor;
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
  if (iaqSensor->bsecStatus != BSEC_OK) {
    if (iaqSensor->bsecStatus < BSEC_OK) {
        return 0;
    }
  }

  if (iaqSensor->bme68xStatus != BME68X_OK) {
    if (iaqSensor->bme68xStatus < BME68X_OK) {
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
    if(iaqSensor->run()){
      mkr_iot_carrier_rev2::cache();
    }
    if (units == FAHRENHEIT){
      return (mkr_iot_carrier_rev2::temperature * 9.0 / 5.0) + 32.0;
    } else {
      return mkr_iot_carrier_rev2::temperature;
    }
  }
  return HTS221->readTemperature(units);
}

float EnvClass::readHumidity()
{
  if (_revision == BOARD_REVISION_2) {
    if(iaqSensor->run()){
      mkr_iot_carrier_rev2::cache();
    }
    return mkr_iot_carrier_rev2::humidity;
  }
  return HTS221->readHumidity();
}
