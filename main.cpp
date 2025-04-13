#include <QApplication>
#include <QTranslator>
#include <iostream>
#include <QFile>
#include <QFontDatabase>

#include "src/main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    if (translator.load("ru", ":/translations/")){
        app.installTranslator(&translator);
        std::cout << "Yes";
    }
    else {
        std::cout << "No";
    }

    QFile styleF(":/qss/style.qss");
    if (styleF.open(QFile::ReadOnly | QIODevice::Text)){
        QString qssStr = styleF.readAll();
        qApp->setStyleSheet(qssStr);
        styleF.close();
    }
    else{
        qDebug()<<"can't open style file";
    }

    int fontId = QFontDatabase::addApplicationFont(":/fonts/GreatVibes");
//    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
//    qDebug()<<fontFamily;
    MainWindow window;
    window.show();
    return app.exec();
}