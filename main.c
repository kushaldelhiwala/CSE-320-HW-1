#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int stringcomp(char *string1, char *string2) {
    while (*string1 && *string2 && *string1 == *string2){
    	 string1++;
	 string2++;
    }
    return (unsigned char)(*string1) - (unsigned char)(*string2);
}

int myStringLength(char *str){
	int length = 0;
	while (*str != 0){
		str++;
		length++;
	}
	return length;
}

typedef struct art_pieces{
	struct art_pieces* next;
	struct art_pieces* prev;
	int art_id;
	char *art_type;
	char *art_name;
	char *artist_name;
	int price;
} art_pieces;

int main(int argc, char** argv) {
	int b_flag = 0;
	char *budget;
	int int_budget;
	int v_flag = 0;
	int i_flag = 0;
	char *id;
	int int_id;
	int t_flag = 0;
	char *type;
	int n_flag = 0;
	char *artist_name;
	int o_flag = 0;
	char *store_file_name;
	char *user_input;				// Ask Sergey if correct way
	int file_name_token = 0;
	char *char_filename;
	int i;
	FILE *storefile;
	FILE *inputfile;
	art_pieces *collection;				// Main Database

	if (argc < 3){
           printf("NO QUERY PROVIDED\n");
     	 }

     	else if (argc >= 3){
    	  for (i = 0; i < argc; i++) {
    	  	char *arg_i = *(argv + i);

		if (stringcomp (arg_i, "./art_collector") == 0){}

		else if (stringcomp (arg_i, "-b") == 0){
			b_flag = 1;
			i++; 
			budget = *(argv + i);
			printf("%s\n", budget);

			int_budget = atoi(budget);
			printf("%d\n", int_budget);

			if (int_budget == 0)
				printf("Error, ATOI failed\n");

			if (int_budget < 0){
				printf("Error, budget cannot be less than 0\n");
			}
		}

		else if (stringcomp (arg_i, "-v") == 0){
			if (i_flag || t_flag || n_flag == 1){
				printf("ERROR");
			}

			v_flag = 1;
		}

		else if (stringcomp (arg_i, "-i") == 0){
			if(v_flag == 1){
				printf("ERROR");
			}
			else{
				i_flag = 1;
				i++;
				id = *(argv + i);
				char *id_end;
				int_id = strtol(id, &id_end, 10);

				if(!*id_end){}

				else{
					printf("ID ERROR\n");
				}
			}

		}

		else if (stringcomp (arg_i, "-t") == 0){
			if(v_flag == 1){
				printf("ERROR");
			}
			else{
				t_flag = 1;
				i++;
				type = *(argv + i);
			}

		}

		else if (stringcomp (arg_i, "-n") == 0){
			if(v_flag == 1){
				printf("ERROR");
			}

			else{
				n_flag = 1; 
				i++;
				artist_name = *(argv + i);
			}
		}

		else if (stringcomp (arg_i, "-o") == 0){
			o_flag = 1; 
			i++;
			store_file_name = *(argv + i);

			//Ask Sergey if proper 

			if (access(store_file_name, F_OK) != -1){
				// File exists
				printf("Should the file be overwritten?\n");
				scanf("%s", user_input);
				if (stringcomp(user_input, "yes") == 0 || stringcomp(user_input, "y") == 0){
					storefile = fopen(store_file_name, "w");
				}

				else if (stringcomp(user_input, "no") == 0|| stringcomp(user_input, "n") == 0){
					printf("FILE EXISTS\n");
					exit(0);
				}

			}
			else{
				storefile = fopen(store_file_name, "w");
				//When do we close?
			}

		}

		else {
			if (file_name_token == 0){
				char_filename = *(argv + i);
				file_name_token = 1;
			}
			else if (file_name_token == 1){
				printf("ERROR\n");
			}
		}
	}

}

	// Check if input file exists or not

	if (access(char_filename, F_OK)!= -1){
		inputfile=fopen(char_filename, "rt");

	char* art_type = (char*)malloc(25 * sizeof(char));
		char* art_name = (char*)malloc(25 * sizeof(char));
		char* artist_name = (char*)malloc(25 * sizeof(char));
		char* command = (char*)malloc(25 * sizeof(char));

		int art_id;
		int price;
		int ret = -1;

	char* singleLine = (char*)malloc(150 * sizeof(char));

	    while(!feof(inputfile)){
    		fgets(singleLine, 150, inputfile);

		if (*singleLine == 'B' || *singleLine == 'U'){
    			ret = sscanf(singleLine, "%*s %d %s %s %s %d ", &art_id, art_type, art_name, artist_name, &price);

    			if (ret != 5)
    				ret = sscanf(singleLine, "%*s %d %s \"%[^\"]\" %s %d ", &art_id, art_type, art_name, artist_name, &price);

			if (ret != 5)
    				ret = sscanf(singleLine, "%*s %d %s \"%[^\"]\" \"%[^\"]\" %d ", &art_id, art_type, art_name, artist_name, &price);

    			if (ret != 5)
    				ret = sscanf(singleLine, "%*s %d %s %s \"%[^\"]\" %d ", &art_id, art_type, art_name, artist_name, &price);
		}

    			else if (*singleLine == 'S'){
    				ret = sscanf(singleLine, "%d %d", &art_id, &price);
			}

			else{
    				printf("ERROR: INVALID COMMAND\n");
				free(singleLine);
				free(art_type);
				free(art_name);
				free(artist_name);
				fclose(inputfile);
				return -1;
    			}

		if (art_id < 0){
    			printf("ERROR: ART ID LESS THAN 0\n");
			free(singleLine);
			free(art_type);
			free(art_name);
			free(artist_name);
			fclose(inputfile);
			return -1;
    		}

    		if (myStringLength(art_type) > 10){
    			printf("ERROR: ART TYPE GREATER THAN 10\n");
			free(singleLine);
			free(art_type);
			free(art_name);
			free(artist_name);
			fclose(inputfile);
			return -1;
    		}
			else{
    				*art_type = toupper(*art_type);
    			}

		if(myStringLength(art_name) < 3 || myStringLength(art_name) > 50){
    			printf("ERROR: ART NAME LENGTH ERROR\n");
			free(singleLine);
			free(art_type);
			free(art_name);
			free(artist_name);
			fclose(inputfile);
			return -1;
    		}
    			else{
    				*art_name = toupper(*art_name);
    			}

		if(myStringLength(artist_name) < 3 || myStringLength(artist_name) > 50){
    			printf("ERROR: ARTIST NAME LENGTH ERROR\n");
			free(singleLine);
			free(art_type);
			free(art_name);
			free(artist_name);
			fclose(inputfile);
			return -1;
    		}
    			else{
    				*artist_name = toupper(*artist_name);
    			}

    		if(price < 0){
    			printf("ERROR: INVALID PRICE\n");
			free(singleLine);
			free(art_type);
			free(art_name);
			free(artist_name);
			fclose(inputfile);
			return -1;
    		}

	}
	free(singleLine);
	free(art_type);
	free(art_name);
	free(artist_name);
	fclose(inputfile);
	//printf("%d\n", ret);
    	return 0;
	}

	else{
		// File does not exist
		printf("FILENAME DOES NOT EXIST\n");
	}
	return 0;
  	


}
