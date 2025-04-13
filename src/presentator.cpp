//
// Created by e.kravchenkova on 04.04.2025.
//

#include "presentator.h"
#include "widgets/CircleImage.h"
#include "widgets/ClicableLabel.h"
#include "widgets/Products.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPropertyAnimation>
#include <QToolBar>


uint64_t Presentator::requestId = 0;

Presentator::Presentator(QWidget *parent) : QWidget(parent)
{
//    setMinimumSize(1024,768);
}

void Presentator::readHttpData(const QByteArray& data) {
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 2" << jsonError.errorString();
        sendToAnswerFunction(0,doc,false);
        return;
    }
    QJsonObject json = doc.object();
    qDebug()<<doc;
    uint64_t requestIdGet = json.value("responceId").toInteger();
    if (requstMapper.count(requestIdGet) == 0){
        qDebug() << "not so request" << jsonError.errorString();
        sendToAnswerFunction(requestIdGet,doc,false);
        return;
    }

    sendToAnswerFunction(requestIdGet,doc,true);
}

void Presentator::sendToAnswerFunction(uint64_t requstId,QJsonDocument doc, bool success){
    if (requstMapper[requstId] == RequestType::clientRegistration){
        checkAnswerToRegistrationRequest(doc, success);
    }
    else if (requstMapper[requstId] == RequestType::getClients){
        checkAnswerToGetClientsRequest(doc, success);
    }
    else if (requstMapper[requstId] == RequestType::clientModify){
        checkAnswerToModifyClientsRequest(doc, success);
    }
    else if (requstMapper[requstId] == RequestType::deleteClient){
        checkAnswerToDeleteClientsRequest(doc, success);
    }
    else if (requstMapper[requstId] == RequestType::getItems){
        checkAnswerToGetItemsRequest(doc, success);
    }
    else if (requstMapper[requstId] == RequestType::addItem){
        checkAnswerToAddItemsRequest(doc, success);
    }
    else if (requstMapper[requstId] == RequestType::modifyItem){
        checkAnswerToModifyItemsRequest(doc, success);
    }
    else if (requstMapper[requstId] == RequestType::deleteItem){
        checkAnswerToDeleteItemsRequest(doc, success);
    }
}

void Presentator::onHttpFinished() {
    for (auto b : currentButtons){
        b->setEnabled(true);
    }
}

void Presentator::startApplication() {
    background = new QLabel(this);
    background->setPixmap(QPixmap(":/image/background"));
    background->setScaledContents(true);
    background->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    background->setGeometry(this->rect());
    background->lower();

    LoginScreen();
//    CommonScreen();
}

void Presentator::LoginScreen() {
    clearLayout(this->layout());

    CircleImage* cupcake = new CircleImage(":/image/cupcake",this);
    cupcake->setMaximumSize(150,150);

    auto* mainLabel = new QLabel(this);
    mainLabel->setText(QLabel::tr("Entering"));
    mainLabel->setAlignment(Qt::AlignCenter);
    mainLabel->setObjectName("mainLabel");

    QLineEdit* login = new QLineEdit(this);
    login->setPlaceholderText(QLineEdit::tr("name"));

    QLineEdit* password = new QLineEdit(this);
    password->setPlaceholderText(QLineEdit::tr("password"));
    password->setEchoMode(QLineEdit::Password);

    QPushButton* button = new QPushButton(this);
    //button->setFixedWidth(100);
    button->setText(QPushButton::tr("Enter"));

    ClickableLabel* regisryLabel = new ClickableLabel(this);
    regisryLabel->setText(QLabel::tr("registry"));

    ClickableLabel* secondEnterLabel = new ClickableLabel(this);
    secondEnterLabel->setText(QLabel::tr("enter without account"));

    auto* labelsLayout = new QHBoxLayout();
    labelsLayout->addWidget(regisryLabel);
    labelsLayout->addSpacing(10);
    labelsLayout->addWidget(secondEnterLabel);
    labelsLayout->setAlignment(Qt::AlignCenter);


    auto* parentLayout = new QVBoxLayout();
    this->setLayout(parentLayout);
    parentLayout->addWidget(cupcake,0,Qt::AlignCenter);
    parentLayout->addSpacing(70);
    parentLayout->addWidget(mainLabel,0,Qt::AlignCenter);
    parentLayout->addWidget(login,0,Qt::AlignCenter);
    parentLayout->addWidget(password,0,Qt::AlignCenter);
    parentLayout->addSpacing(10);
    parentLayout->addWidget(button,0,Qt::AlignCenter);
    parentLayout->addLayout(labelsLayout);
    parentLayout->setAlignment(Qt::AlignCenter);

    setMinimumSize(parentLayout->minimumSize().expandedTo(QSize(800,600)));

    //currentLayout=parentLayout;

    currentWidgets.append({login,password});
    currentButtons.append(button);
    currentLabels.append({regisryLabel,secondEnterLabel});


    connect(button, &QPushButton::clicked, this, &Presentator::checkGetRequest);
    connect(regisryLabel, &ClickableLabel::clicked, this, &Presentator::startRegistryScreen);
    connect(secondEnterLabel, &ClickableLabel::clicked, this, &Presentator::CommonScreen);
}

