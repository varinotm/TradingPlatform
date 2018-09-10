#pragma once

#include <memory>

class IBWrapper;

class MainModel
{
public:
   /// Constructor
   MainModel();

   /// Destructor
   ~MainModel() = default;

private:
   std::shared_ptr<IBWrapper> mIBWrapper;
};