#include "common.h"

//Define validate function
int Validate_inputs(char **argv)
{
	//Declare the variables
	size_t no_of_args = 0,i;
	char *ptr;
	int len = 0;
	FILE *fp;
	unsigned short code;

	//Check for count of arguements
	for(i=0 ;argv[i] ;i++)
	{
		no_of_args++;
	}
    
    //Check for 1 arguement
	if (no_of_args == 1) 
	{ 
		printf("INSUFFICIENT ARGUEMENTS\nUSAGE :\n./steganography <option 1> <option 2> <option 3> <option 4>\n");
		printf("Option 1 : '-e'\nOption 2 :.bmp\nOption 3 :.txt\nOption 4 :\n1.bmp\n2.bmp not present\n");
		return ERROR;
	}

	//Check the error case 1:
	if((strcmp(argv[1], "-e") != 0) && (strcmp(argv[1], "-d") != 0))
	{
		printf("INVALID OPTION\nOPTIONS : -e/-d");
		return ERROR;
	}

	//Check the error case to check no of arguements for encryption
	if(strcmp(argv[1], "-e") == 0)
	{
		if (no_of_args < 4 || no_of_args > 5)
		{ 
			printf("INSUFFICIENT ARGUEMENTS\nUSAGE :\n./steganography <option 1> <option 2> <option 3> <option 4>\n");
			printf("Option 1 : '-e'\nOption 2 :.bmp\nOption 3 :.txt\nOption 4 :\n1.bmp\n2.bmp not present\n");
			return ERROR;
		}
	}

	//Check the error case to check no of arguements for Decryption
	if(strcmp(argv[1],"-d") == 0)
	{
		if(no_of_args < 3 || no_of_args > 4)
		{
			printf("INSUFFICIENT ARGUEMENTS\nUSAGE :\n./steganography <option 1> <option 2> <option 3> <option 4>\n");
			printf("Option 1 : '-d'\nOption 2 :.bmp\nOption 3 :\n1.txt\n2.txt not present\n");
			return ERROR;
		}
	}


	//Check for second error case to check whether bmp file or not
	len = strlen(argv[2]);
	if(strcmp((argv[2] + (len - 3)), "bmp") != 0)
	{
		printf("INVALID FILE FORMAT\n");
		return ERROR;
	}

	//Open the bmp file
	if(strcmp(argv[1], "-e") == 0)
	{	
		if((fp = fopen(argv[2], "rb")) == NULL)
		{
			perror("fopen");
			printf("UNABLE TO OPEN SOURCE FILE\n");
			return ERROR;
		}

		//Read two bytes + store it in int variable
		fread(&code, 2, 1, fp);
		if(code != 0x4D42)
		{
			printf("THE OPENED FILE CODE DOESN'T MATCH\n");
			return ERROR;
		}
		fclose(fp);
	}

	//Check for 3rd error case to check whether txt file or not 
	if (argv[3] != NULL)
	{
		len = strlen(argv[3]);
		if(strcmp((argv[3] + (len - 3)), "txt") != 0)
		{
			printf("INVALID FILE FORMAT OF SECRET FILE\n");
			return ERROR;
		}
	}

	//Check 4th error case whether file is bmp or not 
	if((argv[4] != NULL) && (strcmp(argv[1], "-e") == 0))
	{
		len = strlen(argv[4]);
		if(strcmp((argv[4] + (len - 3)), "bmp") != 0)
		{
			printf("INVALID FILE FORMAT FOR .BMP FILE\n");
			return ERROR;
		}
	}
	return SUCCESS;
}
