//
// Created by e.kravchenkova on 04.04.2025.
//

#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <unordered_map>
#include "widgets/Products.h"
#include "widgets/ClicableLabel.h"

//enum ScreenType {
//    LOGIN,
//    COMMON,
//    REGISTRY,
//};

enum RequestType {
    clientRegistration,
    getClients,
    clientModify,
    deleteClient,
    getItems,
    modifyItem,
    addItem,
    deleteItem,
};

struct ClientInfo{
    bool undef = true;
    uint64_t id = 0;
    QString name;
    QString birthday;
    QString password;
};



class Presentator : public QWidget {
Q_OBJECT

public:
    Presentator(QWidget *parent);
    ~Presentator() = default;

Q_SIGNALS:
    void startRequest(QUrl request,QString requestType, const QByteArray& data);

public Q_SLOTS:
    void startApplication();
    virtual void readHttpData(const QByteArray& data);
    virtual void onHttpFinished();
    virtual void timeout();

protected Q_SLOTS:

    virtual void deleteItem(ItemInfo info);
    virtual void modifyItem(ItemInfo info);



protected:
    void resizeEvent(QResizeEvent *event) override;

    virtual void startRegistryScreen();

    virtual void LoginScreen();

    virtual void CommonScreen();

    virtual void checkRegistrationRequest();

    virtual void createModifyRequest();

    virtual void checkGetRequest();

    virtual void showSidePanel();

    virtual void modifyClient();

    virtual void deleteClient();

    virtual void addItem();

    virtual void createAddItemRequest();

    virtual void createModifyItemRequest();

    virtual void createDeleteItemRequest();

    virtual void startDownloadItems();

private:
    QLabel* background;

    QWidget* sidePanel;

    QVector<QLineEdit*> currentWidgets;
    QVector<QPushButton*> currentButtons;
    QVector<ClickableLabel*> currentLabels;
    QVector<ItemInfo> items;
    QString address="http://localhost:8080";
    static uint64_t requestId;
    std::unordered_map<uint64_t,RequestType> requstMapper;
    bool firstCommonScreen = true;
    ClientInfo clientInfo;
    uint64_t curItemId=0;


    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    void checkAnswerToRegistrationRequest(QJsonDocument doc, bool success = true);
    void checkAnswerToGetClientsRequest(QJsonDocument doc, bool success = true);
    void checkAnswerToModifyClientsRequest(QJsonDocument doc, bool success = true);
    void checkAnswerToDeleteClientsRequest(QJsonDocument doc, bool success = true);

    void checkAnswerToGetItemsRequest(QJsonDocument doc, bool success = true);
    void checkAnswerToAddItemsRequest(QJsonDocument doc, bool success = true);
    void checkAnswerToModifyItemsRequest(QJsonDocument doc, bool success = true);
    void checkAnswerToDeleteItemsRequest(QJsonDocument doc, bool success = true);

    void sendToAnswerFunction(uint64_t requstId,QJsonDocument doc, bool success = true);
};

