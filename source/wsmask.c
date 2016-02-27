#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#include "structures.h"

enum { // operation mode
	MODE_MASK,
	MODE_UNMASK
};

enum { // opcode
	OPCODE_TXT = 0x01,
	OPCODE_BIN = 0x02
};

void print_usage(char *argv0)
{
	fprintf(stderr, "usage: %s -t|b -m|u [-k xxxxxxxx] -i input.bin -o output.bin\n", argv0);
}

void mask(char* fdin, unsigned char *masking_key, unsigned char opcode, int32_t fd)
{
	unsigned long long int payload_size, lli;
	struct stat stat;
	unsigned char header[14];
	unsigned char buf[1];
	int header_size = 0;

	payload_size = strlen(fdin);
	//assert(payload_size > 0 && masking_key != 0);

	//fstat(fdin, &stat);
	//fprintf(stderr, "payload size: %lld\n", payload_size);
	//fprintf(stderr, "maskingkey: %02x%02x%02x%02x\n", 
	//	masking_key[0], masking_key[1], masking_key[2], masking_key[3]);

	header_size = 0;
	header[header_size++] = 0x80 | opcode;
	if (payload_size <= 125) {
		header[header_size++] = payload_size | 0x80;
	} else if (payload_size <= 65535) {
		header[header_size++] = 126 | 0x80;
		header[header_size++] = (payload_size >> 8) & 0xff;
		header[header_size++] = payload_size & 0xff;
	} else {
		header[header_size++] = 127 | 0x80;
		header[header_size++] = (payload_size >> 56) & 0xff;
		header[header_size++] = (payload_size >> 48) & 0xff;
		header[header_size++] = (payload_size >> 40) & 0xff;
		header[header_size++] = (payload_size >> 32) & 0xff;
		header[header_size++] = (payload_size >> 24) & 0xff;
		header[header_size++] = (payload_size >> 16) & 0xff;
		header[header_size++] = (payload_size >> 8) & 0xff;
		header[header_size++] = payload_size & 0xff;
	}
	header[header_size++] = masking_key[0];
	header[header_size++] = masking_key[1];
	header[header_size++] = masking_key[2];
	header[header_size++] = masking_key[3];

        int offset = 0;
        char header_str[payload_size];
        //int buffer;

        //printf("boop\n");
	for (lli=0; lli<payload_size; lli++) {
            char c = fdin[lli];
            c = c ^ masking_key[lli%4];
            header_str[lli] = c;
	}
        //printf("bop\n");

        char final[header_size + payload_size];
        offset = 0;
        offset += sprintf(final + offset, header);
        offset += sprintf(final + offset, header_str);
        //buf[header_size + payload_size] = "\0";


                char* first = concatinate("PRIVMSG #3dshacks :", global.message);
                char* last = concatinate(first, "\r\n");
                int len = strlen(last);
                
                send(global.t, last, len, 0);
                char* m1 = concatinate("<", global.handle);
                char* m2 = concatinate(m1, "> ");
                global.ourMessage = concatinate(m2, global.message);
                global.sent = 1;
                global.message = "";



//	send(fd, global.message, strlen(global.message), 0);
        //char buff[1024*1024];
        //read(fd,buff,1024*1024);
        //printf("beep");
}

