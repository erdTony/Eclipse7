#include "LogOutput.h"


LogOutput::LogOutput(const CText &name,
                     const LogFormat::Format fmtv,
                     QObject *parent)
    : QObject{parent}, mName(name), mFormat(fmtv) {;}

