//
// Created by e.kravchenkova on 07.04.2025.
//
#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>

struct ItemInfo{
    bool undef = true;
    uint64_t id = 0;
    QString name;
    QString description;
    QString category;
    uint64_t count;
};

inline bool operator==(const ItemInfo& lhs, const ItemInfo& rhs){
    return lhs.id==rhs.id && lhs.count==rhs.count && lhs.description==rhs.description && lhs.name==rhs.name && lhs.category == rhs.category && lhs.undef==rhs.undef;
}

class ProductCard : public QFrame {
Q_OBJECT
public:
    Q_SIGNALS:
        void addItem();
        void deleteItem(ItemInfo info);
        void modifyItem(ItemInfo info);

private Q_SLOTS:
        void deleteItemSlot();
        void modifyItemSlot();
public:
    explicit ProductCard(ItemInfo info, QWidget *parent = nullptr,QString image_path = ":/image/loading") : QFrame(parent),image_path(image_path),
                                                                                                            info(info){
        setFrameStyle(QFrame::Box|QFrame::Plain);
//        setFrameShape(QFrame::StyledPanel);
//        setFrameShadow(QFrame::Raised);
        setLineWidth(2);
        setAttribute(Qt::WA_StyledBackground);

        // Основной вертикальный layout
        //setMaximumSize(150,150);
        QWidget* mainWidget = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout();
        mainLayout->setContentsMargins(10, 10, 10, 10);

        // Пример информационных элементов карточки
        imageLabel = new QLabel(this);
        imageLabel->setMaximumSize(QSize(150,150));
        imageLabel->setMinimumSize(100,100);
//        imageLabel->setContentsMargins(5,5,5,5);
        imageLabel->setScaledContents(true);

        setMinimumSize(170,170);
        setMaximumSize(200,220);
//        imageLabel->setStyleSheet("background-color: lightgray;"); // пример оформления
if (info.undef){
    imageLabel->setPixmap(QPixmap(image_path));
    nameLabel = new QLabel(QLabel::tr("name"), this);
    descriptionLabel = new QLabel(QLabel::tr("Description..."), this);
    categoryLabel = new QLabel(QLabel::tr("category"), this);
    countLabel = new QLabel(QLabel::tr("count"), this);
}
else{
    imageLabel->setPixmap(QPixmap(":/image/kiev"));
    nameLabel = new QLabel(info.name, this);
    descriptionLabel = new QLabel(info.description, this);
    categoryLabel = new QLabel(info.category, this);
    countLabel = new QLabel(QString::number(info.count), this);
}

        QWidget* descW = new QWidget(this);
        QVBoxLayout* desc = new QVBoxLayout();
        desc->setAlignment(Qt::AlignCenter);
        desc->addWidget(nameLabel, 0,Qt::AlignCenter);
        desc->addWidget(descriptionLabel, 0,Qt::AlignCenter);
        desc->addWidget(categoryLabel, 0,Qt::AlignCenter);
        desc->addWidget(countLabel, 0,Qt::AlignCenter);
        // Контейнер для кнопок (редактирование и удаление)
        buttonWidget = new QWidget(this);
        QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
        buttonLayout->setContentsMargins(0, 0, 0, 0);
        buttonLayout->setSpacing(5);

        editButton = new QPushButton( this);

        editButton->setIcon(QIcon(":/image/setting"));
        editButton->setFixedSize(50,50);
        editButton->setIconSize(editButton->size());
        deleteButton = new QPushButton(this);
        deleteButton->setIcon(QIcon(":/image/delete"));
        deleteButton->setFixedSize(50,50);
        deleteButton->setIconSize(deleteButton->size());

        buttonLayout->addWidget(editButton);
        buttonLayout->addWidget(deleteButton);

        // Изначально скрываем кнопки
        buttonWidget->hide();
        desc->addWidget(buttonWidget);
        descW->setLayout(desc);
//        descW->setObjectName("card");

        mainLayout->setSpacing(5);
        mainLayout->addWidget(imageLabel, 0,Qt::AlignCenter);
        mainLayout->setSpacing(5);
        mainLayout->addWidget(descW);

        mainWidget->setLayout(mainLayout);
        mainWidget->setObjectName("card");
        mainWidget->lower();

        QVBoxLayout* parentLayout = new QVBoxLayout();
        parentLayout->addWidget(mainWidget);
        setLayout(parentLayout);

        setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
        connect(editButton, &QPushButton::clicked,this, &ProductCard::modifyItemSlot);
        connect(deleteButton, &QPushButton::clicked,this, &ProductCard::deleteItemSlot);
    }

public:

protected:
    void mousePressEvent(QMouseEvent *event) override {

        if (image_path==":/image/add"){
            emit addItem();
            return;
        }

        nameLabel->setHidden(!nameLabel->isHidden());
        descriptionLabel->setHidden(!descriptionLabel->isHidden());
        categoryLabel->setHidden(!categoryLabel->isHidden());
        countLabel->setHidden(!countLabel->isHidden());
        buttonWidget->setVisible(!buttonWidget->isVisible());
        QWidget::mousePressEvent(event);

    }
//    void resizeEvent(QResizeEvent* event) override{
//        QWidget::resizeEvent(event);
//        QSize new_size = event->size();
//    }

private:
    QWidget *buttonWidget;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QString image_path=":/image/loading";
    QLabel *imageLabel;
    QLabel *nameLabel;
    QLabel *descriptionLabel;
    QLabel *categoryLabel;
    QLabel *countLabel;
    ItemInfo info;

};

