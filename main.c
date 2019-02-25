#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int stringcomp(char *a, char *b) {
    while (*a && *b && *a == *b){
        ++a; ++b;
    }
    return (unsigned char)(*a) - (unsigned char)(*b);
}

void kushal_string_copy(char *target, char *source){
    while(*source)
    {
        *target = *source;
        source++;
        target++;
    }
    *target = '\0';
}

int myStringLength(char *str){
    int length = 0;
    while (*str != 0){
        str++;
        length++;
    }
    return length;
}

void formatArtName(char* art_name){
    *art_name = toupper((*art_name));
    art_name++;
    while (*art_name != 0){
        *(art_name) = tolower(*art_name);
        art_name++;
    }
}

typedef struct art_pieces{
    struct art_pieces* next;
    int art_id;
    char *art_type;
    char *art_name;
    char *artist_name;
    int price;
} art_pieces;

art_pieces* createNode(int art_id, char* art_type, char* art_name, char* artist_name, int price){
    art_pieces *newArtPiece = (art_pieces*)malloc(sizeof(art_pieces));
    newArtPiece->next = NULL;
    newArtPiece->art_id = art_id;
    newArtPiece->art_type = (char*)malloc(25*sizeof(char));
    newArtPiece->art_name = (char*)malloc(25*sizeof(char));
    newArtPiece->artist_name = (char*)malloc(25*sizeof(char));
    kushal_string_copy((newArtPiece->art_type),art_type);
    kushal_string_copy((newArtPiece->artist_name),artist_name);
    kushal_string_copy((newArtPiece->art_name),art_name);
    newArtPiece->price = price;

    return newArtPiece;
}

int addToDatabase(art_pieces* head, int art_id, char* art_type, char* art_name, char* artist_name, int price);

int updateDatabase(art_pieces* head, int art_id, char* art_type, char* art_name, char* artist_name, int price);

art_pieces * deleteFromDatabase(art_pieces* head, int art_id, int price);

int printPerFlags(art_pieces* head, int v_flag, int i_flag, char *flag_id, int t_flag, char *flag_type, int n_flag, int o_flag, char* flag_artist_name, FILE* storefile);

