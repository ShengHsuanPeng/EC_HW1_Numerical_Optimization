#include "utility.h"

namespace utility {

bool FitnessCmp(individual::Individual* i1, individual::Individual* i2) {
    if(i1->fitness < i2->fitness)
        return true;
    return false;
}

} // namespace utility