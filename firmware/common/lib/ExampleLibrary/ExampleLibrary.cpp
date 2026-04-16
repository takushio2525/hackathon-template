// ExampleLibrary.cpp — ExampleLibrary.h の実装
#include "ExampleLibrary.h"

int32_t exampleAdd(int32_t a, int32_t b) {
    return a + b;
}

int32_t exampleClamp(int32_t value, int32_t minVal, int32_t maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

ExamplePacket exampleCreatePacket(uint8_t senderId, uint8_t command, int16_t value) {
    ExamplePacket packet;
    packet.senderId = senderId;
    packet.command  = command;
    packet.value    = value;
    return packet;
}
