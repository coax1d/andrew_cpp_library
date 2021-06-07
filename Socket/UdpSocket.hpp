/**
*   UDP Socket Interface allows either client or server configuration
*   supports IPV4 only.
*
*   Author: Andrew Burger
*/

#include <string>

enum class SockConfiguration {SERVER, CLIENT, ERROR};

class UdpSocket {
    public:
        virtual ~UdpSocket() = default;

        /**
        *   @return true if successful
        */
        virtual bool bind(int fd, const std::string address) = 0;

        /**
        *   @return true if successful
        */
        virtual bool listen(int fd) = 0;

        /**
        *   @return true if successful
        */
        virtual bool send(int fd, std::string &buffer) = 0;

        /**
        *   @return true if successful
        */
        virtual bool receive(int fd, std::string &buffer) = 0;

        /**
        *   @return true if successful
        */
        virtual bool close() = 0;
};