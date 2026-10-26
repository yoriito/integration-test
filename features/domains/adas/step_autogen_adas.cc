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


#include "adas/ADAS.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitADAS(void) {
    REGISTER_ACTUATOR("Vehicle.ADAS.ABS.IsEnabled", yoriito::vehicle::adas::abs::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ABS.IsEngaged", yoriito::vehicle::adas::abs::isengaged, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ActiveAutonomyLevel", yoriito::vehicle::adas::activeautonomylevel, std::string);
    REGISTER_ACTUATOR("Vehicle.ADAS.CruiseControl.AdaptiveDistanceSet", yoriito::vehicle::adas::cruisecontrol::adaptivedistanceset, float);
    REGISTER_ACTUATOR("Vehicle.ADAS.CruiseControl.AdaptiveIntervalSet", yoriito::vehicle::adas::cruisecontrol::adaptiveintervalset, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.CruiseControl.DegradationStatus", yoriito::vehicle::adas::cruisecontrol::degradationstatus, std::string);
    REGISTER_ACTUATOR("Vehicle.ADAS.CruiseControl.IsActive", yoriito::vehicle::adas::cruisecontrol::isactive, bool);
    REGISTER_ACTUATOR("Vehicle.ADAS.CruiseControl.IsAdaptive", yoriito::vehicle::adas::cruisecontrol::isadaptive, bool);
    REGISTER_ACTUATOR("Vehicle.ADAS.CruiseControl.IsEnabled", yoriito::vehicle::adas::cruisecontrol::isenabled, bool);
    REGISTER_ACTUATOR("Vehicle.ADAS.CruiseControl.SpeedSet", yoriito::vehicle::adas::cruisecontrol::speedset, float);
    REGISTER_SENSOR("Vehicle.ADAS.DMS.DegradationStatus", yoriito::vehicle::adas::dms::degradationstatus, std::string);
    REGISTER_ACTUATOR("Vehicle.ADAS.DMS.IsEnabled", yoriito::vehicle::adas::dms::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.DMS.IsWarning", yoriito::vehicle::adas::dms::iswarning, bool);
    REGISTER_ACTUATOR("Vehicle.ADAS.EBA.IsEnabled", yoriito::vehicle::adas::eba::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.EBA.IsEngaged", yoriito::vehicle::adas::eba::isengaged, bool);
    REGISTER_ACTUATOR("Vehicle.ADAS.EBD.IsEnabled", yoriito::vehicle::adas::ebd::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.EBD.IsEngaged", yoriito::vehicle::adas::ebd::isengaged, bool);
    REGISTER_ACTUATOR("Vehicle.ADAS.ESC.IsEnabled", yoriito::vehicle::adas::esc::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ESC.IsEngaged", yoriito::vehicle::adas::esc::isengaged, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ESC.IsStrongCrossWindDetected", yoriito::vehicle::adas::esc::isstrongcrosswinddetected, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ESC.RoadFriction", yoriito::vehicle::adas::esc::roadfriction, yoriito::types::RoadFrictionRange);
    REGISTER_ACTUATOR("Vehicle.ADAS.IsAutoPowerOptimize", yoriito::vehicle::adas::isautopoweroptimize, bool);
    REGISTER_SENSOR("Vehicle.ADAS.LaneDepartureDetection.DegradationStatus", yoriito::vehicle::adas::lanedeparturedetection::degradationstatus, std::string);
    REGISTER_ACTUATOR("Vehicle.ADAS.LaneDepartureDetection.IsEnabled", yoriito::vehicle::adas::lanedeparturedetection::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.LaneDepartureDetection.IsWarning", yoriito::vehicle::adas::lanedeparturedetection::iswarning, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Center.DegradationStatus", yoriito::vehicle::adas::obstacledetection::front::center::degradationstatus, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Center.Distance", yoriito::vehicle::adas::obstacledetection::front::center::distance, float);
    REGISTER_ACTUATOR("Vehicle.ADAS.ObstacleDetection.Front.Center.IsEnabled", yoriito::vehicle::adas::obstacledetection::front::center::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Center.IsWarning", yoriito::vehicle::adas::obstacledetection::front::center::iswarning, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Center.TimeGap", yoriito::vehicle::adas::obstacledetection::front::center::timegap, int32_t);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Center.WarningType", yoriito::vehicle::adas::obstacledetection::front::center::warningtype, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Left.DegradationStatus", yoriito::vehicle::adas::obstacledetection::front::left::degradationstatus, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Left.Distance", yoriito::vehicle::adas::obstacledetection::front::left::distance, float);
    REGISTER_ACTUATOR("Vehicle.ADAS.ObstacleDetection.Front.Left.IsEnabled", yoriito::vehicle::adas::obstacledetection::front::left::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Left.IsWarning", yoriito::vehicle::adas::obstacledetection::front::left::iswarning, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Left.TimeGap", yoriito::vehicle::adas::obstacledetection::front::left::timegap, int32_t);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Left.WarningType", yoriito::vehicle::adas::obstacledetection::front::left::warningtype, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Right.DegradationStatus", yoriito::vehicle::adas::obstacledetection::front::right::degradationstatus, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Right.Distance", yoriito::vehicle::adas::obstacledetection::front::right::distance, float);
    REGISTER_ACTUATOR("Vehicle.ADAS.ObstacleDetection.Front.Right.IsEnabled", yoriito::vehicle::adas::obstacledetection::front::right::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Right.IsWarning", yoriito::vehicle::adas::obstacledetection::front::right::iswarning, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Right.TimeGap", yoriito::vehicle::adas::obstacledetection::front::right::timegap, int32_t);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Front.Right.WarningType", yoriito::vehicle::adas::obstacledetection::front::right::warningtype, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Center.DegradationStatus", yoriito::vehicle::adas::obstacledetection::rear::center::degradationstatus, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Center.Distance", yoriito::vehicle::adas::obstacledetection::rear::center::distance, float);
    REGISTER_ACTUATOR("Vehicle.ADAS.ObstacleDetection.Rear.Center.IsEnabled", yoriito::vehicle::adas::obstacledetection::rear::center::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Center.IsWarning", yoriito::vehicle::adas::obstacledetection::rear::center::iswarning, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Center.TimeGap", yoriito::vehicle::adas::obstacledetection::rear::center::timegap, int32_t);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Center.WarningType", yoriito::vehicle::adas::obstacledetection::rear::center::warningtype, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Left.DegradationStatus", yoriito::vehicle::adas::obstacledetection::rear::left::degradationstatus, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Left.Distance", yoriito::vehicle::adas::obstacledetection::rear::left::distance, float);
    REGISTER_ACTUATOR("Vehicle.ADAS.ObstacleDetection.Rear.Left.IsEnabled", yoriito::vehicle::adas::obstacledetection::rear::left::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Left.IsWarning", yoriito::vehicle::adas::obstacledetection::rear::left::iswarning, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Left.TimeGap", yoriito::vehicle::adas::obstacledetection::rear::left::timegap, int32_t);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Left.WarningType", yoriito::vehicle::adas::obstacledetection::rear::left::warningtype, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Right.DegradationStatus", yoriito::vehicle::adas::obstacledetection::rear::right::degradationstatus, std::string);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Right.Distance", yoriito::vehicle::adas::obstacledetection::rear::right::distance, float);
    REGISTER_ACTUATOR("Vehicle.ADAS.ObstacleDetection.Rear.Right.IsEnabled", yoriito::vehicle::adas::obstacledetection::rear::right::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Right.IsWarning", yoriito::vehicle::adas::obstacledetection::rear::right::iswarning, bool);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Right.TimeGap", yoriito::vehicle::adas::obstacledetection::rear::right::timegap, int32_t);
    REGISTER_SENSOR("Vehicle.ADAS.ObstacleDetection.Rear.Right.WarningType", yoriito::vehicle::adas::obstacledetection::rear::right::warningtype, std::string);
    REGISTER_ACTUATOR("Vehicle.ADAS.PowerOptimizeLevel", yoriito::vehicle::adas::poweroptimizelevel, uint8_t);
    REGISTER_ATTRIBUTE("Vehicle.ADAS.SupportedAutonomyLevel", yoriito::vehicle::adas::supportedautonomylevel, std::string);
    REGISTER_ACTUATOR("Vehicle.ADAS.TCS.IsEnabled", yoriito::vehicle::adas::tcs::isenabled, bool);
    REGISTER_SENSOR("Vehicle.ADAS.TCS.IsEngaged", yoriito::vehicle::adas::tcs::isengaged, bool);
    
} // namespace
}