/*
 *
 * Compiler for the Bare Bones programming language written in C
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct var
{
	char key[10];
	int value;
};


int main(int argc, char *argv[])
{
	FILE *fptr;
	
	struct var bones[200];
	struct var *listptr = &bones[0]; // pointer for the variable list
	int listlength = 0; // length of variable list

	/*
	// search testing
	struct var b1, b2, b3;
	strcpy(b1.key, "apple");
	b1.value = 4;
	strcpy(b2.key, "orange");
	b2.value = 5;
	strcpy(b3.key, "banana");
	b3.value = 6;
	
	bones[0] = b1;
	bones[1] = b2;
	bones[2] = b3;
	listlength = 3;

	//int index = search("orange", listlength, bones);

	//printf("search for orange in bones: %d\n", index);
	
	clear("banana", &listlength, bones);
	clear("taco", &listlength, bones);
	incr("banana", listlength, bones);
	decr("orange", listlength, bones);
	//printf("List length: %d\n banana value = %d", listlength, bones[search("banana", listlength, bones)].value);	
	//printf("List length: %d\n orange value = %d", listlength, bones[search("orange", &listlength, bones)].value);
	*/
	// print the name of the file	
	printf("Bare Bones file: %s\n", argv[1]);

	// attempt to read file argument	
	if ((fptr = fopen(argv[1], "r")) == NULL)
	{
       		printf("Error! opening file\n");
       		// Program exits if the file pointer returns NULL.
       		exit(1);
   	}
	
	char line[ 256 ];	
	while(fgets(line, sizeof line, fptr) != NULL)
	{
		char command[10];
		char variable[10];
		char * lineptr = strtok(line, " ");
		strcpy(command, lineptr);
		lineptr = strtok(NULL, " ");
		strcpy(variable, lineptr);
		printf("%s	%s\n", command, variable);
		// Execute the desired command
		execute(command, variable, &listlength, bones);
	
	}	
	
	printf("We read it!\n");	
	fclose(fptr); // Close file when program is finished
	
	exit(0);
}


int execute(char command[], char variable[], int *listlength, struct var bones[])
{
	//printf("%d	%d	%d", listlength);
	if(strcmp(command, "incr") == 0)
	{
		incr(variable, listlength, bones);
	}
	else if(strcmp(command, "decr") == 0)
	{
		decr(variable, listlength, bones);
	}
	else if(strcmp(command, "clear") == 0)
	{
		clear(variable,	listlength, bones);
	}
	else if(strcmp(command, "print") == 0)
	{
		int index = search(variable, listlength, bones);
		printf("%s: %d\n", variable, bones[index].value);
	}
	else
	{
		printf("Error, command %s does not exist", command);
		return -1;
	}
	return 0;
}


int decr(char key[], int listlength, struct var bones[])
{
	int index;
	if((index = search(key, listlength, bones)) == -1)
	{
		printf("Unknown Variable Error: Var %s not declared!", key);
		return -1;
	}
	if(bones[index].value == 0)
	{
		return 0;
	}
	return --bones[index].value;
}

int incr(char key[], int listlength, struct var bones[])
{
	int index;
	if((index = search(key, listlength, bones)) == -1)
	{
		printf("Unknown Variable Error: var %s not declared!", key);
		return -1;
	}
	return ++bones[index].value;
}


int clear(char key[], int *listlength, struct var bones[])
{
	struct var bone;
	strcpy(bone.key, key);
	bone.value = 0;
	int index;
	if((index = search(key, *listlength, bones)) == -1)
	{
		bones[*listlength] = bone;
		*listlength = *listlength + 1;
		return 0;
	}
	bones[index] = bone;
	return -1;	

}


// search finds var in map and returns ptr to var
// if var does not exist, returns NULL
int search(char key[], int listlength, struct var bones[])
{
	int loc = 0;
	//printf("%d", *listlength);
	while(loc < listlength)
	{
		if(strcmp(bones[loc].key, key) == 0)
		{
			//printf("found it!");
			return loc;
		}
		loc++;

	}
	return -1;
}
