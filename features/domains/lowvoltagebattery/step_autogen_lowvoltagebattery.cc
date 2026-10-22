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


#include "lowvoltagebattery/LowVoltageBattery.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitLowVoltageBattery(void) {
    REGISTER_SENSOR("Vehicle.LowVoltageBattery.CurrentElectricity", yoriito::vehicle::lowvoltagebattery::currentelectricity, yoriito::types::Electricity);
    REGISTER_ATTRIBUTE("Vehicle.LowVoltageBattery.NominalCapacity", yoriito::vehicle::lowvoltagebattery::nominalcapacity, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.LowVoltageBattery.NominalVoltage", yoriito::vehicle::lowvoltagebattery::nominalvoltage, uint16_t);
    
} // namespace
}