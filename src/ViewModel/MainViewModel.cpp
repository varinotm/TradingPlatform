#include "MainViewModel.h"

#include <qqmlcontext.h>
#include <qcoreapplication.h>

#include <iostream>

MainViewModel::MainViewModel(QObject* parent) :
   QObject(parent)
{
   mMainModel = std::make_unique<MainModel>();

   mQmlEngine.load(QUrl(QStringLiteral("qrc:/Resources/MainWindow.qml")));

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

void MainViewModel::quit()
{
   QCoreApplication::quit();
}

void MainViewModel::disconnect()
{
   mMainModel->Disconnect();
}

bool MainViewModel::isConnected() const
{
   return mMainModel->IsConnected();
}