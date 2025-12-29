//
// Created by Adrian Rupp on 29.12.25.
//
#pragma once

#include <QObject>
#include <memory>

#include "core/interface/i_tab_component.hpp"
#include "model/DbcModel.hpp"
#include "view/DbcFileView.hpp"

namespace Dbc {
class IEventBroker;
class DbcComponent : public Core::ITabComponent, Core::IEventBroker {
    Q_OBJECT

public:
    explicit DbcComponent(IEventBroker& broker);
    ~DbcComponent() override;

    // --- ITabComponent Interface ---
    auto getView() -> QWidget* override;

    // Lifecycle
    void onStart() override;
    void onStop() override;

private slots:
    /** @brief Handle file loading request from View (publish to broker) */
    void onFileLoadRequested(const QString& filePath);

private:

    IEventBroker& m_broker;

    std::unique_ptr<::Dbc::DbcModel> m_model;
    std::unique_ptr<DbcDelegate> m_delegate;
    std::unique_ptr<::Dbc::DbcView> m_view;
};
}