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

#define DATA_LENGTH 256
#define DIGIT_INT_N 8
#define DIGIT_DEC_N 8

void float2bin(double, char*, char*, int, int);

void main (void) {
    FILE *p_read_file;
    char *read_file_name;
    double *p_float;
    double array_float[DATA_LENGTH];

    p_float = &array_float[0];

    read_file_name="test.dat";

    if ((p_read_file = fopen(read_file_name,"r")) == NULL) {
        printf("Error: cannot open file(%s)\n", read_file_name);
        exit(1);
    } else {
        for (int i=0;i<DATA_LENGTH;i++) {
            fscanf(p_read_file, "%lf", p_float);
            p_float++;
        }
    }
    fclose(p_read_file);

    p_float = &array_float[0];

    FILE *p_write_file;
    char *write_file_name;
    char *bin_int;
    char *bin_dec;
    char array_bin_int[8];
    char array_bin_dec[8];

    bin_int = &array_bin_int[0];
    bin_dec = &array_bin_dec[0];

    write_file_name = "out.dat";
    p_write_file = fopen(write_file_name,"w");

        for (int i=0;i<256;i++) {
            float2bin(*p_float, bin_int, bin_dec, DIGIT_DEC_N, DIGIT_INT_N);
            fputs(bin_int, p_write_file);
            fputs(bin_dec, p_write_file);
            fputs("\n", p_write_file);
            p_float++;
        }
    fclose(p_write_file);
}

void float2bin (double data_float, char *bin_int, char *bin_dec, int digit_int, int digit_dec) {
    double int_float;
    double dec_float;

    dec_float = modf(data_float, &int_float);

    unsigned int mask;
    unsigned int n = (int)int_float;

    if (digit_int == 0) {
        ;
    } else {
        for (mask=(0x1U<<(digit_int-1)); mask>0; mask>>=1) {
            *(bin_int++) = (mask&n) ? '1' : '0';
        }
    }
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
            if (i < digit_dec)
                bin_dec++;
        }
    }
}