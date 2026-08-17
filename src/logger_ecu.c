#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

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

    FILE *logfile;

    logfile = fopen("can_log.csv", "w");

    fprintf(logfile,
            "Timestamp,CAN_ID,DLC,Payload\n");

    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, "vcan0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(s, (struct sockaddr *)&addr, sizeof(addr));

    printf("Logger ECU Started\n");

    while (1)
    {
        read(s, &frame, sizeof(frame));

        time_t now = time(NULL);

        fprintf(logfile,
                "%ld,0x%X,%d,",
                now,
                frame.can_id,
                frame.can_dlc);

        for (int i = 0; i < frame.can_dlc; i++)
        {
            fprintf(logfile,
                    "%02X",
                    frame.data[i]);
        }

        fprintf(logfile, "\n");
        fflush(logfile);

        printf("Logged CAN ID: 0x%X\n",
               frame.can_id);
    }

    fclose(logfile);
    close(s);

    return 0;
}
