# SPDX-FileCopyrightText: 2019-2020 Casper Meijn <casper@meijn.net>
# SPDX-License-Identifier: GPL-3.0-or-later
#

cmake_minimum_required(VERSION 3.7)

include(ECMAddTests)

ecm_add_tests(
    test_wsdiscoveryclient.cpp
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Network Qt${QT_MAJOR_VERSION}::Test KDSoap::WSDiscoveryClient
)
