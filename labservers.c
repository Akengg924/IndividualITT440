#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAX 60
int i,j,tem;
char buff[4069],t;
int main(int afg,char *argv)
{

       //Define Ip and Port
       const int port =21;
       char *ip = "192.168.8.106";

       //Define The Variable
       char* filename = "serverdata.txt";
       int sockfd,newsockfd,clength;
       struct sockaddr_in serv_addr,cli_addr;
       char t[MAX],str[MAX];
       FILE *ft;

       //Creating The Socket
       sockfd=socket(AF_INET,SOCK_STREAM,0);
       if(sockfd<0)
       {
              perror("ERROR! Finding Socket Fail");
              exit(EXIT_FAILURE);
       }
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr(ip);
        serv_addr.sin_port= port;
        printf("\nThe Server Has Started");
        
        //Reading The Data
        bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
        printf("\nWaiting....");
        listen(sockfd,5);
        clength=sizeof(cli_addr);
        newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
        close(sockfd);
        read(newsockfd,&str,MAX);
        printf("\nClient message\n File Name : %s\n",str);
        ft=fopen(str,"r");
        while(fgets(buff,4096,ft)!=NULL)
        {
              write(newsockfd,buff,MAX);
              printf("\n");
        }
         
        //If Data Reading Fail
        if(ft ==NULL)
        {
               perror("ERROR! Data Reading Fail");
               exit(EXIT_FAILURE);
        }
         
         fclose(ft);
         printf("\nFile Transferred\n");
         printf("\nClosing Server\n");
         close (sockfd);
         return 0;
}

