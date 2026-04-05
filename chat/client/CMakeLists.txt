add_executable(client src/main.cpp src/Client.cpp)
target_include_directories(ecdh PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(client PRIVATE chat_deps)
