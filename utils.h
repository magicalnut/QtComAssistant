#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QString>

namespace Utils{
QByteArray hexToBytes(const QString &hex, bool *ok = nullptr);

QString bytesToHex(const QByteArray &bytes, char separator = ' ');

QByteArray parseEscapes(const QString &text,const QString &encoding, bool *ok = nullptr);

enum class ChecksumType { None, XOR, Sum, CRC16_CCITT, CRC16_Modbus };

QString checksumString(const QByteArray &data, ChecksumType type);

quint8 xorChecksum(const QByteArray &data);

quint8 sumChecksum(const QByteArray &data);

quint16 crc16CCITT(const QByteArray &data);

quint16 crc16Modbus(const QByteArray &data);

QByteArray encode(const QString &text, const QString &encoding);

QString decode(const QByteArray &data, const QString &encoding);

QString timestampNow();
}

#endif // UTILS_H
