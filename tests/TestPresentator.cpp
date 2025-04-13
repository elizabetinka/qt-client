//
// Created by e.kravchenkova on 13.04.2025.
//

#include <QTest>
#include <QtWidgets/QLineEdit>
#include <QSignalSpy>
#include "mock/WrappedPresentator.h"


class Test_Presentator : public QObject
{
Q_OBJECT
private slots: // должны быть приватными
    void loginScreen();
    void loginScreenCheckGetRequest();
    void loginScreenStartRegistryScreen();
    void loginScreenCommonScreen();
    void commonScreen();
    void commonScreenModifyClient();
    void commonScreenLoginScreen();
    void commonScreenShowSidePanel();
    void commonScreenDeleteClient();

private:
    WrappedPresentator presentator = new WrappedPresentator(nullptr);
};


void Test_Presentator ::loginScreen()
{
    presentator.LoginScreen();

    QCOMPARE(presentator.currentWidgets.count(),2);
    QCOMPARE(presentator.currentButtons.count(),1);
    QCOMPARE(presentator.currentLabels.count(),2);
}

void Test_Presentator ::loginScreenCheckGetRequest()
{
    presentator.LoginScreen();

    presentator.currentWidgets[0]->setText("name");
    presentator.currentWidgets[1]->setText("name");

    QTest::mouseClick(presentator.currentButtons[0], Qt::LeftButton);

    QCOMPARE(presentator.checkGetRequestCount,1);
}


void Test_Presentator ::loginScreenStartRegistryScreen(){
    presentator.LoginScreen();

    QTest::mouseClick(presentator.currentLabels[0], Qt::LeftButton);

    QCOMPARE(presentator.startRegistryScreenCount,1);
}
void Test_Presentator ::loginScreenCommonScreen(){
    presentator.LoginScreen();

    QTest::mouseClick(presentator.currentLabels[1], Qt::LeftButton);

    QCOMPARE(presentator.CommonScreenCount,1);
}

void Test_Presentator ::commonScreen()
{
    presentator.CommonScreen();

    QCOMPARE(presentator.currentWidgets.count(),0);
    QCOMPARE(presentator.currentButtons.count(),3);
    QCOMPARE(presentator.currentLabels.count(),1);
}

void Test_Presentator ::commonScreenModifyClient()
{
    presentator.CommonScreen();
    presentator.clientInfo.undef=false;

    QTest::mouseClick(presentator.currentButtons[0], Qt::LeftButton);

    QCOMPARE(presentator.modifyClientCount,1);
}

void Test_Presentator ::commonScreenDeleteClient()
{
    presentator.CommonScreen();
    presentator.clientInfo.undef=false;

    QTest::mouseClick(presentator.currentButtons[1], Qt::LeftButton);

    QCOMPARE(presentator.deleteClientCount,1);
}

void Test_Presentator ::commonScreenShowSidePanel()
{
    presentator.CommonScreen();

    QTest::mouseClick(presentator.currentButtons[2], Qt::LeftButton);

    QCOMPARE(presentator.showSidePanelCount,1);
}

void Test_Presentator ::commonScreenLoginScreen()
{
    presentator.CommonScreen();
    presentator.LoginScreenCount=0;

    QTest::mouseClick(presentator.currentLabels[0], Qt::LeftButton);

    QCOMPARE(presentator.LoginScreenCount,1);
}


QTEST_MAIN(Test_Presentator)
#include "TestPresentator.moc"