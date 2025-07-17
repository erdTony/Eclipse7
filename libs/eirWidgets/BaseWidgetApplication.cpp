#include "BaseWidgetApplication.h"

#include <ExeSupport.h>

BaseWidgetApplication::BaseWidgetApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , mpExeSupport(new ExeSupport(this))
{
    setObjectName("BaseWidgetApplication:"
                  + QApplication::applicationName());
}
