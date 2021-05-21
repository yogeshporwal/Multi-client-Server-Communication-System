# Multi-Client-Server-Communication-System

## Project Description

Here I implemented a multi_client server communication system using TCP protocol in which server can communicate with multiple clients simultaniously,I implemented this system using two following ways:

- **Using "Fork" system call:** 

  In this server program “fork” a process for every new client it receives, such that each child process is responsible for handling                                   the request of one client.
  
- **Using "Select" system call:** 

  The server uses the “select” call to see which clients are making the requests (it can be a connection request or read/write request) and serve the requests of     multiple clients.
  
  In both the implementations, client and server interact with each other in the following way:
  
  * The client connects to the server and then asks the user for input. The user enters a simple arithmetic expression string in infix form (e.g., "1 + 2", 
    "(5 + 6) * 8.9"). The user's input is sent to the server via the connected socket.
   
  * The server reads the user's input from the client socket, converts it into a postfix expression and then evaluates the postfix expression, and sends the result     and the converted postfix expression back to the client as well as writes the following in a file named “server_records.txt” (at the beginning create an empty       file).
    > <client_id> <infix_expr> <converted_expr><answer> <time_elapsed>
  
      **Note:** The time elapsed is the time elapsed (in seconds) from when the server connected to this client to returning the response to this query.
  
  * The client should display the server's reply to the user, and prompt the user for the next input until the user terminates the client program.
  
## Instructions to run the code
  
Commands for ubuntu terminal:

**For client file:**

To complie : ```$ g++ <source_filename> -o <any name> 
                eg: $ g++ client1.cpp -o client ```
                
To Run : ```$ ./<any name*> <host name> <Port number>
            eg:$ ./client localhost 8000 ```
            
            *this should be same as given while compiling tha file

**For server file:**
  
To complie : ```$ g++ <source_filename> -o <any name>
                eg:$ g++ server1.cpp -o server ```
                
To Run : ```$ ./<any name*> <Port number>
            eg:$ ./server 8000 ```
            
            *this should be same as given while compiling that file
            
            Please press ctrl+c to terminate server.
  
  
