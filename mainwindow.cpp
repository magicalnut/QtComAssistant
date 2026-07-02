#include "mainwindow.h"
#include "serialservice.h"
#include "utils.h"
#include "commanddialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QStandardPaths>
#include <QRegularExpression>
#include <QStatusBar>
#include <QApplication>
#include <QTextBlock>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_service(new SerialService(this))
    , m_timedSendTimer(new QTimer(this))
{
    setupUi();

    // SerialService signals -> MainWindow slots
    connect(m_service, &SerialService::dataReceived,this, &MainWindow::onDataReceived);
    connect(m_service, &SerialService::dataSent,this, &MainWindow::onDataSent);
    connect(m_service, &SerialService::portOpened,this, &MainWindow::onPortOpened);
    connect(m_service, &SerialService::portClosed,this, &MainWindow::onPortClosed);
    connect(m_service, &SerialService::errorOccurred,this, &MainWindow::onError);

    // UI control signals
    connect(m_openBtn, &QPushButton::clicked,this, &MainWindow::onOpenCloseClicked);
    connect(m_sendBtn, &QPushButton::clicked,this, &MainWindow::onSend);
    connect(m_inputLine, &QLineEdit::returnPressed,this, &MainWindow::onSend);
    connect(m_timedSendTimer, &QTimer::timeout,this, &MainWindow::onTimedSendTick);
    connect(m_keywordBtn, &QPushButton::clicked,this, &MainWindow::onKeywordHighlight);
    connect(m_keywordEdit, &QLineEdit::returnPressed,this, &MainWindow::onKeywordHighlight);
    connect(m_clearBtn, &QPushButton::clicked,this, &MainWindow::onClearScreen);
    connect(m_saveBtn, &QPushButton::clicked,this, &MainWindow::onSaveClicked);
    connect(m_commandBtn, &QPushButton::clicked,this, &MainWindow::onCommandMenu);
    connect(m_dtrCheck, &QCheckBox::toggled,m_service, &SerialService::setDtr);
    connect(m_rtsCheck, &QCheckBox::toggled,m_service, &SerialService::setRts);

    connect(m_timedSendCheck, &QCheckBox::toggled, this,
            [this](bool checked) {
                if (checked){
                    m_timedSendTimer->start(m_timedIntervalSpin->value());
                }
                else{
                    m_timedSendTimer->stop();
                }
    });

    connect(m_timedIntervalSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [this](int val) {
                if (m_timedSendCheck->isChecked()) {
                    m_timedSendTimer->stop();
                    m_timedSendTimer->start(val);
                }
    });

    connect(m_keywordEdit, &QLineEdit::textChanged, this,
            [this]() {
                if (m_keywordApplied) {
                    m_keywordBtn->setEnabled(true);
                    m_keywordBtn->setText("确定");
                }
    });

    connect(m_checksumCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),this,
            [this]() {
                updateChecksumDisplay();
    });

    connect(m_inputLine, &QLineEdit::textChanged,this,
            [this]() {
                updateChecksumDisplay();
    });

    connect(m_encodingCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),this,
            [this]() {
                updateChecksumDisplay();
    });

    refreshPortList();
    setPortParamsEnabled(true);
    onPortClosed();

    m_KeywordNext.resize(0);
    // 发送历史上下键浏览
    m_inputLine->installEventFilter(this);


}

MainWindow::~MainWindow() = default;

