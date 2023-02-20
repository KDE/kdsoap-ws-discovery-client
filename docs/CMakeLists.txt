# SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
# SPDX-License-Identifier: GPL-3.0-or-later
#

cmake_minimum_required(VERSION 3.7)

find_package(Doxygen
             OPTIONAL_COMPONENTS dot mscgen dia)
             
if(DOXYGEN_FOUND)             
    doxygen_add_docs(docs
        "README.md"
        "src/wsdiscoveryclient.h"
        "src/wsdiscoveryprobejob.h"
        "src/wsdiscoverytargetservice.h"
        "src/wsdiscoveryserviceaggregator.h"
        ALL
        USE_STAMP_FILE
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
        )
    install(DIRECTORY
            ${CMAKE_CURRENT_BINARY_DIR}/html/
        DESTINATION ${KDE_INSTALL_DATADIR}/doc/KDSoapWSDiscoveryClient
        COMPONENT Devel)
endif()