void Presentator::resizeEvent(QResizeEvent *event) {
    background->setGeometry(this->rect());
    QWidget::resizeEvent(event);
}

void Presentator::startRegistryScreen() {
    clearLayout(this->layout());

    CircleImage* cupcake = new CircleImage(":/image/cupcake",this);
    cupcake->setMaximumSize(150,150);

    auto* mainLabel = new QLabel(this);
    mainLabel->setText(QLabel::tr("Registration"));
    mainLabel->setAlignment(Qt::AlignCenter);
    mainLabel->setObjectName("mainLabel");

    QLineEdit* login = new QLineEdit(this);
    login->setPlaceholderText(QLineEdit::tr("name"));
    QLineEdit* password = new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);
    password->setPlaceholderText(QLineEdit::tr("password"));

    QLineEdit* birthday = new QLineEdit(this);
   birthday->setPlaceholderText("31-12-2024");

    QPushButton* button = new QPushButton(this);
    //button->setFixedWidth(100);
    button->setText(QPushButton::tr("Registry"));

    ClickableLabel* returnLabel = new ClickableLabel(this);
    returnLabel->setText(QLabel::tr("return"));


    auto* labelsLayout = new QHBoxLayout();
    labelsLayout->addWidget(returnLabel);
    labelsLayout->setAlignment(Qt::AlignCenter);


    auto* parentLayout = new QVBoxLayout();
    this->setLayout(parentLayout);
    parentLayout->addWidget(cupcake,0,Qt::AlignCenter);
    parentLayout->addSpacing(70);
    parentLayout->addWidget(mainLabel,0,Qt::AlignCenter);
    parentLayout->addWidget(login,0,Qt::AlignCenter);
    parentLayout->addWidget(password,0,Qt::AlignCenter);
    parentLayout->addWidget(birthday,0,Qt::AlignCenter);
    parentLayout->addSpacing(10);
    parentLayout->addWidget(button,0,Qt::AlignCenter);
    parentLayout->addLayout(labelsLayout);
    parentLayout->setAlignment(Qt::AlignCenter);

    setMinimumSize(parentLayout->minimumSize().expandedTo(QSize(800,600)));

    //currentLayout=parentLayout;

    currentWidgets.append({login,password,birthday});
    currentButtons.append(button);
    currentLabels.append(returnLabel);

    connect(button, &QPushButton::clicked, this, &Presentator::checkRegistrationRequest);
    connect(returnLabel, &ClickableLabel::clicked, this, &Presentator::LoginScreen);
}

void Presentator::clearLayout(QLayout* layout, bool deleteWidgets)
{
    currentWidgets.clear();
    currentButtons.clear();
    currentLabels.clear();
    if (layout== NULL){
        return;
    }
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
    if (layout == this->layout()){
        delete layout;
    }
}

void Presentator::checkRegistrationRequest() {
    QString name = currentWidgets[0]->text().trimmed();

    QString password = currentWidgets[1]->text().trimmed();
    QString birthday = currentWidgets[2]->text().trimmed();

    if (name.isEmpty() || password.isEmpty() || birthday.isEmpty()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter name, password and birthday"));
        return;
    }

    QString json_string = QString("{ \"requestId\": %1 , \"nickname\": \"%2\", \"birthday\": \"%3\"}").arg(requestId).arg(name).arg(birthday);
    requstMapper[requestId]=RequestType::clientRegistration;
    requestId+=1;

    QByteArray jsonData = json_string.toUtf8();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    //qDebug()<<jsonDoc;
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 3" << jsonError.errorString();
        return;
    }
    const QString url = address+"/api/client";
    const QUrl newUrl = QUrl::fromUserInput(url);

    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(url, newUrl.errorString()));
        return;
    }

    for (auto v: currentButtons) {
        v->setEnabled(false);
    }

    emit startRequest(newUrl,"post", jsonData);
}

void Presentator::createModifyRequest() {
    QString name = currentWidgets[0]->text().trimmed();

    QString password = currentWidgets[1]->text().trimmed();
    QString birthday = currentWidgets[2]->text().trimmed();

    if (name.isEmpty() || password.isEmpty() || birthday.isEmpty()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter name, password and birthday"));
        return;
    }

    QString json_string = QString("{ \"requestId\": %1 , \"new_client\" : {\"id\": %2, \"nickname\": \"%3\", \"birthday\": \"%4\"}}").arg(requestId).arg(clientInfo.id).arg(name).arg(birthday);
    requstMapper[requestId]=RequestType::clientModify;
    requestId+=1;

    QByteArray jsonData = json_string.toUtf8();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    qDebug()<<jsonDoc;
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 6" << jsonError.errorString();
        return;
    }
    const QString url = address+"/api/client";
    const QUrl newUrl = QUrl::fromUserInput(url);

    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(url, newUrl.errorString()));
        return;
    }

    for (auto v: currentButtons) {
        v->setEnabled(false);
    }

    emit startRequest(newUrl,"put", jsonData);
}


