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


#include "driver/Driver.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitDriver(void) {
    REGISTER_SENSOR("Vehicle.Driver.DistractionLevel", yoriito::vehicle::driver::distractionlevel, float);
    REGISTER_SENSOR("Vehicle.Driver.FatigueLevel", yoriito::vehicle::driver::fatiguelevel, float);
    REGISTER_SENSOR("Vehicle.Driver.HeartRate", yoriito::vehicle::driver::heartrate, uint16_t);
    REGISTER_SENSOR("Vehicle.Driver.IsEyesOnRoad", yoriito::vehicle::driver::iseyesonroad, bool);
    REGISTER_SENSOR("Vehicle.Driver.IsHandsOnWheel", yoriito::vehicle::driver::ishandsonwheel, bool);
    
} // namespace
}