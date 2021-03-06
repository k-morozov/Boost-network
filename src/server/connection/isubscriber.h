#ifndef ISUBSCRIBER_H
#define ISUBSCRIBER_H

#include <iostream>
#include <memory>
#include <string>
#include <boost/asio.hpp>
#include "protocol/protocol.h"

/**
 * @brief Channel Subscriber Interface 
 */
class ISubscriber
{
public:

    /**
     * @brief Entry point to handle incoming requests
     */
    virtual void start() = 0;

    /**
     * @brief Get the client id object
     * @details Returns current client id
     * @return identifier_t 
     */
    virtual identifier_t get_client_id() const = 0;

    /**
     * @brief Get the login
     * @details Return client's login
     * @return const std::string& 
     */
    virtual const std::string& get_login() const = 0;
    virtual void set_channel(identifier_t new_id_room) = 0;

    virtual void async_read_pb_header() = 0;
    virtual void async_read_pb_msg(Serialize::Header) = 0;

    virtual void do_parse_pb_header(boost::system::error_code, std::size_t) = 0;
    virtual void do_read_pb_input_req(boost::system::error_code, std::size_t) = 0;
    virtual void do_read_pb_reg_req(boost::system::error_code, std::size_t) = 0;
    virtual void do_read_pb_join_room_req(boost::system::error_code, std::size_t) = 0;
    virtual void do_read_pb_text_req(boost::system::error_code, std::size_t) = 0;

    virtual void send_msg_to_client(const std::string&,const std::string&, int) = 0;
    virtual void add_msg_send_queue(std::vector<uint8_t>&&) = 0;
    virtual void sending_msgs_to_client() = 0;

    virtual bool is_busy() const noexcept = 0;
    virtual void set_busy(bool flag = true) noexcept = 0;
    virtual void reuse(boost::asio::ip::tcp::socket&& _socket)  = 0;
    virtual void free_connection() = 0;
    virtual ~ISubscriber() = default;
};

using subscriber_ptr = std::shared_ptr<ISubscriber>;

#endif // ISUBSCRIBER_H
