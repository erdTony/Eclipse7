#include "BaseWidgetApplication.h"

BaseWidgetApplication::BaseWidgetApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setObjectName("BaseWidgetApplication:"
                  + QApplication::applicationName());
}
