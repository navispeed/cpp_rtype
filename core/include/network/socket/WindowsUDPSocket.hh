//
// Created by drouar_b on 12/6/16.
//

#ifndef CPP_RTYPE_WINDOWSUDPSOCKET_HH
#define CPP_RTYPE_WINDOWSUDPSOCKET_HH

#include <string>
#include <list>
#include <forward_list>
#include <io.h>
#include <WinSock2.h>
#include <thread/Thread.hpp>
#include <helpers/WindowsStopwatch.hh>
#include "ISocket.hh"

namespace network {
    namespace socket {
        /*!
         * @class WindowsUDPSocket
         * @brief UDP socket handler for Windows systems
         */
        class WindowsUDPSocket : public ISocket {
        private:
            struct s_UDPClient {
                int npings;
                unsigned short ack;
                helpers::WindowsStopwatch sw;
                e_socketStatus status;
                struct sockaddr_in client;
            };

            enum e_handshakeState {
                SYN,
                SYNACK,
                ACK
            };

        public:
            /*!
             * @brief Instantiate UDP Server
             * @param port Port to listen
             * @throw std::runtime_error Throw if port is already used
             */
            WindowsUDPSocket(unsigned short port);

            /*!
             * @brief Connect to an UDP server
             * @param address Ip to connect
             * @param port Port of the server
             * @throw std::runtime_error Throw a runtime error when connection failed
             */
            WindowsUDPSocket(const std::string &address, unsigned short port);

            virtual ~WindowsUDPSocket();

            virtual bool run();
            virtual void poll();
            virtual bool stop();
            virtual void broadcast(const std::vector<uint8_t> &data);
            virtual void send(const std::vector<uint8_t> &data, unsigned long dest);
            virtual void registerConnectionListener(listener::ISocketConnectionListener *listener);
            virtual void unregisterConnectionListener(listener::ISocketConnectionListener *listener);
            virtual void registerDisconnectionListener(listener::ISocketDisconnectionListener *listener);
            virtual void unregisterDisconnectionListener(listener::ISocketDisconnectionListener *listener);
            virtual void registerDataListener(listener::ISocketDataListener *listener);
            virtual void unregisterDataListener(listener::ISocketDataListener *listener);
            virtual e_socketType getType();
            virtual e_socketStatus getStatus();

        private:
            void init();
            void clientInit();
            void serverInit();

            void serverPoll();
            void clientPoll();

            void clientDisconnect();
            void serverDisconnect(const struct sockaddr_in &client);

            //Server stuffs
            void serverTimeout();
            bool serverHandshake(std::vector<uint8_t> &data, struct s_UDPClient &client, e_handshakeState state);

            //Client stuffs
            void clientTimeout();
            void clientHandshake();

            unsigned long getClientId(const struct sockaddr_in &client);
            void handleData(const std::vector<uint8_t> &data, const struct sockaddr_in &client);

        private:
            e_socketType type;
            e_socketStatus status;

            //Socket stuffs
            SOCKET mainSocketFd;
            struct pollfd pollfd;
            struct sockaddr_in mainSocket;

            //Client stuffs
            int npings;
            unsigned short syn;
            helpers::WindowsStopwatch sw;

            //Server Stuffs
            std::list<struct s_UDPClient> clients;

            IThread *thread;

            std::forward_list<listener::ISocketConnectionListener *> connectionListeners;
            std::forward_list<listener::ISocketDisconnectionListener *> disconnectionListeners;
            std::forward_list<listener::ISocketDataListener *> dataListeners;
        };
    }
}

#endif //CPP_RTYPE_WINDOWSUDPSOCKET_HH
