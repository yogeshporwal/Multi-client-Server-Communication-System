/*  Name : Yogesh Porwal
    Roll No : 20CS60R52
    Email Id:yogeshporwal@kgpian.iitkgp.ac.in
    File name : server.cpp

    Compilation Instructions:
    To complie : g++ <source_filename> -o <any name>
                eg: g++ server1.cpp -o server
    To Run : ./<any name*> <Port number>
            eg: ./server 3000
            
            *this should be same as given while compiling tha file
*/

#include <unistd.h>   
#include <iostream> 
#include <sys/socket.h> 
#include <stdlib.h>      //for exit()
#include<stdio.h>
#include <netinet/in.h> //for struct sockaddr_in
#include <string.h> 
#include<sstream>
#include<math.h>
#include <fstream> 
#include<time.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<string>
#include<netdb.h>

using namespace std;


struct optr                     // For operator stack
{
	int top=-1;
	char Op_Stack[2000];
};

struct value                     // For operand stack
{
	int head=-1;
	string num_Stack[2000];
};


/*  Function Prototype : void Push(char ch,optr *stack)
    Input :         charachter to be pushed,address of instance of the operator stack where to be pushed
    Output:         Operator Pushed in Operator Stack
    Description:    Perform Push operation in Operator Stack 
*/

void Push(char ch,optr *stack) 
{
   
      stack->top++;
      stack->Op_Stack[stack->top]=ch;
}


/*  Function Prototype: char Pop(optr *stack)
    Input :         address of the instance of the operator stack
    Output:         Operator Poped from Operator Stack,if stack empty then return '#'
    Description:    Perform Pop operation on operator stack 
*/

char Pop(optr *stack) 
{
	if(stack->top<0)
	return '#';
	else {
	char ch=stack->Op_Stack[stack->top];
	stack->top--;
	return ch;
	}
}

/*  Function Prototype : char Top(optr *stack)
    Input :         address of the operator stack
    Output:         Top of the Operator Stack is returned
    Description:    if stack empty then return '#'
*/

char Top(optr *stack)
 {   
	if(stack->top>-1)
	return stack->Op_Stack[stack->top];
	else
	return '#';
 }


/*  Function Prototype : void Push(string s,value *stack) 
    Input :         string(number in form of string) to be pushed in value stack,address of the instance of the value stack
    Output:         string pushed in value stack 
    Description:    perform push operaion in num_Stack
*/
 
  void Push(string s,value *stack) 
  {
	stack->head++;
	stack->num_Stack[stack->head]=s;
   }


/*  Function Prototype: string Pop(value *stack) 
    Input :         address of the instance of the value stack
    Output:         number Poped from the value Stack
    Description:    Perform Pop operation on value stack
*/

string Pop(value *stack) 
{
	if(stack->head<0)
	return 0;
	else 
	{
	string s=stack->num_Stack[stack->head];
	stack->head--;
	return s;
	}
}

/*  Function Prototype: int val(char op)
    Input :         operator as a char
    Output:         return preference value for that operator
*/

int val(char op)
 {
	if(op=='(' || op==')')
	return 5;
	else if(op=='^')
	return 4;
	else if(op=='$')
	return 3;
	else if(op=='*'||op=='/'||op=='%')
	return 2;
	else
	return 1;
 }   

 /*  Function Prototype: bool greater_pref(char op1,char op2)
    Input :         two operators as a char
    Output:         return 1 if op1 has higher or equal peference than op2
*/

 bool greater_pref(char op1,char op2)
 {
  
	if(val(op1)>=val(op2))
	return 1;
	else
	return 0;
 }  
 
 /*  Function Prototype: void send_msg(string s,int &new_sockfd)
    Input :         message to be sent to client as a string,reference to socket id of client
    Output:         message sent to client
*/
 void send_msg(string s,int &new_sockfd)
 {
	
	char message[1024];
	bzero(message,1023);
	strcpy(message, s.c_str());
	int n = write(new_sockfd,message,1023); 
	cout<<"Response sent to the client!"<<endl;
 }
 
  
 /*  Function Prototype: bool isOperator(char op)
    Input :         charachter to be checked if it is operator
    Output:         return 1 if is is operator else return 0
*/

 bool isOperator(char op)
 {
	if(op=='+' || op=='-' || op=='*' || op=='/' || op=='%' || op=='^'||op=='$')
	return 1;
	else
	return 0;
 } 
 
/*  Function Prototype: bool isInteger( string s) 
    Input :         string(number as a string)
    Output:         return 1 if number is integer,if it is float or double then return 0
*/

 bool isInteger( string s) 
 {
	for(int i=0;i<s.size();i++)
	{
	if(s[i]=='.')
	return 0;
	}
	return 1;
 }
 
