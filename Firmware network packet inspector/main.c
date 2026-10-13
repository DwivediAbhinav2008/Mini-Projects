#include<stdio.h>
#include<stdint.h>
extern void inspect_packet_header(uint16_t);
int main(void)
{
    uint16_t header = 0x7f;

    inspect_packet_header(header);

    return 0;
}
