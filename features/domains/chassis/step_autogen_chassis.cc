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


#include "chassis/Chassis.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitChassis(void) {
    REGISTER_SENSOR("Vehicle.Chassis.Accelerator.PedalPosition", yoriito::vehicle::chassis::accelerator::pedalposition, uint8_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row1.AxleWidth", yoriito::vehicle::chassis::axle::row1::axlewidth, uint16_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.SteeringAngle", yoriito::vehicle::chassis::axle::row1::steeringangle, float);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row1.TireAspectRatio", yoriito::vehicle::chassis::axle::row1::tireaspectratio, uint8_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row1.TireWidth", yoriito::vehicle::chassis::axle::row1::tirewidth, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row1.TrackWidth", yoriito::vehicle::chassis::axle::row1::trackwidth, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row1.TreadWidth", yoriito::vehicle::chassis::axle::row1::treadwidth, uint16_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.AngularSpeed", yoriito::vehicle::chassis::axle::row1::wheel::left::angularspeed, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Brake.FluidLevel", yoriito::vehicle::chassis::axle::row1::wheel::left::brake::fluidlevel, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Brake.IsBrakesWorn", yoriito::vehicle::chassis::axle::row1::wheel::left::brake::isbrakesworn, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Brake.IsFluidLevelLow", yoriito::vehicle::chassis::axle::row1::wheel::left::brake::isfluidlevellow, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Brake.PadWear", yoriito::vehicle::chassis::axle::row1::wheel::left::brake::padwear, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Speed", yoriito::vehicle::chassis::axle::row1::wheel::left::speed, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Tire.AirTemperature", yoriito::vehicle::chassis::axle::row1::wheel::left::tire::airtemperature, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Tire.IsPressureLow", yoriito::vehicle::chassis::axle::row1::wheel::left::tire::ispressurelow, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Tire.Pressure", yoriito::vehicle::chassis::axle::row1::wheel::left::tire::pressure, uint16_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Left.Tire.RubberTemperature", yoriito::vehicle::chassis::axle::row1::wheel::left::tire::rubbertemperature, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.AngularSpeed", yoriito::vehicle::chassis::axle::row1::wheel::right::angularspeed, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Brake.FluidLevel", yoriito::vehicle::chassis::axle::row1::wheel::right::brake::fluidlevel, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Brake.IsBrakesWorn", yoriito::vehicle::chassis::axle::row1::wheel::right::brake::isbrakesworn, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Brake.IsFluidLevelLow", yoriito::vehicle::chassis::axle::row1::wheel::right::brake::isfluidlevellow, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Brake.PadWear", yoriito::vehicle::chassis::axle::row1::wheel::right::brake::padwear, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Speed", yoriito::vehicle::chassis::axle::row1::wheel::right::speed, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Tire.AirTemperature", yoriito::vehicle::chassis::axle::row1::wheel::right::tire::airtemperature, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Tire.IsPressureLow", yoriito::vehicle::chassis::axle::row1::wheel::right::tire::ispressurelow, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Tire.Pressure", yoriito::vehicle::chassis::axle::row1::wheel::right::tire::pressure, uint16_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row1.Wheel.Right.Tire.RubberTemperature", yoriito::vehicle::chassis::axle::row1::wheel::right::tire::rubbertemperature, float);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row1.WheelCount", yoriito::vehicle::chassis::axle::row1::wheelcount, uint8_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row1.WheelDiameter", yoriito::vehicle::chassis::axle::row1::wheeldiameter, float);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row1.WheelWidth", yoriito::vehicle::chassis::axle::row1::wheelwidth, float);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row2.AxleWidth", yoriito::vehicle::chassis::axle::row2::axlewidth, uint16_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.SteeringAngle", yoriito::vehicle::chassis::axle::row2::steeringangle, float);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row2.TireAspectRatio", yoriito::vehicle::chassis::axle::row2::tireaspectratio, uint8_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row2.TireWidth", yoriito::vehicle::chassis::axle::row2::tirewidth, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row2.TrackWidth", yoriito::vehicle::chassis::axle::row2::trackwidth, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row2.TreadWidth", yoriito::vehicle::chassis::axle::row2::treadwidth, uint16_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.AngularSpeed", yoriito::vehicle::chassis::axle::row2::wheel::left::angularspeed, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Brake.FluidLevel", yoriito::vehicle::chassis::axle::row2::wheel::left::brake::fluidlevel, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Brake.IsBrakesWorn", yoriito::vehicle::chassis::axle::row2::wheel::left::brake::isbrakesworn, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Brake.IsFluidLevelLow", yoriito::vehicle::chassis::axle::row2::wheel::left::brake::isfluidlevellow, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Brake.PadWear", yoriito::vehicle::chassis::axle::row2::wheel::left::brake::padwear, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Speed", yoriito::vehicle::chassis::axle::row2::wheel::left::speed, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Tire.AirTemperature", yoriito::vehicle::chassis::axle::row2::wheel::left::tire::airtemperature, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Tire.IsPressureLow", yoriito::vehicle::chassis::axle::row2::wheel::left::tire::ispressurelow, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Tire.Pressure", yoriito::vehicle::chassis::axle::row2::wheel::left::tire::pressure, uint16_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Left.Tire.RubberTemperature", yoriito::vehicle::chassis::axle::row2::wheel::left::tire::rubbertemperature, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.AngularSpeed", yoriito::vehicle::chassis::axle::row2::wheel::right::angularspeed, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Brake.FluidLevel", yoriito::vehicle::chassis::axle::row2::wheel::right::brake::fluidlevel, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Brake.IsBrakesWorn", yoriito::vehicle::chassis::axle::row2::wheel::right::brake::isbrakesworn, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Brake.IsFluidLevelLow", yoriito::vehicle::chassis::axle::row2::wheel::right::brake::isfluidlevellow, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Brake.PadWear", yoriito::vehicle::chassis::axle::row2::wheel::right::brake::padwear, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Speed", yoriito::vehicle::chassis::axle::row2::wheel::right::speed, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Tire.AirTemperature", yoriito::vehicle::chassis::axle::row2::wheel::right::tire::airtemperature, float);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Tire.IsPressureLow", yoriito::vehicle::chassis::axle::row2::wheel::right::tire::ispressurelow, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Tire.Pressure", yoriito::vehicle::chassis::axle::row2::wheel::right::tire::pressure, uint16_t);
    REGISTER_SENSOR("Vehicle.Chassis.Axle.Row2.Wheel.Right.Tire.RubberTemperature", yoriito::vehicle::chassis::axle::row2::wheel::right::tire::rubbertemperature, float);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row2.WheelCount", yoriito::vehicle::chassis::axle::row2::wheelcount, uint8_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row2.WheelDiameter", yoriito::vehicle::chassis::axle::row2::wheeldiameter, float);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Axle.Row2.WheelWidth", yoriito::vehicle::chassis::axle::row2::wheelwidth, float);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.AxleCount", yoriito::vehicle::chassis::axlecount, uint8_t);
    REGISTER_SENSOR("Vehicle.Chassis.Brake.IsDriverEmergencyBrakingDetected", yoriito::vehicle::chassis::brake::isdriveremergencybrakingdetected, bool);
    REGISTER_SENSOR("Vehicle.Chassis.Brake.PedalPosition", yoriito::vehicle::chassis::brake::pedalposition, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Chassis.ParkingBrake.IsAutoApplyEnabled", yoriito::vehicle::chassis::parkingbrake::isautoapplyenabled, bool);
    REGISTER_ACTUATOR("Vehicle.Chassis.ParkingBrake.IsEngaged", yoriito::vehicle::chassis::parkingbrake::isengaged, bool);
    REGISTER_SENSOR("Vehicle.Chassis.SteeringWheel.Angle", yoriito::vehicle::chassis::steeringwheel::angle, int16_t);
    REGISTER_ACTUATOR("Vehicle.Chassis.SteeringWheel.Extension", yoriito::vehicle::chassis::steeringwheel::extension, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Chassis.SteeringWheel.Heating", yoriito::vehicle::chassis::steeringwheel::heating, uint8_t);
    REGISTER_ACTUATOR("Vehicle.Chassis.SteeringWheel.Tilt", yoriito::vehicle::chassis::steeringwheel::tilt, uint8_t);
    REGISTER_ATTRIBUTE("Vehicle.Chassis.Wheelbase", yoriito::vehicle::chassis::wheelbase, uint16_t);
    
} // namespace
}