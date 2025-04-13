#pragma once

#include "requestMaster.h"
#include "presentator.h"

#include <QWidget>
#include <QThread>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(RequestMaster* _requestMaster,Presentator* _presentator, bool with_network_thread = true,QWidget *parent = nullptr);
    ~MainWindow();

private: Q_SIGNALS:
    void startApplication();

private:
    bool with_network_thread;
    Presentator* presentator;
    QThread* m_networkThread;
    QScopedPointer<RequestMaster, QScopedPointerDeleter<RequestMaster>> requestMaster;
};