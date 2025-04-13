//
// Created by e.kravchenkova on 13.04.2025.
//

#pragma once

#include "../src/presentator.h"

class MockPresentator : public Presentator {

    void readHttpData(const QByteArray& data) override{
        readHttpDataInvoked=true;
        readHttpDataCount+=1;
        _data=data;
        //Presentator::readHttpData(data);
    }
    void onHttpFinished() override{
        onHttpFinishedInvoked=true;
        onHttpFinishedCount+=1;
        //Presentator::onHttpFinished();
    }
    void timeout() override {
        timeoutInvoked = true;
        timeoutDataCount+=1;
        //Presentator::timeout();
    }

public:
    bool readHttpDataInvoked = false;
    int readHttpDataCount = 0;

    bool onHttpFinishedInvoked = false;
    int onHttpFinishedCount = 0;

    bool timeoutInvoked = false;
    int timeoutDataCount = 0;
\
    QByteArray _data;

    MockPresentator(QWidget *parent) : Presentator(parent)
    {
    }
};