/*  Function Prototype: bool isBalanced(string ex)
    Input :         expression to be checked if it is balanced
    Output:         return 1 if is is balanced in term of paranthesis else return 0
*/

  bool isBalanced(string ex)
 {
	optr stack;

	for(int i=0;i<ex.size();i++)
	{
	if(ex[i]=='(')
	Push('(',&stack);

	if(ex[i]==')')
	{
	if(Top(&stack)=='(')
	Pop(&stack);
	else
	return 0;

	}
	}

	if(Top(&stack)=='#')
	return 1;
	else
	return 0;

}
 
/*  Function Prototype: bool valid_expr(string expr)
    Input :         expression to be checked if it is valid
    Output:         return 1 if is is valid else return 0
*/

 bool valid_expr(string expr)
 {
  
	if(!isBalanced(expr))
	return 0;

	int count=0,j=-1;

	for(int i=0;i<expr.size();i++)
	{

	if(expr[i]=='\n')
	continue;

	if(count>1)
	{ return 0;}

	if(expr[i]==' '||expr[i]=='	')
	{
	count =0;
	continue;
	}

	if(isOperator(expr[i]))
	{
	count=0;

	if(i==expr.size()-2 )
	{ return 0; } 

	if(i==0 && expr[i]!='$')
	{ return 0; } 

	if(i!=0 && isOperator(expr[j]) )
	{
	return 0;
	}
	}
	else if(isdigit(expr[i]) || expr[i]=='.')
	{
	if(i!=0 && expr[j]==')')
	return 0;

	if(expr[i]=='.')
	count++;
	}
	else if(expr[i]==')' || expr[i]=='(')
	{
	count =0;
	if(i!=0 && (expr[j]=='('&& expr[i]==')' || expr[j]==')'&& expr[i]=='('))
	{
	return 0;
	}

	if(expr[i]=='(' && (isdigit(expr[j]) || expr[j]=='.') )
	return 0;

	}
	else
	{ 
	return 0;}

	j=i;
	}

	if(count>1)
	{ return 0;}
	else
	return 1;
 } 

 /*  Function Prototype : string infix_to_postfix(string line)
    Input :         infix expression(as a string)
    Output:         return postfix expression(as a string) 
    Description:    algorithm to convert infix operation to postfix is implemented in this function
*/

string infix_to_postfix(string line)
{
	struct optr op_stack;
	string postfix="";
	string str="";

	for(int i=0;i<line.size();i++)
	{
	if(line[i]==' ')
	{

	 if(str!="")
	{
	postfix+=str+" ";
	str="";
	}
	 continue;
	}


	if(line[i]=='.' || isdigit(line[i]))
	{

	str+=line[i];

	}
	else if(isOperator(line[i]) || line[i]=='(' || line[i]==')')
	{
	if(str!="")
	{
	postfix+=str+" ";
	str="";
	}

	char ch=Top(&op_stack);

	if(line[i]=='(')
	Push(line[i],&op_stack);
	else if(line[i]==')')
	{
	while(Top(&op_stack)!='(')
	{
	ch=Pop(&op_stack);
	postfix+=ch;
	postfix+=" ";
	}
	Pop(&op_stack);
	}
	else if(ch=='^' && line[i]=='^')
	{
	Push(line[i],&op_stack);
	}
	else if(ch=='(' || ch=='#'|| val(line[i])>val(ch))
	{
	Push(line[i],&op_stack);
	}
	else
	{
	while(Top(&op_stack)!='#' && Top(&op_stack)!='(' && greater_pref(Top(&op_stack),line[i]))
	{
	ch=Pop(&op_stack);
	postfix+=ch;
	postfix+=" ";
	}

	Push(line[i],&op_stack);
	}

	}

	}

	if(str!="")
	{
	postfix+=str+" ";
	str="";
	}

	while(Top(&op_stack)!='#')
	{
	char ch=Pop(&op_stack);
	postfix+=ch;
	postfix+=" ";
	}

	return postfix;
}

/*  Function Prototype: string cal(string s1,string s2,char op)
    Input :         two operand(as a string),then operator as a char
    Output:         return resultant value(as a string) after performing appropriate operation on passed operators
	Description:    convert operands from string to number,perform operation and return appropriate result or msg
*/

