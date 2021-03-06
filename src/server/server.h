#ifndef SMWSERVER_H
#define SMWSERVER_H

#include "NetworkLayer.h"
#include "ProtocolPackages.h"

#include "Player.h"
#include "Room.h"

#include <cstdio>
#include <ctime>
#include <unordered_map>
#include <string>
#include <vector>


#define MAX_INACTIVE_TIME ???

class SMWServer : public NetworkEventHandler
{
private:
    std::string serverName;
    ServerInfoPackage serverInfo;

    uint32_t currentPlayerCount;
    uint32_t maxPlayerCount;
    std::unordered_map<uint64_t, Player> players;

    uint32_t roomCreateID; // temporary
    uint32_t currentRoomCount;
    std::unordered_map<uint32_t, Room> rooms;


    void sendServerInfo(NetClient&);
    void sendConnectOK(NetClient&);
    void playerConnectsServer(uint64_t playerID, const void* data);
    void sendVisibleRoomEntries(NetClient&);
    void removeInactivePlayers();

    void playerCreatesRoom(uint64_t playerID, const void* data);
    void playerJoinsRoom(uint64_t playerID, const void* data);
    void playerLeavesRoom(uint64_t playerID);
    void playerSendsChatMsg(uint64_t playerID, const void* data);

    void playerStartsRoom(uint64_t playerID);
    void startRoomIfEveryoneReady(uint64_t playerID);
    void sendInputToHost(uint64_t playerID);
    void sendHostStateToOtherPlayers(uint64_t playerID);


    void readConfig();

    void sendCode(NetClient&, uint8_t code);
    void sendCode(NetClient*, uint8_t code);
    void sendCode(uint64_t playerID, uint8_t code);

public:
    SMWServer();
    ~SMWServer();

    bool init();
    void cleanup();

    void update(bool& running);

    // NetworkEventHandler methods
    void onConnect(NetClient*);
    void onReceive(NetClient&, const uint8_t*, size_t);
    void onDisconnect(NetClient& client);
};

#endif // SMWSERVER_H
