#include "common.h"


//Define the Encryption function
void Encryption(char **argv)
{
	//Declare the file pointers and variabes
	FILE *fp1, *fp2, *fp3;
	int len;

	//Open the source file
	fp1 = fopen(argv[2], "rb");
	if(fp1 == NULL)
	{
		perror("fopen");
		exit(1);
	}

	//Open the destination file
	if(argv[4] == NULL)
	{
		fp2 = fopen("destination.bmp", "wb");
	}
	else
	{
		fp2 = fopen(argv[4],"wb");
	}

	//Open the secret file
	fp3 = fopen(argv[3], "rb");
	if(fp3 == NULL)
	{
		perror("fopen");
		exit(2);
	}

	//Call the functions
	header(fp1, fp2);
	passcode(fp1, fp2);
	len = length(fp1, fp3, fp2);
	secret(fp1, fp2, fp3, len);
	copydata(fp1,fp2);

	//Close the files
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

//Define the header function
void header(FILE *src, FILE *dest)
{   
	//Declare the buffer
	char buffer[54];

	//Read the header part from source and write into destination
	fread(buffer, 1, 54, src);
	fwrite(buffer, 1, 54, dest);
	printf("\nHEADER OF SOURCE FILE COPIED\n");
}

//Define the passcode function
void  passcode(FILE *src, FILE *dest)
{
	//Declare the variables
	int passcode;
	int  i;
	char buff;

	//Prompt + Read inputs from user
	printf("\nEnter the passcode:\n");
	scanf("%d", &passcode);

	//Encoding passcode in source file
	for(i = 0; i < 32; i++)
	{   
		//Open the source file
		fread(&buff, 1, 1, src);
		if(passcode & (1 << (31 - i)))
		{
			buff = buff | 1;
		}
		else
		{
			buff = buff & ~1;
		}
		//Write on destination file
		fwrite(&buff, 1, 1, dest);
	}
	printf("PASSCODE IS SUCCESSFULLY ENCODED\n");
}

//Define function for finding and encoding the length 
int length(FILE *src, FILE *sec, FILE *dest)
{
	//Declare the variables
	int l, i;
	char buff;
	char bits;

	//Count the length of secret file
	fseek(sec, 0, SEEK_END);
	l = ftell(sec);

	//Encode the length of message
	for(i = 0 ;i < 32 ;i++)
	{
		fread(&buff, 1, 1, src);
		if(l & (1 << (31 - i)))
		{
			buff = buff | 1;
		}
		else
		{
			buff = buff & (~1);
		}
		fwrite(&buff, 1, 1, dest);
	}

	//To seek the file at first
	fseek(sec, 0, SEEK_SET);

	//Print the lengthnof file
	printf("LENGTH OF SECRET FILE IS %d\n", l);
	printf("LENGTH OF SECRET FILE IS SUCCESSFULLY ENCODED\n");
	return l;
}

//Define the secret function for encoding secret message
void secret(FILE *src, FILE *dest, FILE *sec, int len)
{
	//Declare the variables
	char buff;
	char bits;
	int i,j;
	fseek(sec, 0, SEEK_SET);
	for(j = 0; j < len; j++)
	{
		//Read the secret file in a variable
		fread(&bits, 1, 1, sec);
		//Encode the message in image file
		for(i = 0 ;i < 8 ; i++)
		{
			//Read the source file in another variable 
			fread(&buff, 1, 1, src);
			if(bits & (1 << (7 - i)))
			{
				buff = buff | 1;
			}
			else
			{
				buff = buff & ~1;
			}
			fwrite(&buff, 1, 1, dest);
		}
	}
	printf("SECRET MESSAGE SUCCESSFULLY ENCODED\n");
	printf("File pointer points to %ld\n", ftell(dest));
}

//Define the function to copy remaining data
void copydata(FILE *src, FILE *dest)
{
	//Declare the buffer
	char buffer;

	//Copy the remaining data to destination file
	while(fread(&buffer, 1, 1, src) > 0)
	{
		fwrite(&buffer, 1, 1, dest);
	}
	printf("REMAINING DATA SUCCESSFULLY COPIED\n");
}
