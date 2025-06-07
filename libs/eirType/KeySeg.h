#pragma once

#include "AText.h"

class KeySeg : public AText
{
public:
    KeySeg() {;}
    KeySeg(const char * pch) : AText(pch) {;}
    KeySeg(const AText &other) : AText(other) {;}
    KeySeg(const QString &s) : AText(s) {;}



public: // pointers

protected: // static
    static bool isValidFirst(const char ch);
    static bool isValidChar(const char ch);

private:


};
