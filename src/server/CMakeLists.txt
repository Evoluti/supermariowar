set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall -std=c++11")

set (SERVER_SRCS
    Log.cpp
    NetworkLayerENet.cpp
    Player.cpp
    Room.cpp
    server.cpp
    mainServer.cpp
)

add_executable (smw-server ${SERVER_SRCS})
target_link_libraries (smw-server enet)