void Presentator::checkGetRequest() {
    QString name = currentWidgets[0]->text().trimmed();

    QString password = currentWidgets[1]->text().trimmed();
    if (password != name){
        QMessageBox::information(this, tr("Error"),
                                 tr("Not valid password"));
        return;
    }

    if (name.isEmpty() || password.isEmpty()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter name, password and birthday"));
        return;
    }

    QString json_string = QString("{ \"requestId\": %1}").arg(requestId);

    requstMapper[requestId]=RequestType::getClients;
    requestId+=1;

    QByteArray jsonData = json_string.toUtf8();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    //qDebug()<<jsonDoc;
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 4" << jsonError.errorString();
        return;
    }
    const QString url = address+"/api/client";
    const QUrl newUrl = QUrl::fromUserInput(url);

    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(url, newUrl.errorString()));
        return;
    }

    for (auto v: currentButtons) {
        v->setEnabled(false);
    }

    emit startRequest(newUrl,"get", jsonData);
}

void Presentator::checkAnswerToRegistrationRequest(QJsonDocument doc, bool success) {
    if (!success){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid registration. Try again"));
        return;
    }
    QJsonObject json = doc.object();
    bool status = json.value("success").toBool();
    if (!status){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid registration. Try again"));
        return;
    }
    uint64_t id = json.value("id").toInteger();
    qDebug()<<id;
    QString name = currentWidgets[0]->text().trimmed();
    QString password = currentWidgets[1]->text().trimmed();
    QString birthday = currentWidgets[2]->text().trimmed();
    clientInfo={.undef=false,.id = id,.name=name,.birthday=birthday,.password=password};

    CommonScreen();
}

void Presentator::checkAnswerToModifyClientsRequest(QJsonDocument doc, bool success) {
    if (!success){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid modify. Try again"));
        CommonScreen();
        return;
    }
    QJsonObject json = doc.object();
    bool status = json.value("success").toBool();
    if (!status){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid modify. Try again"));
        CommonScreen();
        return;
    }

    QString name = currentWidgets[0]->text().trimmed();
    QString password = currentWidgets[1]->text().trimmed();
    QString birthday = currentWidgets[2]->text().trimmed();
    clientInfo={.undef=false,.id = clientInfo.id,.name=name,.birthday=birthday,.password=password};

    CommonScreen();
}

void Presentator::checkAnswerToDeleteClientsRequest(QJsonDocument doc, bool success) {
    if (!success){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid delete account. Try again"));
        CommonScreen();
        return;
    }
    QJsonObject json = doc.object();
    bool status = json.value("success").toBool();
    if (!status){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid delete account. Try again"));
        CommonScreen();
        return;
    }

    clientInfo.undef= true;

    CommonScreen();
}

void Presentator::checkAnswerToGetClientsRequest(QJsonDocument doc, bool success) {
    if (!success){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid entering. Try again"));
        return;
    }
    QJsonObject json = doc.object();
    QJsonArray clients = json.value("clients").toArray();

    QString name = currentWidgets[0]->text().trimmed();
    QString password = currentWidgets[1]->text().trimmed();
    QString birthday;
    uint64_t id =0;


    for (const QJsonValue str : clients)
    {
        auto obj = str.toObject();
        if (obj.value("nickname").toString() == name){
            birthday=obj.value("birthday").toString();
            id=obj.value("id").toInteger();
        }
    }
    if (birthday.isEmpty() || password != name){
        QMessageBox::information(this, tr("Error"),
                                 tr("No so clients. Try registration"));
        return;
    }
    clientInfo={.undef=false,.id = id,.name=name,.birthday=birthday,.password=password};
    CommonScreen();
}

void Presentator::checkAnswerToGetItemsRequest(QJsonDocument doc, bool success) {
    if (!success){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid loading items. Try again"));
        LoginScreen();
        return;
    }
    QJsonObject json = doc.object();
    QJsonArray items2 = json.value("items").toArray();
    items.clear();
    for (const QJsonValue str : items2)
    {
        auto obj = str.toObject();
        uint64_t count = obj.value("count").toInteger();
        auto item = obj.value("item").toObject();
        uint64_t id = item.value("id").toInteger();
        items.append(ItemInfo{.undef=false,.id=id,.name=item.value("name").toString(),.description=item.value("description").toString(),.category=item.value("category").toString(), .count=count});
    }
//    if (products != nullptr){
//        products->setItems(items);
//    }
CommonScreen();
}

