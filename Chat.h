#pragma once
#include "sha1.h"
#include <cstring>

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
public:
    Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);
        
private:
    enum class Status 
    {
        free,
        engaged,
        deleted
    };

    struct AuthData 
    {
        AuthData() : login(""), pass_sha1_hash(0), status(Status::free) {}
        ~AuthData();
        AuthData(char _login[LOGINLENGTH], uint* sh1); 
        AuthData& operator = (const AuthData& other);

        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
        Status status;
    };

    AuthData* data;
    int data_count;
    int memSize;

    int hashFunc(char login[LOGINLENGTH], int offset);
    int hfMult(int val);
    void resize();
    void add(char login[LOGINLENGTH], uint* digest);
};