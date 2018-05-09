#pragma once
#ifndef SIPSERVER_SIPSERVER_HPP
#define SIPSERVER_SIPSERVER_HPP

#include <vector>

#include <asio/io_service.hpp>
#include <asio/ip/udp.hpp>

#include <resip/stack/SipMessage.hxx>

#include <Registrar.hpp>


class SipServer {
    private:
        asio::io_service* serverIo; // Object for connecting to I/O services of OS.
        asio::ip::udp::socket* serverSocket;
        unsigned short port;
        asio::ip::address networkInterface;
        std::vector<asio::ip::udp::endpoint> clients;
        Registrar* registrar;

        void setPort(unsigned short port);
        void setServerIo(asio::io_service* serverIo);
        void setNetworkInterface(asio::ip::address networkInterface);

        void process(resip::SipMessage& incomingMessage);

    public:
        class Builder;

        SipServer();
        SipServer(asio::io_service* ioService, asio::ip::address networkInterface, unsigned short port, Registrar* registrar);
        ~SipServer();
        void init();
        void updateSocket();
        void run();
        void removeClient(asio::ip::udp::endpoint& client);

        void changePort(unsigned short port);
        void changeServerIo(asio::io_service* serverIo);
        void changeNetworkInterface(asio::ip::address networkInterface);


        void onRegister(resip::SipMessage registerRequest);

        bool send(resip::SipMessage msg, asio::ip::udp::endpoint to);
        resip::SipMessage receive(asio::ip::udp::endpoint from);

        bool isAuth(resip::SipMessage&);
        unsigned short getPort();
        asio::ip::address getNetworkInterface();
        std::vector<asio::ip::udp::endpoint> getClients();

        const char* nonce = "99b12a42a73b0da8dc2b4f071a5efb16"; //TODO: nonce generation
};

#endif //SIPSERVER_SIPSERVER_HPP
