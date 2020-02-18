
#ifndef COMMON_H
#define COMMON_H
#define ERROR -1
#define SUCCESS 1

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int Validate_inputs(char **argv);

void Encryption(char **argv);

void header(FILE *src, FILE *dest);
void passcode(FILE *src, FILE *dest);
int length(FILE *src, FILE *sec, FILE *dest);
void secret(FILE *src, FILE *dest, FILE *sec, int len);
void copydata(FILE *src, FILE *dest);

void Decryption(char **argv);

void Extract_passcode(FILE *dest);
unsigned int Extract_msg_length(FILE *dest);
void Extract_secret_msg(FILE *dest,FILE *sec,unsigned int len);


#endif
