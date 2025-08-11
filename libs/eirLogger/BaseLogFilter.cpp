#include "BaseLogFilter.h"

BaseLogFilter::BaseLogFilter(QObject *parent)
    : QObject{parent}
{
    setObjectName("BaseLogFilter:null");
}

void BaseLogFilter::add(const BaseLogFilterItem &lfi)
{

}
