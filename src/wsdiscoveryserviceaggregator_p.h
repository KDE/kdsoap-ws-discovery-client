/* SPDX-FileCopyrightText: 2020 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef WSDISCOVERYSERVICEAGGREGATOR_P_H
#define WSDISCOVERYSERVICEAGGREGATOR_P_H

#include <QSharedPointer>
#include <QObject>
#include "wsdiscoverytargetservice.h"

class WSDiscoveryServiceAggregatorPrivate
{
public:
    QHash<QString, QSharedPointer<WSDiscoveryTargetService>> targetServiceMap;
};

#endif // WSDISCOVERYSERVICEAGGREGATOR_P_H
