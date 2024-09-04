/**
 * @file SocketCAN.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-09-03
 *
 * @copyright Copyright (c) 2024
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "socketCAN.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
typedef struct can_frame can_frame_t;
/*------------------------------------------------------------------------------
------
------    Macro
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    variables(external)
------
------------------------------------------------------------------------------*/
static int sockfd;
/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
void SocketCAN_Create(const char * socket_name)
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    if ((sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("CANInterface: Error While Opening CAN Socket");
    }
    else {
        // Retrieve the interface index for the interface name (can0, can1, vcan0) to be used to the ifreq struct
        strcpy(ifr.ifr_name, socket_name);

        // Send an I/O control call and pass an ifreq structure containing the interface name
        // ioctl() system call manipulates the underlying device parameters of special files.
        // SIOCGIFINDEX Retrieve the interface index of the interface into ifr_ifindex inside ifr struct.
        ioctl(sockfd, SIOCGIFINDEX, &ifr);

        // set address to all zeros. Done in example/man pages. But why?
        memset(&addr, 0, sizeof(addr));

        // Setup the interface parameters in the socketcan address struct
        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;

        if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("CANInterface: Error while binding to the CAN Socket.");
        }
        else
        {
            printf("The Socket Descriptor is: %d\n", sockfd);
        }
    }
}
void SocketCAN_Destroy()
{
	close(sockfd);
}

BOOL SocketCAN_SendFrame(uint32_t id, uint8_t dlc, const uint8_t * CANMsg)
{
    can_frame_t send_frame;

    send_frame.can_id = id;
    send_frame.can_dlc = dlc;
    memcpy(send_frame.data, CANMsg, send_frame.can_dlc);

    if (write(sockfd, &send_frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("write");
        return FALSE;
    }
    return TRUE;
}

BOOL SocketCAN_ReceiveFrame(uint8_t * CANMsg)
{
    can_frame_t recv_frame;

    int nbytes = read(sockfd, &recv_frame, sizeof(struct can_frame));
    if (nbytes < 0) {
        perror("read");
        return FALSE;
    }
    else
    {
        memcpy(CANMsg, &recv_frame.data, recv_frame.can_dlc);
        return TRUE;
    }
}