# CMakeList.txt: проект CMake для ecdh; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

add_library(ecdh STATIC
    src/ecdh.cpp
    src/uint256.cpp
    src/Fe25519.cpp
)

target_include_directories(ecdh PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ecdh PRIVATE
    bcrypt
)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
