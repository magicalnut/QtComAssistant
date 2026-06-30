#include "serialservice.h"
#include <QtDebug>

SerialService::SerialService(QObject *parent) : QObject(parent), m_port(new QSerialPort(this)){
    connect(m_port, &QSerialPort::readyRead,this, &SerialService::onReadyRead);
    connect(m_port, &QSerialPort::errorOccurred,this, &SerialService::onErrorOccurred);
}

SerialService::~SerialService(){
    if (m_port->isOpen()){
        m_port->close();
    }
}

bool SerialService::isOpen() const{
    return m_port->isOpen();
}

QStringList SerialService::availablePorts() const{
    QStringList ports;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const auto &info : infos)
        ports.append(info.portName());
    return ports;
}

void SerialService::open(const SerialConfig &config){
    if (m_port->isOpen()) {
        emit errorOccurred("串口已打开，请先关闭");
        return;
    }

    m_port->setPortName(config.portName);
    m_port->setBaudRate(config.baudRate);
    m_port->setDataBits(config.dataBits);
    m_port->setStopBits(config.stopBits);
    m_port->setParity(config.parity);
    m_port->setFlowControl(config.flowControl);

    if (!m_port->open(QIODevice::ReadWrite)) {
        emit errorOccurred(
            QString("无法打开 %1：%2")
                .arg(config.portName, m_port->errorString()));
        return;
    }
    m_buffer.clear();
    emit portOpened(config.portName);
}

void SerialService::close(){
    if (m_port->isOpen()) {
        m_port->close();
        emit portClosed();
    }
}

void SerialService::sendBytes(const QByteArray &data){
    if (!m_port->isOpen()) {
        emit errorOccurred("请先打开串口");
        return;
    }
    qint64 written = m_port->write(data);
    if (written < 0) {
        emit errorOccurred(
            QString("发送失败：%1").arg(m_port->errorString()));
    } else if (written == data.size()) {
        emit dataSent(data);
    } else {
        // 部分写入，也发出已写入的部分
        emit dataSent(data.left(static_cast<int>(written)));
        emit errorOccurred("部分数据发送失败");
    }
}

void SerialService::setDtr(bool on){
    m_port->setDataTerminalReady(on);
}

void SerialService::setRts(bool on){
    m_port->setRequestToSend(on);
}

void SerialService::setAutoReplyRules(const QList<QPair<QByteArray, QByteArray>> &rules){
    m_autoReplyRules = rules;
}

bool SerialService::autoReplyEnabled() const{
    return m_autoReplyEnabled;
}

void SerialService::setAutoReplyEnabled(bool enabled){
    m_autoReplyEnabled = enabled;
}

void SerialService::onReadyRead(){
    m_buffer.append(m_port->readAll());
    emit dataReceived(m_buffer);
    tryAutoReply(m_buffer);
    m_buffer.clear();
}

void SerialService::onErrorOccurred(QSerialPort::SerialPortError error){
    if (error == QSerialPort::NoError){
        return;
    }
    QString msg;
    switch (error) {
    case QSerialPort::DeviceNotFoundError:
        msg = "设备未找到";
        break;
    case QSerialPort::PermissionError:
        msg = "权限不足或串口被占用";
        break;
    case QSerialPort::OpenError:
        msg = "串口已被占用或不存在";
        break;
    case QSerialPort::ResourceError:
        msg = "串口连接丢失（设备可能被拔出）";
        break;
    default:
        msg = m_port->errorString();
        break;
    }

    if (error == QSerialPort::ResourceError && m_port->isOpen()) {
        m_port->close();
        emit portClosed();
    }
    emit errorOccurred(msg);
}

void SerialService::tryAutoReply(const QByteArray &data){
    if (!m_autoReplyEnabled || m_autoReplyRules.isEmpty()){
        return;
    }
    for (const auto &rule : m_autoReplyRules) {
        if (rule.first.isEmpty()){
            continue;
        }
        if (data.contains(rule.first)) {
            sendBytes(rule.second);
            break; // 只匹配第一条
        }
    }
}