#include <MainWindowPageStack.h>
#include "EFPApplication.h"

int main(int argc, char *argv[])
{
    EFPApplication a(argc, argv);
    MainWindowPageStack w(&a);
    w.show();
    return a.exec();
}
