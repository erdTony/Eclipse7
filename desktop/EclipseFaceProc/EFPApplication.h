#pragma once

#include <BaseWidgetApplication.h>

#include <Url.h>

class EFPMainWindow;

class EFPApplication : public BaseWidgetApplication
{
    Q_OBJECT
public: // ctors
    explicit EFPApplication(int &argc, char **argv);

public slots:
    void setup();
    void start();

signals:

public: // const

public: // non-const

public: // pointers


private:
    Url mInputUrl;
};