void Presentator::CommonScreen() {
    clearLayout(this->layout());

    if (firstCommonScreen){startDownloadItems();firstCommonScreen= false;}

    QHBoxLayout* parentLayout = new QHBoxLayout();
    parentLayout->setContentsMargins(0,0,0,0);

    Products* products = new Products(items,this);
    connect(products,&Products::deleteItem,this,&Presentator::deleteItem);
    connect(products,&Products::modifyItem,this,&Presentator::modifyItem);

    sidePanel = new QWidget(this);
    QVBoxLayout* sideLayout = new QVBoxLayout();

    CircleImage* avatar = new CircleImage(":/image/avatar",this);
    avatar->setMaximumSize(150,150);

    auto* nameLabel = new QLabel(this);
    auto* birthdayLabel = new QLabel(this);

    if (clientInfo.undef){
        nameLabel->setText(QLabel::tr("Nickname: Unknown"));
        birthdayLabel->setText(QLabel::tr("Birthday: Unknown"));
    }
    else{
        nameLabel->setText(QLabel::tr("Nickname: ")+clientInfo.name);
        birthdayLabel->setText(QLabel::tr("Birthday: ")+clientInfo.birthday);
    }
    QPushButton* modifyButton= new QPushButton(this);
//    modifyButton->setFixedWidth(100);
    modifyButton->setText(QPushButton::tr("Redact"));

    QPushButton* deleteButton= new QPushButton(this);
//    deleteButton->setFixedWidth(100);
    deleteButton->setText(QPushButton::tr("Delete account"));

    ClickableLabel* exLabel = new ClickableLabel(this);
    exLabel->setText(QLabel::tr("exit"));
    exLabel->setObjectName("fromCommonExitLabel");

    sideLayout->setAlignment(Qt::AlignTop);
    sideLayout->addWidget(avatar,0,Qt::AlignTop);
    sideLayout->addWidget(nameLabel,0,Qt::AlignTop);
    sideLayout->addWidget(birthdayLabel,0,Qt::AlignTop);
    sideLayout->addWidget(modifyButton,0,Qt::AlignTop);
    sideLayout->addWidget(deleteButton,0,Qt::AlignTop);
    sideLayout->addWidget(exLabel,0,Qt::AlignCenter);
    sidePanel->setLayout(sideLayout);
    sidePanel->setFixedWidth(0);


//    buttonLayout->setContentsMargins(0, 0, 0, 0);
//    buttonLayout->setSpacing(5);

    QPushButton* clientButton = new QPushButton( this);

    clientButton->setIcon(QIcon(":/image/avatar"));
    clientButton->setFixedSize(30,30);
    clientButton->setIconSize(clientButton->size());

//    QPushButton* itemButton = new QPushButton(this);
//    itemButton->setIcon(QIcon(":/image/cupcake"));
//    itemButton->setFixedSize(30,30);
//    itemButton->setIconSize(itemButton->size());

//    menu->setContentsMargins(0,0,0,0);
//    menu->setSpacing(0);
    QWidget* menuWidget = new QWidget(this);
    QVBoxLayout* menu = new QVBoxLayout();
    menuWidget->setObjectName("menu");
    menu->setAlignment(Qt::AlignTop);
    menu->addSpacing(30);
    menu->addWidget(clientButton);
//    menu->addSpacing(5);
//    menu->addWidget(itemButton);

    menuWidget->setLayout(menu);

    parentLayout->setAlignment(Qt::AlignLeft);
    parentLayout->addWidget(products);
    parentLayout->addWidget(menuWidget);
    parentLayout->addWidget(sidePanel);


    this->setLayout(parentLayout);

    currentButtons.append({modifyButton,deleteButton,clientButton});
    currentLabels.append({exLabel});

    setMinimumSize(parentLayout->minimumSize().expandedTo(QSize(800,600)));
    connect(clientButton,&QPushButton::clicked,this,&Presentator::showSidePanel);
    connect(modifyButton,&QPushButton::clicked,this,&Presentator::modifyClient);
    connect(deleteButton,&QPushButton::clicked,this,&Presentator::deleteClient);
    connect(exLabel,&ClickableLabel::clicked,this,&Presentator::LoginScreen);
    connect(products,&Products::addItem,this,&Presentator::addItem);
}

void Presentator::timeout() {
    QMessageBox::information(this, tr("Error"),
                             tr("Timeout. Try again"));
    return;
}

