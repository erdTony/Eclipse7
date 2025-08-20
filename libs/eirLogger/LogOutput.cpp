#include "LogOutput.h"


LogOutput::LogOutput(const CText &name,
                     const LogFormat::Format fmt,
                     QObject *parent)
    : QObject{parent}, mName(name), mFormat(fmt) {;}

