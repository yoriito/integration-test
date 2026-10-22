# SPDX-License-Identifier: Apache-2.0
#
# Copyright 2026 JASPAR
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# Integration Tests Options
option(ENABLE_VEHICLE "Enable building integration tests of Vehicle domain" OFF)
option(ENABLE_POWERTRAIN "Enable building integration tests of Powertrain domain" OFF)
option(ENABLE_BODY "Enable building integration tests of Body domain" OFF)
option(ENABLE_CABIN "Enable building integration tests of Cabin domain" OFF)
option(ENABLE_ADAS "Enable building integration tests of ADAS domain" OFF)
option(ENABLE_CHASSIS "Enable building integration tests of Chassis domain" OFF)
option(ENABLE_DRIVER "Enable building integration tests of Driver domain" OFF)
option(ENABLE_OCCUPANT "Enable building integration tests of Occupant domain" OFF)
option(ENABLE_EXTERIOR "Enable building integration tests of Exterior domain" OFF)
option(ENABLE_VERSIONVSS "Enable building integration tests of VersionVSS domain" OFF)
option(ENABLE_VEHICLEIDENTIFICATION "Enable building integration tests of VehicleIdentification domain" OFF)
option(ENABLE_LOWVOLTAGEBATTERY "Enable building integration tests of LowVoltageBattery domain" OFF)
option(ENABLE_TRAILER "Enable building integration tests of Trailer domain" OFF)
option(ENABLE_CURRENTLOCATION "Enable building integration tests of CurrentLocation domain" OFF)
option(ENABLE_MOTIONMANAGEMENT "Enable building integration tests of MotionManagement domain" OFF)
option(ENABLE_TRIPMETER "Enable building integration tests of TripMeter domain" OFF)
option(ENABLE_VERSIONYORIITOVSS "Enable building integration tests of VersionYoriitoVSS domain" OFF)


# Check if domains are specified to build
set(_ANY_DOMAIN_SPECIFIED OFF)
foreach(_domain
    ENABLE_VEHICLE
    ENABLE_POWERTRAIN
    ENABLE_BODY
    ENABLE_CABIN
    ENABLE_ADAS
    ENABLE_CHASSIS
    ENABLE_DRIVER
    ENABLE_OCCUPANT
    ENABLE_EXTERIOR
    ENABLE_VERSIONVSS
    ENABLE_VEHICLEIDENTIFICATION
    ENABLE_LOWVOLTAGEBATTERY
    ENABLE_TRAILER
    ENABLE_CURRENTLOCATION
    ENABLE_MOTIONMANAGEMENT
    ENABLE_TRIPMETER
    ENABLE_VERSIONYORIITOVSS
    )
    if(${_domain})
        set(_ANY_DOMAIN_SPECIFIED ON)
        break()
    endif()
endforeach()

# If no domain specified, treat is as all
if(NOT _ANY_DOMAIN_SPECIFIED)
    message(STATUS "No domain specified. Enabling all domains.")
    set(ENABLE_VEHICLE ON)
    set(ENABLE_POWERTRAIN ON)
    set(ENABLE_BODY ON)
    set(ENABLE_CABIN ON)
    set(ENABLE_ADAS ON)
    set(ENABLE_CHASSIS ON)
    set(ENABLE_DRIVER ON)
    set(ENABLE_OCCUPANT ON)
    set(ENABLE_EXTERIOR ON)
    set(ENABLE_VERSIONVSS ON)
    set(ENABLE_VEHICLEIDENTIFICATION ON)
    set(ENABLE_LOWVOLTAGEBATTERY ON)
    set(ENABLE_TRAILER ON)
    set(ENABLE_CURRENTLOCATION ON)
    set(ENABLE_MOTIONMANAGEMENT ON)
    set(ENABLE_TRIPMETER ON)
    set(ENABLE_VERSIONYORIITOVSS ON)
    endif()

# Enable/Disable Integration Tests per domain
if(ENABLE_VEHICLE)
    add_subdirectory(vehicle)
endif()
if(ENABLE_POWERTRAIN)
    add_subdirectory(powertrain)
endif()
if(ENABLE_BODY)
    add_subdirectory(body)
endif()
if(ENABLE_CABIN)
    add_subdirectory(cabin)
endif()
if(ENABLE_ADAS)
    add_subdirectory(adas)
endif()
if(ENABLE_CHASSIS)
    add_subdirectory(chassis)
endif()
if(ENABLE_DRIVER)
    add_subdirectory(driver)
endif()
if(ENABLE_OCCUPANT)
    add_subdirectory(occupant)
endif()
if(ENABLE_EXTERIOR)
    add_subdirectory(exterior)
endif()
if(ENABLE_VERSIONVSS)
    add_subdirectory(versionvss)
endif()
if(ENABLE_VEHICLEIDENTIFICATION)
    add_subdirectory(vehicleidentification)
endif()
if(ENABLE_LOWVOLTAGEBATTERY)
    add_subdirectory(lowvoltagebattery)
endif()
if(ENABLE_TRAILER)
    add_subdirectory(trailer)
endif()
if(ENABLE_CURRENTLOCATION)
    add_subdirectory(currentlocation)
endif()
if(ENABLE_MOTIONMANAGEMENT)
    add_subdirectory(motionmanagement)
endif()
if(ENABLE_TRIPMETER)
    add_subdirectory(tripmeter)
endif()
if(ENABLE_VERSIONYORIITOVSS)
    add_subdirectory(versionyoriitovss)
endif()
