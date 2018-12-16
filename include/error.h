#ifndef INC_ERROR_H
#define INC_ERROR_H

#include<stdexcept>
#include<string>

class AoCError : public std::runtime_error {
    public:
        AoCError(const std::string& emsg)
            : std::runtime_error(emsg) {
            }
};
#endif