string cal(string s1,string s2,char op)
{
	double op1,op2;
	int o1,o2;
 
 
 switch(op)
 {
	case '+':
		if(isInteger(s1) && isInteger(s2))
		{
		o1=stoi(s1); o2=stoi(s2);
		return to_string(o1+o2);
		}
		else
		{
		op1=stof(s1); op2=stof(s2);
		return to_string(op1+op2);
		}
 
  
	case '-': 
		if(isInteger(s1) && isInteger(s2))
		{
		o1=stoi(s1); o2=stoi(s2);
		return to_string(o1-o2);
		}
		else
		{
		op1=stof(s1); op2=stof(s2);
		return to_string(op1-op2);
		}
  
	case '*': 
		if(isInteger(s1) && isInteger(s2))
		{
		o1=stoi(s1); o2=stoi(s2);
		return to_string(o1*o2);
		}
		else
		{
		op1=stof(s1); op2=stof(s2);
		return to_string(op1*op2);
		}

	case '/':
		if(isInteger(s1) && isInteger(s2))
		{
		op1=stof(s1); o2=stoi(s2);

		if(o2!=0)
		return to_string(op1/o2);
		else
		return "&";

		}
		else
		{
		op1=stof(s1); op2=stof(s2);
		if(op2!=0.0)
		return to_string(op1/op2);
		else
		return "&";
		}
  
  
	case '%':  
		if(isInteger(s1) && isInteger(s2))
		{
		o1=stoi(s1); o2=stoi(s2);
		return to_string(o1%o2);
		}
		else
		{
		return "@";
		}
  
	case '^': 
		if(isInteger(s1) && isInteger(s2))
		{
		o1=stoi(s1); o2=stoi(s2);
		return to_string(pow(o1,o2));
		}
		else
		{
		op1=stof(s1); op2=stof(s2);
		return to_string(pow(op1,op2));
		}
 }
 
	return "x";

}

 /*  Function Prototype: string calculate(char op,value &num_stack)
    Input :         operator as a char, reference to the instance of the value stack
    Output:         Pop two values from value stack if available,perform operation,push back result,and return appropriate msg
*/

string calculate(char op,value &num_stack)
{
 double op1;
 int o1;
 string s1,s2;
 
 if(op=='$')
 {
  if(num_stack.head<0)
  return "#";
  s1=Pop(&num_stack);
  if(isInteger(s1))
  {
  o1=stoi(s1);
  string s=to_string(-1*o1);
  Push(s,&num_stack);
  }
  else
  {
   op1=stof(s1);
   string s=to_string(-1*op1);
   Push(s,&num_stack);
  }
  return "1";
 }
 else
 {
    if(num_stack.head<0)
    return "#";
    s2=Pop(&num_stack);
    if(num_stack.head<0)
    return "#";
    s1=Pop(&num_stack);
    string s=cal(s1,s2,op);
    if(s=="&" || s=="@")
    return s;
    Push(s,&num_stack);
    return "1";
 }
 
 return "1";
  
}

/*  Function Prototype : string postfix_eval(string expr)
    Input :         postfix expression(as a string)
    Output:         return result of evaluation of postfix expression or any appropriate msg
    Description:    algorithm to evaluate postfix expression is implemented
*/

string postfix_eval(string expr)
{
 value num_stack;
 
 stringstream ss(expr);
 string line;
 
 while(ss>>line)
 {
   if(isOperator(line[0]))
   {
    string s=calculate(line[0],num_stack);
    if(s=="#"||s=="&" || s=="@")
    return s;
   }
   else
   {
    Push(line,&num_stack);
   }
 }
 
 string res=Pop(&num_stack);
 
 if(num_stack.head<0)
 return res;
 else
 return "#";
}

/*  Function Prototype : int main(int args,char* argv[])
    Input :         port number as acommand line arguement
    Description:    concept of multi-client communication using fork is implemented
*/

