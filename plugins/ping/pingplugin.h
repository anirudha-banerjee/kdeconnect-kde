/**
 * SPDX-FileCopyrightText: 2013 Albert Vaca <albertvaka@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#ifndef PINGPLUGIN_H
#define PINGPLUGIN_H

#include <QObject>

#include <core/kdeconnectplugin.h>

#define PACKET_TYPE_PING QStringLiteral("kdeconnect.ping")

class Q_DECL_EXPORT PingPlugin
    : public KdeConnectPlugin
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.kdeconnect.device.ping")

public:
    explicit PingPlugin(QObject* parent, const QVariantList& args);
    ~PingPlugin() override;

    Q_SCRIPTABLE void sendPing();
    Q_SCRIPTABLE void sendPing(const QString& customMessage);

    bool receivePacket(const NetworkPacket& np) override;
    void connected() override {}

    QString dbusPath() const override;
};

#endif
