/**
 * SPDX-FileCopyrightText: 2013 Albert Vaca <albertvaka@gmail.com>
 * SPDX-FileCopyrightText: 2020 Aditya Mehra <aix.m@outlook.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#ifndef BIGSCREENPLUGIN_H
#define BIGSCREENPLUGIN_H

#include <core/kdeconnectplugin.h>

#define PACKET_TYPE_BIGSCREEN_STT QStringLiteral("kdeconnect.bigscreen.stt")

class Q_DECL_EXPORT BigscreenPlugin
    : public KdeConnectPlugin
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.kdeconnect.device.bigscreen")

public:
    explicit BigscreenPlugin(QObject* parent, const QVariantList& args);
    ~BigscreenPlugin() override;

    bool receivePacket(const NetworkPacket& np) override;
    void connected() override {};
    QString dbusPath() const override;

Q_SIGNALS:
    Q_SCRIPTABLE void messageReceived(const QString& message);

};

#endif
