//
// Created by luogan on 16-10-15.
//

#ifndef DBPROJECT_CONSTRAINTS_H
#define DBPROJECT_CONSTRAINTS_H


#include "../recmanage/MyData.h"

class Constraints {
private:
    // int ranp,tot;
    int kind;
    //0 select *
public:
    Constraints(int k = 0)
    {
        kind = k;
        // ranp=1;tot=0;
    }

    // Constraints(int p)
    // {
    //     ranp=p;tot=0;
    // }
    //返回true表示满足条件
    bool checkData(MyData *data)
    {
        switch (kind){
            case 0:
                return true;
        }
        // if (ranp==0)
        // {
        //     int v=*(int*)(data->data+1);
        //     if (v>=99&&v<=990)
        //         return true;
        //     else
        //         return false;
        // }
        // ++tot;
        // if (tot%ranp==0)
        //     return true;
        // else
        //     return false;
    }
};


#endif //DBPROJECT_CONSTRAINTS_H
