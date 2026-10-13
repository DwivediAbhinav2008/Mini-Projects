#include<stdio.h>
#include<stdint.h>
#define VERSION (0xE000) // Version mask
#define TYPE (0x1E00) // Type mask
#define FLAGS (0x01C0) // Flags mask
#define PAYLOADSIZE (0x3F) // payload size mask
void inspect_packet_header(uint16_t rawheader)
{
       // Get version number
       printf("Version is: %hu\n", (rawheader & VERSION) >> 13);
       // Get Type
       printf("Type is: %hu\n", (rawheader & TYPE) >> 9);
       // Get flags
       uint16_t flags = (rawheader & FLAGS) >> 6;
       printf("Flags\n");
       printf("U: %hu, A: %hu, M: %hu\n", (flags >> 2 ) & 1, (flags >> 1) & 1, flags & 1 );
       // Get Payload size in bytes
       printf("Payload size in bytes is: %hu\n", (rawheader & PAYLOADSIZE));

}
