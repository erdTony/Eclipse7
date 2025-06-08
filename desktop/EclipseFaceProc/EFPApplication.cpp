#include "EFPApplication.h"



EFPApplication::EFPApplication(int &argc, char **argv)
    : BaseWidgetApplication{argc, argv}
{
    qDebug() << Q_FUNC_INFO;
    setObjectName("EFPApplication:" + applicationName());
}

void EFPApplication::setup()
{

}
