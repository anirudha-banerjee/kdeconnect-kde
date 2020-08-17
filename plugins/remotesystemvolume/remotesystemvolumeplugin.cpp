/**
 * SPDX-FileCopyrightText: 2018 Nicolas Fella <nicolas.fella@gmx.de>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#include "remotesystemvolumeplugin.h"

#include <KLocalizedString>
#include <KPluginFactory>

#include <QDebug>
#include <QDBusConnection>
#include <QJsonArray>
#include <QJsonDocument>

#include <core/device.h>
#include <core/daemon.h>

#include "plugin_remotesystemvolume_debug.h"

K_PLUGIN_CLASS_WITH_JSON(RemoteSystemVolumePlugin, "kdeconnect_remotesystemvolume.json")

RemoteSystemVolumePlugin::RemoteSystemVolumePlugin(QObject* parent, const QVariantList& args)
    : KdeConnectPlugin(parent, args)
{
}

RemoteSystemVolumePlugin::~RemoteSystemVolumePlugin()
{
}

bool RemoteSystemVolumePlugin::receivePacket(const NetworkPacket& np)
{

    if (np.has(QStringLiteral("sinkList"))) {
        QJsonDocument document(np.get<QJsonArray>(QStringLiteral("sinkList")));
        m_sinks = document.toJson();
        Q_EMIT sinksChanged();
    } else {

        QString name = np.get<QString>(QStringLiteral("name"));

        if (np.has(QStringLiteral("volume"))) {
            Q_EMIT volumeChanged(name, np.get<int>(QStringLiteral("volume")));
        }

        if (np.has(QStringLiteral("muted"))) {
            Q_EMIT mutedChanged(name, np.get<int>(QStringLiteral("muted")));
        }
    }

    return true;
}

void RemoteSystemVolumePlugin::sendVolume(const QString& name, int volume)
{
    NetworkPacket np(PACKET_TYPE_SYSTEMVOLUME_REQUEST);
    np.set<QString>(QStringLiteral("name"), name);
    np.set<int>(QStringLiteral("volume"), volume);
    sendPacket(np);
}

void RemoteSystemVolumePlugin::sendMuted(const QString& name, bool muted)
{
    NetworkPacket np(PACKET_TYPE_SYSTEMVOLUME_REQUEST);
    np.set<QString>(QStringLiteral("name"), name);
    np.set<bool>(QStringLiteral("muted"), muted);
    sendPacket(np);
}

void RemoteSystemVolumePlugin::connected()
{
    NetworkPacket np(PACKET_TYPE_SYSTEMVOLUME_REQUEST);
    np.set<bool>(QStringLiteral("requestSinks"), true);
    sendPacket(np);
}

QByteArray RemoteSystemVolumePlugin::sinks()
{
    return m_sinks;
}

QString RemoteSystemVolumePlugin::dbusPath() const
{
    return QStringLiteral("/modules/kdeconnect/devices/") + device()->id() + QStringLiteral("/remotesystemvolume");
}

#include "remotesystemvolumeplugin.moc"

