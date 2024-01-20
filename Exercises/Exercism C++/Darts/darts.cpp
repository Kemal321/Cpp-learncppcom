#include "darts.h"
#include <cmath>
namespace darts {
    const double OUTER_RING = 10.0;
    const double MIDDLE_RING = 5.0;
    const double INNER_RING = 1.0;
int score(double x, double y){
    double hypotenuse = std::sqrt(((x * x) + (y * y)));
    if(hypotenuse <= 1)
        return 10;
    if (hypotenuse > 10)
        return 0;
    if ( hypotenuse <=5 && hypotenuse >1)
        return 5;
    if (hypotenuse >5 && hypotenuse <= 10)
        return 1;
    return 999;
    }

} // namespace darts