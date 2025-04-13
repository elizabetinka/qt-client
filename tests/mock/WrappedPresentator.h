//
// Created by e.kravchenkova on 13.04.2025.
//


#pragma once

#define private public
#include "../src/presentator.h"
#undef private

class WrappedPresentator : public Presentator {

public:
    int readHttpDataCount = 0;
    int onHttpFinishedCount = 0;
    int timeoutDataCount = 0;
    int startRegistryScreenCount=0;
    int LoginScreenCount=0;
    int CommonScreenCount=0;
    int checkRegistrationRequestCount=0;
    int createModifyRequestCount=0;
    int checkGetRequestCount=0;
    int showSidePanelCount=0;
    int modifyClientCount=0;
    int deleteClientCount=0;
    int addItemCount=0;
    int createAddItemRequestCount=0;
    int createModifyItemRequestCount=0;
    int createDeleteItemRequestCount=0;
    int startDownloadItemsCount=0;
    int deleteItemCount=0;
    int modifyItemCount=0;

    WrappedPresentator(QWidget *parent) : Presentator(parent)
    {
    }

    void LoginScreen() override {
        LoginScreenCount+=1;
        Presentator::LoginScreen();
    }

    void readHttpData(const QByteArray& data) override{
        readHttpDataCount+=1;
        Presentator::readHttpData(data);
    }
    void onHttpFinished() override{
        onHttpFinishedCount+=1;
        Presentator::onHttpFinished();
    }
    void timeout() override {
        timeoutDataCount+=1;
        Presentator::timeout();
    }

    void startRegistryScreen() override {
        startRegistryScreenCount+=1;
        Presentator::startRegistryScreen();
    }

    void CommonScreen() override {
        CommonScreenCount+=1;
        Presentator::CommonScreen();
    }
    void checkRegistrationRequest() override {
        checkRegistrationRequestCount+=1;
        Presentator::checkRegistrationRequest();
    }
    void createModifyRequest() override {
        createModifyRequestCount+=1;
        Presentator::createModifyRequest();
    }
    void checkGetRequest() override {
        checkGetRequestCount+=1;
        Presentator::checkGetRequest();
    }
    void showSidePanel() override {
        showSidePanelCount+=1;
        Presentator::showSidePanel();
    }
    void modifyClient() override {
        modifyClientCount+=1;
        Presentator::modifyClient();
    }
    void deleteClient() override {
        deleteClientCount+=1;
        Presentator::deleteClient();
    }
    void addItem() override {
        addItemCount+=1;
        Presentator::addItem();
    }
    void createAddItemRequest() override {
        createAddItemRequestCount+=1;
        Presentator::createAddItemRequest();
    }
    void createModifyItemRequest() override {
        createModifyItemRequestCount+=1;
        Presentator::createModifyItemRequest();
    }
    void createDeleteItemRequest() override {
        createDeleteItemRequestCount+=1;
        Presentator::createDeleteItemRequest();
    }

    void startDownloadItems() override {
        startDownloadItemsCount+=1;
        Presentator::startDownloadItems();
    }
    void deleteItem(ItemInfo info) override {
        deleteItemCount +=1;
        Presentator::deleteItem(info);
    }
    void modifyItem(ItemInfo info) override {
        modifyItemCount+=1;
        Presentator::modifyItem(info);
    }
};
