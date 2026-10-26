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


#include "motionmanagement/MotionManagement.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitMotionManagement(void) {
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.TorqueDistributionFrictionRightMaximum", yoriito::vehicle::motionmanagement::brake::axle::row1::torquedistributionfrictionrightmaximum, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.TorqueDistributionFrictionRightMinimum", yoriito::vehicle::motionmanagement::brake::axle::row1::torquedistributionfrictionrightminimum, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.TorqueElectricMinimum", yoriito::vehicle::motionmanagement::brake::axle::row1::torqueelectricminimum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.TorqueFrictionDifferenceMaximum", yoriito::vehicle::motionmanagement::brake::axle::row1::torquefrictiondifferencemaximum, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Left.OmegaLower", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::left::omegalower, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Left.OmegaUpper", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::left::omegaupper, uint16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Left.Torque", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::left::torque, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Left.TorqueArbitrated", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::left::torquearbitrated, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Left.TorqueFrictionMaximum", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::left::torquefrictionmaximum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Left.TorqueFrictionMinimum", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::left::torquefrictionminimum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Right.OmegaLower", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::right::omegalower, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Right.OmegaUpper", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::right::omegaupper, uint16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Right.Torque", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::right::torque, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Right.TorqueArbitrated", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::right::torquearbitrated, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Right.TorqueFrictionMaximum", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::right::torquefrictionmaximum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row1.Wheel.Right.TorqueFrictionMinimum", yoriito::vehicle::motionmanagement::brake::axle::row1::wheel::right::torquefrictionminimum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.TorqueDistributionFrictionRightMaximum", yoriito::vehicle::motionmanagement::brake::axle::row2::torquedistributionfrictionrightmaximum, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.TorqueDistributionFrictionRightMinimum", yoriito::vehicle::motionmanagement::brake::axle::row2::torquedistributionfrictionrightminimum, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.TorqueElectricMinimum", yoriito::vehicle::motionmanagement::brake::axle::row2::torqueelectricminimum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.TorqueFrictionDifferenceMaximum", yoriito::vehicle::motionmanagement::brake::axle::row2::torquefrictiondifferencemaximum, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Left.OmegaLower", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::left::omegalower, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Left.OmegaUpper", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::left::omegaupper, uint16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Left.Torque", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::left::torque, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Left.TorqueArbitrated", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::left::torquearbitrated, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Left.TorqueFrictionMaximum", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::left::torquefrictionmaximum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Left.TorqueFrictionMinimum", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::left::torquefrictionminimum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Right.OmegaLower", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::right::omegalower, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Right.OmegaUpper", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::right::omegaupper, uint16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Right.Torque", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::right::torque, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Right.TorqueArbitrated", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::right::torquearbitrated, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Right.TorqueFrictionMaximum", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::right::torquefrictionmaximum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.Axle.Row2.Wheel.Right.TorqueFrictionMinimum", yoriito::vehicle::motionmanagement::brake::axle::row2::wheel::right::torquefrictionminimum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.VehicleForceDistributionFrontMaximum", yoriito::vehicle::motionmanagement::brake::vehicleforcedistributionfrontmaximum, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.VehicleForceDistributionFrontMinimum", yoriito::vehicle::motionmanagement::brake::vehicleforcedistributionfrontminimum, uint16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.VehicleForceElectric", yoriito::vehicle::motionmanagement::brake::vehicleforceelectric, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Brake.VehicleForceElectricMinimumArbitrated", yoriito::vehicle::motionmanagement::brake::vehicleforceelectricminimumarbitrated, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Brake.VehicleForceMaximum", yoriito::vehicle::motionmanagement::brake::vehicleforcemaximum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row1.RotationalSpeed", yoriito::vehicle::motionmanagement::electricaxle::row1::rotationalspeed, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row1.RotationalSpeedMaximumLimit", yoriito::vehicle::motionmanagement::electricaxle::row1::rotationalspeedmaximumlimit, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row1.RotationalSpeedMinimumLimit", yoriito::vehicle::motionmanagement::electricaxle::row1::rotationalspeedminimumlimit, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row1.Torque", yoriito::vehicle::motionmanagement::electricaxle::row1::torque, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.ElectricAxle.Row1.TorqueMaximum", yoriito::vehicle::motionmanagement::electricaxle::row1::torquemaximum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row1.TorqueMaximumLimit", yoriito::vehicle::motionmanagement::electricaxle::row1::torquemaximumlimit, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.ElectricAxle.Row1.TorqueMinimum", yoriito::vehicle::motionmanagement::electricaxle::row1::torqueminimum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row1.TorqueMinimumLimit", yoriito::vehicle::motionmanagement::electricaxle::row1::torqueminimumlimit, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row2.RotationalSpeed", yoriito::vehicle::motionmanagement::electricaxle::row2::rotationalspeed, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row2.RotationalSpeedMaximumLimit", yoriito::vehicle::motionmanagement::electricaxle::row2::rotationalspeedmaximumlimit, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row2.RotationalSpeedMinimumLimit", yoriito::vehicle::motionmanagement::electricaxle::row2::rotationalspeedminimumlimit, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row2.Torque", yoriito::vehicle::motionmanagement::electricaxle::row2::torque, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.ElectricAxle.Row2.TorqueMaximum", yoriito::vehicle::motionmanagement::electricaxle::row2::torquemaximum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row2.TorqueMaximumLimit", yoriito::vehicle::motionmanagement::electricaxle::row2::torquemaximumlimit, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.ElectricAxle.Row2.TorqueMinimum", yoriito::vehicle::motionmanagement::electricaxle::row2::torqueminimum, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.ElectricAxle.Row2.TorqueMinimumLimit", yoriito::vehicle::motionmanagement::electricaxle::row2::torqueminimumlimit, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.Axle.Row1.PositionOffsetTargetMode", yoriito::vehicle::motionmanagement::steering::axle::row1::positionoffsettargetmode, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.Axle.Row1.PositionTargetMode", yoriito::vehicle::motionmanagement::steering::axle::row1::positiontargetmode, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.Axle.Row1.RackPosition", yoriito::vehicle::motionmanagement::steering::axle::row1::rackposition, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.Axle.Row1.RackPositionOffsetTarget", yoriito::vehicle::motionmanagement::steering::axle::row1::rackpositionoffsettarget, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.Axle.Row1.SteerAngle", yoriito::vehicle::motionmanagement::steering::axle::row1::steerangle, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.Axle.Row1.SteerAngleOffsetTarget", yoriito::vehicle::motionmanagement::steering::axle::row1::steerangleoffsettarget, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.Axle.Row2.SteerAngle", yoriito::vehicle::motionmanagement::steering::axle::row2::steerangle, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.Axle.Row2.SteerAngleVelocityTarget", yoriito::vehicle::motionmanagement::steering::axle::row2::steeranglevelocitytarget, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.SteeringWheel.Angle", yoriito::vehicle::motionmanagement::steering::steeringwheel::angle, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.SteeringWheel.AngleTargetMode", yoriito::vehicle::motionmanagement::steering::steeringwheel::angletargetmode, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.SteeringWheel.Torque", yoriito::vehicle::motionmanagement::steering::steeringwheel::torque, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.SteeringWheel.TorqueOffsetTarget", yoriito::vehicle::motionmanagement::steering::steeringwheel::torqueoffsettarget, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.SteeringWheel.TorqueOffsetTargetMode", yoriito::vehicle::motionmanagement::steering::steeringwheel::torqueoffsettargetmode, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Steering.SteeringWheel.TorqueTargetMode", yoriito::vehicle::motionmanagement::steering::steeringwheel::torquetargetmode, uint8_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row1.RollTorque", yoriito::vehicle::motionmanagement::suspension::axle::row1::rolltorque, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row1.Wheel.Left.DampingForce", yoriito::vehicle::motionmanagement::suspension::axle::row1::wheel::left::dampingforce, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.Axle.Row1.Wheel.Left.DampingForceTarget", yoriito::vehicle::motionmanagement::suspension::axle::row1::wheel::left::dampingforcetarget, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row1.Wheel.Left.DampingRate", yoriito::vehicle::motionmanagement::suspension::axle::row1::wheel::left::dampingrate, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.Axle.Row1.Wheel.Left.DampingRateTarget", yoriito::vehicle::motionmanagement::suspension::axle::row1::wheel::left::dampingratetarget, uint8_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row1.Wheel.Right.DampingForce", yoriito::vehicle::motionmanagement::suspension::axle::row1::wheel::right::dampingforce, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.Axle.Row1.Wheel.Right.DampingForceTarget", yoriito::vehicle::motionmanagement::suspension::axle::row1::wheel::right::dampingforcetarget, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row1.Wheel.Right.DampingRate", yoriito::vehicle::motionmanagement::suspension::axle::row1::wheel::right::dampingrate, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.Axle.Row1.Wheel.Right.DampingRateTarget", yoriito::vehicle::motionmanagement::suspension::axle::row1::wheel::right::dampingratetarget, uint8_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row2.RollTorque", yoriito::vehicle::motionmanagement::suspension::axle::row2::rolltorque, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row2.Wheel.Left.DampingForce", yoriito::vehicle::motionmanagement::suspension::axle::row2::wheel::left::dampingforce, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.Axle.Row2.Wheel.Left.DampingForceTarget", yoriito::vehicle::motionmanagement::suspension::axle::row2::wheel::left::dampingforcetarget, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row2.Wheel.Left.DampingRate", yoriito::vehicle::motionmanagement::suspension::axle::row2::wheel::left::dampingrate, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.Axle.Row2.Wheel.Left.DampingRateTarget", yoriito::vehicle::motionmanagement::suspension::axle::row2::wheel::left::dampingratetarget, uint8_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row2.Wheel.Right.DampingForce", yoriito::vehicle::motionmanagement::suspension::axle::row2::wheel::right::dampingforce, int16_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.Axle.Row2.Wheel.Right.DampingForceTarget", yoriito::vehicle::motionmanagement::suspension::axle::row2::wheel::right::dampingforcetarget, int16_t);
    REGISTER_SENSOR("Vehicle.MotionManagement.Suspension.Axle.Row2.Wheel.Right.DampingRate", yoriito::vehicle::motionmanagement::suspension::axle::row2::wheel::right::dampingrate, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.Axle.Row2.Wheel.Right.DampingRateTarget", yoriito::vehicle::motionmanagement::suspension::axle::row2::wheel::right::dampingratetarget, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.DampingPrioTarget", yoriito::vehicle::motionmanagement::suspension::dampingpriotarget, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.RollPrioTarget", yoriito::vehicle::motionmanagement::suspension::rollpriotarget, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.RollTorqueDistributionFrontMaximum", yoriito::vehicle::motionmanagement::suspension::rolltorquedistributionfrontmaximum, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.RollTorqueDistributionFrontMinimum", yoriito::vehicle::motionmanagement::suspension::rolltorquedistributionfrontminimum, uint8_t);
    REGISTER_ACTUATOR("Vehicle.MotionManagement.Suspension.RollTorqueTarget", yoriito::vehicle::motionmanagement::suspension::rolltorquetarget, int16_t);
    
} // namespace
}