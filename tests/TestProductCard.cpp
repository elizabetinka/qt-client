//
// Created by e.kravchenkova on 13.04.2025.
//

#include <QTest>
#include <QtWidgets/QLineEdit>
#include <QSignalSpy>
#define private public
#include "../src/widgets/ProductCard.h"
#undef private

class Test_ProductCard : public QObject
{
Q_OBJECT
private slots: // должны быть приватными
    void click();
    void buttonsVisible();
    void buttonsInvisible();
    void modifyUndef();
    void deleteButtonUndef();
    void modify();
    void deleteButton();

};

void Test_ProductCard ::click()
{
    auto addCard=ProductCard(ItemInfo(), nullptr, ":/image/add");
    addCard.show();
    addCard.setFocus();

    QSignalSpy spy(&addCard, SIGNAL(addItem()));

    QTest::mouseClick(&addCard, Qt::LeftButton);

    QVERIFY(addCard.buttonWidget->isHidden());
    QCOMPARE(spy.count(),1);
}


void Test_ProductCard ::buttonsVisible()
{
    auto productCard=ProductCard(ItemInfo(), nullptr);
    productCard.show();
    productCard.setFocus();

    QTest::mouseClick(&productCard, Qt::LeftButton);

    QVERIFY(productCard.buttonWidget->isVisible());
}

void Test_ProductCard ::buttonsInvisible()
{
    auto productCard=ProductCard(ItemInfo(), nullptr);
    productCard.show();
    productCard.setFocus();

    QVERIFY(productCard.buttonWidget->isHidden());
}

void Test_ProductCard ::modifyUndef()
{
    qRegisterMetaType<ItemInfo>();
    auto productCard=ProductCard(ItemInfo(), nullptr);
    productCard.show();
    productCard.setFocus();

    QSignalSpy spy(&productCard, SIGNAL(modifyItem(ItemInfo)));

    QTest::mouseClick(&productCard, Qt::LeftButton);
    QVERIFY(productCard.editButton->isVisible());
    productCard.editButton->show();
    productCard.editButton->setFocus();
    QTest::mouseClick(&*productCard.editButton, Qt::LeftButton);

    QCOMPARE(spy.count(),0);

}

void Test_ProductCard ::deleteButtonUndef()
{
    qRegisterMetaType<ItemInfo>();
    auto productCard=ProductCard(ItemInfo(), nullptr);
    productCard.show();
    productCard.setFocus();

    QSignalSpy spy(&productCard, SIGNAL(deleteItem(ItemInfo)));

    QTest::mouseClick(&productCard, Qt::LeftButton);
    QVERIFY(productCard.editButton->isVisible());
    productCard.deleteButton->setFocus();
    QTest::mouseClick(&*productCard.deleteButton, Qt::LeftButton);

    QCOMPARE(spy.count(),0);

}

void Test_ProductCard ::modify()
{
    qRegisterMetaType<ItemInfo>();
    auto productCard=ProductCard(ItemInfo(), nullptr);
    productCard.info.undef= false;
    productCard.show();
    productCard.setFocus();

    QSignalSpy spy(&productCard, SIGNAL(modifyItem(ItemInfo)));

    QTest::mouseClick(&productCard, Qt::LeftButton);
    QVERIFY(productCard.editButton->isVisible());
    productCard.editButton->show();
    productCard.editButton->setFocus();
    QTest::mouseClick(&*productCard.editButton, Qt::LeftButton);

    QCOMPARE(spy.count(),1);

    QList<QVariant> arguments = spy.takeFirst();
    auto result = qvariant_cast<ItemInfo>(arguments.at(0));
    QCOMPARE(result,productCard.info);

}

void Test_ProductCard ::deleteButton()
{
    qRegisterMetaType<ItemInfo>();
    auto productCard=ProductCard(ItemInfo(), nullptr);
    productCard.info.undef= false;
    productCard.show();
    productCard.setFocus();

    QSignalSpy spy(&productCard, SIGNAL(deleteItem(ItemInfo)));

    QTest::mouseClick(&productCard, Qt::LeftButton);
    QVERIFY(productCard.editButton->isVisible());
    productCard.deleteButton->setFocus();
    QTest::mouseClick(&*productCard.deleteButton, Qt::LeftButton);

    QCOMPARE(spy.count(),1);

    QList<QVariant> arguments = spy.takeFirst();
    auto result = qvariant_cast<ItemInfo>(arguments.at(0));
    QCOMPARE(result,productCard.info);

}

QTEST_MAIN(Test_ProductCard)
#include "TestProductCard.moc"