void Presentator::showSidePanel() {
    if (sidePanel->width()==0){
        QPropertyAnimation* animation = new QPropertyAnimation(sidePanel, "maximumWidth");
        animation->setDuration(300);
        animation->setStartValue(0);
        animation->setEndValue(200);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else{
        QPropertyAnimation* animation = new QPropertyAnimation(sidePanel, "maximumWidth");
        animation->setDuration(300);
        animation->setStartValue(200);
        animation->setEndValue(0);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }

}

void Presentator::deleteClient() {
    if (clientInfo.undef){
        QMessageBox::information(this, tr("Error"),
                                 tr("You not entered user. Sorry!"));
        return;
    }
    QString json_string = QString("{ \"requestId\": %1 , \"clientId\": %2 }").arg(requestId).arg(clientInfo.id);
    requstMapper[requestId]=RequestType::deleteClient;
    requestId+=1;

    QByteArray jsonData = json_string.toUtf8();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    qDebug()<<jsonDoc;
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 6" << jsonError.errorString();
        return;
    }
    const QString url = address+"/api/client";
    const QUrl newUrl = QUrl::fromUserInput(url);

    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(url, newUrl.errorString()));
        return;
    }

    for (auto v: currentButtons) {
        v->setEnabled(false);
    }

    emit startRequest(newUrl,"delete", jsonData);
}

void Presentator::modifyClient() {
    if (clientInfo.undef){
        QMessageBox::information(this, tr("Error"),
                                 tr("You not entered user. Sorry!"));
        return;
    }
    clearLayout(this->layout());

    CircleImage* cupcake = new CircleImage(":/image/cupcake",this);
    cupcake->setMaximumSize(150,150);

    auto* mainLabel = new QLabel(this);
    mainLabel->setText(QLabel::tr("Enter new value of"));
    mainLabel->setAlignment(Qt::AlignCenter);
    mainLabel->setObjectName("mainLabel");

    QLineEdit* login = new QLineEdit(this);
    login->setPlaceholderText(clientInfo.name);
    QLineEdit* password = new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);
    password->setPlaceholderText(QLineEdit::tr("password"));

    QLineEdit* birthday = new QLineEdit(this);
    birthday->setPlaceholderText(clientInfo.birthday);

    QPushButton* button = new QPushButton(this);
    //button->setFixedWidth(100);
    button->setText(QPushButton::tr("Modify"));

    ClickableLabel* returnLabel = new ClickableLabel(this);
    returnLabel->setText(QLabel::tr("return"));


    auto* labelsLayout = new QHBoxLayout();
    labelsLayout->addWidget(returnLabel);
    labelsLayout->setAlignment(Qt::AlignCenter);


    auto* parentLayout = new QVBoxLayout();
    this->setLayout(parentLayout);
    parentLayout->addWidget(cupcake,0,Qt::AlignCenter);
    parentLayout->addSpacing(70);
    parentLayout->addWidget(mainLabel,0,Qt::AlignCenter);
    parentLayout->addWidget(login,0,Qt::AlignCenter);
    parentLayout->addWidget(password,0,Qt::AlignCenter);
    parentLayout->addWidget(birthday,0,Qt::AlignCenter);
    parentLayout->addSpacing(10);
    parentLayout->addWidget(button,0,Qt::AlignCenter);
    parentLayout->addLayout(labelsLayout);
    parentLayout->setAlignment(Qt::AlignCenter);

    setMinimumSize(parentLayout->minimumSize().expandedTo(QSize(800,600)));

    //currentLayout=parentLayout;

    currentWidgets.append({login,password,birthday});
    currentButtons.append(button);
    currentLabels.append(returnLabel);

    connect(button, &QPushButton::clicked, this, &Presentator::createModifyRequest);
    connect(returnLabel, &ClickableLabel::clicked, this, &Presentator::CommonScreen);
}

void Presentator::startDownloadItems() {
    QString json_string = QString("{ \"requestId\": %1}").arg(requestId);

    requstMapper[requestId]=RequestType::getItems;
    requestId+=1;

    QByteArray jsonData = json_string.toUtf8();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    //qDebug()<<jsonDoc;
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 4" << jsonError.errorString();
        return;
    }
    const QString url = address+"/api/item";
    const QUrl newUrl = QUrl::fromUserInput(url);

    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(url, newUrl.errorString()));
        return;
    }

    for (auto v: currentButtons) {
        v->setEnabled(false);
    }

    emit startRequest(newUrl,"get", jsonData);
}

