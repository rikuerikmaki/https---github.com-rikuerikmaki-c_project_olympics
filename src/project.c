#include "project.h"
#include "stdio.h"
#include "strings.h"
#include "stdlib.h"
#include "string.h"
#define UNINITIALIZED 9999

// Use 


//!!!ATTENTION!!!
//Run the code and write H to see possible commands!


//Olympic medal statistics

/*
The program ranks countries based on medals they've earned. Gold medals are the most valuable, then silver
and bronze medals are the least valuable.
If there is a tie situation with gold medals, the one with most silver medals comes first, and if they are tied too
the one with most bronze medals comes first.
*/

	int memory = 10;
	
	
	
	void init (country *country_list, int s)
	{
	    int i = s;
		while (i < memory) {
		
			country_list[i].gold = UNINITIALIZED;
			i++;
		}
	}
	
	
	int main() {
	    char user_input[1000] = {0};
	    country *countries = (country*)malloc(sizeof(country) * memory);
	    init(countries, 0);
	    while(user_input[0] != 'Q') {
	        fgets(user_input, sizeof user_input, stdin);
	        switch(user_input[0]) {
	            case 'A':
	            addCountry(countries, user_input);
	            break;

	            case 'H':
	            printf("Write 'A country' to add a country\n\n");
				printf("Write 'M country number1 number2 number3' where numbers represent medals\n");
				printf("First number is the amount of gold medals, second silver and third bronze.\n");
				printf("for example, if you added Finland to the list, writing 'M Finland 1 0 1.\n");
				printf("gives Finland one gold and one bronze medal.\n\n");
				printf("Write 'L' to see the statistics.\n\n");
				printf("Write 'Q' to shut down the program.\n\n");
	            break;
	
	            case 'M':
	            addMedal(countries, user_input);
	            break;
	
	            case 'L':
	            printResults(countries);
                printf("SUCCESS\n");
	            break;
	
	            case 'O':
	            countries = loadFile(user_input, countries);

	            break;
	
            default:
	            if (user_input[0] != 'Q') {
	            printf("Invalid command %c\n", user_input[0]);
	            }
	            break;
	        }
	    } printf("SUCCESS\n");
	    free(countries);
        return 1;
	}
	
	
	void addCountry(country *country_list, char *user_input) {


    int c = 0;
	char *p = strtok(user_input, " ");
    char* array[10] = {0};
    while(p != NULL) {                  // split the input and set it to an array
        array[c++] = p;
        p = strtok (NULL, " ");
    }


    if(array[1] == NULL) {
        printf("A should be followed by exactly 1 argument.\n");
        return;    
    }
    if(array[3] != NULL ) {
        printf("A should be followed by exactly 1 argument.\n");
        return;    
    }
    if(c != 2) {
        printf("A should be followed by exactly 1 argument.\n");
        return;
    }

	    int n = 0;
	    while(country_list[n].gold != UNINITIALIZED) {
            if (strcmp(array[1], country_list[n].name) == 0){
                int size = strlen(country_list[n].name); 
                country_list[n].name[size-1] = '\0';                //remove the newliner from strcmp
			    printf("Nation %s is already in the database.\n", country_list[n].name);
			    return;
                }

	        if(memory == (n - 1)) {
	            memory *= 2;
	            country_list = realloc(country_list, sizeof(country) * memory);
	            init(country_list, n);
	        }
	        n++;
	    }
		strcpy(country_list[n].name, array[1]);   //set the new country to the array and initialize it's medals to zero.
	    country_list[n].gold = 0;
	    country_list[n].silver = 0;
	    country_list[n].bronze = 0;
        printf("SUCCESS\n");
	    return;
            }
	
	
	
	void addMedal(country *country_list, char *str) {
	    
	    int k = 0;
	    char *p = strtok(str, " ");
	    char *array[6];
	
	    while(p != NULL) {                          //again split the user input to words and set it to an array
	        array[k++] = p;
	        p = strtok (NULL, " ");
            if (k > 5) { 
                printf("M should be followed by exactly 4 arguments.\n");			//Check that user writes the right amount of arguments
                return;
            }
	    }
        if (k != 5) {
            printf("M should be followed by exactly 4 arguments.\n");
            return;
            }
	    int goldmedals = atoi(array[2]);                //change medals to int format
	    int silvermedals = atoi(array[3]);
	    int bronzemedals = atoi(array[4]);
	
	
	    char *findCountry = array[1];
	    int j = 0;
	    int i = -1;
	    while(country_list[j].gold != UNINITIALIZED) {
	        if (strstr(country_list[j].name, findCountry) != NULL) {            //check if the country exists
	            i = j;
	        }
	        j++;
	    }
	    if (i != -1) {
	        country_list[i].gold += goldmedals;             //add medals
	        country_list[i].silver += silvermedals;
	        country_list[i].bronze += bronzemedals;
	    } else {
	            printf("No such a country found\n");
	        }
            printf("SUCCESS\n");
	}
	
	
	    int cmpfunc (const void *a, const void *b) {            //compare function to set countries to correct order
	
	        country *c1 = (country *)a;
	        country *c2 = (country *)b;
	
	        if(c1->gold == c2->gold) {
	            if (c1->silver == c2->silver) {
	                return(c2->bronze - c1->bronze);
	            } else return(c2->silver - c1->silver);
	        } else return(c2->gold - c1->gold);
	    }
	
	void printResults(country *country_list) {
	    
	    int n = 0;
	    int size = 0;
	    while(country_list[size].gold != UNINITIALIZED) {
	        size++;
	    }
	
	    qsort(country_list, size, sizeof(country), cmpfunc);        //sort countries
	
	    while(country_list[n].gold != UNINITIALIZED) {

            char *newline = strchr( country_list[n].name, '\n' );           //get rid of newline
                if ( newline )
                *newline = 0;

	        printf("%s %u %u %u\n",
            country_list[n].name,
            country_list[n].gold,
            country_list[n].silver,
            country_list[n].bronze);
	        n++;
	    }
	}
	
	
	
	country* loadFile(char *filename, country *countries) {
	    int b = 1000;
	    char line[b];
	    char *p = filename + 2;
	    sscanf(p, "%s", line);
	   FILE *fp = fopen(line, "r");                 //          test :    "./src/textfile.txt"
	
	   if (fp == NULL) {
	       printf("Cannot open file invalid-test.txt for reading.\n");
	       return countries;
	   } else {
	    free(countries);
	    country *countries = (country*)malloc(sizeof(country) * memory);
	    init(countries, 0);
	    while(feof(fp) == 0) {
	       if (fgets(line, b, fp) == NULL) {
	           break;
	       }
	       switch(line[0]) {
	            case 'A':
	            addCountry(countries, line);
	            break;
	
	            case 'M':
	            addMedal(countries, line);
	            break;
	
	            case 'L':
	            printResults(countries);
	            break;
	            }
	        }

       printf("SUCCESS\n");
	   fclose(fp);
	   return countries;
       }
	}