/*
 *
 * Compiler for the Bare Bones programming language written in C
 * 
 * TJ Liggett
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256		/* Maximum length of a line */
#define MAXVARNAME 10		/* Maximum length of a variable name */

/*
 * Variables are stored in an array (bones). They are retrieved from the 
 * array utilizing the search function.
 */
struct var
{
	char key[MAXVARNAME];	/* variable key: used to find in array */
	int value;		/* variable value: all vars in barebones are ints */
};

/*
 * Instructions are read from a .bb file and stored as the instr structure.
 */
struct instr
{
    char function[MAXVARNAME]; 	/* the function/command of the instruction */
    char variable[MAXVARNAME]; 	/* the impacted variable */
    int loopindex;     		/* For loop instructions, an instruction's loop
    			   	   is stored in the loops array */
};

/*
 * All loops are built and stored in the loops array
 */
struct loop
{
    char boolean[MAXVARNAME];	/* The variable to be checked on each iteration */
    struct instr list[50];	/* The instructions to be executed */
    int length;			/* The length of the loop */
};


int parseLine(char line[MAXLINE], struct instr *command);
int search(char key[], int listlength, struct var bones[]);

int execute(struct instr command, int *listlength, struct var bones[], FILE *fptr, struct loop loops[], int *looplength);

int buildLoop(struct instr *command, int *listlength, struct var bones[], FILE *fptr, struct loop loops[], int *looplength);
int executeLoop(struct instr command, int *listlength, struct var bones[], FILE *fptr, struct loop loops[], int *looplength);

int clear(char key[], int *listlength, struct var bones[]);
int incr(char key[], int listlength, struct var bones[]);
int decr(char key[], int listlength, struct var bones[]);




int main(int argc, char *argv[])
{
	FILE *fptr;
	
	struct var bones[200];	/* All variables are stored here */
	struct loop loops[200]; /* All loops are stored here */
	int listlength = 0; /* length of variable list (bones) */
	int looplength = 0; /* length of loops list */
	
	/* Prints bare bones file name */
	printf("Bare Bones file: %s\n", argv[1]);

	/* attempt to read file argument */	
	if ((fptr = fopen(argv[1], "r")) == NULL)
	{
       		/* Program exits if the file pointer returns NULL. */
       		printf("Error! opening file\n");
		exit(1);
   	}

	/* Read through each line of file, parse instruction, execute */
	char line[ MAXLINE ];	/* File lines are read here */	
	while(fgets(line, sizeof line, fptr) != NULL)
	{
		struct instr command;	   /* The line's instruction */
		

		/* Filters comments, not executed by interpreter */
		if(strstr(line, "#") != NULL)
		{
			continue;
		}
		
		parseLine(line, &command); 
		
		/* Loops are built (recursively) before executed */
		if(strstr(command.function, "while") != NULL)
		{
			buildLoop(&command, &listlength, bones, fptr, loops, &looplength);
			//printf("BUILT LOOP %d\n", command.loopindex);
		}

		/* All instructions (including loops) are executed here */
        	execute(command, &listlength, bones, fptr, loops, &looplength);
		
	}	
	
	/* Just a little flair to the interpreter. Barebones is hard, but everything is greek to me. */
	printf("||barebones φινίρισμα||\n");	

	fclose(fptr); // Close file when program is finished
	exit(0);
}


int execute(struct instr command, int *listlength, struct var bones[], FILE *fptr, struct loop loops[], int *looplength)
{
	//printf("%d	%d", listlength, *listlength);
	int length = *listlength;
	if(strstr(command.function, "while") != NULL)		/* Executes loop instruction here */
	{
	        //printf("Can I get anything?\n");
		executeLoop(command, listlength, bones, fptr, loops, looplength);	
	}
	else if(strstr(command.function, "incr") != NULL) 	/* Increment instruction */
	{
		incr(command.variable, length, bones);
	}
	else if(strstr(command.function, "decr") != NULL)	/* Decrement instruction */
	{
		decr(command.variable, length, bones);
	}
	else if(strstr(command.function, "clear") != NULL)	/* Clear instruction */
	{
		clear(command.variable,	listlength, bones);
	}
	else if(strstr(command.function, "print") != NULL)	/* Print instruction */
	{
		/* NOTE: Print is foreign to */
		int index = search(command.variable, length, bones);
		printf("%s ==> %d\n", command.variable, bones[index].value);
	}
	else
	{
		printf("Error, command %s does not exist", command);
		return -1;
	}
	return 0;
}


