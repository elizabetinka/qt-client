//
// Created by e.kravchenkova on 13.04.2025.
//

#pragma once
#include "../src/requestMaster.h"

class MockRequestMaster : public RequestMaster {

    void onProcessRequest(QUrl url,QString requestType, const QByteArray& data) override{
        slotInvoked=true;
        count+=1;
        //RequestMaster::onProcessRequest(url,requestType,data);
        _url=url;
        _requestType=requestType;
        _data=data;
}
public:
    bool slotInvoked = false;
    int count = 0;
    QUrl _url;
    QString _requestType;
    QByteArray _data;
};