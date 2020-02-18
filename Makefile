#steganography.exe: Validate_inputs.o Encryption.o Decryption.o main.o
#	 gcc -o steganography.exe Validate_inputs.o Encryption.o Decryption.o main.o -g

#Validate_inputs.o: Validate_inputs.c
#	gcc -c Validate_inputs.c -g

#Encryption.o: Encryption.c
#	gcc -c Encryption.c -g

#Decryption.o:
#	gcc -c Decryption.c -g
     
#main.o: main.c
#	gcc -c main.c -g
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))
steg.exe: $(OBJ)
	gcc -o $@ $^
run: 
	make && ./steganography.exe
   
clean:
	rm *.o *.exe