// ---- UI setup ----
void MainWindow::setupUi()
{
    auto *central = new QWidget(this);
    setCentralWidget(central);
    auto *mainLayout = new QVBoxLayout(central);
    mainLayout->setContentsMargins(6, 6, 6, 6);
    mainLayout->setSpacing(4);

    // ======== 参数栏 ========
    m_portCombo = new QComboBox;
    m_portCombo->setEditable(true);
    m_portCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_portCombo->setToolTip("串口号（点击下拉刷新）");
    // 点击时刷新列表
    connect(m_portCombo, &QComboBox::activated, this, [this]() {
        refreshPortList();
    });

    m_baudCombo = new QComboBox;
    m_baudCombo->setEditable(true);
    m_baudCombo->addItems({"300","600","1200","2400","4800",
                           "9600","14400","19200","38400","57600",
                           "115200","230400","460800","921600"});
    m_baudCombo->setCurrentText("115200");
    m_baudCombo->setToolTip("波特率（可手动输入）");

    m_dataBitsCombo = new QComboBox;
    m_dataBitsCombo->addItems({"5","6","7","8"});
    m_dataBitsCombo->setCurrentText("8");

    m_stopBitsCombo = new QComboBox;
    m_stopBitsCombo->addItems({"1","1.5","2"});

    m_parityCombo = new QComboBox;
    m_parityCombo->addItems({"None","Even","Odd"});

    m_flowCombo = new QComboBox;
    m_flowCombo->addItems({"None","RTS/CTS","XON/XOFF"});

    m_openBtn = new QPushButton("打开串口");
    m_openBtn->setMinimumWidth(80);

    m_dtrCheck = new QCheckBox("DTR");
    m_rtsCheck = new QCheckBox("RTS");

    m_statusLabel = new QLabel("● 已断开");
    m_statusLabel->setStyleSheet("color: gray; font-weight: bold;");

    auto *paramRow1 = new QHBoxLayout;
    paramRow1->addWidget(new QLabel("串口号:"));
    paramRow1->addWidget(m_portCombo);
    paramRow1->addWidget(new QLabel("波特率:"));
    paramRow1->addWidget(m_baudCombo);
    paramRow1->addWidget(new QLabel("数据位:"));
    paramRow1->addWidget(m_dataBitsCombo);

    auto *paramRow2 = new QHBoxLayout;
    paramRow2->addWidget(new QLabel("停止位:"));
    paramRow2->addWidget(m_stopBitsCombo);
    paramRow2->addWidget(new QLabel("校验位:"));
    paramRow2->addWidget(m_parityCombo);
    paramRow2->addWidget(new QLabel("流控:"));
    paramRow2->addWidget(m_flowCombo);
    paramRow2->addWidget(m_openBtn);
    paramRow2->addWidget(m_dtrCheck);
    paramRow2->addWidget(m_rtsCheck);
    paramRow2->addWidget(m_statusLabel);
    paramRow2->addStretch();

    mainLayout->addLayout(paramRow1);
    mainLayout->addLayout(paramRow2);

    // ======== 显示工具栏 ========
    m_timestampCheck = new QCheckBox("时间戳");
    m_timestampCheck->setChecked(false);
    m_hexDisplayCheck = new QCheckBox("HEX 显示");
    m_pauseScrollCheck = new QCheckBox("暂停滚动");

    m_newlineCombo = new QComboBox;
    m_newlineCombo->addItems({"CRLF (\\r\\n)", "LF (\\n)", "CR (\\r)", "无换行"});
    m_newlineCombo->setToolTip("接收换行符处理");

    m_encodingCombo = new QComboBox;
    m_encodingCombo->addItems({"UTF-8", "GBK", "Latin1"});

    m_keywordEdit = new QLineEdit;
    m_keywordEdit->setPlaceholderText("关键字高亮...");
    m_keywordEdit->setMaximumWidth(160);
    m_keywordBtn = new QPushButton("确定");

    auto *displayToolbar = new QHBoxLayout;
    displayToolbar->addWidget(m_timestampCheck);
    displayToolbar->addWidget(m_hexDisplayCheck);
    displayToolbar->addWidget(m_pauseScrollCheck);
    displayToolbar->addWidget(new QLabel("换行:"));
    displayToolbar->addWidget(m_newlineCombo);
    displayToolbar->addSpacing(12);
    displayToolbar->addWidget(new QLabel("编码:"));
    displayToolbar->addWidget(m_encodingCombo);
    displayToolbar->addSpacing(12);
    displayToolbar->addWidget(new QLabel("关键字:"));
    displayToolbar->addWidget(m_keywordEdit);
    displayToolbar->addWidget(m_keywordBtn);
    mainLayout->addLayout(displayToolbar);

    // ======== 终端区 ========
    m_terminal = new QPlainTextEdit;
    m_terminal->setReadOnly(true);
    m_terminal->setMaximumBlockCount(10000);
    m_terminal->setFont(QFont("NSimSun", 10));
    m_terminal->setStyleSheet("QPlainTextEdit { background-color: #1E1E1E; "
                              "color: #D4D4D4; }");
    mainLayout->addWidget(m_terminal, 1); // stretch=1

    // ======== 输入行 ========
    m_inputLine = new QLineEdit;
    m_inputLine->setPlaceholderText("输入发送内容，按回车发送...");
    m_inputLine->setFont(QFont("NSimSun", 10));
    m_sendBtn = new QPushButton("发送");
    m_sendBtn->setMinimumWidth(60);

    auto *inputRow = new QHBoxLayout;
    inputRow->addWidget(new QLabel("发送:"));
    inputRow->addWidget(m_inputLine, 1);
    inputRow->addWidget(m_sendBtn);
    mainLayout->addLayout(inputRow);

    // ======== 发送选项 ========
    m_hexSendCheck = new QCheckBox("HEX");
    m_timedSendCheck = new QCheckBox("定时");
    m_timedIntervalSpin = new QSpinBox;
    m_timedIntervalSpin->setRange(10, 60000);
    m_timedIntervalSpin->setValue(1000);
    m_timedIntervalSpin->setSuffix("ms");
    m_timedIntervalSpin->setMaximumWidth(100);

    m_checksumCombo = new QComboBox;
    m_checksumCombo->addItems({"无校验", "XOR", "累加和",
                               "CRC16-CCITT", "CRC16-Modbus"});
    m_checksumResultLabel = new QLabel;
    m_checksumResultLabel->setStyleSheet("color: #569CD6; font-weight: bold;");

    m_commandBtn = new QPushButton("指令▼");
    m_clearBtn = new QPushButton("清屏");
    m_saveBtn = new QPushButton("保存▼");
    m_fileSendBtn = new QPushButton("文件发送");

    auto *sendOptions = new QHBoxLayout;
    sendOptions->addWidget(m_hexSendCheck);
    sendOptions->addWidget(m_timedSendCheck);
    sendOptions->addWidget(m_timedIntervalSpin);
    sendOptions->addSpacing(8);
    sendOptions->addWidget(new QLabel("校验码:"));
    sendOptions->addWidget(m_checksumCombo);
    sendOptions->addWidget(m_checksumResultLabel);
    sendOptions->addStretch();
    sendOptions->addWidget(m_commandBtn);
    sendOptions->addWidget(m_clearBtn);
    sendOptions->addWidget(m_saveBtn);
    sendOptions->addWidget(m_fileSendBtn);
    connect(m_fileSendBtn, &QPushButton::clicked,this, &MainWindow::onFileSendClicked);
    mainLayout->addLayout(sendOptions);

    // ======== 状态栏 ========
    m_txRxLabel = new QLabel("TX: 0  RX: 0");
    m_pinLabel = new QLabel("CTS○ DSR○ DCD○");
    m_portLabel = new QLabel;

    statusBar()->addWidget(m_txRxLabel);
    statusBar()->addWidget(m_pinLabel, 1);
    statusBar()->addPermanentWidget(m_portLabel);
}

