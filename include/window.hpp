#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <KParts/ReadOnlyPart>

class TerminalInterface;

class Tester : public QMainWindow
{
    Q_OBJECT

    // Bottom buttons
    QPushButton* m_changeLogsButton;
    QPushButton* m_updateButton;
    QPushButton* m_applyUpdateButton;
    QPushButton* m_exitButton;
    
    // KParts terminal integration
    KParts::ReadOnlyPart* m_konsolePart;
    QWidget* m_terminalWidget;
    TerminalInterface* m_terminal;

    void setupTerminal();
    void setupUI();

public:
    Tester(QWidget* parent = nullptr);
    ~Tester() = default;

private slots:
    void onChangeLogsClicked();
    void onUpdateClicked();
    void onApplyUpdateClicked();
    void onExitClicked();
};