#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QMenu>
#include <QSerialPort>

#include "commanddialog.h"

class SerialService;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onOpenCloseClicked();
    void onSend();
    void onDataReceived(const QByteArray &data);
    void onDataSent(const QByteArray &data);
    void onPortOpened(const QString &name);
    void onPortClosed();
    void onError(const QString &message);
    void onTimedSendTick();
    void onKeywordHighlight();
    void onSaveClicked();
    void onFileSendClicked();
    void onCommandMenu();
    void onClearScreen();
    void refreshPortList();

private:
    void setupUi();
    void setPortParamsEnabled(bool enabled);
    void appendToTerminal(const QString &prefix, const QString &content,
                          const QColor &prefixColor);
    void trimTerminalLines();
    void applyHighlight(const QString &keyword);
    void clearHighlights();
    QByteArray makeSendContent() const;
    void updateChecksumDisplay();

    // Service
    SerialService *m_service = nullptr;

    // Port params
    QComboBox *m_portCombo = nullptr;
    QComboBox *m_baudCombo = nullptr;
    QComboBox *m_dataBitsCombo = nullptr;
    QComboBox *m_stopBitsCombo = nullptr;
    QComboBox *m_parityCombo = nullptr;
    QComboBox *m_flowCombo = nullptr;
    QPushButton *m_openBtn = nullptr;
    QCheckBox *m_dtrCheck = nullptr;
    QCheckBox *m_rtsCheck = nullptr;
    QLabel *m_statusLabel = nullptr;

    // Display toolbar
    QCheckBox *m_timestampCheck = nullptr;
    QCheckBox *m_hexDisplayCheck = nullptr;
    QCheckBox *m_pauseScrollCheck = nullptr;
    QComboBox *m_newlineCombo = nullptr;
    QComboBox *m_encodingCombo = nullptr;
    QLineEdit *m_keywordEdit = nullptr;
    QPushButton *m_keywordBtn = nullptr;

    // Terminal
    QPlainTextEdit *m_terminal = nullptr;
    std::vector<int>m_KeywordNext;

    // Input
    QLineEdit *m_inputLine = nullptr;
    QPushButton *m_sendBtn = nullptr;
    QCheckBox *m_hexSendCheck = nullptr;
    QCheckBox *m_timedSendCheck = nullptr;
    QSpinBox *m_timedIntervalSpin = nullptr;
    QComboBox *m_checksumCombo = nullptr;
    QLabel *m_checksumResultLabel = nullptr;
    QPushButton *m_commandBtn = nullptr;
    QPushButton *m_clearBtn = nullptr;
    QPushButton *m_saveBtn = nullptr;
    QPushButton *m_fileSendBtn = nullptr;

    // Status bar
    QLabel *m_txRxLabel = nullptr;
    QLabel *m_pinLabel = nullptr;
    QLabel *m_portLabel = nullptr;

    // State
    QTimer *m_timedSendTimer = nullptr;
    QStringList m_sendHistory;
    int m_sendHistoryIndex = -1;
    qint64 m_txCount = 0;
    qint64 m_rxCount = 0;
    bool m_keywordApplied = false;
    QString m_currentKeyword;
    QList<CommandItem> m_commands;
};
#endif // MAINWINDOW_H
