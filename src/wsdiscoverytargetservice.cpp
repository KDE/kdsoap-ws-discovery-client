/* SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#include "wsdiscoverytargetservice.h"

class WSDiscoveryTargetServiceData : public QSharedData
{
  public:
    QString endpointReference;
    QList<KDQName> typeList;
    QList<QUrl> scopeList;
    QList<QUrl> xAddrList;
    QDateTime lastSeen;
};

WSDiscoveryTargetService::WSDiscoveryTargetService()
{
    d = new WSDiscoveryTargetServiceData();
}

WSDiscoveryTargetService::WSDiscoveryTargetService(const QString &endpointReference)
{
    d = new WSDiscoveryTargetServiceData();
    d->endpointReference = endpointReference;
}

WSDiscoveryTargetService::WSDiscoveryTargetService(const WSDiscoveryTargetService &other) = default;
WSDiscoveryTargetService::~WSDiscoveryTargetService() = default;

QDateTime WSDiscoveryTargetService::lastSeen() const
{
    return d->lastSeen;
}

void WSDiscoveryTargetService::setLastSeen(const QDateTime &lastSeen)
{
    d->lastSeen = lastSeen;
}

void WSDiscoveryTargetService::updateLastSeen()
{
    setLastSeen(QDateTime::currentDateTime());
}

bool WSDiscoveryTargetService::isMatchingType(const KDQName &matchingType) const
{
    for(const KDQName &type : d->typeList) {
        if(matchingType.nameSpace() == type.nameSpace() &&
                matchingType.localName() == type.localName()) {
            return true;
        }
    }
    return false;
}

bool WSDiscoveryTargetService::isMatchingScope(const QUrl &matchingScope) const
{
    for(const QUrl &scope : d->scopeList) {
        if(matchingScope == scope) {
            return true;
        }
    }
    return false;
}

QList<QUrl> WSDiscoveryTargetService::xAddrList() const
{
    return d->xAddrList;
}

void WSDiscoveryTargetService::setXAddrList(const QList<QUrl> &xAddrList)
{
    d->xAddrList = xAddrList;
}

QList<QUrl> WSDiscoveryTargetService::scopeList() const
{
    return d->scopeList;
}

void WSDiscoveryTargetService::setScopeList(const QList<QUrl> &scopeList)
{
    d->scopeList = scopeList;
}

QList<KDQName> WSDiscoveryTargetService::typeList() const
{
    return d->typeList;
}

void WSDiscoveryTargetService::setTypeList(const QList<KDQName> &typeList)
{
    d->typeList = typeList;
}

QString WSDiscoveryTargetService::endpointReference() const
{
    return d->endpointReference;
}

void WSDiscoveryTargetService::setEndpointReference(const QString& endpointReference)
{
    d->endpointReference = endpointReference;
}

