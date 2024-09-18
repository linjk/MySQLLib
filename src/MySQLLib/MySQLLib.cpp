#include <mysql.h>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    mysql_library_init(0, 0, 0);

    MYSQL mysql;
    mysql_init(&mysql);

    const char* host = "127.0.0.1";
    const char* user = "root";
    const char* pwd = "ljk121121";
    const char* db = "jarvis_user";

    int to = 3; // 数据库连接超时3秒
    int re = mysql_options(&mysql, MYSQL_OPT_CONNECT_TIMEOUT, &to);
    if (re != 0) {
        std::cout << "mysql options [MYSQL_OPT_CONNECT_TIMEOUT] failed, detail: " << mysql_error(&mysql) << std::endl;
    }

    int reconnect = 1; // 数据库1秒重连
    re = mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnect);
    if (re != 0) {
        std::cout << "mysql options [MYSQL_OPT_RECONNECT] failed, detail: " << mysql_error(&mysql) << std::endl;
    }

    if (!mysql_real_connect(&mysql, host, user, pwd, db, 3306, 0, 0)) {
        std::cout << "mysql connect failed, detail: " << mysql_error(&mysql) << std::endl;
    }
    else {
        std::cout << "mysql connect success." << std::endl;
    }

    for (int i = 0; i < 1000; i++) {
        int re = mysql_ping(&mysql);
        if (re == 0) {
            std::cout << "mysql ping success." << std::endl;
        }
        else {
            std::cout << "mysql ping failed, " << mysql_error(&mysql) << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    mysql_close(&mysql);

    mysql_library_end();

    return getchar();
}