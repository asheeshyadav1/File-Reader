//Asheesh Kumar Yadav
//301584113
// aky7
#include <stdio.h> // standard librrary
#include "a3_talklib.h" // functions defined here

Talk* createTalk(short hours, short minutes, short seconds, const char* title, const char* overview) {
    
    Talk* newTalk = (Talk*)malloc(sizeof(Talk));

    newTalk->hours = hours;
    newTalk->minutes = minutes;
    newTalk->seconds = seconds;

    newTalk->title = (char*)malloc(strlen(title) + 1);
    strcpy(newTalk->title, title);

    newTalk->overview = (char*)malloc(strlen(overview) + 1);
    strcpy(newTalk->overview, overview);
    
    return newTalk;
}

void clearTalk(Talk* talk){

    free(talk->title);
    talk->title = NULL; 

    free(talk->overview);
    talk->overview = NULL; 
}

int* lookupTalkByTitle(Talk **array, int size, const char* title) { //used chatgpt to help me make this
    
    int* index = NULL;
    int countr = 0;

    for (int i = 0; i < size; i++) {//counter accounts for every match
        if (strstr(array[i]->title, title) != NULL) {
            countr++;
        }
    }

    if (countr == 0) {// no matches
        return NULL;
    }

    index = (int*)malloc((countr + 1) * sizeof(int));// dynamic array 

    if (index != NULL) {
        countr = 0;
        for (int i = 0; i < size; i++) {// finds the specific talks where it matches
            if (strstr(array[i]->title, title) != NULL) {
                index[countr++] = i;
            }
        }
        index[countr] = -1;
    }
    return index;
}

int compareTalksByDuration(const void *p1, const void *p2){ 

    int talk1 = (*(Talk**)p1)->hours*3600+(*(Talk**)p1)->minutes*60+(*(Talk**)p1)->seconds;
    int talk2 = (*(Talk**)p2)->hours*3600+(*(Talk**)p2)->minutes*60+(*(Talk**)p2)->seconds;

    int diffTalk = talk1-talk2;

    return diffTalk;
}

int compareTalksByTitle(const void *p1, const void *p2) { 

    return strcmp((*(Talk**)p1)->title, (*(Talk**)p2)->title);

}

Talk** parseFile(FILE *fileptr, int *used, int *capacity) { 

    Talk **talkArray = (Talk**)malloc(*capacity * sizeof(Talk*));
    char inputBuffer[300];

    while (fgets(inputBuffer, 15, fileptr) != NULL) {

        if (*used == *capacity) {
            *capacity *= 2;
            talkArray = (Talk **)realloc(talkArray, sizeof(Talk *) * (*capacity));
        }

        int hours = 0, minutes = 0, seconds = 0;
        fscanf(fileptr, "%d%*c hour, %d%*c minutes, %d%*c seconds\n", 
        &hours, &minutes, &seconds);

        fgets(inputBuffer, 17, fileptr);
        char title[300];
        fgets(title, 300, fileptr);

        char *start = strchr(title, '\"');
        char *end = strrchr(title, '\"');
        if (start && end) {
            memmove(start, start + 1, end - start);
            end[-1] = '\0';
        }

        fgets(inputBuffer, 15, fileptr);
        char overview[300];
        fgets(overview, 300, fileptr);
        fscanf(fileptr, "%*[^\n]\n");

        talkArray[*used] = createTalk(hours, minutes, seconds, title, overview);
        
        (*used)++;
    }
    return talkArray;
}





