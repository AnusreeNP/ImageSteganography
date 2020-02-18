#include "common.h"

//Define the decryption function
void Decryption(char **argv)
{
	//Declare the file pointers
	FILE *fp1, *fp2;

	//Open the destination file
	fp1 = fopen(argv[2], "rb");
	if(fp1 == NULL)
	{
		perror("fopen");
		exit(1);
	}

	//Open the txt file to view secret message
	if(argv[3] == NULL)
	{
		fp2 = fopen("message.txt", "w");
	}
	else
	{
		fp2 = fopen(argv[3], "w");
	}

	//Point the file after header
	fseek(fp1, 54L, SEEK_SET);

	//Call the functions
	Extract_passcode(fp1);
	unsigned int len = Extract_msg_length(fp1);
	Extract_secret_msg(fp1, fp2, len);

	//Close the files
	fclose(fp1);
	fclose(fp2);
}

//Define the function for extracting the passcode
void Extract_passcode(FILE *dest)
{   
	//Declare the variables
	int passcode, i;
	char buff;
	unsigned int hidden_passcode = 0;
    
	//Prompt + Read the passcode
	printf("Enter the passcode:\n");
	scanf("%d", &passcode);

	//Take each byte and extract passcode from lsb bit
	for(i = 0; i < 32; i++)
	{
		fread(&buff, 1, 1, dest);
		hidden_passcode = ((buff & 1) << (31 - i)) | hidden_passcode;
	}
	printf("Hidden passcode is %u\n", hidden_passcode);

	//Check if passcode matches with hidden passcode
	if(passcode != hidden_passcode)
	{
		printf("The passcode doesn't match\n");
	}
	else
	{
		printf("Passcode matches\n");
		return;
	}
}

//Extract the message length in this function
unsigned int Extract_msg_length(FILE *dest)
{
	//Declare the variables
	char buff;int i;
	unsigned int length = 0;

	//Extract the length of message from destination file
	for(i = 0 ;i < 32 ;i++)
	{
		fread(&buff, 1, 1, dest);
		length = ((buff & 1) << (31 - i)) | length;
	}

	//Print the length and return the length
	printf("THE LENGTH OF MESSAGE IS %u\n", length);
	return length;
}

//Define the function to extract the secret message
void Extract_secret_msg(FILE *dest, FILE *sec, unsigned int len)
{
	char buff;
	int i, j;
	unsigned char msg = 0;

	//Extract message and write to txt file
	for(j = 0 ;j < len; j++)
	{ 
		for(i = 0 ;i < 8 ;i++)
		{
			fread(&buff, 1, 1, dest);
			msg = ((buff & 1) << (7 - i)) | msg;
		}
		fwrite(&msg,1,1,sec);
		msg = 0;
	}
}
