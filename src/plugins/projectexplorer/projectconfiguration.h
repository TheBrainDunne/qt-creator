/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include "projectexplorer_export.h"

#include <coreplugin/id.h>
#include <utils/macroexpander.h>

#include <QObject>
#include <QString>
#include <QVariantMap>

namespace ProjectExplorer {

class Project;

class PROJECTEXPLORER_EXPORT ProjectConfiguration : public QObject
{
    Q_OBJECT

protected:
    explicit ProjectConfiguration(QObject *parent, Core::Id id);

public:
    ~ProjectConfiguration() = default;

    Core::Id id() const;

    QString displayName() const;

    bool usesDefaultDisplayName() const;
    void setDisplayName(const QString &name);
    void setDefaultDisplayName(const QString &name);

    void setToolTip(const QString &text);
    QString toolTip() const;

    // Note: Make sure subclasses call the superclasses' fromMap() function!
    virtual bool fromMap(const QVariantMap &map);

    // Note: Make sure subclasses call the superclasses' toMap() function!
    virtual QVariantMap toMap() const;

    Utils::MacroExpander *macroExpander() { return &m_macroExpander; }
    const Utils::MacroExpander *macroExpander() const { return &m_macroExpander; }

    virtual Project *project() const = 0;

    virtual bool isActive() const = 0;

    // Used in settings to mangle in build targets in RunConfigurations.
    virtual QString extraId() const;

    static QString settingsIdKey();

signals:
    void displayNameChanged();
    void toolTipChanged();

private:
    const Core::Id m_id;
    QString m_displayName;
    QString m_defaultDisplayName;
    QString m_toolTip;
    Utils::MacroExpander m_macroExpander;
};

class PROJECTEXPLORER_EXPORT StatefulProjectConfiguration : public ProjectConfiguration
{
    Q_OBJECT

public:
    StatefulProjectConfiguration() = default;

    bool isEnabled() const;

    virtual QString disabledReason() const = 0;

signals:
    void enabledChanged();

protected:
    StatefulProjectConfiguration(QObject *parent, Core::Id id);

    void setEnabled(bool enabled);

private:
    bool m_isEnabled = false;
};

// helper functions:
PROJECTEXPLORER_EXPORT Core::Id idFromMap(const QVariantMap &map);
PROJECTEXPLORER_EXPORT QString displayNameFromMap(const QVariantMap &map);

} // namespace ProjectExplorer
