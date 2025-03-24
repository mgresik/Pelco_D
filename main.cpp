#include "main.hpp"
#include <string.h>

void Parse::getParse(const std::byte* data, Packet& packet, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        
        switch (status)
        {
            case State::SYNC:
                if (static_cast<uint8_t>(data[i]) == 0xFF)
                {
                    status = State::ID;
                };
                break;
            
            case State::ID:
                memcpy(&packet.id, &data[i], 1);
                status = State::CMD;

                break;

            case State::CMD:
                memcpy(&packet.cmd, &data[i], 2);
                status = State::DATA;
                i++;
                break;
            
            // case State::CMD2:
            //     memcpy(&packet.cmd2, &data[i], 1);
            //     status = State::DATA1;
            //     break;

            case State::DATA:
                memcpy(&packet.data, &data[i], 2);
                status = State::CRC;
                i++;
                break;

            // case State::DATA2:
            //     memcpy(&packet.data2, &data[i], 1);
            //     status = State::CRC;
            //     break;

            case State::CRC:
                if (static_cast<uint8_t>(&data[i]) != (getCrc(packet)))
                {
                    break;
                }
                status = State::ENDED;
                return;

            default:
                status = State::ENDED;
                return;
        };
    };
};

uint8_t Parse::getCrc(const Packet& obj)
{
    uint8_t crc = 0x23;
    ////////
    return crc;
};

int main()
{
    Parse parser;

    std::byte data[0];
    size_t len = 7;

    return 0;
}