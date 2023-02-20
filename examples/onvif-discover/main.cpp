/* SPDX-FileCopyrightText: 2019 Casper Meijn <casper@meijn.net>
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "onvifdiscover.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << "Starting ONVIF discovery for 5 seconds";
    QTimer::singleShot(5000, &app, &QCoreApplication::quit);

    auto onvifDiscover = new OnvifDiscover(&app);
    onvifDiscover->start();

    return QCoreApplication::exec();
}
