#include "common.h"


#include<stdio.h>

int main(int argc, char *argv[])
{
	//Collect the status
	int status = Validate_inputs(argv);
	if (status == ERROR)
	{
		return 0;
	}

	//Check for encryption without error
	if(strcmp(argv[1],"-e") == 0)
	{
		if (status != ERROR)
		{
			Encryption(argv);
			printf("ENCRYPTION DONE SUCCESSFULLY");
			return 0;
		}
	}
	//Check for decryption without error
	else
	{
		if(status != ERROR)
		{
			Decryption(argv);
			printf("DECRYPTION DONE SUCCESSFULLY");
			return 0;
		}
	}
}

