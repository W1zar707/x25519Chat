#include "Client.h"
#include <string>
#include <thread>
#include <locale.h>
using namespace std;
int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8);  // вывод в UTF-8
    SetConsoleCP(CP_UTF8);        // ввод в UTF-8
    net::io_context ioc;
    cout << "Введите ip хоста" << endl;
    string host;
    getline(cin, host);
    auto client = std::make_shared<Client>(ioc, host.c_str(), "/");
    client->run();

    // запускаем ioc в отдельном потоке — там крутятся все async операции
    std::thread t([&ioc]() { ioc.run(); });

    // в главном потоке читаем ввод и отправляем
    std::string message;
    while (std::getline(std::cin, message)) {
        client->send(message);
    }

    t.join();
}