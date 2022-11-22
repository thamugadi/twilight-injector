#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QLD 0x4040 
#define QLD1 0x4048
#define OFFSET_BACKUP 0x2000
#define CHECKSUM 0x603c
#define QLD1_CHECKSUM 0x4ad4
#define QLD1_NSM 0x4ad8
#define LINK 0x41fc
#define EPONA 0x420D

#define LE2BE(n) { (n >> 24) & 255, \
                 (n >> 16) & 255, \
                 (n >> 8)  & 255, \
                 (n >> 0)  & 255 }

unsigned int checksum(unsigned char* qld)
{
        unsigned short qld_u16;
        unsigned int csm;
        unsigned int nsm;
        for (int i = 0; i < (CHECKSUM-QLD); i+=2)
        {
                qld_u16 = ((qld[i]) << 8) | qld[i+1];
                csm += qld_u16;
                nsm += ~qld_u16;
                nsm &= 0xffff;
        }
        return ((csm << 0x10) & 0xffff0000) + nsm;
}

int main(int argc, char** argv)
{
        if (argc != 2) return -1;
        unsigned char qld1[0x2000];
        unsigned char qld[0x2000];
        unsigned int qld1_csm = 0;
        unsigned int qld1_nsm = 0;
        unsigned int qld_csm = 0;
        unsigned char code[0x1000];   
        unsigned char ret_addr[] = {0x80, 0x3e, 0xd2, 0x14};
        unsigned char aligner[7] = "ALIGN..";

        FILE* fp_code = fopen("code.bin", "r");
        fread(code, 1, 0x1000, fp_code);
        fclose(fp_code);

        FILE* fp = fopen(argv[1], "r+");
        fseek(fp, EPONA, SEEK_SET);
        char padding = 'A';
        for (int i = 0; i < 0xe4; ++i) fwrite(&padding, 1, 1, fp);
        fwrite(ret_addr, 4, 1, fp);
        fwrite(aligner, 7, 1, fp);
        fseek(fp, 0x4314, SEEK_SET);
        for (int i = 0; i < 0x68; ++i) fwrite(&padding, 1, 1, fp);
        fwrite(code, 0x1000, 1, fp);

        //Fixing checksums:

        fseek(fp, QLD1, SEEK_SET);
        fread(qld1, QLD1_CHECKSUM-QLD1, 1, fp);
        for (int i = 0; i < QLD1_CHECKSUM-QLD1; i++) qld1_csm += qld1[i];
        for (int i = 0; i < QLD1_CHECKSUM-QLD1; i++) qld1_nsm += ~qld1[i];

        printf("qld1 checksum: %x\n", qld1_csm);
        printf("qld1 checksum: %x\n", qld1_nsm);

        fseek(fp, QLD, SEEK_SET);
        fread(qld, CHECKSUM-QLD, 1, fp);

        qld_csm = checksum(qld);
        printf("qld checksum: %x\n", qld_csm);

        unsigned char qld_csm_bytes[] = LE2BE(qld_csm);
        unsigned char qld1_csm_bytes[] = LE2BE(qld1_csm);
        unsigned char qld1_nsm_bytes[] = LE2BE(qld1_nsm);

        fseek(fp, CHECKSUM, SEEK_SET);
        fwrite(qld_csm_bytes, 4, 1, fp);

        fseek(fp, QLD1_CHECKSUM, SEEK_SET);
        fwrite(qld1_csm_bytes, 4, 1, fp);

        fseek(fp, QLD1_NSM, SEEK_SET);
        fwrite(qld1_nsm_bytes, 4, 1, fp);

        fclose(fp);
}
