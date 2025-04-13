//
// Created by e.kravchenkova on 13.04.2025.
//

#include <QTest>
#include <QtWidgets/QLineEdit>
#include <QSignalSpy>
#include "../src/widgets/ClicableLabel.h"

class Test_ClickableLabel : public QObject
{
    Q_OBJECT
private slots: // должны быть приватными
    void click();

};

void Test_ClickableLabel::click()
{
    ClickableLabel a;
    a.show();
    a.setFocus();

    QSignalSpy spy(&a, SIGNAL(clicked()));

    QTest::mouseClick(&a, Qt::LeftButton);


    QCOMPARE(spy.count(),1);
}

QTEST_MAIN(Test_ClickableLabel)
#include "TestClickableLabel.moc"