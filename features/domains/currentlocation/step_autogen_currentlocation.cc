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


#include "currentlocation/CurrentLocation.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitCurrentLocation(void) {
    REGISTER_SENSOR("Vehicle.CurrentLocation.GNSSReceiver.GNSSLocationType", yoriito::vehicle::currentlocation::gnssreceiver::gnsslocationtype, yoriito::types::GNSSLocation);
    REGISTER_ATTRIBUTE("Vehicle.CurrentLocation.GNSSReceiver.MountingPosition.X", yoriito::vehicle::currentlocation::gnssreceiver::mountingposition::x, int16_t);
    REGISTER_ATTRIBUTE("Vehicle.CurrentLocation.GNSSReceiver.MountingPosition.Y", yoriito::vehicle::currentlocation::gnssreceiver::mountingposition::y, int16_t);
    REGISTER_ATTRIBUTE("Vehicle.CurrentLocation.GNSSReceiver.MountingPosition.Z", yoriito::vehicle::currentlocation::gnssreceiver::mountingposition::z, int16_t);
    REGISTER_ATTRIBUTE("Vehicle.CurrentLocation.ReferencePosition.X", yoriito::vehicle::currentlocation::referenceposition::x, int16_t);
    REGISTER_ATTRIBUTE("Vehicle.CurrentLocation.ReferencePosition.Y", yoriito::vehicle::currentlocation::referenceposition::y, int16_t);
    REGISTER_ATTRIBUTE("Vehicle.CurrentLocation.ReferencePosition.Z", yoriito::vehicle::currentlocation::referenceposition::z, int16_t);
    REGISTER_SENSOR("Vehicle.CurrentLocation.VehicleLocation", yoriito::vehicle::currentlocation::vehiclelocation, yoriito::types::VehicleLocation);
    
} // namespace
}