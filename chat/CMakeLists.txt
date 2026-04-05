option(BUILD_CLIENT "Build client" ON)
option(BUILD_SERVER "Build server" ON)

add_library(chat_deps INTERFACE)
find_package(boost_beast CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
target_link_libraries(chat_deps INTERFACE
    ecdh
    Boost::beast
    Boost::system
    Threads::Threads
    OpenSSL::Crypto
)

if(BUILD_CLIENT)
	add_subdirectory(client)
endif()

if(BUILD_SERVER)
	add_subdirectory(server)
endif()