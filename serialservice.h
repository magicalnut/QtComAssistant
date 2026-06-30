#ifndef SERIALSERVICE_H
#define SERIALSERVICE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QMap>

struct SerialConfig {
    QString portName;
    qint32 baudRate = 115200;
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
};

class SerialService : public QObject
{
    Q_OBJECT
public:
    explicit SerialService(QObject *parent = nullptr);
    ~SerialService() override;

    bool isOpen() const;
    QStringList availablePorts() const;

public slots:
    void open(const SerialConfig &config);
    void close();
    void sendBytes(const QByteArray &data);
    void setDtr(bool on);
    void setRts(bool on);

    // 自动回复规则管理
    void setAutoReplyRules(const QList<QPair<QByteArray, QByteArray>> &rules);
    bool autoReplyEnabled() const;
    void setAutoReplyEnabled(bool enabled);

signals:
    void dataReceived(const QByteArray &data);
    void dataSent(const QByteArray &data);
    void portOpened(const QString &name);
    void portClosed();
    void errorOccurred(const QString &message);

private slots:
    void onReadyRead();
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:
    void tryAutoReply(const QByteArray &data);

    QSerialPort *m_port = nullptr;
    QByteArray m_buffer;
    QList<QPair<QByteArray, QByteArray>> m_autoReplyRules;
    bool m_autoReplyEnabled = false;
};

#endif // SERIALSERVICE_H
