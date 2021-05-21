/*  Name : Yogesh Porwal
    Roll No : 20CS60R52
    Email Id:yogeshporwal@kgpian.iitkgp.ac.in
    File name : client.cpp

    Compilation Instructions:
    To complie : g++ <source_filename> -o <any name>
                eg: g++ client1.cpp -o client
    To Run : ./<any name*> <host name> <Port number>
            eg: ./client localhost 3000
            
            *this should be same as given while compiling tha file
*/

#include <unistd.h> 
#include <iostream> 
#include <sys/socket.h> 
#include<sys/types.h>
#include <stdlib.h> 
#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include <string.h> 

using namespace std;

/*  Function Prototype : int main(int args,char* argv[])
    Input :         host name followed by port number as acommand line arguement
    Description:    code to set up connection with server is written,it is a continous program that contously take
                    query from client and server return appropriate response to that
*/

int main(int args,char* argv[])
{
 
 struct sockaddr_in server_addr,client_addr;
 int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
 
 if(socket_fd<0)
 {
   perror("socket creation failed!");
   exit(EXIT_FAILURE);
 }
 else
 cout<<"socket created succesfully!"<<endl;
 
 if(argv[1]==NULL)
 {
  cout<<"Please pass the hostname"<<endl;
  return 0;
 }
 
 if(argv[2]==NULL)
 {
  cout<<"Please pass the port number"<<endl;
  return 0;
 }
 int port_no=stoi(argv[2]);
 struct hostent *server;
 server = gethostbyname(argv[1]);
 bzero((char *) &server_addr, sizeof(server_addr));
 server_addr.sin_family = AF_INET;
 bcopy((char *)server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);
 server_addr.sin_port = htons(port_no);
 
 if(connect(socket_fd,(struct sockaddr *) &server_addr,sizeof(server_addr)) < 0) 
 { 
  perror("Error in connecting");
  exit(EXIT_FAILURE); 
 }
 else
 cout<<"connected to server succesfully!"<<endl;
 
 char buffer[1024];
 int n,m;

 cout<<"To close the connection,please write \"end\" without quotes at any point of time "<<endl;
 while(1)
 {
 bzero(buffer,1023);
 printf("\nEnter a expression for server: "); 
 fgets(buffer,1023,stdin);
 n = write(socket_fd, buffer, strlen(buffer)); 
 if(strncmp("end", buffer, 3)==0)
 break;
 
 
 bzero(buffer,1023);
 n = read(socket_fd,buffer,1023);
 
 if (n< 0) 
 {
  perror("\nClient Error: Reading from Client");
  exit(EXIT_FAILURE);
 }
 
 printf("Response from server: %s\n", buffer);
 }
 
 cout<<"client is closing..."<<endl;
 close(socket_fd);
 
 return 0;
}
