//Asheesh Yadav 
//301584113 
//aky7
#include <stdio.h> //include stdio library 
#include "a2_question2.h" // include the assignment 2 question 2 header 

int main() {

    printf("=============================================\n"); // fancy banner in the beginning
    printf("===============File Reader===================\n");
    printf("================Asheesh======================\n");
    printf("*============================================\n");
    printf("=============================================\n");
    printf("=============================================\n");

    FILE *fileptr = fopen("CSTalksList.txt", "r"); //opened the file 

    if(fileptr == NULL) return 1; //returns nothing if the file doesn't have anything(null)

    int capacity = 16;

    int used = 0;

    Talk **talkArray = (Talk **)malloc(sizeof(Talk *) * capacity); // made an array to take in the info from the file

    char inputbuffer[300]; //initiallized the input buffer 



while (fgets(inputbuffer, 15, fileptr) != NULL) {

    if (used == capacity) { //doubling the array incase it fills up 
        capacity *= 2;
        talkArray = (Talk **)realloc(talkArray, sizeof(Talk *) * capacity);
    }

    int hours = 0; //initillized the variables that will be used to store in the create()
    int minutes = 0;
    int seconds = 0;

    
    fscanf(fileptr, "%d%*c hour, %d%*c minutes, %d%*c seconds\n", &hours, &minutes, &seconds); // Use fscanf to scan the hours, minutes, and seconds


    fgets(inputbuffer,17, fileptr); // read in the title overview 
    char title[300];
    fgets(title, 300, fileptr);// read the rest of the line and get the title(line above helps us ignore the parts we dont need)
    
    
    char *start = strchr(title, '\"'); // gets rid of the quotations for talk title using 3 functions; chatgpt helped me undertand and inspired me to make this
    char *end = strrchr(title, '\"'); //strchr() searches for the first 'c' in the string 
    if (start && end) {               // strrchr() searchs for the last 'c' in the string
        memmove(start, start + 1, end - start); //memove() combines the 2 strings 
        end[-1] = '\0';
        
    }


    fgets(inputbuffer, 15, fileptr);
    char overview[300];
    fgets(overview, 300, fileptr);
    fscanf(fileptr, "%*[^\n]\n"); //ends the rest of the line(a format chatgpt showed me that would allow for me to skip over all the null parts of the line)

    talkArray[used] = createTalk(hours, minutes, seconds, title, overview); // store all te variables we gained from the file into the create()
    used++; 
}

    fclose(fileptr); // close the file 
    

    for (int i = 0; i < used; i++) { // simple for loop that prints the info from the file in the format we want
        printf("Talk %d\n", i + 1);
        printf("%dh%dm%ds\n", talkArray[i]->hours, talkArray[i]->minutes, talkArray[i]->seconds); // you need to do this in the for loop because every variable alters as they parse
        printf("%s\n", talkArray[i]->title); // through new passages, thus we can not do this outside of the for loop(chatgpt helped me understand and inspired me to format it this way)
        printf("%s", talkArray[i]->overview);
        printf("---\n");
        clearTalk(talkArray[i]);
        free(talkArray[i]); //important we have this in the for loop as well as it helps for there to be no memory leak
    }

    free(talkArray);// free the array 

    talkArray = NULL; 
    fileptr = NULL; 

    return 0; // end of code
}
