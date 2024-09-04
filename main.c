#include <stdio.h>
#include "socketCAN.h"

int main(void) {
    uint8_t data[8];
    SocketCAN_Create();
    SocketCAN_SetUp("can0");
    SocketCAN_SocketBind();

    data[0] = 1;
    data[1] = 2;
    data[2] = 3;
    data[3] = 4;
    data[4] = 5;
    data[5] = 6;
    data[6] = 7;
    data[7] = 8;
    while(1)
    {
        SocketCAN_SendFrame(data);
    }
}