void MainWindow::onOpenCloseClicked()
{
    if (m_service->isOpen()) {
        m_service->close();
    }
    else {
        SerialConfig cfg;
        cfg.portName = m_portCombo->currentText().trimmed();
        if (cfg.portName.isEmpty()) {
            onError("请选择串口号");
            return;
        }
        cfg.baudRate = m_baudCombo->currentText().toInt();
        cfg.dataBits = static_cast<QSerialPort::DataBits>(m_dataBitsCombo->currentText().toInt());
        QString stopText = m_stopBitsCombo->currentText();
        if (stopText == "1.5"){
            cfg.stopBits = QSerialPort::OneAndHalfStop;
        }
        else if (stopText == "2"){
            cfg.stopBits = QSerialPort::TwoStop;
        }
        else{
            cfg.stopBits = QSerialPort::OneStop;
        }

        QString parityText = m_parityCombo->currentText();
        if (parityText == "Even"){
            cfg.parity = QSerialPort::EvenParity;
        }
        else if (parityText == "Odd"){
            cfg.parity = QSerialPort::OddParity;
        }
        else{
            cfg.parity = QSerialPort::NoParity;
        }

        QString flowText = m_flowCombo->currentText();
        if (flowText == "RTS/CTS"){
            cfg.flowControl = QSerialPort::HardwareControl;
        }
        else if (flowText == "XON/XOFF"){
            cfg.flowControl = QSerialPort::SoftwareControl;
        }
        else{
            cfg.flowControl = QSerialPort::NoFlowControl;
        }

        m_service->open(cfg);
    }
}