int buildLoop(struct instr *command, int *listlength, struct var bones[], FILE *fptr, struct loop loops[], int *looplength)
{
	/* Do while loop stuff */
			
	/* Set up the loop structure */
	char boolean[MAXVARNAME];
	struct loop buildloop;
	struct instr comm;
	comm = *command;
	strcpy(boolean, comm.variable);
	int index = search(comm.variable, *listlength, bones);
	if(index == -1)
	{
		printf("Error accessing variable! %s\n", comm.variable);
		exit(1);
	}
	strcpy(buildloop.boolean, boolean);
	buildloop.length = 0;
	/* Pull loop instructions until loop is done or EOF */
	char line[ MAXLINE ];
	while(fgets(line, sizeof line, fptr) != NULL && strstr(line, ";") == NULL)
	{
		struct instr ins;
	       	if(strstr(line, "#") != NULL)
		{
			continue;
		}	
		//printf("line: %s\n", line);
		parseLine(line, &ins);
		//printf("loopvar: %s\n", buildloop.boolean);
		//printf("func: %s, variable: %s\n", ins.function, ins.variable);
		if(strstr(ins.function, "while") != NULL)
		{
			buildLoop(&ins, listlength, bones, fptr, loops, looplength);
		}	
		buildloop.list[buildloop.length] = ins;
		buildloop.length = buildloop.length + 1;
	}
	loops[*looplength] = buildloop;
	comm.loopindex = *looplength;
	*command = comm;	
	*looplength = *looplength + 1;
	//printf("BUILT LOOP %d\n", comm.loopindex);
	return 0;
}

int parseLine(char line[MAXLINE], struct instr *command)
{
	struct instr ins;
	char function[ MAXVARNAME ];
	char variable[ MAXVARNAME ];
	char * lineptr = strtok(line, " ");
	strcpy(function, lineptr);
	lineptr = strtok(NULL, " ");
	strcpy(variable, lineptr);
	//printf("%s	%s", function, variable);
	strcpy(ins.function, function);
	strcpy(ins.variable, variable);
	// assign ins to command
	*command = ins;
	return 0;

}

int executeLoop(struct instr command, int *listlength, struct var bones[], FILE *fptr, struct loop loops[], int *looplength)
{
	// Executes loop until loop boolean value is 0
	while(1)
	{
		int index, value, loopindex, i;
		loopindex = command.loopindex;
		//printf("Here");
		
		struct loop whileloop = loops[command.loopindex];
		index = search(whileloop.boolean, *listlength, bones);
		value = bones[index].value;
		//printf("value %d\n", value);
		//printf("loop length: %d\n", whileloop.length);	
		if(value == 0)
		{
			return 0;
		}
		for(i=0; i<whileloop.length; i++)
		{
			// executes each stored instruction in the loop
			
			/* For debugging
			struct instr loopcommand; 
			strcpy(loopcommand.function, whileloop.list[i].function);
			char variable[ MAXVARNAME ];
			strcpy(loopcommand.variable, whileloop.list[i].variable);
			printf("func: %s, variable: %s\n", loopcommand.function, loopcommand.variable);
			*/

			execute(whileloop.list[i], listlength, bones, fptr, loops, looplength); 
		}
	}
	
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
	bones[index].value = bones[index].value - 1;
	return bones[index].value;
}

int incr(char key[], int listlength, struct var bones[])
{
	int index;
	if((index = search(key, listlength, bones)) == -1)
	{
		printf("Unknown Variable Error: var %s not declared!", key);
		return -1;
	}
	bones[index].value = bones[index].value + 1;
	return bones[index].value;
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
	while(loc < listlength)
	{
		if(strcmp(bones[loc].key, key) == 0)
		{
			return loc;
		}
		loc++;

	}
	return -1;
}
