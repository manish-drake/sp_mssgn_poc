#ifndef MESSAGING_EXCEPTIONS_H
#define MESSAGING_EXCEPTIONS_H
#include <string>
#include <exception>
using std::string;
namespace Messaging
{
    class UnknownMessageException: public std::exception
    {
    public:
        const char* what() const noexcept
        {
            return "Unknown message.";
        }
    };
} // namespace Messaging

#endif //MESSAGING_EXCEPTIONS_H
