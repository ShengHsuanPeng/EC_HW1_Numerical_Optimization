#include "utility.h"
using namespace utility;

bool utility::fitness_cmp(Individual::individual* i1, Individual::individual* i2)
{
    if(i1->fitness < i2->fitness)
        return true;
    return false;
}