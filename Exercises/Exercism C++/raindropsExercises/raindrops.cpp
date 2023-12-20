#include raindrops.h
#include string
namespace raindrops {
    stdstring convert(int raindrop){
        stdstring converted {};
        if (raindrop % 3 == 0 ){
            converted += Pling;
        }
        if ( raindrop % 5 == 0 ){
            converted += Plang;
        }
        if ( raindrop % 7 == 0 ){
            converted += Plong;
        }
        if ( raindrop % 3 != 0 && raindrop % 5 != 0 && raindrop % 7 != 0) {
            stdstring bad = stdto_string(raindrop);
            return bad ;
        }
        return converted;
    }
}   namespace raindrops
