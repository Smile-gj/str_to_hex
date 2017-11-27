#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned int    u_int32_t;
#define MAX_BUFFER_LENGTH ((65536 * 2) + 4096)
/* same as above but working with a static buffer */
u_int32_t ByteStrToHexStr(const u_char *xdata, int length,char *retbuf)
{
    char conv[] = "0123456789ABCDEF";
    const u_char *index;
    const u_char *end;
    char *ridx;

    if( (xdata == NULL) ||
	(retbuf == NULL) ||
	(((length *2) + 1) > MAX_BUFFER_LENGTH))
    {
		return 1;
    }

    index = xdata;
    end = xdata + length;
    
    memset(retbuf,'\0',MAX_BUFFER_LENGTH);
    
    ridx = retbuf;
    
    while(index < end)
    {
        *ridx++ = conv[((*index & 0xFF)>>4)];
        *ridx++ = conv[((*index & 0xFF)&0x0F)];
        index++;
    }
    
    return 0;
}
u_int32_t HexStrToByteStr(const u_char * src_buf, char * dest_buf, int src_len)
{
    u_char highByte, lowByte;
    if(NULL == src_buf)
		return 1;
	const u_char * index = src_buf, * end = src_buf + src_len;
    char * ridx = dest_buf;
    
    while (index < end)
    {
        highByte = toupper(* (index ++));
        lowByte  = toupper(* (index ++));

        if (highByte > 0x39)
            highByte -= 0x37;
        else
            highByte -= 0x30;

        if (lowByte > 0x39)
            lowByte -= 0x37;
        else
            lowByte -= 0x30;

        *ridx++ = (highByte << 4) | lowByte;
    }
    return 0;
}
int main(int argc,char *argv) 
{
	//u_char src_buf[1024] = "wwwwwwwwwwwwwwwweeeeeeeeeeeeeeeeeeeeaaaaaaaaaaaaaaaa888833333sssssssssssssss";
	//u_char src_buf[1024] = "Content-Length: 5667\r\nContent-Type: text/xml; charset=\"utf-8\"\r\nServer: Microsoft-Windows-NT/5.1 UPnP/1.0 UPnP-Device-Host/1.0 Microsoft-HTTPAPI/2.0\r\nDate: Wed, 22 Nov 2017 02:03:30 GMT\r\nConnection: close\r\n";
	u_char src_buf[1024] = "<icon>\r\n	\
				<mimetype>image/jpeg</mimetype>\r\n	\
				<width>120</width>\r\n	\
				<height>120</height>\r\n	\
				<depth>24</depth>\r\n	\
				<url>/upnphost/udhisapi.dll?content=uuid:c468f590-cff7-4b9f-934d-2e1b026ab655</url>\r\n	\
			</icon>\r\n";
	printf("src_buf is :%s\n",src_buf);
	u_char dest_buf[MAX_BUFFER_LENGTH + 1];
	ByteStrToHexStr(src_buf,strlen(src_buf),dest_buf);
	printf("dest_buf is :%s\n",dest_buf);
	char de_dest_buf[MAX_BUFFER_LENGTH + 1] = {0};
	//HexToStr(de_dest_buf,dest_buf,strlen(dest_buf));
	HexStrToByteStr(dest_buf, de_dest_buf, strlen(dest_buf));
	printf("de dest buf is :%s\n",de_dest_buf);
	return 0;
}

