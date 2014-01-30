/**
 * Copyright 2014 Samoilenko Yuri<kinnalru@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SFTPPLUGIN_MOUNTJOB_H
#define SFTPPLUGIN_MOUNTJOB_H

#include <KJob>
#include <KProcess>

#include "sftpplugin.h"
#include "mountloop.h"

class Mounter
    : public QObject
{
    Q_OBJECT
public:
  
    explicit Mounter(SftpPlugin *sftp, int idleTimeout);
    virtual ~Mounter();
    
    bool wait();
    bool isMounted() const {return m_started;}
    
Q_SIGNALS:
    void mounted();
    void unmounted(bool idleTimeout);    
    void failed(const QString& message);
   
private Q_SLOTS:
    void onPakcageReceived(const NetworkPackage& np);
    void onStarted();
    void onError(QProcess::ProcessError error);
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onMountTimeout();
    void onIdleTimeout();
    void readProcessOut();
    void start();

private: 
    int generateId();
    void cleanMountPoint();
    void unmount();
    
private:
    SftpPlugin* m_sftp;
    QScopedPointer<KProcess> m_proc;
    int m_id;
    const QString m_mpoint;
    QTimer m_connectTimer;
    QTimer m_idleTimer;
    QDateTime m_lastActivity;
    MountLoop m_loop;
    bool m_started;
};


#endif
