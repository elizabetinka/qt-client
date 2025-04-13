//
// Created by e.kravchenkova on 13.04.2025.
//

#include <QTest>
#include <QtWidgets/QLineEdit>
#include <QSignalSpy>
#define private public
#include "../src/widgets/Products.h"
#undef private

class Test_Products : public QObject
{
Q_OBJECT
private slots: // должны быть приватными
    void addItem();
    void modifyItem();
    void deleteItem();
private:
    QVector<ItemInfo> items = QVector<ItemInfo>({ItemInfo{.undef=false}});
    Products products=Products(items);
};


void Test_Products ::addItem()
{
    auto& addCard=*products.addCard;

    addCard.show();
    addCard.setFocus();

    QSignalSpy spy(&products, SIGNAL(addItem()));

    emit addCard.addItem();

    QCOMPARE(spy.count(),1);
}

void Test_Products ::modifyItem()
{
    qRegisterMetaType<ItemInfo>();
    auto& card=*products.card[0];

    card.show();
    card.setFocus();

    QSignalSpy spy(&products, SIGNAL(modifyItem(ItemInfo)));

    emit card.modifyItem(card.info);

    QCOMPARE(spy.count(),1);
    QList<QVariant> arguments = spy.takeFirst();
    auto result = qvariant_cast<ItemInfo>(arguments.at(0));
    QCOMPARE(result,card.info);
}

void Test_Products ::deleteItem()
{
    qRegisterMetaType<ItemInfo>();
    auto& card=*products.card[0];

    card.show();
    card.setFocus();

    QSignalSpy spy(&products, SIGNAL(deleteItem(ItemInfo)));

    emit card.deleteItem(card.info);

    QCOMPARE(spy.count(),1);

    QList<QVariant> arguments = spy.takeFirst();
    auto result = qvariant_cast<ItemInfo>(arguments.at(0));
    QCOMPARE(result,card.info);
}


//void Test_Products ::modifyItem()
//{
//    auto& productCard=*products.card[0];
//    productCard.show();
//    productCard.setFocus();
//
//    QTest::mouseClick(&productCard, Qt::LeftButton);
//
//    QVERIFY(productCard.buttonWidget->isVisible());
//}
//
//void Test_ProductCard ::buttonsInvisible()
//{
//    auto productCard=ProductCard(ItemInfo(), nullptr);
//    productCard.show();
//    productCard.setFocus();
//
//    QVERIFY(productCard.buttonWidget->isHidden());
//}
//
//void Test_ProductCard ::modifyUndef()
//{
//    qRegisterMetaType<ItemInfo>();
//    auto productCard=ProductCard(ItemInfo(), nullptr);
//    productCard.show();
//    productCard.setFocus();
//
//    QSignalSpy spy(&productCard, SIGNAL(modifyItem(ItemInfo)));
//
//    QTest::mouseClick(&productCard, Qt::LeftButton);
//    QVERIFY(productCard.editButton->isVisible());
//    productCard.editButton->show();
//    productCard.editButton->setFocus();
//    QTest::mouseClick(&*productCard.editButton, Qt::LeftButton);
//
//    QCOMPARE(spy.count(),0);
//
//}
//
//void Test_ProductCard ::deleteButtonUndef()
//{
//    qRegisterMetaType<ItemInfo>();
//    auto productCard=ProductCard(ItemInfo(), nullptr);
//    productCard.show();
//    productCard.setFocus();
//
//    QSignalSpy spy(&productCard, SIGNAL(deleteItem(ItemInfo)));
//
//    QTest::mouseClick(&productCard, Qt::LeftButton);
//    QVERIFY(productCard.editButton->isVisible());
//    productCard.deleteButton->setFocus();
//    QTest::mouseClick(&*productCard.deleteButton, Qt::LeftButton);
//
//    QCOMPARE(spy.count(),0);
//
//}
//
//void Test_ProductCard ::modify()
//{
//    qRegisterMetaType<ItemInfo>();
//    auto productCard=ProductCard(ItemInfo(), nullptr);
//    productCard.info.undef= false;
//    productCard.show();
//    productCard.setFocus();
//
//    QSignalSpy spy(&productCard, SIGNAL(modifyItem(ItemInfo)));
//
//    QTest::mouseClick(&productCard, Qt::LeftButton);
//    QVERIFY(productCard.editButton->isVisible());
//    productCard.editButton->show();
//    productCard.editButton->setFocus();
//    QTest::mouseClick(&*productCard.editButton, Qt::LeftButton);
//
//    QCOMPARE(spy.count(),1);
//
//    QList<QVariant> arguments = spy.takeFirst();
//    auto result = qvariant_cast<ItemInfo>(arguments.at(0));
//    QCOMPARE(result,productCard.info);
//
//}
//
//void Test_ProductCard ::deleteButton()
//{
//    qRegisterMetaType<ItemInfo>();
//    auto productCard=ProductCard(ItemInfo(), nullptr);
//    productCard.info.undef= false;
//    productCard.show();
//    productCard.setFocus();
//
//    QSignalSpy spy(&productCard, SIGNAL(deleteItem(ItemInfo)));
//
//    QTest::mouseClick(&productCard, Qt::LeftButton);
//    QVERIFY(productCard.editButton->isVisible());
//    productCard.deleteButton->setFocus();
//    QTest::mouseClick(&*productCard.deleteButton, Qt::LeftButton);
//
//    QCOMPARE(spy.count(),1);
//
//    QList<QVariant> arguments = spy.takeFirst();
//    auto result = qvariant_cast<ItemInfo>(arguments.at(0));
//    QCOMPARE(result,productCard.info);
//
//}

QTEST_MAIN(Test_Products)
#include "TestProducts.moc"