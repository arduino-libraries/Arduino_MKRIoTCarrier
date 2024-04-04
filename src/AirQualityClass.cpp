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

#include "AirQualityClass.h"

// sets function called on slave write
AirQualityClass::AirQualityClass( getRev_t getRevision)
{
  board_revision = getRevision;
}

AirQualityClass::~AirQualityClass()
{
}

/* Configure the BSEC library with information about the sensor
    18v/33v = Voltage at Vdd. 1.8V or 3.3V
    3s/300s = BSEC operating mode, BSEC_SAMPLE_RATE_LP or BSEC_SAMPLE_RATE_ULP
    4d/28d = Operating age of the sensor in days
    generic_18v_3s_4d
    generic_18v_3s_28d
    generic_18v_300s_4d
    generic_18v_300s_28d
    generic_33v_3s_4d
    generic_33v_3s_28d
    generic_33v_300s_4d
    generic_33v_300s_28d
*/

extern "C" const uint8_t bsec_config_iaq[] = {
#include "config/generic_33v_3s_4d/bsec_iaq.txt"
};

int AirQualityClass::begin()
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
      iaqSensor->updateSubscription(sensorList, 13, BSEC_SAMPLE_RATE_LP);
      if (checkIaqSensorStatus() == STATUS_ERROR){
        return 0;
      }
      mkr_iot_carrier_rev2::iaqSensor = iaqSensor;
    } else {
      iaqSensor = mkr_iot_carrier_rev2::iaqSensor;
    }
    return 1;
  }
  return 0;
}

int AirQualityClass::checkIaqSensorStatus(void)
{
  if (iaqSensor->bsecStatus != BSEC_OK) {
    if (iaqSensor->bsecStatus < BSEC_OK) {
     return STATUS_ERROR;
    }
  }

  if (iaqSensor->bme68xStatus != BME68X_OK) {
    if (iaqSensor->bme68xStatus < BME68X_OK) {
     return STATUS_ERROR;
    }
  }
  return STATUS_OK;
}

void AirQualityClass::end()
{
  if (_revision == BOARD_REVISION_2) {
    delete iaqSensor;
    iaqSensor = nullptr;
  }
}

float AirQualityClass::readVOC()
{
  if (_revision == BOARD_REVISION_2) {
    if(iaqSensor->run()){
      mkr_iot_carrier_rev2::cache();
    }
  }
  return mkr_iot_carrier_rev2::breathVocEquivalent;
}

float AirQualityClass::readGasResistor()
{
  if (_revision == BOARD_REVISION_2) {
    if(iaqSensor->run()){
      mkr_iot_carrier_rev2::cache();
    }
  }
  return mkr_iot_carrier_rev2::gasResistance;
}

float AirQualityClass::readIAQ()
{
  if (_revision == BOARD_REVISION_2) {
    if(iaqSensor->run()){
      mkr_iot_carrier_rev2::cache();
    }
  }
  return mkr_iot_carrier_rev2::iaq;
}

float AirQualityClass::readIAQAccuracy()
{
  if (_revision == BOARD_REVISION_2) {
    if(iaqSensor->run()){
      mkr_iot_carrier_rev2::cache();
    }
  }
  return mkr_iot_carrier_rev2::iaqAccuracy;
}

float AirQualityClass::readStaticIAQ()
{
  if (_revision == BOARD_REVISION_2) {
    if(iaqSensor->run()){
      mkr_iot_carrier_rev2::cache();
    }
  }
  return mkr_iot_carrier_rev2::staticIaq;
}


float AirQualityClass::readCO2()
{
  float reading = 0.0;
  if (_revision == BOARD_REVISION_2) {
    if(iaqSensor->run()){
      mkr_iot_carrier_rev2::cache();
    }
  }
  return mkr_iot_carrier_rev2::co2Equivalent;
}

