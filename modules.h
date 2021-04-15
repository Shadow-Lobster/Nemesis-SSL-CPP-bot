#include <iostream>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void ping(std::string buffer_string,char buf[1024], SSL *ssl){
    if(strstr(buf, "PING :") != NULL){
    std::string pong_raw = "PONG :" + buffer_string.substr(6,-1);
    const char *pong = pong_raw.c_str();
    SSL_write(ssl, pong, strlen(pong));
    std::cout << pong << std::endl;
    }
}
