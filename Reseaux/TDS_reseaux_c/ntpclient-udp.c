#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <time.h>

#define SET_LI(packet, li) (uint8_t)(packet.li_vn_mode |= (li << 6))
#define SET_VN(packet, vn) (uint8_t)(packet.li_vn_mode |= (vn << 3))
#define SET_MODE(packet, mode) (uint8_t)(packet.li_vn_mode |= (mode << 0))

#define HOST_NAME "fr.pool.ntp.org"
#define PORT 123

#define NTP_TIMESTAMP_DELTA 2208988800ull

typedef struct
{

    uint8_t li_vn_mode; // Eight bits. li, vn, and mode.
                        // li.   Two bits.   Leap indicator.
                        // vn.   Three bits. Version number of the protocol.
                        // mode. Three bits. Client will pick mode 3 for client.

    uint8_t stratum;   // Eight bits. Stratum level of the local clock.
    uint8_t poll;      // Eight bits. Maximum interval between successive messages.
    uint8_t precision; // Eight bits. Precision of the local clock.

    uint32_t rootDelay;      // 32 bits. Total round trip delay time.
    uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
    uint32_t refId;          // 32 bits. Reference clock identifier.

    uint32_t refTm_s; // 32 bits. Reference time-stamp seconds.
    uint32_t refTm_f; // 32 bits. Reference time-stamp fraction of a second.

    uint32_t origTm_s; // 32 bits. Originate time-stamp seconds.
    uint32_t origTm_f; // 32 bits. Originate time-stamp fraction of a second.

    uint32_t rxTm_s; // 32 bits. Received time-stamp seconds.
    uint32_t rxTm_f; // 32 bits. Received time-stamp fraction of a second.

    uint32_t txTm_s; // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
    uint32_t txTm_f; // 32 bits. Transmit time-stamp fraction of a second.

} ntp_packet; // Total: 384 bits or 48 bytes.
void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    ntp_packet packet = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    memset(&packet, 0, sizeof(ntp_packet));
    SET_LI(packet, 0);
    SET_VN(packet, 3);
    SET_MODE(packet, 3);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int socket_udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_udp < 0)
    {
        error("ERROR OPEN SOCKET");
    }

    server = gethostbyname(HOST_NAME);

    if (server == NULL)
    {
        error("ERROR,CAN'T FIND HOST");
    }

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));

    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (connect(socket_udp, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0)
        error("CANT CONNECT");

    if (write(socket_udp, (char *)&packet, sizeof(ntp_packet)) < 0)
        error("CANT WRITE");

    if (read(socket_udp, (char *)&packet, sizeof(ntp_packet)) < 0)
        error("CANT READ");

    if (write(socket_udp, (char *)&packet, sizeof(ntp_packet)) < 0)
        error("CANT WRITE");

    packet.txTm_s = ntohl(packet.txTm_s);

    time_t txTm = (time_t)(packet.txTm_s - NTP_TIMESTAMP_DELTA);
    printf("timestamps:%ld\n", txTm);
    printf("Time: %s", ctime((const time_t *)&txTm));

    exit(EXIT_SUCCESS);
}