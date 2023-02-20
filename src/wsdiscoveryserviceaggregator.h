/* SPDX-FileCopyrightText: 2020 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef WSDISCOVERYSERVICEAGGREGATOR_H
#define WSDISCOVERYSERVICEAGGREGATOR_H

#include "wsdiscoveryclient_export.h"
#include <QObject>

class WSDiscoveryTargetService;
class WSDiscoveryServiceAggregatorPrivate;

/*!
 * \brief Aggregates multiple updates from the same WSDiscoveryTargetService
 *
 * When receiving multiple probe and resolve matches of the same service, this
 * class will aggregate those into a single shared instance. This eases the
 * administration needed by the application.
 */
class WSDISCOVERYCLIENT_EXPORT WSDiscoveryServiceAggregator : public QObject
{
    Q_OBJECT

public:
    /*!
     * Create a WSDiscoveryClient
     * \param parent The QObject parent
     */
    WSDiscoveryServiceAggregator(QObject *parent = nullptr);

    /*!
     * Destructor
     */
    ~WSDiscoveryServiceAggregator();

signals:
    /*!
     * Emitted when a service has new information. The service instance is
     * reused, when a new update is received. Therefore you can compare the
     * pointers when looking for updates of a previous received service.
     * \param updatedService A pointer to the updated service
     */
    void serviceUpdated(const QSharedPointer<WSDiscoveryTargetService> &updatedService);

public slots:
    /*!
     * Provides a new service update.
     * \param receivedService The service with updated information
     */
    void updateService(const WSDiscoveryTargetService &receivedService);

private:
    WSDiscoveryServiceAggregatorPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(WSDiscoveryServiceAggregator)
};

#endif // WSDISCOVERYSERVICEAGGREGATOR_H
