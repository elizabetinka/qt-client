//
// Created by e.kravchenkova on 13.04.2025.
//

#include <QTest>
#include <QtWidgets/QLineEdit>
#include <QSignalSpy>

#include "../src/main_window.h"
#include "mock/MockRequestMaster.h"
#include "mock/MockPresentator.h"



class Test_MainWindow : public QObject
{
Q_OBJECT
public:
    Test_MainWindow();

private slots: // должны быть приватными
    void presentatorStartRequest();
    void requestMasterTimeout();
    void requestMasterHttpFinished();
    void requestMasterGotHttpData();

private:
    MockRequestMaster* requestMaster;
    MockPresentator* presentator;
    MainWindow window;
};

Test_MainWindow::Test_MainWindow() : requestMaster(new MockRequestMaster()),presentator(new MockPresentator(nullptr)), window(requestMaster,presentator,
                                                                                                                          false) {}

void Test_MainWindow ::presentatorStartRequest()
{
    QUrl request=QUrl::fromUserInput("https://www.google.ru/");
    QString requestType = "post";
    QByteArray data = QString("liza").toUtf8();

    emit presentator->startRequest(request,requestType,data);

    QVERIFY(requestMaster->slotInvoked);
    QCOMPARE(requestMaster->count,1);
    QCOMPARE(requestMaster->_url,request);
    QCOMPARE(requestMaster->_requestType,requestType);
    QCOMPARE(requestMaster->_data,data);

}

void Test_MainWindow ::requestMasterGotHttpData()
{
    QByteArray data = QString("liza").toUtf8();

    emit requestMaster->gotHttpData(data);

    QVERIFY(presentator->readHttpDataInvoked);
    QCOMPARE(presentator->readHttpDataCount,1);
    QCOMPARE(presentator->_data,data);
}

void Test_MainWindow ::requestMasterTimeout()
{
    emit requestMaster->timeout();

    QVERIFY(presentator->timeoutInvoked);
    QCOMPARE(presentator->timeoutDataCount,1);
}

void Test_MainWindow ::requestMasterHttpFinished()
{
    emit requestMaster->httpFinished();

    QVERIFY(presentator->onHttpFinishedInvoked);
    QCOMPARE(presentator->onHttpFinishedCount,1);
}

QTEST_MAIN(Test_MainWindow)
#include "TestMainWindow.moc"