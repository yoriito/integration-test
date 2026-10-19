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


#include "body/Body.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitBody(void) {
    REGISTER_ACTUATOR("Vehicle.Body.Hood.IsLocked", yoriito::vehicle::body::hood::islocked, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Hood.IsOpen", yoriito::vehicle::body::hood::isopen, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Hood.Position", yoriito::vehicle::body::hood::position, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Horn.IsActive", yoriito::vehicle::body::horn::isactive, bool);
    REGISTER_ACTUATOR("Vehicle.Body.IsAutoPowerOptimize", yoriito::vehicle::body::isautopoweroptimize, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.Backup.IsDefect", yoriito::vehicle::body::lights::backup::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Backup.IsOn", yoriito::vehicle::body::lights::backup::ison, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.Beam.High.IsDefect", yoriito::vehicle::body::lights::beam::high::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Beam.High.IsOn", yoriito::vehicle::body::lights::beam::high::ison, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.Beam.Low.IsDefect", yoriito::vehicle::body::lights::beam::low::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Beam.Low.IsOn", yoriito::vehicle::body::lights::beam::low::ison, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Brake.IsActive", yoriito::vehicle::body::lights::brake::isactive, std::string);
    REGISTER_SENSOR("Vehicle.Body.Lights.Brake.IsDefect", yoriito::vehicle::body::lights::brake::isdefect, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.DirectionIndicator.Left.IsDefect", yoriito::vehicle::body::lights::directionindicator::left::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.DirectionIndicator.Left.IsSignaling", yoriito::vehicle::body::lights::directionindicator::left::issignaling, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.DirectionIndicator.Right.IsDefect", yoriito::vehicle::body::lights::directionindicator::right::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.DirectionIndicator.Right.IsSignaling", yoriito::vehicle::body::lights::directionindicator::right::issignaling, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.Fog.Front.IsDefect", yoriito::vehicle::body::lights::fog::front::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Fog.Front.IsOn", yoriito::vehicle::body::lights::fog::front::ison, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.Fog.Rear.IsDefect", yoriito::vehicle::body::lights::fog::rear::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Fog.Rear.IsOn", yoriito::vehicle::body::lights::fog::rear::ison, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.Hazard.IsDefect", yoriito::vehicle::body::lights::hazard::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Hazard.IsSignaling", yoriito::vehicle::body::lights::hazard::issignaling, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.LicensePlate.IsDefect", yoriito::vehicle::body::lights::licenseplate::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.LicensePlate.IsOn", yoriito::vehicle::body::lights::licenseplate::ison, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.Parking.IsDefect", yoriito::vehicle::body::lights::parking::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Parking.IsOn", yoriito::vehicle::body::lights::parking::ison, bool);
    REGISTER_SENSOR("Vehicle.Body.Lights.Running.IsDefect", yoriito::vehicle::body::lights::running::isdefect, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Lights.Running.IsOn", yoriito::vehicle::body::lights::running::ison, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.DriverSide.IsFolded", yoriito::vehicle::body::mirrors::driverside::isfolded, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.DriverSide.IsHeatingOn", yoriito::vehicle::body::mirrors::driverside::isheatingon, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.DriverSide.IsLocked", yoriito::vehicle::body::mirrors::driverside::islocked, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.DriverSide.Tilt", yoriito::vehicle::body::mirrors::driverside::tilt, int8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.DriverSide.Yaw", yoriito::vehicle::body::mirrors::driverside::yaw, int8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.PassengerSide.IsFolded", yoriito::vehicle::body::mirrors::passengerside::isfolded, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.PassengerSide.IsHeatingOn", yoriito::vehicle::body::mirrors::passengerside::isheatingon, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.PassengerSide.IsLocked", yoriito::vehicle::body::mirrors::passengerside::islocked, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.PassengerSide.Tilt", yoriito::vehicle::body::mirrors::passengerside::tilt, int8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Mirrors.PassengerSide.Yaw", yoriito::vehicle::body::mirrors::passengerside::yaw, int8_t);
    REGISTER_ACTUATOR("Vehicle.Body.PowerOptimizeLevel", yoriito::vehicle::body::poweroptimizelevel, uint8_t);
    REGISTER_SENSOR("Vehicle.Body.Raindetection.Intensity", yoriito::vehicle::body::raindetection::intensity, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Body.RearMainSpoilerPosition", yoriito::vehicle::body::rearmainspoilerposition, float);
    REGISTER_ACTUATOR("Vehicle.Body.Trunk.Front.IsLightOn", yoriito::vehicle::body::trunk::front::islighton, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Trunk.Front.IsLocked", yoriito::vehicle::body::trunk::front::islocked, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Trunk.Front.IsOpen", yoriito::vehicle::body::trunk::front::isopen, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Trunk.Front.Position", yoriito::vehicle::body::trunk::front::position, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Trunk.Rear.IsLightOn", yoriito::vehicle::body::trunk::rear::islighton, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Trunk.Rear.IsLocked", yoriito::vehicle::body::trunk::rear::islocked, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Trunk.Rear.IsOpen", yoriito::vehicle::body::trunk::rear::isopen, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Trunk.Rear.Position", yoriito::vehicle::body::trunk::rear::position, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Front.IsHeatingOn", yoriito::vehicle::body::windshield::front::isheatingon, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.WasherFluid.Level", yoriito::vehicle::body::windshield::front::washerfluid::level, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Front.Wiping.Intensity", yoriito::vehicle::body::windshield::front::wiping::intensity, uint8_t);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.IsWipersWorn", yoriito::vehicle::body::windshield::front::wiping::iswipersworn, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Front.Wiping.Mode", yoriito::vehicle::body::windshield::front::wiping::mode, std::string);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.System.DriveCurrent", yoriito::vehicle::body::windshield::front::wiping::system::drivecurrent, float);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Front.Wiping.System.Frequency", yoriito::vehicle::body::windshield::front::wiping::system::frequency, uint8_t);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.System.IsBlocked", yoriito::vehicle::body::windshield::front::wiping::system::isblocked, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.System.IsEndingWipeCycle", yoriito::vehicle::body::windshield::front::wiping::system::isendingwipecycle, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.System.IsOverheated", yoriito::vehicle::body::windshield::front::wiping::system::isoverheated, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.System.IsPositionReached", yoriito::vehicle::body::windshield::front::wiping::system::ispositionreached, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.System.IsWiperError", yoriito::vehicle::body::windshield::front::wiping::system::iswipererror, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.System.IsWiping", yoriito::vehicle::body::windshield::front::wiping::system::iswiping, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Front.Wiping.System.Mode", yoriito::vehicle::body::windshield::front::wiping::system::mode, std::string);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Front.Wiping.System.Position", yoriito::vehicle::body::windshield::front::wiping::system::position, uint8_t);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Front.Wiping.WiperWear", yoriito::vehicle::body::windshield::front::wiping::wiperwear, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Rear.IsHeatingOn", yoriito::vehicle::body::windshield::rear::isheatingon, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.WasherFluid.Level", yoriito::vehicle::body::windshield::rear::washerfluid::level, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Rear.Wiping.Intensity", yoriito::vehicle::body::windshield::rear::wiping::intensity, uint8_t);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.IsWipersWorn", yoriito::vehicle::body::windshield::rear::wiping::iswipersworn, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Rear.Wiping.Mode", yoriito::vehicle::body::windshield::rear::wiping::mode, std::string);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.System.DriveCurrent", yoriito::vehicle::body::windshield::rear::wiping::system::drivecurrent, float);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Rear.Wiping.System.Frequency", yoriito::vehicle::body::windshield::rear::wiping::system::frequency, uint8_t);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.System.IsBlocked", yoriito::vehicle::body::windshield::rear::wiping::system::isblocked, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.System.IsEndingWipeCycle", yoriito::vehicle::body::windshield::rear::wiping::system::isendingwipecycle, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.System.IsOverheated", yoriito::vehicle::body::windshield::rear::wiping::system::isoverheated, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.System.IsPositionReached", yoriito::vehicle::body::windshield::rear::wiping::system::ispositionreached, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.System.IsWiperError", yoriito::vehicle::body::windshield::rear::wiping::system::iswipererror, bool);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.System.IsWiping", yoriito::vehicle::body::windshield::rear::wiping::system::iswiping, bool);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Rear.Wiping.System.Mode", yoriito::vehicle::body::windshield::rear::wiping::system::mode, std::string);
    REGISTER_ACTUATOR("Vehicle.Body.Windshield.Rear.Wiping.System.Position", yoriito::vehicle::body::windshield::rear::wiping::system::position, uint8_t);
    REGISTER_SENSOR("Vehicle.Body.Windshield.Rear.Wiping.WiperWear", yoriito::vehicle::body::windshield::rear::wiping::wiperwear, uint8_t);
    
} // namespace
}