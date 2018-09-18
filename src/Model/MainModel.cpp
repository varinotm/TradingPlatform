#include "MainModel.h"

#include "IBWrapper.h"

#include <boost\shared_ptr.hpp>

MainModel::MainModel()
{
   mIBWrapper = std::make_shared<IBWrapper>();

   // Connections
   mIBWrapper->ConnectionStatusChanged.connect([this]
   {
      ConnectionStatusChanged();
   });
}

void MainModel::Connect()
{
   mIBWrapper->Connect("127.0.0.1", 4002, 1);
}

bool MainModel::IsConnected() const
{
   return mIBWrapper->IsConnected();
}