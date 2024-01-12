#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Please modify CWD to wherever you have put this file.
#define CWD "/home/boratoker/Desktop/ee103-hw2"
#define SAVEFOLDER "/games/"
#define EASY "/easy.txt"
#define MEDIUM "/medium.txt"
#define HARD "/hard.txt"

void clearscr(void){ //Cross-platform utility function to clear the screen. 
#ifdef _WIN32
	system("cls"); 
#elif   defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
	system("clear"); //add some other OSes here if needed 
#else
	#error "OS not supported."
	print("error OS not supported"); 
#endif 
}

void ls(){ // Cross-platform utility function to list the files in the save folder.
#ifdef _WIN32
	system("dir" CWD SAVEFOLDER); 
#elif   defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
	system("ls" CWD SAVEFOLDER); //add some other OSes here if needed 
#else
	#error "OS not supported."
	print("error OS not supported"); 
#endif
}

int getInputInt(char *prompt){ // Gets the input as integer.
	int result;
	printf("%s",prompt);
	scanf("%d",&result);
	getchar();
	return result;
}

char getInputChar(char *prompt){ // Gets the input as a single character.
	char result;
	printf("%s",prompt);
	scanf("%c",&result);
	getchar();
	return result;
}

void getInputString(char *prompt, char* result){ // Gets the input as an array of characters.
	printf("%s",prompt);
	fgets(result,64,stdin);
	result[strcspn(result,"\n")] = '\0';
	getchar();
}


bool checkValidity(char array[9][9], int row, int column, int number){return true;}; // Could not implement a function which behaves correctly.

int readFileIntoArray(char array[9][9],char* fname){
	FILE* file;
	char ch;
	// Open the file for reading
	file = fopen(fname, "r");
	//Check if the file has opened successfully.
	if(file == NULL){
		printf("Error opening the file.\n");
		return 1;
	}
	
	int ic = 0;	
	while((ch = fgetc(file)) != EOF){
		if(('0' < ch ) && ( ch<= '9')){
			array[ic/9][ic%9] = ch; 
			ic++;
			// Putting each number in the correct position of the 2D array.
		}
		else if ( ch == '0') {array[ic/9][ic%9] = ' ';ic++;} // Putting spaces instead of zeroes.
		else if(ch == ' ' || ch == '\n'){
			continue;
		}
	}
	// Close file
	fclose(file);
	return 0;
}

