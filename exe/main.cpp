#include "StartupManager.h"
#include <qresource.h>

#include <iostream>

int main(int argc, char *argv[])
{
   Q_INIT_RESOURCE(qml);

   StartupManager s(argc, argv);
   return 0;
}