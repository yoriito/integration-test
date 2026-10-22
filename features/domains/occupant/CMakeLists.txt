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


project(test_integration_occupant)

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${INTEGRATION_TEST_SOURCES} step_autogen_occupant.cc)

target_include_directories(
    ${EXECUTABLE_NAME} AFTER
    PRIVATE
    ${INTERFACE_INCLUDE_DIR}
    ${INTERFACE_INCLUDE_DIR}/signal
    ${INTERFACE_INCLUDE_DIR}/signal/types
    ${INTERFACE_INCLUDE_DIR}/databroker
)
target_link_options(
    ${EXECUTABLE_NAME} PRIVATE "-Wl,--no-as-needed"
)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    BUILD_RPATH   "${SYSROOT}/usr/lib/${YORIITO}"
)
target_link_libraries(${EXECUTABLE_NAME} yoriito_vehicle_api_occupant ${INTEGRATION_TEST_DEPENDENCY_LIBRARIES})