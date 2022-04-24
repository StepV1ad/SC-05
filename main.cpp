#include "chat.h"
#include <iostream>
int main()
{
    Chat chat;

    chat.reg((char*)"user", (char*)"12345", sizeof("12345"));
    chat.reg((char*)"qwe", (char*)"qwe", sizeof("qwe"));
    chat.reg((char*)"asdf", (char*)"123t", sizeof("123t"));
    chat.reg((char*)"xzcv1", (char*)"nhjn435", sizeof("nhjn435"));
    chat.reg((char*)"xzcv1", (char*)"nhjn435", sizeof("nhjn435"));
        
    if (chat.login((char*)"user", (char*)"12345", sizeof("12345"))) 
        std::cout << "user log in" << std::endl;
    if (chat.login((char*)"qwe", (char*)"qwe", sizeof("qwe")))
        std::cout << "qwe log in" << std::endl;
    if (chat.login((char*)"asdf", (char*)"123t", sizeof("123t")))
        std::cout << "asdf log in" << std::endl; 
    if (chat.login((char*)"xzcv1", (char*)"nhjn435", sizeof("nhjn435"))) 
        std::cout << "xzcv1 log in" << std::endl;;
    if (chat.login((char*)"xzcv1", (char*)"nhjn435", sizeof("nhjn435")))  
        std::cout << "xzcv1 log in" << std::endl;;
    return 0;
}
