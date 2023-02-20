# SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
# SPDX-License-Identifier: GPL-3.0-or-later
#

cmake_minimum_required(VERSION 3.7)

project(onvif-discover)

add_executable(${PROJECT_NAME}
    "main.cpp"
    "onvifdiscover.cpp"
)
target_link_libraries(${PROJECT_NAME} KDSoapWSDiscoveryClient)
