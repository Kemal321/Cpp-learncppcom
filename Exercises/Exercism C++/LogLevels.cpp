#include <string>
using namespace std;
namespace log_line {
    string message(string s) {
        int indexDouble = s.find(" ");
        string newS = s.substr((indexDouble)+1);
        return newS;
    }
    string log_level(string s) {
        int lastIndex = s.find("]");
        string newS = s.substr(1, lastIndex - 1);
        return newS;
    }
    string reformat(string s) {
        int indexDouble = s.find(" ");
        int lastIndex = s.find("]");
        string newS = s.substr((indexDouble)+1);
        newS = newS + " (" + s.substr(1, lastIndex - 1) + ")";
        return newS;
    }
} // namespace log_line
