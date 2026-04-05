add_executable(server src/main.cpp src/Server.cpp)
target_include_directories(ecdh PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(server PRIVATE chat_deps)