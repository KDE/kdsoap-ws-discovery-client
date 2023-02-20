/* SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#include "onvifdiscover.h"

#include <QDebug>
#include <QSharedPointer>
#include <WSDiscoveryClient>
#include <WSDiscoveryProbeJob>
#include <WSDiscoveryTargetService>
#include <WSDiscoveryServiceAggregator>

OnvifDiscover::OnvifDiscover(QObject *parent) : QObject(parent)
{
    m_client = new WSDiscoveryClient(this);

    m_probeJob = new WSDiscoveryProbeJob(m_client);
    
    m_aggregator = new WSDiscoveryServiceAggregator(this);
    
    connect(m_probeJob, &WSDiscoveryProbeJob::matchReceived, m_aggregator, &WSDiscoveryServiceAggregator::updateService);
    connect(m_aggregator, &WSDiscoveryServiceAggregator::serviceUpdated, this, &OnvifDiscover::matchReceived);
    
    KDQName type("tdn:NetworkVideoTransmitter");
    type.setNameSpace("http://www.onvif.org/ver10/network/wsdl");
    m_probeJob->addType(type);
}

OnvifDiscover::~OnvifDiscover() = default;

void OnvifDiscover::start()
{
    m_client->start();
    m_probeJob->start();
}

void OnvifDiscover::matchReceived(const QSharedPointer<WSDiscoveryTargetService> &matchedService)
{
    qDebug() << "ProbeMatch received:";
    qDebug() << "  Endpoint reference:" << matchedService->endpointReference();
    const auto& typeList = matchedService->typeList();
    for(const auto& type : typeList) {
        qDebug() << "  Type:"  << type.localName() << "in namespace" << type.nameSpace();
    }
    const auto& scopeList = matchedService->scopeList();
    for(const auto& scope : scopeList) {
        qDebug() << "  Scope:"  << scope.toString();
    }
    const auto& xAddrList = matchedService->xAddrList();
    for(const auto& xAddr : xAddrList) {
        qDebug() << "  XAddr:" << xAddr.toString();
    }
}
