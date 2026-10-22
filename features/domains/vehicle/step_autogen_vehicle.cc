// SPDX-License-Identifier: Apache-2.0
//
// Copyright 2026 JASPAR
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "../../step_definitions/step.h"


#include "Signal_Acceleration.h" // IWYU pragma: keep
#include "Signal_AngularVelocity.h" // IWYU pragma: keep
#include "Signal_AverageSpeed.h" // IWYU pragma: keep
#include "Signal_CargoVolume.h" // IWYU pragma: keep
#include "Signal_CurbWeight.h" // IWYU pragma: keep
#include "Signal_CurrentOverallWeight.h" // IWYU pragma: keep
#include "Signal_EmissionsCO2.h" // IWYU pragma: keep
#include "Signal_GrossWeight.h" // IWYU pragma: keep
#include "Signal_Height.h" // IWYU pragma: keep
#include "Signal_IsAutoPowerOptimize.h" // IWYU pragma: keep
#include "Signal_IsBrokenDown.h" // IWYU pragma: keep
#include "Signal_IsMoving.h" // IWYU pragma: keep
#include "Signal_Length.h" // IWYU pragma: keep
#include "Signal_LowVoltageSystemState.h" // IWYU pragma: keep
#include "Signal_MaxTowBallWeight.h" // IWYU pragma: keep
#include "Signal_MaxTowWeight.h" // IWYU pragma: keep
#include "Signal_PowerOptimizeLevel.h" // IWYU pragma: keep
#include "Signal_RoofLoad.h" // IWYU pragma: keep
#include "Signal_Speed.h" // IWYU pragma: keep
#include "Signal_StartTime.h" // IWYU pragma: keep
#include "Signal_TraveledDistance.h" // IWYU pragma: keep
#include "Signal_TraveledDistanceSinceStart.h" // IWYU pragma: keep
#include "Signal_TripDuration.h" // IWYU pragma: keep
#include "Signal_TurningDiameter.h" // IWYU pragma: keep
#include "Signal_WidthExcludingMirrors.h" // IWYU pragma: keep
#include "Signal_WidthFoldedMirrors.h" // IWYU pragma: keep
#include "Signal_WidthIncludingMirrors.h" // IWYU pragma: keep


namespace {
__attribute__((constructor)) void InitVehicle(void) {
    REGISTER_SENSOR("Vehicle.Acceleration", yoriito::vehicle::acceleration, yoriito::types::Acceleration);
    REGISTER_SENSOR("Vehicle.AngularVelocity", yoriito::vehicle::angularvelocity, yoriito::types::AngularVelocity);
    REGISTER_SENSOR("Vehicle.AverageSpeed", yoriito::vehicle::averagespeed, float);
    REGISTER_ATTRIBUTE("Vehicle.CargoVolume", yoriito::vehicle::cargovolume, float);
    REGISTER_ATTRIBUTE("Vehicle.CurbWeight", yoriito::vehicle::curbweight, uint16_t);
    REGISTER_SENSOR("Vehicle.CurrentOverallWeight", yoriito::vehicle::currentoverallweight, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.EmissionsCO2", yoriito::vehicle::emissionsco2, int16_t);
    REGISTER_ATTRIBUTE("Vehicle.GrossWeight", yoriito::vehicle::grossweight, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.Height", yoriito::vehicle::height, uint16_t);
    REGISTER_ACTUATOR("Vehicle.IsAutoPowerOptimize", yoriito::vehicle::isautopoweroptimize, bool);
    REGISTER_SENSOR("Vehicle.IsBrokenDown", yoriito::vehicle::isbrokendown, bool);
    REGISTER_SENSOR("Vehicle.IsMoving", yoriito::vehicle::ismoving, bool);
    REGISTER_ATTRIBUTE("Vehicle.Length", yoriito::vehicle::length, uint16_t);
    REGISTER_SENSOR("Vehicle.LowVoltageSystemState", yoriito::vehicle::lowvoltagesystemstate, std::string);
    REGISTER_ATTRIBUTE("Vehicle.MaxTowBallWeight", yoriito::vehicle::maxtowballweight, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.MaxTowWeight", yoriito::vehicle::maxtowweight, uint16_t);
    REGISTER_ACTUATOR("Vehicle.PowerOptimizeLevel", yoriito::vehicle::poweroptimizelevel, uint8_t);
    REGISTER_ATTRIBUTE("Vehicle.RoofLoad", yoriito::vehicle::roofload, int16_t);
    REGISTER_SENSOR("Vehicle.Speed", yoriito::vehicle::speed, float);
    REGISTER_ATTRIBUTE("Vehicle.StartTime", yoriito::vehicle::starttime, std::string);
    REGISTER_SENSOR("Vehicle.TraveledDistance", yoriito::vehicle::traveleddistance, uint32_t);
    REGISTER_SENSOR("Vehicle.TraveledDistanceSinceStart", yoriito::vehicle::traveleddistancesincestart, uint32_t);
    REGISTER_SENSOR("Vehicle.TripDuration", yoriito::vehicle::tripduration, float);
    REGISTER_ATTRIBUTE("Vehicle.TurningDiameter", yoriito::vehicle::turningdiameter, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.WidthExcludingMirrors", yoriito::vehicle::widthexcludingmirrors, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.WidthFoldedMirrors", yoriito::vehicle::widthfoldedmirrors, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.WidthIncludingMirrors", yoriito::vehicle::widthincludingmirrors, uint16_t);
    
} // namespace
}