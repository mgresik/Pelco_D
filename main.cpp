#include "main.hpp"
#include <cstring>

void Parse::getParse(const std::byte* data, Packet* packet, size_t len)
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
                memcpy(&packet->id, &data[i], 1);
                status = State::CMD1;
                break;

            case State::CMD1:
                memcpy(&packet->cmd1, &data[i], 1);
                status = State::CMD2;
                break;
            
            case State::CMD2:
                memcpy(&packet->cmd2, &data[i], 1);
                status = State::DATA1;
                break;

            case State::DATA1:
                memcpy(&packet->data1, &data[i], 1);
                status = State::DATA2;
                break;

            case State::DATA2:
                memcpy(&packet->data2, &data[i], 1);
                status = State::CRC;
                break;

            case State::CRC:
                memcpy(&packet->crc, &data[i], 1);
                status = State::ENDED;
                break;

            default:
                status = State::ENDED;
                break;
            // Тут возможно надо добавить проверку что все поля заполнены
            // выскочить из функции ?
        };
    };
};

int main()
{
    Parse parser;

    std::byte data[0];
    size_t len = 7;

    return 0;
}