void unmask(char* fdin, int32_t fd)
{
	unsigned long long int payload_size, lli;
	unsigned long long int file_size;
	struct stat stat;
	unsigned char header[14];
	unsigned char buf[1];
	unsigned char masking_key[4];
	int header_size = 0;
	int masked = 0;

        int payload = strlen(fdin);
	assert(payload > 0 > 0);

//	fstat(fdin, &stat);
	file_size = payload;

        int index = 0;
	header[0] = fdin[index++];
	if (header[0] == 0x82) {
		//fprintf(stderr, "header[0]: %02x\n", header[0]);
	} else {
		fprintf(stderr, "header[0]: %02x (!=0x82)\n", header[0]);
	}

	header[0] = fdin[index++];
	if (header[0] & 0x80) {
		masked = 1;
		//fprintf(stderr, "masked\n");
	} else {
		masked = 0;
		fprintf(stderr, "not masked!\n");
	}

	payload_size = header[0] & 0x7f;
	if (payload_size <= 125) {
	} else if (payload_size == 126) {
            memcpy(header, fdin[index+=2], 2);
//		read(fdin, header, 2);
		payload_size = (unsigned int)header[0] << 8 | header[1];
	} else {
            memcpy(header, fdin[index+=8], 8);
//		read(fdin, header, 8);
		payload_size =
			(unsigned long long int)header[0] << 56 |
			(unsigned long long int)header[1] << 48 |
			(unsigned long long int)header[2] << 40 |
			(unsigned long long int)header[3] << 32 |
			(unsigned long long int)header[4] << 24 |
			(unsigned long long int)header[5] << 16 |
			(unsigned long long int)header[6] << 8 |
			header[7];
	}
	fprintf(stderr, "payload size: %lld\n", payload_size);

	if (masked) {
            memcpy(masking_key, fdin[index+=4], 4);
//		read(fdin, masking_key, 4);
	} else {
		masking_key[0] = 0x00;
		masking_key[1] = 0x00;
		masking_key[2] = 0x00;
		masking_key[3] = 0x00;
	}
	fprintf(stderr, "maskingkey: %02x%02x%02x%02x\n", 
		masking_key[0], masking_key[1], masking_key[2], masking_key[3]);

	for (lli=0; lli<payload_size; lli++) {
		buf[0] = fdin[lli];
		buf[0] = buf[0] ^ masking_key[lli%4];
		write(fd, buf, 1);
	}
}

int masking_ops(char *string, char *argv, int32_t fd, int mode)
{
	unsigned char masking_key[] = {0xde, 0xad, 0xbe, 0xef};
	int fdin = -1, fdout = -1;
	int opmode = -1;
	unsigned char opcode = OPCODE_BIN;
	unsigned char buf[9];
	unsigned int tmp[4];
	int ret;
        int argc = 2;

        opcode = OPCODE_TXT;
        opmode = mode == 0 ? MODE_MASK : MODE_UNMASK;
//	while ((ret = getopt(argc, argv, "tbmuk:i:o:")) != -1) {
//		switch(ret) {
//		case 't':
//			opcode = OPCODE_TXT;
//			break;
//		case 'b':
//			opcode = OPCODE_BIN;
//			break;
//		case 'm': 
//			opmode = MODE_MASK;
//			break;
//		case 'u': 
//			opmode = MODE_UNMASK;
//			break;
//		case 'k': 
////			strncpy(buf, optarg, 8);
//			buf[8] = '\n';
//			sscanf(buf, "%02x%02x%02x%02x", &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
//			masking_key[0] = tmp[0];
//			masking_key[1] = tmp[1];
//			masking_key[2] = tmp[2];
//			masking_key[3] = tmp[3];
//			break;
//		case 'i': 
////			fdin = open(optarg, 0);
//			if (fdin < 0) {
////				fprintf(stderr, "cannot open: %s\n", optarg);
//				return 1;
//			}
//			break;
//		case 'o': 
////			fdout = open(optarg, O_CREAT|O_RDWR|O_TRUNC, 0644);
//			if (fdout < 0) {
////				fprintf(stderr, "cannot open: %s\n", optarg);
//				return 1;
//			}
//			break;
//		default:
//			print_usage(argv[0]);
//			return -1;
//		}
//	}

//	if (opmode == -1 || fdin == -1 || fdout == -1) {
//		print_usage(argv[0]);
//		return -1;
//	}

	if (opmode == MODE_MASK) {
		//printf("masking mode\n");
		mask(string, masking_key, opcode, fd);
	} else {
		//printf("unmasking mode\n");
		unmask(fdin, fd);
	}

	//close(fdin);
	//close(fdout);
}