char GameModeMenu(){
	printf("*-*-*-*-*-*-*-*  Game Mode  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("*                1- Easy                                *\n");
	printf("*                2- Medium                              *\n");
	printf("*                3- Hard                                *\n");
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	while(true){
		char flowcontrol = getInputChar("Your selection.");
		switch(flowcontrol){
			case '1':
				return flowcontrol;
			case '2':
				return flowcontrol;
			case '3':
				return flowcontrol;
			case 'Q':
				return flowcontrol;
				break;
			default:
				printf("Please enter a valid input.\n");
				continue;
		}
	}
}

void drawScreen(char array[9][9]){ // This function draws the screen according to the assignment paper.
	int ic = 0;
	clearscr();
	printf("Press Key 'S' whenever you want to save the game.\n");
	printf("You can only fill a square once. Be careful.\n");
	for (int i = 0; i < 19; i++) {
		if (i % 6 == 0){printf("+===+===+===+===+===+===+===+===+===+\n");} // Drawing this line at 0,6,12 and 18th lines.
		else if ((i % 6 == 2) || (i % 6 == 4)){printf("+---+---+---+---+---+---+---+---+---+\n");} // Drawing this line at 2,4,8,10,14,16th lines.
		else if (i % 2 == 1){
			for (int j = 0; j < 37; j++) {
				if(j % 12 == 0){
					printf("|"); // Drawing vertical line at the 0,12,24 and 36th columns where complete lines have not been drawn.
					if(j == 36){
						printf("\n");
					}
				}
				else if((j % 12 == 4) || (j % 12 == 8)){
					printf(":"); // Drawing : at 4,8,16,20,28,32th columns where complete lines have not been drawn.	
				}
				else if ((j % 4 == 1) || (j % 4 == 3)){
					printf(" "); // Putting spaces between the number and the lines to the left and right around it.
				}
				else if (j % 4 == 2){
					printf("%c",array[ic/9][ic%9]); //Printing each number at the correct position.
					ic++;
				}
			}
		}
	}
}

void saveGame(char sudokuArray[9][9]){
	FILE *file;
	char savefolder[128] = CWD SAVEFOLDER;
	char filename[64] ,dupArray[9][9];
	getInputString("Please enter saved full game name:",filename);
	strcat(filename,".txt");
	strcat(savefolder,filename); // Full filename
	file = fopen(savefolder, "w");
	if(file == NULL){
		printf("Error opening the file.\n");
	}

	for (int i = 0; i < 9; i++) { // Duplicating sudokuArray into dupArray but changing the spaces into zeroes.
		for (int j = 0; j < 9; j++) {
			if(sudokuArray[i][j] == ' '){dupArray[i][j] = '0';}
			else{dupArray[i][j] = sudokuArray[i][j];}
		}
	}
	for (int k = 0; k < 9; k++) { // This double layer for loop writes every character in dupArray into the specified file according to format.
		for (int l = 0; l < 9; l++) {
			fprintf(file, "%c ",dupArray[k][l]);
		}
		fprintf(file,"\n");
	}
	fclose(file);
}

bool checkWinning(char sudokuArray[9][9]){return false;}; // Could not implement a function which behaves correctly.

void gameLoop(char sudokuArray[9][9]){ //Main function of the game.
	char prompt1, savename[50];
	int row, column, number;
	char *ep;
	bool win = false;
	while(!win){
		drawScreen(sudokuArray);
		while(true){
			prompt1 = getInputChar("Please enter Row (1-9 or 'S'): ");
			if(prompt1 == 'S'){ // Press 'S' to save.
				saveGame(sudokuArray);
				win = true;	
				break;
			}
			else if ( ('0' < prompt1) && (prompt1 <= '9')){ /*Proceed to get column number*/
				row = strtol(&prompt1,&ep,10);
				while(true){
					column = getInputInt("Please enter column (1-9): ");
					if(0<column && 9>= column){break;}
					else{printf("Please enter a number between 1 and 9.\n");}
				}
				while(true){ // Proceed to get the number to put in the cell.
					number = getInputInt("Please enter the number (1-9): ");
					if(0<number && 9>= number){break;}
					else{printf("Please enter a number between 1 and 9.\n");}
				}
				if(sudokuArray[row-1][column-1] != ' '){ // If the cell is full give an error.
					printf("The cell is already filled.\n");
				}
				else if(checkValidity(sudokuArray,row,column,number)){ // If the position and number is valid put the number in.
					sudokuArray[row-1][column-1] = '0' + number;
				}
				else{printf("The number you have entered is not correct.\n");}
			}
			else{
				printf("Please enter a valid input.\n");
			}
			drawScreen(sudokuArray);
			win = checkWinning(sudokuArray);
		}
	}
	printf("The game is finished.\n");
}

int startNewGame(){ // This function initializes the necessary variables for the new game.
	char gameMode, filename[100];
	char sudokuArray[9][9]; // = {{'1','1','1','1','1','1','2','1','1'},{'1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1'},{'1','1','1','1','1','1','1','1','1'}};
	gameMode = GameModeMenu(); // Selecting the game mode.
	switch(gameMode){
		case '1':
			strcpy(filename, CWD EASY);	
			break;
		case '2':
			strcpy(filename, CWD MEDIUM);	
			break;
		case '3':
			strcpy(filename, CWD HARD);
			exit(EXIT_SUCCESS);
			break;
		case 'Q':
			return 1;	
	}
	readFileIntoArray(sudokuArray,filename);
	gameLoop(sudokuArray);
	return 0;
}
void loadNewGame(){ // Loads the file selected by the user.
	char filename[100], sudokuArray[9][9];
	ls();
	getInputString("Please input the name of the file you want to load.",filename);
	readFileIntoArray(sudokuArray,filename);
	gameLoop(sudokuArray);
}
void MainMenu(bool* continuing){ // The main menu before the game is initialized.
	bool a = true;
	while (a){
	printf("*-*-*-*-*-*-* Welcome to IZTECH Sudoku Game *-*-*-*-*-*-*\n");
	printf("*                   Please Press                        *\n");
	printf("*                1- Play New Game                       *\n");
	printf("*                2- Load New Game                       *\n");
	printf("*                3- Quit                                *\n");
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	char flowcontrol = getInputChar("Your selection:");
	switch (flowcontrol) {
			case '1':
				startNewGame();
				break;
				a = false;
			case '2':
				loadNewGame();
				break;
			case '3':
				exit(EXIT_SUCCESS);
				break;
			default:
				printf("Your input is invalid please enter 1, 2 or 3.\n");
				continue;
		}
	}
	*continuing = false;
}

int main(void) // The main function.
{
	bool continuing = true;
	while(continuing){
		MainMenu(&continuing);
	}
	return EXIT_SUCCESS;
}
