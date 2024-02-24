#include "eliuds_eggs.h"

namespace chicken_coop {
int positions_to_quantity(int number){
    if(number <=0)
        return 0;
    int eggCounter{0};
    while(number >= 1){
        if(number == 1)
            return (eggCounter + 1);
        int condition = number % 2;
        if(condition){
            ++eggCounter;
            number = number / 2;
        }
        else{
            number = number / 2;
        }

    }
    return eggCounter;
}
}  // namespace chicken_coop