/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtQml/qqmlextensionplugin.h>

#include "qquickmaterialstyle_p.h"
#include "qquickmaterialtheme_p.h"
#include "qquickmaterialprogressring_p.h"

#include <QtGui/private/qguiapplication_p.h>
#include <QtLabsControls/private/qquickstyleselector_p.h>

static inline void initResources()
{
    Q_INIT_RESOURCE(qtlabsmaterialstyleplugin);
#ifdef QT_STATIC
    Q_INIT_RESOURCE(qmake_Qt_labs_controls_material);
#endif
}

QT_BEGIN_NAMESPACE

class QtLabsMaterialStylePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")

public:
    QtLabsMaterialStylePlugin(QObject *parent = Q_NULLPTR);
    ~QtLabsMaterialStylePlugin();
    void registerTypes(const char *uri) Q_DECL_OVERRIDE;
    void initializeEngine(QQmlEngine *engine, const char *uri) Q_DECL_OVERRIDE;

private:
    QQuickProxyTheme *theme;
};

QtLabsMaterialStylePlugin::QtLabsMaterialStylePlugin(QObject *parent) : QQmlExtensionPlugin(parent)
{
    initResources();
}

QtLabsMaterialStylePlugin::~QtLabsMaterialStylePlugin()
{
    if (theme) {
        QPlatformTheme *old = theme->theme();
        QGuiApplicationPrivate::platform_theme = old;
        delete theme;
    }
}

void QtLabsMaterialStylePlugin::registerTypes(const char *uri)
{
    qmlRegisterUncreatableType<QQuickMaterialStyle>(uri, 1, 0, "Material", tr("Material is an attached property"));
}

void QtLabsMaterialStylePlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine);

    QQuickStyleSelector selector;
    if (selector.style() == QStringLiteral("material")) {
        if (QFont(QStringLiteral("Roboto")).family() == QStringLiteral("Roboto")) {
            QPlatformTheme *old = QGuiApplicationPrivate::platform_theme;
            if (old) {
                QQuickProxyTheme *theme = new QQuickMaterialTheme(old);
                QGuiApplicationPrivate::platform_theme = theme;
            }
        }
    }

    QByteArray import = QByteArray(uri) + ".impl";
    qmlRegisterType<QQuickMaterialProgressRing>(import, 1, 0, "ProgressRing");
    qmlRegisterType<QQuickMaterialRingAnimator>(import, 1, 0, "RingAnimator");
    qmlRegisterType(QUrl(baseUrl().toString() + QStringLiteral("/Ripple.qml")), import, 1, 0, "Ripple");
    qmlRegisterType(QUrl(baseUrl().toString() + QStringLiteral("/SliderHandle.qml")), import, 1, 0, "SliderHandle");
}

QT_END_NAMESPACE

#include "qtlabsmaterialstyleplugin.moc"