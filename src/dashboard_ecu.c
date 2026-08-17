#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <net/if.h>

int main()
{
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    int speed = 0;
    int rpm = 0;
    int temp = 0;

    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, "vcan0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(s, (struct sockaddr *)&addr, sizeof(addr));

    printf("Dashboard ECU Started\n");

    while (1)
    {
        read(s, &frame, sizeof(frame));

        if (frame.can_id == 0x100)
        {
            speed = frame.data[0];
        }
        else if (frame.can_id == 0x101)
        {
            rpm = (frame.data[0] << 8) | frame.data[1];
        }
        else if (frame.can_id == 0x102)
        {
            temp = frame.data[0];
        }

        system("clear");

        printf("--------------------------------\n");
        printf("Vehicle Dashboard\n");
        printf("--------------------------------\n");
        printf("Speed       : %d km/h\n", speed);
        printf("Engine RPM  : %d rpm\n", rpm);
        printf("Temperature : %d C\n", temp);
        printf("--------------------------------\n");
    }

    close(s);
    return 0;
}
