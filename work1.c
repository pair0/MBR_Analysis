#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct Parition_Table {
    u_int8_t booting;
    u_int8_t cls2_123[3];
    u_int8_t file_system;
    u_int8_t cls3_123[3];
    u_int32_t start_address;
    u_int32_t size;
};

int main(int argc, char **argv){
    if (argc != 2) {
		printf("Usage: %s <file 1>\n", *(argv+0));
		return 0;
	}

    FILE *fp;
    struct Parition_Table *PTB = (struct Parition_Table *)malloc(sizeof(struct Parition_Table));
    u_int32_t ebr_base, ebr_carry = 0;
    int count = 0;
    fp = fopen(*(argv+1), "rb");
    fseek(fp, 446, SEEK_SET);
    
    while(1){
        fread(PTB, sizeof(* PTB), 1, fp);

        if(PTB->file_system == 00) break;

        if(PTB->file_system == 07){
            printf("%02x ", PTB->file_system);  //파일시스템타입
            printf("%d ", (PTB->start_address*512) + ebr_carry); //실 시작 Sector 위치
            printf("%d", PTB->size*512); //Size
            printf("\n");
        }

        if(PTB->file_system == 05){
            fseek(fp, (PTB->start_address*512+ebr_base)+446, SEEK_SET);
            ebr_carry = PTB->start_address*512+ebr_base;
            if(count == 0) ebr_base = PTB->start_address*512; //EBR의 Base 값 저장
            count ++;
        }
    }
    free(PTB);
    fclose(fp);
}