//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_CONSTRAINTS_H
#define DBPROJECT_CONSTRAINTS_H


#include "../recmanage/MyData.h"

class Constraints {
private:
    int ranp,tot;
public:
    Constraints()
    {
        ranp=1;tot=0;
    }

    Constraints(int p)
    {
        ranp=p;tot=0;
        if (ranp<1) ranp=1;
    }

    bool checkData(MyData *data)
    {
        ++tot;
        if (tot%ranp==0)
            return true;
        else
            return false;
    }
};


#endif //DBPROJECT_CONSTRAINTS_H
