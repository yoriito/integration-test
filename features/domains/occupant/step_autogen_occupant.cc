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


#include "occupant/Occupant.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitOccupant(void) {
    REGISTER_SENSOR("Vehicle.Occupant.Row1.DriverSide.HeadPosition", yoriito::vehicle::occupant::row1::driverside::headposition, yoriito::types::Pose);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.DriverSide.Identifier.Issuer", yoriito::vehicle::occupant::row1::driverside::identifier::issuer, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.DriverSide.Identifier.Subject", yoriito::vehicle::occupant::row1::driverside::identifier::subject, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.DriverSide.MidEyeGaze", yoriito::vehicle::occupant::row1::driverside::mideyegaze, yoriito::types::PointingDirection);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.Middle.HeadPosition", yoriito::vehicle::occupant::row1::middle::headposition, yoriito::types::Pose);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.Middle.Identifier.Issuer", yoriito::vehicle::occupant::row1::middle::identifier::issuer, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.Middle.Identifier.Subject", yoriito::vehicle::occupant::row1::middle::identifier::subject, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.Middle.MidEyeGaze", yoriito::vehicle::occupant::row1::middle::mideyegaze, yoriito::types::PointingDirection);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.PassengerSide.HeadPosition", yoriito::vehicle::occupant::row1::passengerside::headposition, yoriito::types::Pose);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.PassengerSide.Identifier.Issuer", yoriito::vehicle::occupant::row1::passengerside::identifier::issuer, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.PassengerSide.Identifier.Subject", yoriito::vehicle::occupant::row1::passengerside::identifier::subject, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row1.PassengerSide.MidEyeGaze", yoriito::vehicle::occupant::row1::passengerside::mideyegaze, yoriito::types::PointingDirection);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.DriverSide.HeadPosition", yoriito::vehicle::occupant::row2::driverside::headposition, yoriito::types::Pose);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.DriverSide.Identifier.Issuer", yoriito::vehicle::occupant::row2::driverside::identifier::issuer, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.DriverSide.Identifier.Subject", yoriito::vehicle::occupant::row2::driverside::identifier::subject, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.DriverSide.MidEyeGaze", yoriito::vehicle::occupant::row2::driverside::mideyegaze, yoriito::types::PointingDirection);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.Middle.HeadPosition", yoriito::vehicle::occupant::row2::middle::headposition, yoriito::types::Pose);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.Middle.Identifier.Issuer", yoriito::vehicle::occupant::row2::middle::identifier::issuer, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.Middle.Identifier.Subject", yoriito::vehicle::occupant::row2::middle::identifier::subject, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.Middle.MidEyeGaze", yoriito::vehicle::occupant::row2::middle::mideyegaze, yoriito::types::PointingDirection);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.PassengerSide.HeadPosition", yoriito::vehicle::occupant::row2::passengerside::headposition, yoriito::types::Pose);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.PassengerSide.Identifier.Issuer", yoriito::vehicle::occupant::row2::passengerside::identifier::issuer, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.PassengerSide.Identifier.Subject", yoriito::vehicle::occupant::row2::passengerside::identifier::subject, std::string);
    REGISTER_SENSOR("Vehicle.Occupant.Row2.PassengerSide.MidEyeGaze", yoriito::vehicle::occupant::row2::passengerside::mideyegaze, yoriito::types::PointingDirection);
    
} // namespace
}