void MainWindow::onPortOpened(const QString &name)
{
    setPortParamsEnabled(false);
    m_openBtn->setText("关闭串口");
    m_statusLabel->setText("● 已连接");
    m_statusLabel->setStyleSheet("color: green; font-weight: bold;");
    m_portLabel->setText(name);
}

void MainWindow::onPortClosed()
{
    setPortParamsEnabled(true);
    m_openBtn->setText("打开串口");
    m_statusLabel->setText("● 已断开");
    m_statusLabel->setStyleSheet("color: gray; font-weight: bold;");
    m_portLabel->clear();
    m_dtrCheck->setChecked(false);
    m_rtsCheck->setChecked(false);
    m_timedSendTimer->stop();
    m_timedSendCheck->setChecked(false);
}

void MainWindow::onError(const QString &message)
{
    statusBar()->showMessage(message, 5000);
    // 严重错误弹窗
    if (message.contains("无法打开") || message.contains("丢失"))
        QMessageBox::warning(this, "错误", message);
}

void MainWindow::setPortParamsEnabled(bool enabled)
{
    m_portCombo->setEnabled(enabled);
    m_baudCombo->setEnabled(enabled);
    m_dataBitsCombo->setEnabled(enabled);
    m_stopBitsCombo->setEnabled(enabled);
    m_parityCombo->setEnabled(enabled);
    m_flowCombo->setEnabled(enabled);
    m_dtrCheck->setEnabled(!enabled);
    m_rtsCheck->setEnabled(!enabled);
}

void MainWindow::refreshPortList()
{
    QString current = m_portCombo->currentText();
    m_portCombo->clear();
    m_portCombo->addItems(m_service->availablePorts());
    if (!current.isEmpty())
        m_portCombo->setCurrentText(current);
}

// ---- 发送 ----
void MainWindow::onSend()
{
    if (!m_service->isOpen()) {
        onError("请先打开串口");
        return;
    }

    QString text = m_inputLine->text();
    if (text.isEmpty()){
        return;
    }

    // 校验 HEX 格式
    if (m_hexSendCheck->isChecked()) {
        bool ok = false;
        Utils::hexToBytes(text, &ok);
        if (!ok) {
            m_inputLine->setStyleSheet("QLineEdit { border: 2px solid red; }");
            onError("HEX 格式错误");
            return;
        }
        m_inputLine->setStyleSheet("");
    } else {
        bool ok = false;
        QString encoding = m_encodingCombo->currentText();
        Utils::parseEscapes(text,encoding, &ok);
        if (!ok) {
            m_inputLine->setStyleSheet("QLineEdit { border: 2px solid red; }");
            onError("转义字符格式错误");
            return;
        }
        m_inputLine->setStyleSheet("");
    }

    QByteArray data = makeSendContent();

    // 加入发送历史
    if (m_sendHistory.isEmpty() || m_sendHistory.last() != text){
        m_sendHistory.append(text);
    }
    m_sendHistoryIndex = m_sendHistory.size();

    m_service->sendBytes(data);
    // m_inputLine->clear();
}

