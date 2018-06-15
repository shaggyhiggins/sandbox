#include <iostream>

struct Header
{
    int _timestamp {0};
};

struct Data
{
    char *data;
};

class IHandler
{
    virtual void handleHeader() = 0;
    virtual void handleData() = 0;
};

class StreamHandler : public IHandler
{
    virtual void handleHeader()
    {

    }
    virtual void handleData()
    {

    }
};

class Streamer
{
public:
    void registerHandler(IHandler *handler)
    {
        _handler = handler;
    }

private:
    IHandler *_handler;
};

int main(int argc, char const *argv[])
{
    std::cout << "Hello, Cruel World!" << std::endl;

    StreamHandler handler;
    Streamer stream;

    stream.registerHandler(&handler);

    return 0;
}
