#ifndef LOGIN_METHOD_H
#define LOGIN_METHOD_H

namespace core {

class LoginMethod {
public:
    LoginMethod() {};
    virtual ~LoginMethod() {};
    virtual const std::string &description() const = 0;
};

}

#endif // LOGIN_METHOD_H