QByteArray MainWindow::makeSendContent() const
{
    QString text = m_inputLine->text();
    if (text.isEmpty())
        return {};

    QByteArray data;
    if (m_hexSendCheck->isChecked()) {
        bool ok = false;
        data = Utils::hexToBytes(text, &ok);
        if (!ok) {
            // 需要通知用户 - 通过 non-const 方式
            // 此处返回空，调用方检查
        }
    } else {
        bool ok = false;
        QString encoding = m_encodingCombo->currentText();
        data = Utils::parseEscapes(text,encoding, &ok);
        if (!ok) {
            // 转义格式错误
        }
    }

    // data.append(QByteArray::fromHex(m_checksumResultLabel->text().toUtf8()));
    // 追加换行符
    int nlIndex = m_newlineCombo->currentIndex();
    // 0: CRLF, 1: LF, 2: CR, 3: none
    if (nlIndex == 0)
        data.append("\r\n");
    else if (nlIndex == 1)
        data.append('\n');
    else if (nlIndex == 2)
        data.append('\r');
    // else: no newline
    return data;
}

void MainWindow::onDataSent(const QByteArray &data)
{
    m_txCount += data.size();
    m_txRxLabel->setText(
        QString("TX: %1  RX: %2").arg(m_txCount).arg(m_rxCount));

    QString display;
    if (m_hexDisplayCheck->isChecked()) {
        display = Utils::bytesToHex(data);
    } else {
        QString encoding = m_encodingCombo->currentText();
        display = Utils::decode(data, encoding);
    }
    appendToTerminal("TX ▶", display, QColor("#569CD6"));
}

// ---- 接收 ----
void MainWindow::onDataReceived(const QByteArray &data)
{
    m_rxCount += data.size();
    m_txRxLabel->setText(
        QString("TX: %1  RX: %2").arg(m_txCount).arg(m_rxCount));

    QString display;
    if (m_hexDisplayCheck->isChecked()) {
        display = Utils::bytesToHex(data);
    } else {
        QString encoding = m_encodingCombo->currentText();
        display = Utils::decode(data, encoding);
    }
    appendToTerminal("RX ◀", display, QColor("#D4D4D4"));
}

static auto KMP(const QString &content,const std::vector<int> & m_KeywordNext,const QString &keyword)
    ->std::vector<std::pair<int,int> >{
    int l=0,j=0;
    std::vector<std::pair<int,int> >res;
    for(int i=0;i<content.size();i++){
        if(j==keyword.size()){
            if(res.size()!=0){
                int pre=res.size()-1;
                if(l>res[pre].first+res[pre].second){
                    res.emplace_back(std::pair<int,int>{l,j});
                }
                else{
                    res[pre].second+=j-res[pre].first-res[pre].second+l;
                }
            }
            else{
                res.emplace_back(std::pair<int,int>{l,j});
            }
            i=l+j-1;
            l=i+1;
            j=0;
            continue;
        }
        if(keyword[j]==content[i]){
            j++;
        }
        else{
            j=m_KeywordNext[j];
            l=i-j;
            if(j!=-1){
                i--;
            }
            else{
                j=0;
            }
        }
    }
    if(j==keyword.size()){
        if(res.size()!=0){
            int pre=res.size()-1;
            if(l>res[pre].first+res[pre].second){
                res.emplace_back(std::pair<int,int>{l,j});
            }
            else{
                res[pre].second+=j-res[pre].first-res[pre].second+l;
            }
        }
        else{
            res.emplace_back(std::pair<int,int>{l,j});
        }
    }
    return res;
}

