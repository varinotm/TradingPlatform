#pragma once

#include "Contract.h"
#include <string>

class ContractRepository
{

public:
   struct DefaultContract
   {
      std::string name;
      Contract contract;
   };

   ContractRepository();

   ~ContractRepository() = default;

private:
   std::vector<DefaultContract> mDefaultContractList;
};