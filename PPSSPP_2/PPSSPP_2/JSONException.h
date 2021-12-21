#include <exception>
#include <string>

class JSONException : public std::exception {
public:
    explicit JSONException(const char* message)
        : msg_(message) {}

    explicit JSONException(const std::string& message)
        : msg_(message) {}

    virtual ~JSONException() throw() {}

    virtual const char* what() const throw() {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};
