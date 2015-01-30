/******************************************************************
描    述：客户端socket协议发送函数
修改时间：2014.8.20
******************************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "client_socket.h"


bool client_socket_send(int fd,char* message,string& errormessage)
{
	int write_id;
	write_id = write(fd,message,strlen(message));
	errormessage = "";
	if(write_id=-1)
	{
		errormessage = "message send fail!";
		return false;
	}	
	return true;
}
void client_send_logout(int fd)
{
	char buf[1024] = {0};
	memcpy(buf,CLIENT_LOGOUT,6);
	client_socket_send(fd,buf);
}
bool client_send_login(int fd,char* username,char* password);
{
	char buf[1024] = {0};
	if(strlen(username)+strlen(password) > 1000)
		return false;
	memcpy(buf,CLIENT_LOGIN_,6);
	memncpy(buf+7,username,strlen(username));
	memncpy(buf+8+strlen(username),password,strlen(password));
	
	return client_socket_send(fd,buf);
}
bool client_send_update(int fd,char* message)
{
	if(strlen(message)>1000)
		return false;
	char buf[1024] = {0};
	memcpy(buf,CLIENT_UPDATE,6);
	memncpy(buf+7,message,strlen(message));
	
	return client_socket_send(fd,buf);
}
bool client_send_findhi(int fd,char* DID,char* timestr)
{
	if(strlen(DID)+strlen(timestr) > 1000)
		return false;
	char buf[1024] = {0};
	memcpy(buf,CLIENT_FINDHI,6);
	memncpy(buf+7,DID,strlen(DID));
	memncpy(buf+8+strlen(DID),timestr,strlen(timestr));
	
	return client_socket_send(fd,buf);
}
bool client_send_message(int fd,char* DID，char* message)
{
	char buf[1024] = {0};
	int send_has =0;
	int send_len = 0;
	int need_send = strlen(message);
	memcpy(buf,CLIENT_FINDHI,6);
	memncpy(buf+7,DID,strlen(DID));
	if(need_send>(1016 - strlen(DID)))
		send_len = 1016 - strlen(DID) ;
	else
		send_len = strlen(message);
	memncpy(buf+8 + strlen(DID),message+send_has,send_len);
	while(1)
	{		
		if(client_socket_send(fd,buf)==false)
			return false;
		if(send_len<1024)
		{
			char str_hpend[] = "HPEND";
			if(client_socket_send(fd,str_hpend)==false)
				return false;
			break;
		}
		else
		{
			send_has += send_len;
			if(need_send - send_has >= 1024)
				send_len = 1024;
			else
				send_len = need_send - send_has;
		}
		memncpy(buf,message+send_has,send_len);
	}
	return true;
}