int main(int argc, char** argv) {
    int b_flag = 0;
    char *budget;
    int int_budget;
    int v_flag = 0;
    int i_flag = 0;
    char *flag_id;
    int int_id;
    int t_flag = 0;
    char *flag_type;
    int n_flag = 0;
    char *flag_artist_name;
    int o_flag = 0;
    char *store_file_name;
    char *user_input;
    int file_name_token = 0;
    char *char_filename;
    int i;
    FILE *storefile;
    FILE *inputfile;
    art_pieces *head;				// Main Database
    //char* art_type;
    //char* art_name;
    //char* artist_name;
    //char* command;

    int art_id;
    int price;
    int ret = -1;
    int head_flag = 0;

    //char* singleLine;


    if (argc < 3){
        printf("NO QUERY PROVIDED\n");
        return -1;
    }

    else if (argc >= 3){

        for (i = 0; i < argc; i++) {
            char *arg_i = *(argv + i);

            if (stringcomp (arg_i, "./art_collector") == 0){}

            else if (stringcomp (arg_i, "-b") == 0){
                b_flag = 1;
                i++;
                budget = *(argv + i);
                int_budget = atoi(budget);

                if (int_budget == 0) {
                    printf("Error, ATOI failed\n");
                    return -1;
                }
                if (int_budget < 0){
                    printf("Error, budget cannot be less than 0\n");
                    return -1;
                }

            }

            else if (stringcomp (arg_i, "-v") == 0){
                if (i_flag || t_flag || n_flag == 1){
                    printf("ERROR\n");
                    return -1;
                }
                v_flag = 1;
            }

            else if (stringcomp (arg_i, "-i") == 0){
                if(v_flag == 1){
                    printf("ERROR\n");
                    return -1;
                }
                else{
                    i_flag = 1;
                    i++;
                    flag_id = *(argv + i);
                    char *id_end;
                    int_id = strtol(flag_id, &id_end, 10);

                    if(!*id_end){}

                    else{
                        printf("ID ERROR\n");
                        return -1;
                    }
                }

            }

            else if (stringcomp (arg_i, "-t") == 0){
                if(v_flag == 1){
                    printf("ERROR\n");
                    return -1;
                }
                else{
                    t_flag = 1;
                    i++;
                    flag_type = *(argv + i);
                }
            }

            else if (stringcomp (arg_i, "-n") == 0){
                if(v_flag == 1){
                    printf("ERROR\n");
                    return -1;
                }

                else{
                    n_flag = 1;
                    i++;
                    flag_artist_name = *(argv + i);
                }

            }

            else if (stringcomp (arg_i, "-o") == 0){
                i++;
                store_file_name = *(argv + i);


                if (access(store_file_name, F_OK) != -1){
                    // File exists
                    printf("Should the file be overwritten?\n");
                    scanf("%s", user_input);
                    if (stringcomp(user_input, "yes") == 0 || stringcomp(user_input, "y") == 0){
                        storefile = fopen(store_file_name, "w");			//CHANGE MADE
                        o_flag = 1;
                    }

                    else if (stringcomp(user_input, "no") == 0|| stringcomp(user_input, "n") == 0){
                        printf("FILE EXISTS\n");
                        return -1;
                    }

                }
                else{
                    storefile = fopen(store_file_name, "w");
                    o_flag = 1;
                }

            }

            else {
                if (file_name_token == 0){

                    char_filename = *(argv + i);
                    file_name_token = 1;
                }
                else if (file_name_token == 1){
                    printf("ERROR\n");
                    return -1;
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
        //char* command = (char*)malloc(25 * sizeof(char));

        int art_id;
        int price;
        int ret = -1;

        char* singleLine = (char*)malloc(255 * sizeof(char));

        while(!feof(inputfile)) {
            fgets(singleLine, 255, inputfile);

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
                ret = sscanf(singleLine, "%*s %d %d", &art_id, &price);

            }

            else{

                if (o_flag == 1){
                    fprintf(storefile, "ERROR: INVALID COMMAND\n");
                    free(singleLine);
                    free(art_type);
                    free(art_name);
                    free(artist_name);
                    fclose(inputfile);
                    fclose(storefile);
                    return -1;

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

            }


            if(*singleLine == 'B' || *singleLine == 'U'){
                if (art_id < 0){

                    if (o_flag == 1){
                        fprintf(storefile, "ERROR: ART ID LESS THAN 0\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        fclose(storefile);
                        return -1;
                    }

                    else {
                        printf("ERROR: ART ID LESS THAN 0\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        return -1;
                    }
                }
                if(myStringLength(art_type) > 10){

                    if (o_flag == 1){
                        fprintf(storefile, "ERROR: ART TYPE GREATER THAN 10\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        fclose(storefile);
                        return -1;
                    }
                    else {
                        printf("ERROR: ART TYPE GREATER THAN 10\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        return -1;
                    }
                }

                else {
                    *art_type = toupper(*art_type);
                }
                if(myStringLength(art_name) < 3 || myStringLength(art_name) > 50){

                    if (o_flag == 1){
                        fprintf(storefile, "ERROR: ART NAME LENGTH ERROR\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        fclose(storefile);
                        return -1;
                    }
                    else{
                        printf("ERROR: ART NAME LENGTH ERROR\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        return -1;
                    }

                }
                else {
                    formatArtName(art_name);
                }
                if(myStringLength(artist_name) < 3 || myStringLength(artist_name) > 50){

                    if (o_flag == 1){
                        fprintf(storefile, "ERROR: ARTIST NAME LENGTH ERROR\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        fclose(storefile);
                        return -1;
                    }
                    else{
                        printf("ERROR: ARTIST NAME LENGTH ERROR\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        return -1;
                    }

                }

                else{
                    formatArtName(artist_name);
                }
                if(price < 0){

                    if (o_flag == 1){
                        fprintf(storefile, "ERROR: INVALID PRICE\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        fclose(storefile);
                        return -1;
                    }

                    else
                        printf("ERROR: INVALID PRICE\n");
                    free(singleLine);
                    free(art_type);
                    free(art_name);
                    free(artist_name);
                    fclose(inputfile);
                    return -1;
                }


                if(*singleLine == 'B'){

                    if (head_flag == 0){
                        head = createNode(art_id, art_type, art_name, artist_name, price);
                        head_flag = 1;
                    }

                    else if(head_flag == 1){

                        if (addToDatabase(head,art_id, art_type, art_name, artist_name, price) == -1){
                            printf("ID NOT UNIQUE\n");
                            free(singleLine);
                            free(art_type);
                            free(art_name);
                            free(artist_name);
                            fclose(inputfile);
                            free(head);
                            return -1;
                        }

                    }
                }

                else if (*singleLine == 'U'){

                    if (updateDatabase(head, art_id, art_type, art_name, artist_name, price) == -1){
                        printf("DATABASE COULD NOT BE DELETED OR UPDATED\n");
                        free(singleLine);
                        free(art_type);
                        free(art_name);
                        free(artist_name);
                        fclose(inputfile);
                        free(head);
                        return -1;
                    }
                }

            }

            else if(*singleLine == 'S'){
                if (art_id < 0){
                    printf("ERROR: ART ID LESS THAN 0\n");
                    free(singleLine);
                    free(art_type);
                    free(art_name);
                    free(artist_name);
                    fclose(inputfile);
                    free(head);
                    return -1;
                }
                if(price < 0){
                    printf("ERROR: INVALID PRICE\n");
                    free(singleLine);
                    free(art_type);
                    free(art_name);
                    free(artist_name);
                    fclose(inputfile);
                    free(head);
                    return -1;
                }
                if (head == NULL){
                    printf("RECORD CANNOT BE DELETED NOR UPDATED\n");
                    return -1;
                }
                head = deleteFromDatabase(head, art_id, price);
            }
        }

    }

    else{
        //File does not exist
        printf("FILENAME DOES NOT EXIST");
        return -1;
    }


    printPerFlags(head, v_flag, i_flag, flag_id, t_flag, flag_type, n_flag, o_flag, flag_artist_name, storefile);
    //free(singleLine);
   //free(art_type);
    //free(art_name);
    //free(artist_name);
    fclose(inputfile);
    free(head);
    //printf("%d\n", ret);
    return 0;

}

int addToDatabase(art_pieces* head, int art_id, char* art_type, char* art_name, char* artist_name, int price) {
    art_pieces *pointer = head;
    art_pieces *cursor = head;
    while (pointer != NULL) {
        if (pointer->art_id == art_id) {
            return -1;
        }
        pointer = pointer->next;
    }

    art_pieces *newNode = createNode(art_id, art_type, art_name, artist_name, price);

    while (cursor->next != NULL) {
        if ((newNode->art_id > cursor->art_id)) {
            if (newNode->art_id < cursor->next->art_id) {
                newNode->next = cursor->next;
                cursor->next = newNode;
                return 0;
            }

        }
        cursor = cursor->next;
    }
    cursor->next = newNode;
    return 0;
}

int updateDatabase(art_pieces* head, int art_id, char* art_type, char* art_name, char* artist_name, int price){
    art_pieces* pointer = head;
    while(pointer != NULL){
        if ((pointer->art_id) == art_id){
            kushal_string_copy((pointer->art_type),art_type);
            kushal_string_copy((pointer->artist_name),artist_name);
            kushal_string_copy((pointer->art_name),art_name);
            pointer->price = price;
            return 0;
        }
        pointer = pointer->next;
    }
    return -1;
}

art_pieces* deleteFromDatabase(art_pieces* head, int art_id, int price){

    art_pieces* cursor = head;
    art_pieces* pointer = cursor->next;

    if(cursor->art_id == art_id) {
        if(cursor->next == NULL) {
            head = NULL;
        }
        else {
            head = cursor->next;
        }
        free(cursor);
        return head;
    }
    while(cursor->next != NULL) {
        if(cursor->next->art_id == art_id && pointer->next != NULL) {
            if(pointer->next != NULL) {
                cursor->next = pointer->next;
            }
            else {
                cursor->next = NULL;
            }
            free(pointer);
            return head;
        }
        cursor = cursor->next;
    }
    printf("RECORD COULD NOT BE UPDATED OR DELETED");
    exit(0);
}

int printPerFlags(art_pieces* head, int v_flag, int i_flag, char *flag_id, int t_flag, char *flag_type, int n_flag, int o_flag, char* flag_artist_name, FILE* storefile){
    art_pieces* cursor = head;
    int worth = 0;
    char *id_put;
    int int_flag_id;

    while(cursor != NULL){
        worth = worth + cursor->price;
        cursor = cursor->next;
    }

    if (v_flag == 1){
        art_pieces* cursor = head;
        while(cursor != NULL){
            printf("%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);
            cursor = cursor->next;
        }
        return 0;
    }

    if(i_flag == 1 && t_flag == 0 && n_flag == 0 && o_flag ==0){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if(cursor->art_id == int_flag_id){
                printf("%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);
            }
            cursor = cursor->next;
        }
        return 0;
    }

    if(i_flag == 1 && t_flag == 1 && n_flag == 0 && o_flag == 0){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((cursor->art_id == int_flag_id) && (stringcomp(flag_type, cursor->art_type)==0)){
                printf("%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 1 && t_flag == 0 && n_flag == 1 && o_flag == 0){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((cursor->art_id == int_flag_id) && (stringcomp(flag_artist_name, cursor->artist_name)==0)){
                printf("%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 1 && t_flag == 1 && n_flag == 1 && o_flag == 0){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((cursor->art_id == int_flag_id) && (stringcomp(flag_artist_name, cursor->artist_name)==0) && (stringcomp(flag_type, cursor->art_type)==0)){
                printf("%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 1 && t_flag == 1 && n_flag == 1 && o_flag == 0){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((cursor->art_id == int_flag_id) && (stringcomp(flag_artist_name, cursor->artist_name)==0) && (stringcomp(flag_type, cursor->art_type)==0)){
                printf("%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 0 && t_flag == 1 && n_flag == 0 && o_flag == 0){
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((stringcomp(flag_type, cursor->art_type)==0)){
                printf("%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 0 && t_flag == 0 && n_flag == 1 && o_flag == 0){
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((stringcomp(flag_artist_name, cursor->artist_name)==0)){
                printf("%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;
    }

    if(i_flag == 1 && t_flag == 0 && n_flag == 0 && o_flag == 1){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if(cursor->art_id == int_flag_id){
                fprintf(storefile, "%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 0 && t_flag == 1 && n_flag == 0 && o_flag == 1){
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((stringcomp(flag_type, cursor->art_type)==0)){
                fprintf(storefile, "%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 0 && t_flag == 0 && n_flag == 1 && o_flag == 1){
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((stringcomp(flag_artist_name, cursor->artist_name)==0)){
                fprintf(storefile, "%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;
    }

    if(i_flag == 1 && t_flag == 1 && n_flag == 0 && o_flag == 1){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((cursor->art_id == int_flag_id) && (stringcomp(flag_type, cursor->art_type)==0)){
                fprintf(storefile, "%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 1 && t_flag == 0 && n_flag == 1 && o_flag == 1){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((cursor->art_id == int_flag_id) && (stringcomp(flag_artist_name, cursor->artist_name)==0)){
                fprintf(storefile, "%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 0 && t_flag == 1 && n_flag == 1 && o_flag == 1){
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((stringcomp(flag_artist_name, cursor->artist_name)==0) && (stringcomp(flag_type, cursor->art_type)==0)){
                fprintf(storefile, "%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(i_flag == 1 && t_flag == 1 && n_flag == 1 && o_flag == 1){
        int_flag_id = strtol(flag_id, &id_put, 10);
        art_pieces* cursor = head;
        while(cursor != NULL){
            if((cursor->art_id == int_flag_id) && (stringcomp(flag_artist_name, cursor->artist_name)==0) && (stringcomp(flag_type, cursor->art_type)==0)){
                fprintf(storefile, "%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);

            }
        }
        return 0;

    }

    if(v_flag == 1 && o_flag == 1){
        art_pieces* cursor = head;
        while(cursor != NULL){
            fprintf(storefile, "%d %s %s %s %d\n", cursor->art_id, cursor->art_type, cursor->art_name, cursor->artist_name, cursor->price);
        }
        return 0;

    }
    else{
        printf("RECORD NOT FOUND\n");
        return -1;
    }

    return 0;

}
