/* 
 * Project: Float to binary fixed point number converter
 * Author: toms74209200 <https://github.com/toms74209200>
 *
 * Created on 2019/10/15
 * Copyright (c) 2019 toms74209200
 * 
 * A Part that integer to binary convert is based on follow.
 * https://qiita.com/sugunisu/items/c8b20378970467a2ffa4
 * 
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INIT_DATA_LENGTH 16

void float2bin(double, char*, char*, int, int);

int main (int argc, char *argv[]) {
    int digit_int_n;
    int digit_dec_n;

    FILE *p_read_file;
    char *read_file_name;
    double *p_float;
    int data_length;
    int data_array_size;

    if (argc <= 1) {
        printf("Error: no file specified.\n");
        return 0;
    }
    read_file_name = argv[1];

    p_float = (double *)malloc(INIT_DATA_LENGTH*sizeof(double *));

    printf("Integer digits : ");
    scanf("%d", &digit_int_n);
    printf("Decimal digits : ");
    scanf("%d", &digit_dec_n);

    if ((p_read_file = fopen(read_file_name,"r")) == NULL) {
        printf("Error: cannot open file(%s).\n", read_file_name);
        exit(1);
    } else {
        data_length = 0;
        data_array_size = INIT_DATA_LENGTH;
        while (feof(p_read_file) == 0) {
            fscanf(p_read_file, "%lf", &p_float[data_length++]);
            if (data_length > data_array_size) {
                data_array_size <<= 1;
                p_float = realloc(p_float, data_array_size*sizeof(double *));
            }
        }
    }
    fclose(p_read_file);

    FILE *p_write_file;
    char *write_file_name;
    char *bin_int;
    char *bin_dec;

    bin_int = (char *)malloc(digit_int_n);
    bin_dec = (char *)malloc(digit_dec_n);

    if (argc == 2) {
        write_file_name = "out.dat";
    } else {
        write_file_name = argv[2];
    }
    p_write_file = fopen(write_file_name,"w");

        for (int i=0;i<data_length;i++) {
            float2bin(*p_float, bin_int, bin_dec, digit_int_n, digit_dec_n);
            fputs(bin_int, p_write_file);
            fputs(bin_dec, p_write_file);
            fputs("\n", p_write_file);
            p_float++;
        }
    fclose(p_write_file);

    return 0;
}

void float2bin (double data_float, char *bin_int, char *bin_dec, int digit_int, int digit_dec) {
    double int_float;
    double dec_float;

    dec_float = modf(data_float, &int_float);

    unsigned int mask;
    unsigned int n = (int)int_float;

    if (digit_int == 0) {
        ;
    } else if (digit_int == 1) {
        mask = 0x1U;
        *bin_int = (mask&n) ? '1' : '0';
        bin_int++;
    } else {
        for (mask=(0x1U<<(digit_int-1)); mask>0; mask>>=1) {
            *(bin_int++) = (mask&n) ? '1' : '0';
        }
    }
    *bin_int = '\0';
    if (digit_dec == 0) {
        ;
    } else {
        for (int i = 1;i<=digit_dec; i++) {
            if (dec_float >= powf(2,-i)) {
                dec_float = dec_float - powf(2,-i);
                *bin_dec = '1';
            } else {
                *bin_dec = '0';
            }
            bin_dec++;
        }
    }
    *bin_dec = '\0';
}