#ifndef UTILITY
#define UTILITY
#import "Individual.h"

namespace utility
{
    bool fitness_cmp(const individual &i1, const individual &i2)
    {
        if(i1.fitness > i2.fitness)
            return true;
        return false;
    }
}

#endif