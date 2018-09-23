#include "MainModel.h"

#include "IBWrapper.h"
#include "Data\ContractRepository.h"

#include <boost\shared_ptr.hpp>

MainModel::MainModel()
{
   mIBWrapper = std::make_shared<IBWrapper>();
   mContractRepository = std::make_shared<ContractRepository>();

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

void MainModel::Disconnect()
{
   mIBWrapper->Disconnect();
}

bool MainModel::IsConnected() const
{
   return mIBWrapper->IsConnected();
}