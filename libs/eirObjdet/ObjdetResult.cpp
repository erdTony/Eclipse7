#include "ObjdetResult.h"

class ObjdetResultData : public QSharedData
{
public:

};



// -------------------- QSharedData -----------------------
ObjdetResult::ObjdetResult() : data(new ObjdetResultData) {;}
ObjdetResult::ObjdetResult(const ObjdetResult &rhs) : data{rhs.data} {;}
ObjdetResult::~ObjdetResult() {;}
ObjdetResult &ObjdetResult::operator=(const ObjdetResult &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

