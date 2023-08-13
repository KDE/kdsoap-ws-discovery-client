/* SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#ifndef WSDISCOVERYPROBEJOB_H
#define WSDISCOVERYPROBEJOB_H

#include "wsdiscoveryclient_export.h"
#include <KDSoapClient/KDQName>
#include <QObject>
#include <QTimer>
#include <QUrl>

class WSDiscoveryClient;
class WSDiscoveryTargetService;

/*!
 * \brief Periodically probe the network for WS-Discovery devices.
 *
 * You can set a filter for interested types and scopes, only devices that match
 * the filter will be reported. After starting it will probe the network and
 * report any matches.
 */
class WSDISCOVERYCLIENT_EXPORT WSDiscoveryProbeJob : public QObject
{
    Q_OBJECT
public:
    /*!
     * Creates a WSDiscoveryProbeJob
     * \param parent is both the QObject parent as the WSDiscoveryClient
     *   used for sending and receiving messages
     */
    explicit WSDiscoveryProbeJob(WSDiscoveryClient *parent);

    /*!
     * \return List of types to filter devices with
     */
    QList<KDQName> typeList() const;
    /*!
     * \param typeList List of types to filter devices with
     */
    void setTypeList(const QList<KDQName> &typeList);
    /*!
     * \param type Adds a type to the list to filter devices with
     */
    void addType(const KDQName &type);

    /*!
     * \return List of scopes to filter devices with
     */
    QList<QUrl> scopeList() const;
    /*!
     * \param scopeList List of scopes to filter devices with
     */
    void setScopeList(const QList<QUrl> &scopeList);
    /*!
     * \param scope Adds a scopes to the list to filter devices with
     */
    void addScope(const QUrl &scope);

    /*!
     * \return The interval between probes
     */
    int interval() const;
    /*!
     * \param interval Sets the interval between probes
     */
    void setInterval(int interval);

Q_SIGNALS:
    /*!
     * Emitted when a match is received
     * \param matchedService The service as described in the match
     */
    void matchReceived(const WSDiscoveryTargetService &matchedService);

public Q_SLOTS:
    /*!
     * Start sending periodic probes
     */
    void start();
    /*!
     * Stop sending periodic probes
     */
    void stop();

    // TODO: Hide private interface
private Q_SLOTS:
    void timeout();
    void probeMatchReceived(const WSDiscoveryTargetService &probeMatchService);

private:
    WSDiscoveryClient *m_client;
    QList<KDQName> m_typeList;
    QList<QUrl> m_scopeList;
    QTimer m_timer;
};

#endif // WSDISCOVERYPROBEJOB_H
