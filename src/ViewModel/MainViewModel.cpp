#include "MainViewModel.h"

#include "qqmlcontext.h"

//#include <boost/signals2.hpp>

#include <iostream>

MainViewModel::MainViewModel(QObject* parent) :
   QObject(parent)
{
   mMainModel = std::make_unique<MainModel>();

   mQmlEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));

   QQmlContext* viewContextRoot = mQmlEngine.rootContext();
   viewContextRoot->setContextProperty("mainViewModel", this);

   // Connections
   mMainModel->ConnectionStatusChanged.connect([this]
   {
      Q_EMIT connectionChanged();
   });
}

void MainViewModel::connect()
{
   mMainModel->Connect();
}

bool MainViewModel::isConnected() const
{
   return mMainModel->IsConnected();
}