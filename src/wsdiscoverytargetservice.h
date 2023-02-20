/* SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#ifndef WSDISCOVERYTARGETSERVICE_H
#define WSDISCOVERYTARGETSERVICE_H

#include "wsdiscoveryclient_export.h"
#include <KDSoapClient/KDQName>
#include <QDateTime>
#include <QUrl>

class WSDiscoveryTargetServiceData;

class WSDISCOVERYCLIENT_EXPORT WSDiscoveryTargetService
{
public:
    explicit WSDiscoveryTargetService();
    explicit WSDiscoveryTargetService(const QString &endpointReference);
    WSDiscoveryTargetService(const WSDiscoveryTargetService &other);
    ~WSDiscoveryTargetService();

    void setEndpointReference(const QString &endpointReference);
    QString endpointReference() const;
    QList<KDQName> typeList() const;
    void setTypeList(const QList<KDQName> &typeList);
    QList<QUrl> scopeList() const;
    void setScopeList(const QList<QUrl> &scopeList);
    QList<QUrl> xAddrList() const;
    void setXAddrList(const QList<QUrl> &xAddrList);
    QDateTime lastSeen() const;
    void setLastSeen(const QDateTime &lastSeen);
    void updateLastSeen();

    bool isMatchingType(const KDQName &matchingType) const;
    bool isMatchingScope(const QUrl &matchingScope) const;

private:
    QSharedDataPointer<WSDiscoveryTargetServiceData> d;
};

#endif // WSDISCOVERYTARGETSERVICE_H