void Presentator::addItem() {
    if (clientInfo.undef){
        QMessageBox::information(this, tr("Error"),
                                 tr("You not entered user. Sorry!"));
        return;
    }
    clearLayout(this->layout());

    CircleImage* cupcake = new CircleImage(":/image/cupcake",this);
    cupcake->setMaximumSize(150,150);

    auto* mainLabel = new QLabel(this);
    mainLabel->setText(QLabel::tr("Enter"));
    mainLabel->setAlignment(Qt::AlignCenter);
    mainLabel->setObjectName("mainLabel");

    QLineEdit* login = new QLineEdit(this);
    login->setPlaceholderText(QLineEdit::tr("name"));
    QLineEdit* password = new QLineEdit(this);
    password->setPlaceholderText(QLineEdit::tr("description"));

    QLineEdit* birthday = new QLineEdit(this);
    birthday->setPlaceholderText(QLineEdit::tr("category"));
    QLineEdit* count = new QLineEdit(this);
    count->setPlaceholderText(QLineEdit::tr("count"));

    QPushButton* button = new QPushButton(this);
    //button->setFixedWidth(100);
    button->setText(QPushButton::tr("Enter"));

    ClickableLabel* returnLabel = new ClickableLabel(this);
    returnLabel->setText(QLabel::tr("return"));

    QLabel* label = new QLabel();
    label->setText(QLabel::tr("*valid value of category is: unknown,beauty,technic,clothes"));

    auto* labelsLayout = new QHBoxLayout();
    labelsLayout->addWidget(returnLabel);
    labelsLayout->setAlignment(Qt::AlignCenter);


    auto* parentLayout = new QVBoxLayout();
    this->setLayout(parentLayout);
    parentLayout->addWidget(cupcake,0,Qt::AlignCenter);
    parentLayout->addSpacing(70);
    parentLayout->addWidget(mainLabel,0,Qt::AlignCenter);
    parentLayout->addWidget(login,0,Qt::AlignCenter);
    parentLayout->addWidget(password,0,Qt::AlignCenter);
    parentLayout->addWidget(birthday,0,Qt::AlignCenter);
    parentLayout->addWidget(count,0,Qt::AlignCenter);
    parentLayout->addSpacing(10);
    parentLayout->addWidget(button,0,Qt::AlignCenter);
    parentLayout->addLayout(labelsLayout);
    parentLayout->addWidget(label);
    parentLayout->setAlignment(Qt::AlignCenter);

    setMinimumSize(parentLayout->minimumSize().expandedTo(QSize(800,600)));

    //currentLayout=parentLayout;

    currentWidgets.append({login,password,birthday,count});
    currentButtons.append(button);
    currentLabels.append(returnLabel);

    connect(button, &QPushButton::clicked, this, &Presentator::createAddItemRequest);
    connect(returnLabel, &ClickableLabel::clicked, this, &Presentator::CommonScreen);
}

void Presentator::createAddItemRequest() {
    QString name = currentWidgets[0]->text().trimmed();

    QString description = currentWidgets[1]->text().trimmed();
    QString category = currentWidgets[2]->text().trimmed();
    QString count = currentWidgets[3]->text().trimmed();


    if (name.isEmpty() || count.isEmpty()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter name and count"));
        return;
    }
    bool ok;
    uint64_t count_int = count.QString::toULongLong(&ok);
    if (!ok || count_int==0){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter valid count. 0 is not!"));
        qDebug() << "bad count_int";
        return;
    }


    QString json_string = QString("{ \"requestId\": %1 , \"name\": \"%2\", \"description\": \"%3\", \"count\": %4 , \"category\": \"%5\"}").arg(requestId).arg(name).arg(description).arg(count_int).arg(category);
    requstMapper[requestId]=RequestType::addItem;
    requestId+=1;

    QByteArray jsonData = json_string.toUtf8();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    //qDebug()<<jsonDoc;
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 3" << jsonError.errorString();
        return;
    }
    const QString url = address+"/api/item";
    const QUrl newUrl = QUrl::fromUserInput(url);

    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(url, newUrl.errorString()));
        return;
    }

    for (auto v: currentButtons) {
        v->setEnabled(false);
    }

    emit startRequest(newUrl,"post", jsonData);
}

void Presentator::checkAnswerToAddItemsRequest(QJsonDocument doc, bool success) {
    if (!success){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid adding. Try again"));
        return;
    }
    QJsonObject json = doc.object();
    bool status = json.value("success").toBool();
    if (!status){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid adding. Try again"));
        return;
    }
    uint64_t id = json.value("id").toInteger();
    QString name = currentWidgets[0]->text().trimmed();

    QString description = currentWidgets[1]->text().trimmed();
    QString category = currentWidgets[2]->text().trimmed();
    uint64_t count = currentWidgets[3]->text().trimmed().QString::toULongLong();
    //items.append(ItemInfo{.undef=false,.id = id,.name=name,.description=description,.category=category,.count=count});
    firstCommonScreen= true;
//    if (products != nullptr){
//        products->appendItems({ItemInfo{.undef=false,.id = id,.name=name,.description=description,.category=category,.count=count}});
//    }
CommonScreen();
}