// ---- 终端追加 ----
void MainWindow::appendToTerminal(const QString &prefix,const QString &content,const QColor &prefixColor)
{

    // 设置前缀颜色
    QTextCharFormat fmt;
    fmt.setForeground(prefixColor);
    QTextCursor cursor = m_terminal->textCursor();
    cursor.movePosition(QTextCursor::End);
    if(m_KeywordNext.size()!=0){
        QTextCharFormat fmt_highlight;
        fmt_highlight.setForeground(prefixColor);
        fmt_highlight.setBackground(QColor("#505020"));

        std::vector<std::pair<int,int> > highlighttext=KMP(content,m_KeywordNext,m_currentKeyword);
        if (m_timestampCheck->isChecked())
            cursor.insertText(Utils::timestampNow(),fmt);
        cursor.insertText(prefix+" ", fmt);
        int p=0,i=0;
        while(p!=content.size()){
            if(i==highlighttext.size()){
                cursor.insertText(content.mid(p,content.size()-p),fmt);
                break;
            }
            if(p==highlighttext[i].first){
                cursor.insertText(content.mid(p,highlighttext[i].second),fmt_highlight);
                p+=highlighttext[i].second;
                i++;
            }
            else{
                cursor.insertText(content.mid(p,highlighttext[i].first-p),fmt);
                p=highlighttext[i].first;
            }
        }
        cursor.insertText("\n",fmt);
    }
    else{
        QString line;
        if (m_timestampCheck->isChecked())
            line += Utils::timestampNow();
        line += prefix + " " + content;
        cursor.insertText(line, fmt);
        cursor.insertText("\n",fmt);
    }


    // 自动滚动（除非暂停）
    if (!m_pauseScrollCheck->isChecked()) {
        QScrollBar *sb = m_terminal->verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}

// ---- 定时发送 ----
void MainWindow::onTimedSendTick()
{
    if (m_service->isOpen())
        onSend();
}

// ---- 文件发送 ----
void MainWindow::onFileSendClicked()
{
    if (!m_service->isOpen()) {
        onError("请先打开串口");
        return;
    }

    QString path = QFileDialog::getOpenFileName(
        this, "选择要发送的文件", QString(),
        "所有文件 (*);;文本文件 (*.txt);;二进制文件 (*.bin)");
    if (path.isEmpty())
        return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "错误",
                             QString("无法打开文件：%1").arg(file.errorString()));
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    // 分块发送（256 字节/块），保持 UI 响应
    const int chunkSize = 256;
    int offset = 0;
    while (offset < fileData.size()) {
        QByteArray chunk = fileData.mid(offset, chunkSize);
        m_service->sendBytes(chunk);
        offset += chunkSize;
        QApplication::processEvents();
    }
    statusBar()->showMessage(
        QString("文件发送完成：%1 字节").arg(fileData.size()), 5000);
}

