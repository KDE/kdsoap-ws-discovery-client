/* SPDX-FileCopyrightText: 2020 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "wsdiscoveryserviceaggregator.h"
#include "wsdiscoveryserviceaggregator_p.h"

WSDiscoveryServiceAggregator::WSDiscoveryServiceAggregator(QObject *parent)
    : QObject(parent)
    , d_ptr(new WSDiscoveryServiceAggregatorPrivate())
{
}

WSDiscoveryServiceAggregator::~WSDiscoveryServiceAggregator()
{
    delete d_ptr;
}

void WSDiscoveryServiceAggregator::updateService(const WSDiscoveryTargetService &receivedService)
{
    Q_D(WSDiscoveryServiceAggregator);
    auto endpointReference = receivedService.endpointReference();
    auto aggregatedService = d->targetServiceMap.value(endpointReference);
    if (aggregatedService.isNull()) {
        aggregatedService = QSharedPointer<WSDiscoveryTargetService>::create(endpointReference);
        d->targetServiceMap.insert(endpointReference, aggregatedService);
    }
    aggregatedService->setTypeList(receivedService.typeList());
    aggregatedService->setScopeList(receivedService.scopeList());
    aggregatedService->setXAddrList(receivedService.xAddrList());
    aggregatedService->setLastSeen(receivedService.lastSeen());
    ;
    emit serviceUpdated(aggregatedService);
}
