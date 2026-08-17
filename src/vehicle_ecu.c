#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

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

    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, "vcan0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(s, (struct sockaddr *)&addr, sizeof(addr));

    srand(time(NULL));

    struct can_frame frame;

    printf("Vehicle ECU Started\n");

    while (1)
    {
        int speed = rand() % 121;
        int rpm = 800 + rand() % 4201;
        int temp = 20 + rand() % 101;

        frame.can_id = 0x100;
        frame.can_dlc = 1;
        frame.data[0] = speed;
        write(s, &frame, sizeof(frame));

        frame.can_id = 0x101;
        frame.can_dlc = 2;
        frame.data[0] = (rpm >> 8) & 0xFF;
        frame.data[1] = rpm & 0xFF;
        write(s, &frame, sizeof(frame));

        frame.can_id = 0x102;
        frame.can_dlc = 1;
        frame.data[0] = temp;
        write(s, &frame, sizeof(frame));

        printf("Speed=%d km/h RPM=%d Temp=%d C\n",
               speed, rpm, temp);

        sleep(1);
    }

    close(s);
    return 0;
}
