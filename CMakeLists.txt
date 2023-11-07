# SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.7)

project(kdsoap-ws-discovery-client VERSION 0.3.0)

include(FeatureSummary)
find_package(ECM 5.54.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(CTest)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(KDEClangFormat)
include(KDEGitCommitHooks)

include(GenerateExportHeader)

set(REQUIRED_QT_VERSION 5.9.0)
find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS Core Network Xml)

set(KDSOAP_REQUIRED_VERSION 2.0.0)

if (QT_MAJOR_VERSION EQUAL "6")
    set(KDSOAP_PACKAGE KDSoap-qt6)
else()
    set(KDSOAP_PACKAGE KDSoap)
endif()
find_package(${KDSOAP_PACKAGE} ${KDSOAP_REQUIRED_VERSION} REQUIRED)
set_package_properties(${KDSOAP_PACKAGE} PROPERTIES
    DESCRIPTION "A Qt-based client-side and server-side SOAP component"
    URL "http://www.kdab.com/products/kd-soap"
    TYPE REQUIRED
    PURPOSE "Support for SOAP client protocol"
)

if (BUILD_TESTING)
    find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test)
endif()

include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMQtDeclareLoggingCategory)
include(ECMAddQch)

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

ecm_setup_version(PROJECT
    VARIABLE_PREFIX WSDISCOVERY
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kdsoap_wsdiscovery_client_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDSoapWSDiscoveryClientConfigVersion.cmake"
)

add_definitions(
    -DQT_NO_SIGNALS_SLOTS_KEYWORDS
)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(docs)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KDSoapWSDiscoveryClient")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KDSoapWSDiscoveryClient_QCH
        FILE KDSoapWSDiscoveryClientQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KDSoapWSDiscoveryClientQchTargets.cmake\")")
endif()

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KDSoapWSDiscoveryClientConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KDSoapWSDiscoveryClientConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kdsoap_wsdiscovery_client_version.h
        DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KDSoapWSDiscoveryClient
        COMPONENT Devel)

install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/KDSoapWSDiscoveryClientConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/KDSoapWSDiscoveryClientConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KDSoapWSDiscoveryClientTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KDSoapWSDiscoveryClientTargets.cmake
        NAMESPACE KDSoap::)

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

feature_summary(
    WHAT ALL
    FATAL_ON_MISSING_REQUIRED_PACKAGES
)
