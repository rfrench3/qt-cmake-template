#include "window.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDir>
#include <QSizePolicy>
#include <QTimer>
#include <QShowEvent>
#include <QFrame>
#include <memory>
#include <KPluginFactory>
#include <KPluginMetaData>
#include <KParts/ReadOnlyPart>
#include <kde_terminal_interface.h>

Tester::Tester(QWidget* parent)
    : QMainWindow(parent)
    , m_changeLogsButton(nullptr)
    , m_updateButton(nullptr)
    , m_applyUpdateButton(nullptr)
    , m_exitButton(nullptr)
    , m_konsolePart(nullptr)
    , m_terminalWidget(nullptr)
    , m_terminal(nullptr)
{
    setupUI();
    setupTerminal();
}

void Tester::setupUI()
{
    // Create central widget
    auto centralWidget = new QWidget(this);
    
    // Main vertical layout
    auto mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // Terminal area (will be added in setupTerminal)
    // This space will be filled by the terminal widget
    
    // Bottom button panel
    auto buttonWidget = new QWidget();
    
    // Horizontal layout for buttons
    auto buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(10, 5, 10, 5);
    buttonLayout->setSpacing(10);
    
    // Create buttons
    m_changeLogsButton = new QPushButton("Change Logs", buttonWidget);
    m_updateButton = new QPushButton("Update", buttonWidget);
    m_applyUpdateButton = new QPushButton("Apply Update (Reboot)", buttonWidget);
    m_exitButton = new QPushButton("Exit", buttonWidget);
    
    // Add buttons to layout
    buttonLayout->addWidget(m_changeLogsButton);
    buttonLayout->addWidget(m_updateButton);
    buttonLayout->addWidget(m_applyUpdateButton);
    buttonLayout->addStretch(); // Push exit button to the right
    buttonLayout->addWidget(m_exitButton);
    
    // Connect button signals
    connect(m_changeLogsButton, &QPushButton::clicked, this, &Tester::onChangeLogsClicked);
    connect(m_updateButton, &QPushButton::clicked, this, &Tester::onUpdateClicked);
    connect(m_applyUpdateButton, &QPushButton::clicked, this, &Tester::onApplyUpdateClicked);
    connect(m_exitButton, &QPushButton::clicked, this, &Tester::onExitClicked);
    
    // Add button widget to main layout
    mainLayout->addStretch(); // This will be replaced by terminal widget

    // Add horizontal line separator
    auto separator = new QFrame();
    separator->setFrameShape(QFrame::Shape::HLine);
    separator->setFrameShadow(QFrame::Shadow::Sunken);
    mainLayout->addWidget(separator);
    
    mainLayout->addWidget(buttonWidget);
    
    setCentralWidget(centralWidget);
}

void Tester::setupTerminal()
{
    // Load the Konsole KPart
    KPluginFactory *factory = KPluginFactory::loadFactory(KPluginMetaData(QStringLiteral("kf6/parts/konsolepart"))).plugin;
    m_konsolePart = factory ? factory->create<KParts::ReadOnlyPart>(this) : nullptr;
    
    if (m_konsolePart) {
        m_terminalWidget = m_konsolePart->widget();
        m_terminal = qobject_cast<TerminalInterface *>(m_konsolePart);
        
        if (m_terminal && m_terminalWidget) {
            // Set the terminal to show in the home directory with a clean start
            m_terminal->showShellInDir(QDir::homePath());
            
            // Use QTimer::singleShot with 0ms delay to ensure the clear happens
            // after the event loop processes the terminal initialization
            QTimer::singleShot(0, this, [this]() {
                if (m_terminal) {
                    m_terminal->sendInput("sh && set +o history && PS1='' && clear\n");
                    

                }
            });
            
            // Add terminal widget to the main layout (replace the stretch)
            auto centralWidget = this->centralWidget();
            auto mainLayout = qobject_cast<QVBoxLayout*>(centralWidget->layout());
            if (mainLayout) {
                // Remove the stretch item and add terminal widget
                auto stretchItem = mainLayout->takeAt(0);
                delete stretchItem;
                mainLayout->insertWidget(0, m_terminalWidget);
            }
        }
    }
}

void Tester::onChangeLogsClicked()
{
    if (m_terminal) {
        m_terminal->sendInput("clear\n");
        // Execute command silently and only show output
        m_terminal->sendInput("ujust changelogs 2>/dev/null\n");
    }
}

void Tester::onUpdateClicked()
{
    // Implement update functionality
    if (m_terminal) {
        m_terminal->sendInput("clear\n");
        m_terminal->sendInput("echo 'Starting update...'\n");
    }
}

void Tester::onApplyUpdateClicked()
{
    // Implement apply update functionality
    if (m_terminal) {
        m_terminal->sendInput("echo 'Applying update and rebooting...'\n");
    }
}

void Tester::onExitClicked()
{
    // Close the application
    close();
}