void MainWindow::onSaveClicked()
{
    QMenu menu;
    QAction *saveAll = menu.addAction("保存全部 (TX+RX)");
    QAction *saveTx = menu.addAction("仅保存发送");
    QAction *saveRx = menu.addAction("仅保存接收");
    QAction *saveRxBin = menu.addAction("仅保存接收 (原始二进制)");

    QAction *chosen = menu.exec(m_saveBtn->mapToGlobal(QPoint(0, m_saveBtn->height())));
    if (!chosen)
        return;

    QString filter;
    bool binary = false;
    if (chosen == saveRxBin) {
        filter = "二进制文件 (*.bin)";
        binary = true;
    } else {
        filter = "文本文件 (*.txt)";
    }

    QString path = QFileDialog::getSaveFileName(this, "保存", QString(), filter);
    if (path.isEmpty())
        return;

    if (binary) {
        // 保存原始接收数据：需要从 m_service 获取历史缓冲区
        // 当前设计：m_service 不保存历史。简化处理：从终端区提取 RX 行
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "错误",
                                 QString("无法写入文件：%1").arg(file.errorString()));
            return;
        }
        // 遍历终端文本提取 RX 行，用编码重新编码为字节
        QString text = m_terminal->toPlainText();
        QStringList lines = text.split('\n');
        QByteArray binaryData;
        QString encoding = m_encodingCombo->currentText();
        for (const QString &line : lines) {
            if (line.contains("RX ◀")) {
                // 提取纯数据部分（去掉时间戳和前缀）
                QString content = line;
                // 简单处理：找 "RX ◀ " 之后的内容
                int idx = content.indexOf("RX ◀ ");
                if (idx >= 0) {
                    content = content.mid(idx + 5); // strlen("RX ◀ ")
                    binaryData.append(Utils::encode(content, encoding));
                }
            }
        }
        file.write(binaryData);
        file.close();
    } else {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "错误",
                                 QString("无法写入文件：%1").arg(file.errorString()));
            return;
        }
        QTextStream stream(&file);
        QString text = m_terminal->toPlainText();
        QStringList lines = text.split('\n');

        if (chosen == saveAll) {
            stream << text;
        } else if (chosen == saveTx) {
            for (const QString &line : lines) {
                if (line.contains("TX ▶")) {
                    int idx = line.indexOf("TX ▶ ");
                    stream << (idx >= 0 ? line.mid(idx + 5) : line) << "\n";
                }
            }
        } else if (chosen == saveRx) {
            for (const QString &line : lines) {
                if (line.contains("RX ◀")) {
                    int idx = line.indexOf("RX ◀ ");
                    stream << (idx >= 0 ? line.mid(idx + 5) : line) << "\n";
                }
            }
        }
        file.close();
    }
    statusBar()->showMessage("保存完成", 3000);
}

void MainWindow::onClearScreen()
{
    m_terminal->clear();
}

void MainWindow::onCommandMenu()
{
    QMenu menu;
    QAction *manageAction = menu.addAction("管理指令...");
    menu.addSeparator();

    QList<QAction*> cmdActions;
    for (int i = 0; i < m_commands.size(); ++i) {
        QAction *act = menu.addAction(
            QString("[%1] %2").arg(m_commands[i].isHex ? "HEX" : "TXT", m_commands[i].name));
        cmdActions.append(act);
    }
    if (m_commands.isEmpty())
        menu.addAction("(无指令)")->setEnabled(false);

    QAction *chosen = menu.exec(
        m_commandBtn->mapToGlobal(QPoint(0, m_commandBtn->height())));
    if (!chosen)
        return;

    if (chosen == manageAction) {
        CommandDialog dlg(this);
        dlg.setCommands(m_commands);
        if (dlg.exec() == QDialog::Accepted) {
            m_commands = dlg.commands();
            // 更新自动回复规则
            QList<QPair<QByteArray, QByteArray>> rules;
            for (const auto &cmd : m_commands) {
                if (!cmd.autoReplyPattern.isEmpty() && !cmd.content.isEmpty()) {
                    QByteArray pattern = cmd.isHex
                                             ? Utils::hexToBytes(cmd.autoReplyPattern)
                                             : cmd.autoReplyPattern.toUtf8();
                    QByteArray response = cmd.isHex
                                              ? Utils::hexToBytes(cmd.content)
                                              : cmd.content.toUtf8();
                    rules.append({pattern, response});
                }
            }
            m_service->setAutoReplyRules(rules);
            m_service->setAutoReplyEnabled(!rules.isEmpty());
        }
        return;
    }

    // 选中一个指令
    for (int i = 0; i < cmdActions.size(); ++i) {
        if (chosen == cmdActions[i]) {
            m_inputLine->setText(m_commands[i].content);
            m_hexSendCheck->setChecked(m_commands[i].isHex);
            break;
        }
    }
}

void MainWindow::updateChecksumDisplay()
{
    int index = m_checksumCombo->currentIndex();
    // 0=None, 1=XOR, 2=Sum, 3=CRC16-CCITT, 4=CRC16-Modbus
    if (index == 0) {
        m_checksumResultLabel->clear();
        return;
    }

    QString text = m_inputLine->text();
    if (text.isEmpty()) {
        m_checksumResultLabel->clear();
        return;
    }

    QByteArray data;
    if (m_hexSendCheck->isChecked()) {
        bool ok = false;
        data = Utils::hexToBytes(text, &ok);
        if (!ok) {
            m_checksumResultLabel->setText("(格式错误)");
            return;
        }
    } else {
        QString encoding = m_encodingCombo->currentText();
        data = Utils::encode(text, encoding);
    }

    Utils::ChecksumType type = static_cast<Utils::ChecksumType>(index);
    QString result = Utils::checksumString(data, type);
    m_checksumResultLabel->setText(result);
}

