#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/* Since the largest number is 4294967295, we need 11 characters (including the 
   null character) to read a number from the file */
#define MAX_NUM_LENGTH 12


/* This function checks the number of input parameters to the program to make 
   sure it is correct. If the number of input parameters is incorrect, it 
   prints out a message on how to properly use the program.
   input parameters:
       int    argc
       char** argv 
    return parameters:
       none
 */
void usage(int argc, char** argv)
{
    if(argc < 4) {
        fprintf(stderr, 
                "usage: %s <input file 1> <input file 2> <output file>\n", 
                argv[0]);
        exit(EXIT_FAILURE);
    }
}


/* This function takes in the two input file names (stored in argv) and
   determines the number of integers in each file.
   If the two files both have N integers, return N, otherwise return -1.
   If one or both of the files do not exist, it should exit with EXIT_FAILURE.
   input parameters:
       char** argv
   return parameters:
       -1 if the two input files have different number of integers 
       N  if the two input files both have N integers
 */
int get_num_ints(char** argv)
{
     /* two file names are stored in argv, char** just indicates a pointer to a char poinert */
    // equivalent to char* argv[] which is an array of char pointers
    int count1 = 0;
    int count2 = 0;

    for(int i = 1; i < 3; i++){ 

        FILE* f = fopen(argv[1], "r" );

        // checking if the files exist
        if (f == NULL){
            printf("One or both of the files do not exist.\n");
            exit(EXIT_FAILURE);
        }

        size_t size = MAX_NUM_LENGTH;
        char *buffer = malloc(size * sizeof(char));

        while(getline(&buffer, &size, f) > 0){
            if (atoi(buffer) != 0){
                if(i == 1){
                    count1 += 1;
                }
                else{
                    count2 += 1;
                }
            }
        }
        fclose(f);
        free(buffer);
    }

    // Compare the number of integers in the two files
    if (count1 == count2){
        return count1;
    } else {
        return -1;
    }
}


/* This function allocates enough memory to the three arrays to store
   num_ints elements each.
   This function should exit with EXIT_FAILURE if the program fails to allocate
   the memory.
   input parameters:
       unsigned int*      input_one
       unsigned int*      input_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */
void allocate_mem(unsigned int** input_one, unsigned int** input_two, 
                  unsigned long int** output, int num_ints)
{
    if (input_one == NULL || input_two == NULL){
        printf("One or both of the files do not exist.\n");
        exit(EXIT_FAILURE);
    }
    // allocate memory for the first array
    *input_one = (unsigned int*) malloc(num_ints * sizeof(unsigned int));
    
    // allocate memory for the second array
    *input_two = (unsigned int*) malloc(num_ints * sizeof(unsigned int));    

    *output = (unsigned long int*) malloc(num_ints * sizeof(unsigned long int));
}


/* This function reads in num_ints integers from the two input files and 
   stores them in input_one (first input file) and input_two (second input
   file).
   If one or both of the files do not exist, it should exit with EXIT_FAILURE.
   input parameters:
       char**        argv
       unsigned int* input_one
       unsigned int* input_two
       int           num_ints
   return parameters:
       none

 */



void get_ints(char** argv, unsigned int* input_one, unsigned int* input_two,
              unsigned long int* output, int num_ints)
{
  /* TODO */
    // Open the first input file
    FILE* input_file_1 = fopen(argv[1], "r");
    if (input_file_1 == NULL) {
        printf("Error opening input file 1\n");
        return;
    }
    // Read integers from the first input file and store them in input_one
    int i;
    for (i = 0; i < num_ints; i++) {
        fscanf(input_file_1, "%u", &input_one[i]);
    }
    // Close the first input file
    fclose(input_file_1);

    // Open the second input file
    FILE* input_file_2 = fopen(argv[2], "r");
    if (input_file_2 == NULL) {
        printf("Error opening input file 2\n");
        return;
    }
    // Read integers from the second input file and store them in input_two
    for (i = 0; i < num_ints; i++) {
        fscanf(input_file_2, "%u", &input_two[i]);
    }
    // Close the second input file
    fclose(input_file_2);
}

/* This function does an element-wise addition between the two input arrays 
   (input_one and input_two) of size num_ints and stores the result in the 
   output array (output).
   input parameters:
       unsigned int*      intput_one
       unsigned int*      intput_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */


void sum_ints(unsigned int* input_one, unsigned int* input_two, 
              unsigned long int* output, int num_ints)
{
  /* TODO */
    int i;
    for (i = 0; i < num_ints; i++) {
        output[i] = (unsigned long) input_one[i] + (unsigned long) input_two[i];
    }
}

/* This function saves the summed output to an output file, whose name was 
   specified with the program execution (i.e., argv[3]).
   The file should containe one integer value per line, similarly to how the
   input files were stored.
   input parameters:
       char**             argv
       unsigned int*      intput_one
       unsigned int*      intput_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */
void save_output(char** argv, unsigned int* input_one, unsigned int* input_two,
                 unsigned long int* output, int num_ints)
{
  /* TODO */
    FILE* fp = fopen(argv[3], "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(EXIT_FAILURE);
        return;
    }
    for(int i = 0; i < num_ints; i ++){
        fprintf(fp, "%lu\n", output[i]);
    }
    fclose(fp);
    printf("Output saved to %s\n", argv[3]);
}

/* This program takes in three text file names as input. 
   The first two files contain N integers (where N >=0 and N <= 1,000,000)
   whose values range from 0 to 4294967295 (i.e., 32-bit unsigned integers).
   The last file is the output file that this program should generate.
   For all three files, there should be one integer per line.
  
   For each line in the two input files, read in the two integers, add them, and
   then store the sum in the output file.
   Repeat this process until all integers have been read from the input files.

   For example, if the two input files have eight integerse each
   input file 1		input file 2		output file
   --------------------------------------------------------
   1			2			3
   5			2			7
   8			5			13
   1			12			13
   2			2			4
   10			2			12
   1991			2			1993
   11231245		21235			11252480
 */
int main(int argc, char** argv)
{
    usage(argc, argv);

    // Check the number of integers in the input files
    int num_ints = get_num_ints(argv);
    if(num_ints == -1) {
        fprintf(stderr, "ERR: The two input files have different # of ints\n");
        exit(EXIT_FAILURE);
    } 

    unsigned int* input_one = NULL;
    unsigned int* input_two = NULL;
    unsigned long int* output = NULL;
    // Allocate memory to store the integers
    allocate_mem(&input_one, &input_two, &output, num_ints);

    // Read the integers from the two input files
    get_ints(argv, input_one, input_two, output, num_ints);
   
    // Sum up the numbers
    sum_ints(input_one, input_two, output, num_ints);

    // Store the result in the output file 
    save_output(argv, input_one, input_two, output, num_ints);

    free(input_one);
    free(input_two);
    free(output);

    return 0;
}
