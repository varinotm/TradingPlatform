#include "ContractRepository.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

#include <iostream>

ContractRepository::ContractRepository()
{
   try
   {
      boost::property_tree::ptree pt;
      boost::property_tree::read_json("DefaultContracts.json", pt);

      BOOST_FOREACH(boost::property_tree::ptree::value_type &v, 
                    pt.get_child("Contracts"))
      {
         DefaultContract defaultContract;
         defaultContract.name = v.second.get<std::string>("Name");
         defaultContract.contract.symbol = v.second.get<std::string>("Symbol");
         defaultContract.contract.secType = v.second.get<std::string>("SecType");
         defaultContract.contract.currency = v.second.get<std::string>("Currency");
         defaultContract.contract.exchange = v.second.get<std::string>("Exchange");
         mDefaultContractList.push_back(defaultContract);
      }
   }
   catch (std::exception const& e)
   {
      std::cout << e.what() << std::endl;
   }
}