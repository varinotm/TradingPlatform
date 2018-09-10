#include "MainModel.h"

#include "IBWrapper.h"

#include <boost\shared_ptr.hpp>

MainModel::MainModel()
{
   mIBWrapper = std::make_shared<IBWrapper>();
}