void Presentator::modifyItem(ItemInfo info) {
    if (clientInfo.undef){
        QMessageBox::information(this, tr("Error"),
                                 tr("You not entered user. Sorry!"));
        return;
    }
    clearLayout(this->layout());

    CircleImage* cupcake = new CircleImage(":/image/cupcake",this);
    cupcake->setMaximumSize(150,150);

    auto* mainLabel = new QLabel(this);
    mainLabel->setText(QLabel::tr("Enter"));
    mainLabel->setAlignment(Qt::AlignCenter);
    mainLabel->setObjectName("mainLabel");

    QLineEdit* login = new QLineEdit(this);
    login->setPlaceholderText(info.name);
    QLineEdit* password = new QLineEdit(this);
    password->setPlaceholderText(info.description);

    QLineEdit* birthday = new QLineEdit(this);
    birthday->setPlaceholderText(info.category);
    QLineEdit* count = new QLineEdit(this);
    count->setPlaceholderText(QString::number(info.count));

    QPushButton* button = new QPushButton(this);
    //button->setFixedWidth(100);
    button->setText(QPushButton::tr("Enter"));

    ClickableLabel* returnLabel = new ClickableLabel(this);
    returnLabel->setText(QLabel::tr("return"));

    QLabel* label = new QLabel();
    label->setText(QLabel::tr("*valid value of category is: unknown,beauty,technic,clothes"));

    auto* labelsLayout = new QHBoxLayout();
    labelsLayout->addWidget(returnLabel);
    labelsLayout->setAlignment(Qt::AlignCenter);


    auto* parentLayout = new QVBoxLayout();
    this->setLayout(parentLayout);
    parentLayout->addWidget(cupcake,0,Qt::AlignCenter);
    parentLayout->addSpacing(70);
    parentLayout->addWidget(mainLabel,0,Qt::AlignCenter);
    parentLayout->addWidget(login,0,Qt::AlignCenter);
    parentLayout->addWidget(password,0,Qt::AlignCenter);
    parentLayout->addWidget(birthday,0,Qt::AlignCenter);
    parentLayout->addWidget(count,0,Qt::AlignCenter);
    parentLayout->addSpacing(10);
    parentLayout->addWidget(button,0,Qt::AlignCenter);
    parentLayout->addLayout(labelsLayout);
    parentLayout->addWidget(label);
    parentLayout->setAlignment(Qt::AlignCenter);

    setMinimumSize(parentLayout->minimumSize().expandedTo(QSize(800,600)));

    //currentLayout=parentLayout;

    currentWidgets.append({login,password,birthday,count});
    currentButtons.append(button);
    currentLabels.append(returnLabel);

    curItemId=info.id;
    connect(button, &QPushButton::clicked, this, &Presentator::createModifyItemRequest);
    connect(returnLabel, &ClickableLabel::clicked, this, &Presentator::CommonScreen);
}

void Presentator::createModifyItemRequest() {
    QString name = currentWidgets[0]->text().trimmed();

    QString description = currentWidgets[1]->text().trimmed();
    QString category = currentWidgets[2]->text().trimmed();
    QString count = currentWidgets[3]->text().trimmed();


    if (name.isEmpty() || count.isEmpty()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter name and count"));
        return;
    }
    bool ok;
    uint64_t count_int = count.QString::toULongLong(&ok);
    if (!ok || count_int==0){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter valid count. 0 is not!"));
        qDebug() << "bad count_int";
        return;
    }


    QString json_string = QString("{ \"requestId\": %1 , \"new_item\": {\"item\": { \"id\": %6, \"name\": \"%2\" , \"description\": \"%3\" ,\"category\": \"%4\"}, \"count\": %5}}").arg(requestId).arg(name).arg(description).arg(category).arg(count_int).arg(curItemId);
    requstMapper[requestId]=RequestType::modifyItem;
    requestId+=1;

    QByteArray jsonData = json_string.toUtf8();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    qDebug()<<jsonDoc;
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 3" << jsonError.errorString();
        return;
    }
    const QString url = address+"/api/item";
    const QUrl newUrl = QUrl::fromUserInput(url);

    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(url, newUrl.errorString()));
        return;
    }

    for (auto v: currentButtons) {
        v->setEnabled(false);
    }

    emit startRequest(newUrl,"put", jsonData);
}

void Presentator::checkAnswerToModifyItemsRequest(QJsonDocument doc, bool success) {
    if (!success){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid changing. Try again"));
        return;
    }
    QJsonObject json = doc.object();
    bool status = json.value("success").toBool();
    if (!status){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid changing. Try again"));
        return;
    }
    uint64_t id = curItemId;
    QString name = currentWidgets[0]->text().trimmed();

    QString description = currentWidgets[1]->text().trimmed();
    QString category = currentWidgets[2]->text().trimmed();
    uint64_t count = currentWidgets[3]->text().trimmed().QString::toULongLong();
    firstCommonScreen= true;
//    items.append(ItemInfo{.undef=false,.id = id,.name=name,.description=description,.category=category,.count=count});

//    if (products != nullptr){
//        products->appendItems({ItemInfo{.undef=false,.id = id,.name=name,.description=description,.category=category,.count=count}});
//    }
    CommonScreen();
}

