#include <iostream>
#include "Server.h"
#include <locale.h>
using namespace std;
int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8);  // вывод в UTF-8
    SetConsoleCP(CP_UTF8);        // ввод в UTF-8
    net::io_context ioc;
    cout << "Сервер" << endl;
    auto server = std::make_shared<Server>(ioc);
    server->run();

    // запускаем ioc в отдельном потоке — там крутятся все async операции
    std::thread t([&ioc]() { ioc.run(); });

    // в главном потоке читаем ввод и отправляем
    std::string message;
    while (std::getline(std::cin, message)) {
        server->send(message);
    }

    t.join();
}