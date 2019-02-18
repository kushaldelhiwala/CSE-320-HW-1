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
	char *user_input;	//Ask Sergey if correct way

	int file_name_token = 0;
	char *char_filename;
	
	int i;

	FILE *cmdfile;
	
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
				if (stringcomp(user_input, "yes") == 0 || stringcomp(user_input, "y") == 0){}

				else if (stringcomp(user_input, "no") == 0|| stringcomp(user_input, "n") == 0){
					printf("FILE EXISTS\n");
					exit(0);
				}

			}
			else{
				cmdfile = fopen(store_file_name, "w");
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
		//printf("%s\n", budget);
		//printf("%s\n", char_filename);
		//printf("%d\n", i);
		//printf("%d\n", file_name_token);
		//printf("%d\n", b_flag);
	}
	
	return 0;
    

}
