#include "Chat.h"

Chat::Chat() 
{
    data_count = 0;
    memSize = SIZE;
    data = new AuthData[memSize];
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) 
{
    uint* digest = sha1(_pass, pass_length);
    add(_login, digest);
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) 
{
    int index, i = 0;
    for (; i < memSize; i++) {
        index = hashFunc(_login, i);
        if (data[index].status == Status::free)
            return false;
        else if ((data[index].status == Status::engaged) && !strcmp(_login, data[index].login))
            break;
    }
    if (i >= memSize)
        return false;
    
    uint* digest = sha1(_pass, pass_length);

    bool cmpHashes = !memcmp(
        data[index].pass_sha1_hash,
        digest,
        SHA1HASHLENGTHBYTES);
    delete[] digest;

    return cmpHashes;
}

void Chat::resize() 
{
    AuthData* save = data;
    int save_ms = memSize;

    memSize *= 2;
    data = new AuthData[memSize];
    data_count = 0;

    for (int i = 0; i < save_ms; i++) 
    {
        AuthData& old = save[i];
        if (old.status == Status::engaged) 
        {
            add(old.login, old.pass_sha1_hash);
        }
    }

    delete[] save;
}

void Chat::add(char login[LOGINLENGTH], uint* digest)
{
    int index = -1, i = 0;
    for (; i < memSize; i++) {
        index = hashFunc(login, i);
        if (data[index].status == Status::free)
            break;
    }
    if (i >= memSize)
    {
        resize();
        add(login, digest);
    }
    
    data[index] = AuthData(login, digest);
    data_count++;
}


int Chat::hashFunc(char login[LOGINLENGTH], int offset) {
    long sum = 0;
    for (int i = 0; i < LOGINLENGTH; i++) {
        sum += login[i];
    }
    return (hfMult(sum) + offset * offset) % memSize;
}

int Chat::hfMult(int val) {
    const double A = 0.7;
    return int(memSize * (A * val - int(A * val)));
}

Chat::AuthData::~AuthData() 
{
    if (pass_sha1_hash != 0)
        delete[] pass_sha1_hash;
}

Chat::AuthData::AuthData(char _login[LOGINLENGTH], uint* sh1) 
{
    strcpy_s(login, _login);
    pass_sha1_hash = sh1;
    status = Status::engaged;
}

Chat::AuthData& Chat::AuthData::operator = (const AuthData& other)
{
    strcpy_s(login, other.login);

    if (pass_sha1_hash != 0)
        delete[] pass_sha1_hash;
    pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

    memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
    status = other.status;
    return *this;
}