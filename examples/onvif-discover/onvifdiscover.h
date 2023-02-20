/* SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#ifndef ONVIFDISCOVER_H
#define ONVIFDISCOVER_H

#include <QObject>

class WSDiscoveryClient;
class WSDiscoveryProbeJob;
class WSDiscoveryTargetService;
class WSDiscoveryServiceAggregator;

class OnvifDiscover : public QObject
{
    Q_OBJECT
public:
    explicit OnvifDiscover(QObject *parent = nullptr);
    ~OnvifDiscover();

public slots:
    void start();

private slots:
    void matchReceived(const QSharedPointer<WSDiscoveryTargetService> &matchedService);

private:
    WSDiscoveryClient *m_client;
    WSDiscoveryProbeJob *m_probeJob;
    WSDiscoveryServiceAggregator *m_aggregator;
};

#endif // ONVIFDISCOVER_H
