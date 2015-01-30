#ifndef CLIENT_SOCKET_HEAD
#define	CLIENT_SOCKET_HEAD

#include <stdio.h>
#include <string.h>

#define SERVER_LOGOUT "LogOut"
#define SERVER_LOGIN_ "LogIn_"
#define SERVER_LOGON_ "LogOn_"
#define SERVER_RETUHI "RetuHi"
#define SERVER_UPDATE "Update"

#define CLIENT_LOGOUT "LogOut"
#define CLIENT_LOGIN_ "LogIn_"
#define CLIENT_SEND__ "Send__"
#define CLIENT_FINDHI "FindHi"
#define CLIENT_UPDATE "Update"


bool client_socket_send(int fd,char* message,string& errormessage);
void client_send_logout(int fd);
bool client_send_login(int fd,char* username,char* password);
bool client_send_update(int fd,char* message);
bool client_send_findhi(int fd,char* DID,char* timestr);
bool client_send_message(int fd,char* message);

#endif