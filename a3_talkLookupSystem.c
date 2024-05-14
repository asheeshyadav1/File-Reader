//Asheesh Kumar Yadav
//301584113
// aky7
#include <stdio.h> // include standard library 
#include "a3_talklib.h" // needed for all funciton defitions

int main() {

    int capacity = 16;
    int used = 0;
    char fileName[50]; 
    Talk** talkArray = (Talk**)malloc(capacity * sizeof(Talk*)); //dynamic array
    int option = 0;

    printf("=============================================\n"); //fancy banner 
    printf("===============File Reader===================\n");
    printf("================Asheesh======================\n");
    printf("===============301584113=====================\n");
    printf("===============aky7@sfu.ca===================\n");
    printf("=============================================\n");
    do {
        printf("Press numbers 1-5 for the following options and then enter:\n"); //do-while menu option
        printf("1) To load the talks file.\n");
        printf("2) To list talks sorted by duration.\n");
        printf("3) To list talks sorted by Title.\n");
        printf("4) To Look up a talk.\n");
        printf("5) To terminate the program.\n");
        printf("Option: ");
        scanf("%d%*c", &option);

        switch (option) { //switch case for different options user chooses from

            case 1: { //load talk 

                if(talkArray != NULL) { // clear the array if it is being called more 
                    for (int i = 0; i < used; i++) { //than once in a single compilation
                    clearTalk(talkArray[i]);
                    free(talkArray[i]);
                    }
                    free(talkArray);
                    talkArray = NULL; 
                }

                printf("Enter the entire file name with extention: ");
                scanf("%s", fileName); 
                fileName[strcspn(fileName, "\n")] = '\0'; // gets rid of the null terminator 
                FILE* fileptr = fopen(fileName, "r");

                if (fileptr == NULL) {

                printf("Error in opening the file, please check if it exists\n");
                printf("========================\n");
                break;

                } else {

                    used = 0; 
                    capacity = 16;
                    talkArray = parseFile(fileptr, &used, &capacity);

                    printf("%d Entries read from %s\n", used,fileName);
                    printf("========================\n");

                    fclose(fileptr);
                    break;
                }
            }
            case 2: {// list all the talks by duration
                 
                if(talkArray == NULL || used == 0) { // conditionals to load the file first

                    printf("Please load the file first(OPT. 1).\n");
                    break; 

                } else {
                
                qsort(talkArray,used,sizeof(Talk*),compareTalksByDuration);

                for (int i = 0; i < used; i++) { // print array 
                printf("Talk %d\n", i + 1);
                printf("%dh%dm%ds\n", talkArray[i]->hours,
                talkArray[i]->minutes, talkArray[i]->seconds);
                printf("%s\n", talkArray[i]->title);
                printf("%s\n", talkArray[i]->overview);
                printf("========================\n");
                }

                break; 

                }
            }
            case 3: { // list all the talks by title

                if(talkArray == NULL || used ==0) {

                    printf("Please load the file first(OPT. 1).\n");
                    break; 

                } else {
                
                qsort(talkArray,used,sizeof(Talk*),compareTalksByTitle);

                for (int i = 0; i < used; i++) {
                printf("Talk %d\n", i + 1);
                printf("%dh%dm%ds\n", talkArray[i]->hours, 
                talkArray[i]->minutes, talkArray[i]->seconds);
                printf("%s\n", talkArray[i]->title);
                printf("%s\n", talkArray[i]->overview);
                printf("========================\n");
                }

                break; 

                }
            }
            case 4: { // look up a Talk

                if (talkArray == NULL || used == 0) {

                    printf("Please load the file first(OPT. 1).\n");
                    break; 

                } else {

                    char subString[50];
                    printf("Enter a talk title you wish to see: ");
                    fgets(subString, 50, stdin);
                    subString[strcspn(subString, "\n")] = '\0'; 

                    int* similarTitles = lookupTalkByTitle(talkArray, used, subString);

                    if (similarTitles != NULL) { //finds all the talks with user input

                        printf("Here are all the times %s has been used in %s\n", subString,fileName);
                        
                        for (int i = 0; similarTitles[i] != -1; i++) {
                            printf("Talk %d\n", similarTitles[i] + 1);
                            printf("%dh%dm%ds\n", talkArray[similarTitles[i]]->hours,
                            talkArray[similarTitles[i]]->minutes,talkArray[similarTitles[i]]->seconds);
                            printf("%s\n", talkArray[similarTitles[i]]->title);
                            printf("%s\n", talkArray[similarTitles[i]]->overview);
                            printf("========================\n");
                            }
                        
                        free(similarTitles);
                        
                    }else {
                    
                    printf("No such talk on record\n"); 
                    printf("========================\n");
                        }
                    }
                break;
            }
            case 5: // terminate program 
                
                printf("Thank You for using our program!\n");

                for(int i = 0; i<used; i++){ // free the dynamic array contents
                clearTalk(talkArray[i]);
                free(talkArray[i]);
                }

                free(talkArray);
                talkArray = NULL;
                break;

            default:

                printf("Invalid Option: Please choose a number between 1 and 5\n");
                printf("========================\n");
                
        }
    }while (option!=5);  
    
    return 0;   
}
    