static void compute_Next(std::vector<int> & m_KeywordNext,QString keyword){
    if(keyword.size()==0){
        m_KeywordNext.resize(0);
        return ;
    }
    int i=1,j=0;
    m_KeywordNext.resize(0);
    m_KeywordNext.resize(keyword.size(),-1);
    if (keyword.size() == 1) {
        return;
    }
    m_KeywordNext[1]=0;
    while(i!=keyword.size()-1){
        if(keyword[i]!=keyword[j]){
            j=0;
        }
        else{
            j++;
        }
        i++;
        m_KeywordNext[i]=j;
    }
    for(i=1;i<m_KeywordNext.size();i++){
        if(keyword[i]==keyword[m_KeywordNext[i]]){
            m_KeywordNext[i]=m_KeywordNext[m_KeywordNext[i]];
        }
    }
}

void MainWindow::onKeywordHighlight()
{
    QString keyword = m_keywordEdit->text().trimmed();
    if (keyword.isEmpty()){
        m_KeywordNext.resize(0);
        clearHighlights();
        return;
    }

    // 清除旧高亮
    clearHighlights();

    // 设置新高亮
    m_currentKeyword = keyword;
    compute_Next(m_KeywordNext,m_currentKeyword);
    applyHighlight(keyword);

    m_keywordBtn->setEnabled(false);
    m_keywordBtn->setText("已应用");
    m_keywordApplied = true;
}

void MainWindow::applyHighlight(const QString &keyword)
{
    QTextDocument *doc = m_terminal->document();
    QTextCursor cursor(doc);
    QTextCharFormat fmt;
    fmt.setBackground(QColor("#505020")); // 暗黄底色

    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = doc->find(keyword, cursor);
        if (!cursor.isNull()) {
            cursor.mergeCharFormat(fmt);
        }
    }
}

void MainWindow::clearHighlights()
{
    if (m_currentKeyword.isEmpty())
        return;

    QTextDocument *doc = m_terminal->document();
    QTextCursor cursor(doc);
    QTextCharFormat clearFmt;
    clearFmt.setBackground(Qt::transparent);

    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = doc->find(m_currentKeyword, cursor);
        if (!cursor.isNull()) {
            cursor.mergeCharFormat(clearFmt);
        }
    }
    m_currentKeyword.clear();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_inputLine && event->type() == QEvent::KeyPress) {
        auto *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Up) {
            // 浏览上一条历史
            if (m_sendHistory.isEmpty())
                return true;
            if (m_sendHistoryIndex >= m_sendHistory.size()) {
                // 如果正在输入新内容，先保存
                QString current = m_inputLine->text();
                if (!current.isEmpty()
                    && (m_sendHistory.isEmpty()
                        || m_sendHistory.last() != current)) {
                    m_sendHistory.append(current);
                }
                m_sendHistoryIndex = m_sendHistory.size() - 1;
            } else if (m_sendHistoryIndex > 0) {
                m_sendHistoryIndex--;
            }
            m_inputLine->setText(m_sendHistory.at(m_sendHistoryIndex));
            return true;
        } else if (keyEvent->key() == Qt::Key_Down) {
            if (m_sendHistory.isEmpty())
                return true;
            if (m_sendHistoryIndex < m_sendHistory.size() - 1) {
                m_sendHistoryIndex++;
                m_inputLine->setText(m_sendHistory.at(m_sendHistoryIndex));
            } else {
                m_sendHistoryIndex = m_sendHistory.size();
                m_inputLine->clear();
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
