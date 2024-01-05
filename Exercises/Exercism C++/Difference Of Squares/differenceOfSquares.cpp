#include "difference_of_squares.h"

namespace difference_of_squares {
    int square_of_sum(int counter){
        int sum{0};
        for(int i{1};i<=counter;++i){
            sum += i;
        }
        return (sum * sum);
    }
    int sum_of_squares(int counter){
        int square_sum{0};
        for(int i{1};i<=counter;++i){
            square_sum += (i * i);
        }
        return square_sum;
    }
    int difference(int counter){
        return (square_of_sum(counter) - sum_of_squares(counter));
    }

}  // namespace difference_of_squares
