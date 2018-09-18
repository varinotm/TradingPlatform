#pragma once

#include <memory>

#include "ViewModel\MainViewModel.h"

class StartupManager
{
public:
   StartupManager(int argc, char *argv[]);

   ~StartupManager() = default;

private:
   std::unique_ptr<MainViewModel> mMainViewModel;
};