int main(int args,char* argv[])
{
 struct sockaddr_in server_addr,client_addr; 
 bzero((char *) &server_addr, sizeof(server_addr)); 
 
 if(argv[1]==NULL)
 {
  cout<<"Please pass the port number"<<endl;
  return 0;
 }
 int port_no=stoi(argv[1]);
 
 server_addr.sin_family = AF_INET; 
 server_addr.sin_addr.s_addr = INADDR_ANY; 
 server_addr.sin_port = htons(port_no); 
 
 int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
 
 if(socket_fd<0)
 {
   perror("socket creation failed!");
   exit(EXIT_FAILURE);
 }
 else
 cout<<"socket created succesfully!"<<endl;
 
 
 
 if(bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
 {
  perror("binding failed,Error!");
  exit(EXIT_FAILURE);
 }
 else
 cout<<"binding done "<<endl;
 int new_sockfd;
 
 
 if (listen(socket_fd, 5) < 0) 
 { 
  perror("Error on listen"); 
  exit(EXIT_FAILURE); 
 } 
 else
 cout<<"Listening..."<<endl;
 
 
 socklen_t client_len=sizeof(client_addr);
 ofstream fout;
 fout.open("server_records.txt",ios::out); 
 fout.close();
 
 
 while(1)
 {
 new_sockfd = accept(socket_fd, (struct sockaddr *) &client_addr,&client_len);
 time_t st,et;
 time(&st);
 
 int pid;
 if(new_sockfd<0)
 { 
  perror("Error in accept"); 
  exit(EXIT_FAILURE); 
 } 
 else
 cout<<"accepted..."<<endl;
 
 cout<<"connected with the client "<<inet_ntoa(client_addr.sin_addr)<<":"<<ntohs(client_addr.sin_port)<<endl;
 

        if ((pid = fork()) == -1)
        {
            close(new_sockfd);
            continue;
        }
        else if(pid > 0)
        {
            close(new_sockfd);
            continue;
        }
        else if(pid == 0)
        {
            char buffer[1024];
           
         while(1)
         {
            bzero(buffer,1024);
 	    int n = read(new_sockfd,buffer,1024);
	 if (n< 0) 
	 {
	  perror("\nClient Error: Reading from Client");
	  exit(EXIT_FAILURE);
	 }
	 
	 if(strncmp("end", buffer, 3)==0)
         break;
         
         cout<<endl<<"client "<<inet_ntoa(client_addr.sin_addr)<<":"<<ntohs(client_addr.sin_port)<<" sent an expression"<<endl;
         cout<<"Received Infix Expression : "<<buffer;
	 
	 string expr="";
	 char PO='&';
	 bool flag=1,f=0;
	 for(int i=0;i<1024;i++)
	 {
	  if(buffer[i]=='\0')
	  break;

	  if(buffer[i]=='$')
	  {
		  send_msg("Invalid expression",new_sockfd);
           f=1;
		   break;
	  }
	  
	  if(!isdigit(PO) && PO!='.' && (buffer[i]==' '|| buffer[i]=='	'))
          continue;
          
          
          if(PO=='(' && buffer[i]=='-')
          expr+='$';
          else if(PO=='(' && isOperator(buffer[i]))
          {
           send_msg("Invalid expression",new_sockfd);
           f=1;
   	   break;
          }
          else if(flag && buffer[i]=='-')
          expr+='$';
          else
          expr+=buffer[i];
          
          flag=0;
          
          PO=buffer[i];
	 }
	 
	 if(f)
	 continue;
	
	 
	 if(flag)
  	 {send_msg("No expression to evaluate!",new_sockfd);
  	  continue;
  	 }
   	 
	 
	 if(!valid_expr(expr))  //checking if expression is valid or not
   	 {send_msg("Invalid expression",new_sockfd);
   	  continue;
   	 }
  	 
  	 string postfix=infix_to_postfix(expr);
  	 
  	 string res=postfix_eval(postfix);
  	 
  	 for(int i=0;i<expr.length();i++)
  	 {
  	  if(expr[i]=='$')
  	  expr[i]='-';
  	 }

	
  	 
  	 for(int i=0;i<postfix.length();i++)
  	 {
  	  if(postfix[i]=='$')
  	  postfix[i]='-';
  	 }
     

  	 if(res=="#")
  	 {
  	  send_msg("Invalid expression",new_sockfd);
  	  continue;
  	 }
  	 else if(res=="&")
  	 {
  	  send_msg("Error!,divide by zero is not permitted",new_sockfd);
  	  continue;
  	 }
  	 else if(res=="@")
  	 {
  	  send_msg("Error!,% operator only works with integers",new_sockfd);
  	  continue;
  	 }
  	 else
  	 {
  	  cout<<"Corresponding Postfix Expression : "<<postfix<<endl;
	  cout<<"Result : "<<res<<endl;
  	  send_msg("Result : "+res+" ,Postfix Expression : "+postfix,new_sockfd);
  	 }
  	 
  	 
	   time(&et);
       double total_time=1.0*(et-st);
  	 ofstream fout;
  	 fout.open("server_records.txt",ios::app); 
  	 expr.erase(expr.end()-1);
  	 fout<<"client_id: "<<inet_ntoa(client_addr.sin_addr)<<":"<<ntohs(client_addr.sin_port)<<" , Infix Expression: "<<expr<<" , Postfix Expression: "<<postfix<<" , Result: "<<res<<" , Time Elapsed(in sec): "<<total_time<<endl;
  	 fout.close();
  	 }
	    cout<<endl<<"client "<<inet_ntoa(client_addr.sin_addr)<<":"<<ntohs(client_addr.sin_port)<<" is disconnecting!"<<endl;
            close(new_sockfd);
            break;
        }
 
 
 
 }
 
 close(socket_fd);
 
 return 0;
}
