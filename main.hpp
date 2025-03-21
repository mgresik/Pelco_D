#include <cstdint>
#include <cstddef>
#include <iostream>

struct Packet
{
    uint8_t sync = 0xFF;
    uint8_t id;
    uint8_t cmd1;
    uint8_t cmd2;
    uint8_t data1;
    uint8_t data2;
    uint8_t crc;
};

enum class State : uint8_t
{
    SYNC,
    ID,
    CMD1,
    CMD2,
    DATA1,
    DATA2,
    CRC,
    ENDED,
};

class Parse
{
private:

public:

    Packet packet;
    State status = State::SYNC;

    Parse() {};
    ~Parse() {};
    void getParse(const std::byte* data, Packet* packet, size_t len);
};
