#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    presentator(new Presentator(this)),
    m_networkThread(new QThread(this))
    , requestMaster(new RequestMaster())
{
    presentator->setObjectName("presentator");

    setWindowTitle("Barbie shop");
    setWindowIcon(QIcon(":/image/cupcake"));
    setCentralWidget(presentator);
//    connect(this, &MainWindow::startApplication, presentator, &Presentator::startApplication);
//    emit startApplication();
    presentator->startApplication();

    requestMaster->moveToThread(m_networkThread);

    connect(presentator, &Presentator::startRequest, requestMaster.get(), &RequestMaster::onProcessRequest);
    connect(requestMaster.get(), &RequestMaster::timeout, presentator, &Presentator::timeout);
    connect(requestMaster.get(), &RequestMaster::gotHttpData, presentator, &Presentator::readHttpData);
    connect(requestMaster.get(), &RequestMaster::httpFinished, presentator, &Presentator::onHttpFinished);

    m_networkThread->start();
}

MainWindow::MainWindow(RequestMaster* _requestMaster,Presentator* _presentator,bool with_network_thread,QWidget *parent)
        : QMainWindow(parent),
          with_network_thread(with_network_thread),
          presentator(_presentator),
        requestMaster(_requestMaster)
{
    presentator->setObjectName("presentator");

    setWindowTitle("Barbie shop");
    setWindowIcon(QIcon(":/image/cupcake"));
    setCentralWidget(presentator);
//    connect(this, &MainWindow::startApplication, presentator, &Presentator::startApplication);
//    emit startApplication();
    presentator->startApplication();



    connect(presentator, &Presentator::startRequest, requestMaster.get(), &RequestMaster::onProcessRequest);
    connect(requestMaster.get(), &RequestMaster::timeout, presentator, &Presentator::timeout);
    connect(requestMaster.get(), &RequestMaster::gotHttpData, presentator, &Presentator::readHttpData);
    connect(requestMaster.get(), &RequestMaster::httpFinished, presentator, &Presentator::onHttpFinished);

    if (with_network_thread){
        m_networkThread = new QThread(this);
        requestMaster->moveToThread(m_networkThread);
        m_networkThread->start();
    }
}

MainWindow::~MainWindow()
{
    if (with_network_thread) {
        m_networkThread->quit();
        m_networkThread->wait();
    }
}
