#ifndef CHANNELSMANAGER_H
#define CHANNELSMANAGER_H

#include "channel.h"
#include "log/logger.h"

/**
 * @brief ChannelsManager
 * 
 * @details It is singleton instance that serves channels
 */
class ChannelsManager
{
public:
    /**
     * @brief Getter of singleton instance
     * 
     * @return ChannelsManager& 
     */
    static ChannelsManager& Instance() {
        static ChannelsManager manager;
        return manager;
    }
    /**
     * @brief Join user to room by room_id
     * 
     * @param subscriber room's subscriber
     * 
     * @param room_id room where subscriber joining
     *
     * @param db
     */
    bool join(subscriber_ptr, identifier_t, database_ptr db);

    /**
     * @brief Send message to specific room and specific user
     */
    void send_to_channel(TextSendData data);

    /**
     * @brief Leave user from the room
     */
    void leave(identifier_t client_id, identifier_t room_id);

    void leave_from_all_channels(identifier_t a_client_id);

private:
    /**
     * @brief Construct a new Channels Manager
     */
    ChannelsManager();

    std::unordered_map<identifier_t, iroom_ptr> channels;
    std::unordered_map<identifier_t, std::deque<identifier_t>> client_in_rooms;
    std::unordered_map<identifier_t, std::string> clientid_to_login;

};

#endif // CHANNELSMANAGER_H