void Presentator::createDeleteItemRequest() {
    if (clientInfo.undef){
        QMessageBox::information(this, tr("Error"),
                                 tr("You not entered user. Sorry!"));
        return;
    }
    QString count = currentWidgets[0]->text().trimmed();


    if (count.isEmpty()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter count"));
        return;
    }
    bool ok;
    uint64_t count_int = count.QString::toULongLong(&ok);
    if (!ok || count_int==0){
        QMessageBox::information(this, tr("Error"),
                                 tr("Enter valid count. 0 is not!"));
        qDebug() << "bad count_int";
        return;
    }

    QString json_string = QString("{ \"requestId\": %1 , \"itemId\": %2, \"count\": %3 }").arg(requestId).arg(curItemId).arg(count_int);
    requstMapper[requestId]=RequestType::deleteItem;
    requestId+=1;

    QByteArray jsonData = json_string.toUtf8();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    qDebug()<<jsonDoc;
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "error parsing JSON 6" << jsonError.errorString();
        return;
    }
    const QString url = address+"/api/item";
    const QUrl newUrl = QUrl::fromUserInput(url);

    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(url, newUrl.errorString()));
        return;
    }

    for (auto v: currentButtons) {
        v->setEnabled(false);
    }

    emit startRequest(newUrl,"delete", jsonData);
}

void Presentator::deleteItem(ItemInfo info) {
    if (clientInfo.undef){
        QMessageBox::information(this, tr("Error"),
                                 tr("You not entered user. Sorry!"));
        return;
    }
    clearLayout(this->layout());

    CircleImage* cupcake = new CircleImage(":/image/cupcake",this);
    cupcake->setMaximumSize(150,150);

    auto* mainLabel = new QLabel(this);
    mainLabel->setText(QLabel::tr("Enter count of deleting items"));
    mainLabel->setAlignment(Qt::AlignCenter);
    mainLabel->setObjectName("mainLabel");

    QLineEdit* login = new QLineEdit(this);
    login->setPlaceholderText(QString::number(info.count));

    QPushButton* button = new QPushButton(this);
//button->setFixedWidth(100);
    button->setText(QPushButton::tr("Enter"));

    ClickableLabel* returnLabel = new ClickableLabel(this);
    returnLabel->setText(QLabel::tr("return"));

    auto* labelsLayout = new QHBoxLayout();
    labelsLayout->addWidget(returnLabel);
    labelsLayout->setAlignment(Qt::AlignCenter);


    auto* parentLayout = new QVBoxLayout();
    this->setLayout(parentLayout);
    parentLayout->addWidget(cupcake,0,Qt::AlignCenter);
    parentLayout->addSpacing(70);
    parentLayout->addWidget(mainLabel,0,Qt::AlignCenter);
    parentLayout->addWidget(login,0,Qt::AlignCenter);
    parentLayout->addSpacing(10);
    parentLayout->addWidget(button,0,Qt::AlignCenter);
    parentLayout->addLayout(labelsLayout);
    parentLayout->setAlignment(Qt::AlignCenter);

    setMinimumSize(parentLayout->minimumSize().expandedTo(QSize(800,600)));

    //currentLayout=parentLayout;

    currentWidgets.append({login});
    currentButtons.append(button);
    currentLabels.append(returnLabel);

    curItemId=info.id;
    connect(button, &QPushButton::clicked, this, &Presentator::createDeleteItemRequest);
    connect(returnLabel, &ClickableLabel::clicked, this, &Presentator::CommonScreen);
}

void Presentator::checkAnswerToDeleteItemsRequest(QJsonDocument doc, bool success) {
    if (!success){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid changing. Try again"));
        return;
    }
    QJsonObject json = doc.object();
    bool status = json.value("success").toBool();
    if (!status){
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid changing. Try again"));
        return;
    }
    firstCommonScreen= true;
//    items.append(ItemInfo{.undef=false,.id = id,.name=name,.description=description,.category=category,.count=count});

//    if (products != nullptr){
//        products->appendItems({ItemInfo{.undef=false,.id = id,.name=name,.description=description,.category=category,.count=count}});
//    }
    CommonScreen();
}


//void Presentator::Cleaner() {
//    // Шаг 1: Удаляем все элементы из компоновщика
//    QLayoutItem* item;
//    while ((item = currentLayout->takeAt(0)) != nullptr) {
//        if (QWidget* widget = item->widget()) {
//            delete widget; // Удаляем виджет
//        } else if (QLayout* childLayout = item->layout()) {
//            delete childLayout; // Удаляем вложенный компоновщик
//        }
//        delete item; // Удаляем сам элемент компоновщика
//    }
//
//// Шаг 2: Удаляем компоновщик из родительского виджета
//    setLayout(nullptr);
//
//// Шаг 3: Удаляем сам компоновщик
//    delete currentLayout;
//}
