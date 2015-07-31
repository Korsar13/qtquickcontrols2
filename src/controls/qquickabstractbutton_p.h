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

#ifndef QQUICKABSTRACTBUTTON_P_H
#define QQUICKABSTRACTBUTTON_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQuickControls/private/qquickcontrol_p.h>

QT_BEGIN_NAMESPACE

class QQuickAbstractButtonPrivate;

class Q_QUICKCONTROLS_EXPORT QQuickAbstractButton : public QQuickControl
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)
    Q_PROPERTY(bool pressed READ isPressed WRITE setPressed NOTIFY pressedChanged FINAL)
    Q_PROPERTY(QQuickItem *label READ label WRITE setLabel NOTIFY labelChanged FINAL)

public:
    explicit QQuickAbstractButton(QQuickItem *parent = Q_NULLPTR);

    QString text() const;
    void setText(const QString &text);

    bool isPressed() const;
    void setPressed(bool pressed);

    QQuickItem *label() const;
    void setLabel(QQuickItem *label);

Q_SIGNALS:
    void pressed();
    void released();
    void canceled();
    void clicked();
    void textChanged();
    void pressedChanged();
    void labelChanged();

protected:
    QQuickAbstractButton(QQuickAbstractButtonPrivate &dd, QQuickItem *parent);

    void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseUngrabEvent() Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QQuickAbstractButton)
    Q_DECLARE_PRIVATE(QQuickAbstractButton)
};

Q_DECLARE_TYPEINFO(QQuickAbstractButton, Q_COMPLEX_TYPE);

QT_END_NAMESPACE

#endif // QQUICKABSTRACTBUTTON_P_H