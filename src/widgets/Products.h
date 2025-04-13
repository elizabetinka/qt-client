//
// Created by e.kravchenkova on 07.04.2025.
//


#pragma once
#include <QWidget>
#include <QScrollBar>
#include <QScrollArea>
#include "ProductCard.h"


class Products : public QWidget {
Q_OBJECT

public:
    explicit Products(QVector<ItemInfo> items,QWidget *parent = nullptr) : QWidget(parent) {
        addCard=new ProductCard(ItemInfo(),this, ":/image/add");
        connect(addCard,&ProductCard::addItem,this,&Products::addItem);
        card.clear();
        for (int i=0;i<items.size(); ++i){
            card.append(new ProductCard(items[i],this));
            connect(card[i],&ProductCard::deleteItem,this,&Products::deleteItem);
            connect(card[i],&ProductCard::modifyItem,this,&Products::modifyItem);
        }
        print();

    }

Q_SIGNALS:
    void addItem();
    void deleteItem(ItemInfo info);
    void modifyItem(ItemInfo info);

private:
    const uint64_t item_in_row = 3;
    int visibleRows = 2;
    QVector<ProductCard*> card;
    ProductCard* addCard = nullptr;
    QGridLayout* gridLayout= nullptr;

    void print(){
        QLabel* mainLabel = new QLabel(this);
        mainLabel->setText(QLabel::tr("Catalog"));
        mainLabel->setAlignment(Qt::AlignCenter);
        mainLabel->setObjectName("mainLabel2");

        gridLayout = new QGridLayout();
        for (int i=0;i<card.size();++i){
            card[i]->setFixedSize(card[i]->maximumSize());
            gridLayout->addWidget(card[i],i/item_in_row, i%item_in_row);
        }
        addCard->setFixedSize(addCard->maximumSize());
        gridLayout->addWidget(addCard,card.size()/item_in_row,card.size()%item_in_row);
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(20);
        QWidget* gridWidget = new QWidget(this);
        gridWidget->setObjectName("gridWidget");
        gridWidget->setLayout(gridLayout);
        setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidget(gridWidget);
        scrollArea->setWidgetResizable(true);

        int spacing = gridLayout->spacing();
        QMargins margins = gridLayout->contentsMargins();
        int fixedHeight = addCard->height() * visibleRows + spacing * (visibleRows - 1)+ margins.top() + margins.bottom();

        //scrollArea->setFixedHeight(2*addCard->height());

        QVBoxLayout* parentLayout = new QVBoxLayout();
        parentLayout->addWidget(mainLabel);
        parentLayout->addSpacing(30);
        parentLayout->addWidget(scrollArea);
        setLayout(parentLayout);
    }

};




