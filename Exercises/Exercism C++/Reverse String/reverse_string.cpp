#include "reverse_string.h"
#include <string>
namespace reverse_string {
std::string reverse_string(std::string reversable){
    size_t indexS{(reversable.length() - 1)};
    std::string reversed{""};
    for(size_t i{1};i <= reversable.length(); ++i){
        reversed += reversable[indexS];
        indexS--;
    }
    return reversed;
}

}  // namespace reverse_string
