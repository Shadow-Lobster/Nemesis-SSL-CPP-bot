#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string.h>
#include "ssl.h"
#include "socket.h"
#include "functions.h"
#include "aliases.h"
#include "modules.h"

int main()
{
    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[1024];
    int bytes;
    alias aliases;      //for getting important values stored in alias class

    SSL_library_init();
    ctx = InitCTX();
    server = OpenConnection(aliases.hostname, aliases.portnum);
    ssl = SSL_new(ctx);      /* create new SSL connection state */
    SSL_set_fd(ssl, server);    /* attach the socket descriptor */
    if ( SSL_connect(ssl) != 1 ){   /* perform the connection */
        ERR_print_errors_fp(stderr);
        printf("error opening ssl connection");
    }
    else
    {
        int connected{0};       //for connection loop
        /* construct reply */
        printf("\n\nConnected with %s encryption\n", SSL_get_cipher(ssl));
        ShowCerts(ssl);        /* get any certs */
        bytes = SSL_read(ssl, buf, sizeof(buf)); /* get reply & decrypt */
        buf[bytes] = 0;
        printf("Received: \"%s\"\n", buf);
        if(strstr(buf, "NOTICE * :*** Looking up your hostname") != NULL) {
          SSL_write(ssl, aliases.nick_raw, strlen(aliases.nick_raw));       // Converts nick string to c-array and sends it to server
          std::cout << "sent: " << aliases.nick << " to server \n";
          SSL_write(ssl, aliases.user_raw, strlen(aliases.user_raw));
          std::cout << "sent: " << aliases.user << " to server \n";
        }
        memset(&buf, '\0', sizeof(buf));    //clear out buffer
        std::string buffer_string{0};   //for string version of buf
        while(connected < 1){
            memset(&buf, '\0', sizeof(buf));
            SSL_read(ssl, buf, sizeof(buf));
            printf(buf);
            buffer_string = buf;

            /*** PING and PONG ***/
            ping(buffer_string,buf,ssl);    //sent buffer and ssl connection for ping and pong

            /*** write all the functions down here ***/
        }
        SSL_free(ssl);      /* release connection state */

    }
    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    return 0;
}
