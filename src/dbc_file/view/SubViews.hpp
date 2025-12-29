//
// Created by Adrian Rupp on 28.12.25.
//

#pragma once
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>
#include <QSplitter>

namespace Dbc {
class DbcLoadPage : public QWidget
{
public:
    Q_OBJECT

    explicit DbcLoadPage(QWidget* parent = nullptr);

    signals:
        /**
         * @brief Emitted when the user successfully selects a file.
         *
         * This signal is triggered either by dropping a file onto the widget
         * or by selecting a file via the file dialog.
         *
         * @param filePath The absolute path to the selected DBC file.
         */
        void fileSelected(const QString& filePath);

protected:

    /**
     * @brief Checks if the dragged item is a file and updates the cursor.
     */
    void dragEnterEvent(QDragEnterEvent* event) override;

    /**
     * @brief Extracts the file path from the dropped data and emits fileSelected.
     */
    void dropEvent(QDropEvent* event) override;
private slots:
    /**
     * @brief Opens a QFileDialog to let the user browse for a file.
     */
    void onBrowseButtonClicked();
private:
    /**
     * @brief Initializes the layout and widgets.
     */
    void setupUi();
    QPushButton* m_loadButton;
    QLabel* m_infoLabel;
    QVBoxLayout* m_layout;
};

class DbcSearchTableView : public QWidget
{
    Q_OBJECT
public:
    DbcSearchTableView(QWidget* parent = nullptr);

    [[nodiscard]] auto tableView() const -> QTableView*;
    [[nodiscard]] auto searchBar() const -> const QLineEdit*;

    signals:
    void filterTextChanged(const QString& text);

private:
    QTableView* m_tableView;
    QLineEdit* m_lineEdit;
};

class DbcSearchTreeView : public QWidget
{
    Q_OBJECT

public:
    DbcSearchTreeView(QWidget* parent = nullptr);

    [[nodiscard]] auto treeView() const -> QTreeView*;
    [[nodiscard]] auto searchBar() const -> const QLineEdit*;

    signals:
    void searchTextChanged(const QString& text);

private:
    QTreeView* m_treeView;
    QLineEdit* m_searchBar;
};

class DbcMessagesPage : public QWidget
{
    Q_OBJECT
public:
    DbcMessagesPage(QWidget* parent = nullptr);
    ~DbcMessagesPage() override;

    signals:
    void messageSelectionChanged(const QModelIndex& index);

    private slots:
    void onMessageClicked(const QModelIndex& index);

private:
    void setupUi();

    QSplitter* m_splitter;
    DbcSearchTableView* m_messagesTable;
    QTableView* m_messageDetails;
};
}