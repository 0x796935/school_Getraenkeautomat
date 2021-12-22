#include <stdio.h> // default io lib
#include <stdlib.h> // default io lib
#include <string.h> // including header for string values
#include <stdbool.h> // including header for boolean values

struct drinks {
    short int id; // id of the drink
	char name[50];  //name of drink
    int bAgeCheck; // age check
};

int ageCheck(int iMinAge){
    int iAge;
    fflush(stdin);
    fflush(stdout);
    printf("Input Age >>>");
    scanf("%i",&iAge);

    if(iAge >= iMinAge) //if above 18 return 1 (true)
        return 1;
    else return 0; //else return 0 (false)
}

int lineCount(char* filename){
   FILE *fp;
   char ch;
   int linesCount=0;
   //open file in read more
   fp=fopen(filename,"r");
   if(fp==NULL) {
      printf("File \"%s\" does not exist!!!\n",filename);
      return -1;
   }
   //read character by character and check for new line
   while((ch=fgetc(fp))!=EOF) {
      if(ch=='\n')
         linesCount++;
   }
   //close the file
   fclose(fp);
   //print number of lines
   return linesCount;
}

// Ä = \x8e
// ä = \x84
// Ö = \x99
// ö = \x94
// Ü = \x9a
// ü = \x81
// ß = \xe1

int main(){
    system("cls");
    // Variable der Struktur erstellen
    const int iLenghDrinks = (lineCount("drinks.txt")+1)/2;
    struct drinks structDrinks[iLenghDrinks]; // defining structure of drinks
    int i = 1, iLine = 0; // index of the getraenk used for reading the drinks.txt file
    
    char cUserSelection = 0; // selected drink ID by user


    FILE *fp = fopen("drinks.txt", "r"); // opening file in read only
    if(fp == NULL) {
       perror("Unable to open file!");
       exit(404);
    }

    char chunk[128];
    while(fgets(chunk, sizeof(chunk), fp) != NULL) { // looping trough each line of "drinks.txt"
        if(i > iLenghDrinks){
            printf("Too many Drinks in Thingy");
            exit(500);
        }
        iLine++;
        chunk[strcspn(chunk, "\n")] = 0;             // removing newline from the end
        if(chunk == "" || strlen(chunk) == 0)continue; // check if line is empty

        if(!(iLine % 2)){ //every second line there is the check of age            
            if(*chunk == 49)//True
                structDrinks[i].bAgeCheck = 1;
            else if(*chunk == 48)//False
                structDrinks[i].bAgeCheck = 0;
            else //Wrong / not designed / Error
                structDrinks[i].bAgeCheck = -1;
            //printf("State: %s\n", chunk);
            structDrinks[i].id = i;                      // setting ID going upwards
            i++; // increment the index by one to fill up the automat
        }else{
            //printf("Name: %s\n", chunk);
            
            strcpy(structDrinks[i].name, chunk);         // copying name from text as string
        }
    }
    fclose(fp); //closing file read
    
    //********************************
    //Begin of loop MAYBE??
    //********************************
    while(1){    
        system("cls"); //Clearing console window

        printf("==============================\n");
        printf("Welcome at the Getr\x84nkeautomat\n");
        printf("==============================\n");
        printf("\nProdukte:\n");

        for(int x = 1; x < i; x++){ //Printing all ids and products of the Getränkeautomat
            printf("%i:\t%s\n", structDrinks[x].id, structDrinks[x].name);
        }

        printf("x:\tExit\n");

        printf("Input Drink ID >>>");
        scanf("%c", &cUserSelection);

        if(cUserSelection == 'x' || cUserSelection == 'X'){
            printf("User choose to exit\n");
            exit(1);
        }

        cUserSelection = (int)cUserSelection - 48; // Conversion to int

        if(cUserSelection >= i || cUserSelection <= 0){ //if the user selection is above the max drinks or <= 0 then return incorrect selection
            printf("Incorrect selection");
            exit(404);

        }else{
            if(structDrinks[cUserSelection].bAgeCheck == 1){
                if(!ageCheck(16)){//exit if age check is false
                    printf("You are not old enough!\n");
                    exit(0);
                }   
            }
            printf("You selected %i: %s\n", structDrinks[cUserSelection].id, structDrinks[cUserSelection].name);
            fflush(stdin);
            printf("Press enter to continue...\n");
            scanf("%c");
        }
    }

    return 0; // Successful end of main (will never be reached cuz while(1))
}