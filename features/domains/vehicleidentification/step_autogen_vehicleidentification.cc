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


#include "vehicleidentification/VehicleIdentification.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitVehicleIdentification(void) {
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.AcrissCode", yoriito::vehicle::vehicleidentification::acrisscode, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.BodyType", yoriito::vehicle::vehicleidentification::bodytype, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.Brand", yoriito::vehicle::vehicleidentification::brand, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.DateVehicleFirstRegistered", yoriito::vehicle::vehicleidentification::datevehiclefirstregistered, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.KnownVehicleDamages", yoriito::vehicle::vehicleidentification::knownvehicledamages, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.LicensePlate", yoriito::vehicle::vehicleidentification::licenseplate, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.MeetsEmissionStandard", yoriito::vehicle::vehicleidentification::meetsemissionstandard, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.Model", yoriito::vehicle::vehicleidentification::model, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.OptionalExtras", yoriito::vehicle::vehicleidentification::optionalextras, std::vector<std::string>);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.ProductionDate", yoriito::vehicle::vehicleidentification::productiondate, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.PurchaseDate", yoriito::vehicle::vehicleidentification::purchasedate, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.VIN", yoriito::vehicle::vehicleidentification::vin, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.VehicleConfiguration", yoriito::vehicle::vehicleidentification::vehicleconfiguration, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.VehicleExteriorColor", yoriito::vehicle::vehicleidentification::vehicleexteriorcolor, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.VehicleInteriorColor", yoriito::vehicle::vehicleidentification::vehicleinteriorcolor, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.VehicleInteriorType", yoriito::vehicle::vehicleidentification::vehicleinteriortype, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.VehicleModelDate", yoriito::vehicle::vehicleidentification::vehiclemodeldate, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.VehicleSeatingCapacity", yoriito::vehicle::vehicleidentification::vehicleseatingcapacity, uint16_t);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.VehicleSpecialUsage", yoriito::vehicle::vehicleidentification::vehiclespecialusage, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.WMI", yoriito::vehicle::vehicleidentification::wmi, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VehicleIdentification.Year", yoriito::vehicle::vehicleidentification::year, uint16_t);
    
} // namespace
}