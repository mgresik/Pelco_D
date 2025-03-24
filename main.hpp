#include <cstdint>
#include <cstddef>
#include <iostream>

struct Packet
{
    uint8_t sync = 0xFF;
    uint8_t id;
    uint16_t cmd;
    uint16_t data;
    uint8_t crc;
};

enum class State : uint8_t
{
    SYNC,
    ID,
    CMD,
    // CMD2,
    DATA,
    // DATA2,
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
    void getParse(const std::byte* data, Packet& packet, size_t len);
    uint8_t getCrc(const Packet& obj);
};
