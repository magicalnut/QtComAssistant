#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QtComAssistant_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    a.setApplicationName("QtComAssistant");
    a.setApplicationVersion("1.0.0");

    MainWindow w;
    w.setWindowTitle("串口调试助手");
    w.resize(900, 650);
    w.show();
    return QApplication::exec();
}
