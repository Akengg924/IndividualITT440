#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define MAX 60


int main(int arg,char*argv[])
{
       //Define The Variable
       int sockfd,n;
       struct sockaddr_in serv_addr;
       struct hostent*server;
       char* filename = "ftpdata.txt";

       //Define ip and Port
       const int port =21 ;
       char *ip = "192.168.8.106";
       char send[MAX],recvline[MAX],s[MAX],name[MAX];

       //Creating Socket
       sockfd=socket(AF_INET,SOCK_STREAM,0);
       if(sockfd<0)
       {
        perror("ERROR!");
        exit(EXIT_FAILURE);
       }
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=inet_addr(ip);
       serv_addr.sin_port=port;

       //Requesting Data From Server
       connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       printf("\nEnter the source file name : \n");
       scanf("%s",send);
       write(sockfd,send,MAX);
       while((n=read(sockfd,recvline,MAX))!=0)
       {
          printf("%s",recvline);
       }
       printf("\nFile Received\n");
       printf("\nClosing Server\n");
       close(sockfd);
       return 0;
}
