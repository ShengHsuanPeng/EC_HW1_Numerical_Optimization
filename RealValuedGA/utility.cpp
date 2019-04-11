#include "utility.h"

namespace utility {

bool FitnessCmp(individual::Individual* i1, individual::Individual* i2) {
    return (i1->fitness < i2->fitness);
}

} // namespace utility