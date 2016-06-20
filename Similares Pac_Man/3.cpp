//http://trinidadestrada.com/portfolio/pacdude.php

//PacMan Console Game
//Heritage University CPSC 240


//Those are only includes
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <process.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

//End of includes

// Global Values for the pacman game
const int pacManDefaultVerticalPos = 6; // has pacman's vertical value in the grid
const int pacManDefaultHorizontalPos = 8; // has pacman's horizontal value in the grid
const int ghostDefaultVerticalPos = 15; // has the ghost's vertical value in the grid
const int ghostDefaultHorizontal = 14; // has the ghost's horizontal value in the grid
const int boost1VerticalPos = 1, boost1HorizontalPos = 1; // Has the first boost's position values
const int boost2VerticalPos = 1, boost2HorizontalPos = 8; // Has the second boot's position values
const int boost3VerticalPos = 1, boost3HorizontalPos = 15; // Has the third boost's position values
const int boost4VerticalPos = 8, boost4HorizontalPos = 3; // Has the fourth boost's position values
const int boost5VerticalPos = 8, boost5HorizontalPos = 13; // Has the fifth boost's position values
const int boost6VerticalPos = 15, boost6HorizontalPos = 1; // Has the sixth boost's position values
const int boost7VerticalPos = 15, boost7HorizontalPos = 8; // Has the seventh boost's position values
const int boost8VerticalPos = 15, boost8HorizontalPos = 15; // Has the eighth boost's position values
const char boost = 15, wall = 219, path = 249, escape = 27, packDude = 2, ghost = 1, emptyPath = ' ';

/* ATTENTION TO ALL SCORE PROGRAMMERS
   I made this value in order for the scores to be displayed anywhere 
   in the entire program, without having to make a reference call to it from the
   Game() function.*/
int scoreDisplay = 0;

// Global Values for the pacman game
/*
// Function Prototypes
//------------------------------Function Prototypes---------------------------*/

// I have chaged the ghost function by adding a new variable which I used to slow down the ghost
void boostColor(char grabbedChar, int amountAllowed, bool boostOn);

//Resizes game console to game grid size
void consoleResize();
void setColorOnGrid(char grabbedChar,int amountAllowed);
void toQuitTheGame(bool &run);
void clearBuffer(char &movingDirection); // this function's purpose is to clear out useless user input
void clearScreen();
void gameTitle();
void sound(void *);
void Game(bool &reset);
void setcolor(unsigned short color);
void HighScores(int score);
void Bubblesort(int FirstPlace, int SecondPlace, int ThirdPlace);
void GameMenu(bool &exitGame);//Tyler-Start Menu
int getOption();//Tyler-Start Menu Options
void ghostDeath(int &ghostExterminator, int &ghostTimeOff);//Israel
void clickTime(int &time,int Loop, const int Time);//Israel. This is is the timer's prototype.
void lifeDecrementation(int &numberOfLives);//Israel, this function decrements a life
                                                            // everytime DeathTrigger is false!
void pacmansLives(int numberOfLives, char packDude);//Israel. This displays the lives of pacman to the program
void gameOverLink();
	
// A piece of Trino's  functions
void ghostDudeChasing(int &ghostPos1, int &ghostPos2, int pacManPos1,
	int pacManPos2, char grid[17][17], int &pathReplace1, int &pathReplace2); // This function is for the ghost to chase pacman

void movePacMan(int &pacManVerticalPos, int &pacManHorizontalPos, char grid[17][17], int &score, int &m, bool &boostOn, bool &run);
void grabUserInputForPac(char &userInput);
void pacManSwap(int &pacManVerticalPos, int &pacManHorizontalPos, int moveVerticalPos, int moveHorizontalPos, char grid[17][17], char userInput,
	int &score, int &m, bool &boostOn);
void scores(int moveVerticalPos, int moveHorizontalPos, char grid[17][17], int &score, int &m, bool &boostOn);
void pacManChangePosValue(int &pacManVerticalPos, int &pacManHorizontalPos, char userInput);
void pacManAndGhostContact(int &pacManVerticalPos, int &pacManHorizontalPos, 
	int &ghostVerticalPos, int &ghostHorizontalPos, int &lives, int pathReplace1, 
	int pathReplace2, char grid[17][17]);
void resetValues(int &pacManVerticalPos, int &pacManHorizontalPos, 
	int &ghostVerticalPos, int &ghostHorizontalPos);
bool validateGhostMove(char test); // This function will validate the ghost's move
bool validatePacManMove(char test); // This function will validate pacman's move
void replaceCharsAfterSwap(int pathReplace1, int pathReplace2, 
	int pacManPos1, int pacManPos2, int ghostPos1, int ghostPos2, 
	char grid[17][17]);
void shortCutAcrossGrid(int &verticalPos, int &horizontalPos, char grid[17][17]);

void Bonus(int &bonusY, int &bonusX,char grid[17][17],int &bonusTravelPathY,
int &bonusTravelPathX,char bonus,int pathReplace1,int pathReplace2,
bool &followPath1,bool &followPath2,bool &followPath3,bool &followPath4,bool 
&followPath5,bool &followPath6,bool &followPath7,bool &followPath8);
// This function will take charge of the ghost's movement
void ghostRetreat(int &ghostPos1, int &ghostPos2,char grid[17][17],int &ghostTravelPathY,
int &ghostTravelPathX,char ghost,int pathReplace1,int pathReplace2,
bool &ghostPath1,bool &ghostPath2,bool &ghostPath3,bool &ghostPath4,bool 
&ghostPath5,bool &ghostPath6,bool &ghostPath7,bool &ghostPath8,char boostOn);
void Bonus(int &bonusY, int &bonusX,char grid[17][17],int &bonusTravelPathY,
int &bonusTravelPathX,char bonus,int pathReplace1,int pathReplace2,
bool &followPath1,bool &followPath2,bool &followPath3,bool &followPath4,bool 
&followPath5,bool &followPath6,bool &followPath7,bool &followPath8);

/***************************************Begin Main***************************/
int main(){
    
    
        //Open the input and output files
    ifstream fin("F:\\PacDude_working\\source\\PacmanTotalScores.txt");//This statement belongs to the high scores section
    ofstream sout ("F:\\PacDude_working\\source\\PacmanHighScores.txt");//This statement belongs to the high scores section
    
    
    //Variables & Constants
    bool exitGame = false;
    
	// The title of the game will be displayed on the top bar of the window
	gameTitle();
	
    //Resize the console to game fit game grid
    consoleResize();
    
    //Begin the bacground sound thread.
    _beginthread(sound, 0, NULL);//If You want sound just comment this out.
	
    //Call the game's meuning system   
    do {             
       GameMenu(exitGame);
    }while(exitGame != true);

return 0;
}//End of return cero

/*************************************End of Main is *************************/

// This function will display the game's title on the top bar
void gameTitle(){
	
	// The system command "title" will put the text beyond as the title
	system("title PacDude Ultra 3");
}

// This is the games primary menu.  All aspects of the game are controlled 
//via the menu
void GameMenu(bool &exitGame){
     
     //Function Variables
     int number_Entered = 0;
     bool reset = true;
    
    // bool ShowHighScores = true;
      
      do{
           //Otain user's menu selection
           number_Entered = getOption();

           /*Perform switch-statement to select the number 
           the user has called upon*/    
           switch(number_Entered)
           {
              case 1:
                  //Play Game            
                  cout << "PLAY GAME" << endl;     
                  
                  //Call function to play game
                  Game(reset);
                  break;
              
              case 2:
                  //Exit Program
                  cout << "EXIT GAME " << endl;
                  exitGame = true;
                  break;
             
             //Show User's Scores in Pacman's High Scores   
           /*   case 3:
                   cout<< " Show Pacman's High Scores" <<endl;
                   ShowHighScores = true;
                   break;
           */  
        
                      default:
                  //Display to user that they have entered an invalid option
                  cout << "Invalid menu option; please try again.";
                  break;
                 
                  
              }}//End of switch statement & do statement
      while(number_Entered != 2); //End of do-while loop    
                 

           //For Dev Compiler-Remove for other
           system ("PAUSE");
           
           //Clear screen
           system("CLS");
//End of function     
}


//Game Function
void Game(bool &reset){
    int h = 0;
    // int a = 0;  
    int x = 0;
    //Game grid character constants
    char ghost = 1;
    bool run = true;
    char logo = ' ';
    
    // int pacManPos1 = 6, pacManPos2 = 8;
    int pathReplace1 = 0;
    int pathReplace2 = 0;
    int ghostPos1 = ghostDefaultVerticalPos;
    int ghostPos2 = ghostDefaultHorizontal;
    int ghost2Pos1 = 1;
    int ghost2Pos2 = 11;
	int ghostIncrementForSpeed = 0;
    int ghostSpeedLimit = 2; // values given will control the ghost's speed
    int m = 0;
	int pelletCounter = 0; // this counter will count the amount of pellets
	
	//Define Pacman's position on the playing board
	int pacManVerticalPos = pacManDefaultVerticalPos;
	int pacManHorizontalPos = pacManDefaultHorizontalPos;
	int score = 0; 
    
    char characterForColorCheck = ' ';
    char temp;
    char tempTwo;
    char posForBoost;
    char whereToMove = ' ';
    
    bool boostOn = false;
    
    // char gameOver1 = 'GAME';
    //  char gameOver2 = 'OVER';
       vector<char> Vector;//Vector funtion
    
    //Variables and constants
    char crystal = 3;
    int CountDownTimeForGhostKilling = 18;// This is the ghost countdown timer they have to escape from pacman.
    const int Time = 20;
    int clockTicker = Time;
    int lives = 3;
    int loopRepeats = 0;//This is needed to keep the timer running!
    int clik = 0;//This is just a counter that keeps track on the first time the ghost moves!
    char wallLeftTrasport = 174;
    char wallRightTrasport = 175;
    bool coolColors = false;
        int bonusY = 11;
   int bonusX  = 8;
   int bonusTravelPathY = 1;
   int bonusTravelPathX = 15;
   int ghostTravelPathY = 2;
  int ghostTravelPathX = 1;
   bool followPath1 = true;
   bool followPath2 = true;
    bool followPath3 = true;
   bool followPath4 = true;
   bool followPath5 = true;
   bool followPath6 = true;
   bool followPath7 = true;
   bool followPath8 = true;
   bool ghostPath1 = true;
    bool ghostPath2 = true;
    bool ghostPath3 = true;
    bool ghostPath4 = true;
   bool ghostPath5 = true;
    bool ghostPath6 = true;
    bool ghostPath7 = true;
    bool ghostPath8 = true;
    char bonus = 36;
    
ifstream ipnt_logo("C:\\Logo2.txt");    
//========================================================================begins    
    
    int amountAllowed = 0; // This variable is used to control the speed of the ghost

//============================Tyler's Project====================================================== 
    char grid[17][17] = {
 /*        0    1    2    3    4    5    6    7    8    9   10   11   12   13  14    15   16 */
 /*0*/   {wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall},
 /*1*/   {wall,wall,path,path,path,path,path,path,wall,path,path,path,path,path,path,wall,wall},
 /*2*/   {wall,path,wall,wall,path,wall,wall,wall,path,wall,wall,wall,path,wall,wall,path,wall},
 /*3*/   {wall,path,path,path,path,path,path,wall,path,path,path,path,path,path,wall,path,wall},
 /*4*/   {wallLeftTrasport,path,wall,path,wall,wall,path,path,path,wall,crystal,wall,wall,path,path,path,wallRightTrasport},
 /*5*/   {wall,path,path,path,wall,wall,path,wall,path,wall,wall,wall,wall,path,wall,path,wall},
 /*6*/   {wall,path,wall,path,path,path,path,path,path,path,path,path,path,path,wall,path,wall},
 /*7*/   {wall,path,wall,wall,wall,path,wall,wall,wall,wall,wall,path,wall,wall,wall,path,wall},
 /*8*/   {wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall},
 /*9*/   {wall,path,wall,wall,wall,path,wall,wall,wall,wall,wall,path,wall,wall,wall,path,wall},
 /*10*/  {wall,path,path,wall,path,path,path,path,wall,path,path,path,wall,path,path,path,wall},
 /*11*/  {wall,path,path,path,path,wall,wall,path,path,path,wall,path,wall,path,wall,path,wall},
 /*12*/  {wallLeftTrasport,path,wall,wall,path,wall,wall,wall,path,wall,wall,path,path,path,path,path,wallRightTrasport},
 /*13*/  {wall,path,wall,path,path,path,path,path,path,path,path,path,wall,wall,wall,path,wall},
 /*14*/  {wall,path,wall,path,wall,wall,wall,path,wall,wall,wall,path,wall,wall,wall,path,wall},
 /*15*/  {wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall},
 /*16*/  {wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall},
};

	// These are the boost character values being put to their appropriate positions
	grid[boost1VerticalPos][boost1HorizontalPos] = boost;
	grid[boost2VerticalPos][boost2HorizontalPos] = boost;
	grid[boost3VerticalPos][boost3HorizontalPos] = boost;
	grid[boost4VerticalPos][boost4HorizontalPos] = boost;
	grid[boost5VerticalPos][boost5HorizontalPos] = boost;
	grid[boost6VerticalPos][boost6HorizontalPos] = boost;
	grid[boost7VerticalPos][boost7HorizontalPos] = boost;
	grid[boost8VerticalPos][boost8HorizontalPos] = boost;   

    while(run == true) {
    
		// These are the character values being put into the grid to their appropriate positions
		grid[ghostPos1][ghostPos2] = ghost; // ghost
		grid[pacManVerticalPos][pacManHorizontalPos] = packDude; //pacman	
	
        if(time(0)){
			m++;
		}
	
        //cout << "PacDude Ultra 3" << endl;    
    
        //Perform for loop to output grid to console

        for(int row = 0; row < 17; row++) 
		{

            for(int col = 0; col < 17; col++)
			{
//=========================================================================begins		
                amountAllowed++; 
                /* Like I said this changes the speed of the ghost and I did not want to put it in 
                the ghost function becasue everytime it was reset to zero and 
                returning it as a value by using the ghost fucntion was not the way I wanted to used it.
                So I utilized it as a pointer. This value is very important so pay attention to it in my code.
                */
//==========================================================================ends

                    
				/* This function will call the pacman's movement
					Note: Since the score keeping code was added to my pacman code, 
					I decided to bring it along. That should explain why the 'score', 'm', and 'boostOn' 
					variables are being called into this function */
                movePacMan(pacManVerticalPos, pacManHorizontalPos, grid, score, m, boostOn, run);
				
                	//  Thia ia to reset the empty wall characters when pacman is not on them
               if(grid[4][16] != packDude){
                grid[4][16] = wallRightTrasport;
                }
                if(grid[12][16] != packDude){
                        
                grid[12][16] = wallRightTrasport;
                }
                if(grid[4][0] != packDude){
                        grid[4][0] = wallLeftTrasport;
                }
                        
                if(grid[12][0] != packDude){
                        grid[12][0] = wallLeftTrasport;
                        }
                //  This will prevent packman from eating the crystal
                if(grid[4][10] != packDude){
                grid[4][10] = crystal;
                }
                
				// Whatever character is stored in the array,will get stored to 
                // 'characterForColorCheck'
				characterForColorCheck = grid[row][col];
				
				// This function will make the color changes on the grid
                setColorOnGrid(characterForColorCheck,amountAllowed);
                  
				
                       
                 //  BoostOn needs to be reset to true in this function in order to get colors for other pellets
                if(boostOn == true){
                  
                    boostColor(characterForColorCheck,amountAllowed,boostOn);              
                    
                }
				if(m == 18){
					boostOn = false;
					ghost = 1;
				}
			
				// The value of the grid will be displayed
				cout << grid[row][col];
				
				// If a pellet or a boost are found within the grid, this loop will increment
				// pelletCounter's value
				if(grid[row][col] == path || grid[row][col] == boost){
					pelletCounter++;
				}
            
            }

			cout << endl;
        }
		
		// If there are no pellets found, the game session will have to end
		if(pelletCounter == 0){
			gameOverLink();
			run = false;	
		}
		// If there are pellets found, the game will continue to run
		else if(pelletCounter > 0){
			run = true;
		}
		// pelletCounter will be reset back to '0' after the tests have been made
		pelletCounter = 0;

        setcolor(15);
        clickTime(clockTicker,loopRepeats,Time);//This is the timer's Prototype
		pacmansLives(lives, packDude);
		
		// This conditional statement will control the ghost's speed by incrementing
		// and reseting values. 
        // This loop will be set back 'ghostSpeedLimit' times, from the main while
        // loop's speed. ghostIncrementForSpeed will increment outside this if loop.
		if(ghostIncrementForSpeed == ghostSpeedLimit){
        
			// This function will call the ghost to move
			/* The pacman's positions are being called into this function, that way the ghost knows
				how far away the pacman is from it. The 'pathReplace' variables have other purposes for
				the program, which is why they are being called and modified through this function.*/
			ghostDudeChasing(ghostPos1, ghostPos2, pacManVerticalPos, pacManHorizontalPos, 
				grid, pathReplace1, pathReplace2);
		
			// This value will be resetted back to zero, that way the timer starts with its recount
			ghostIncrementForSpeed = 0;
		}
				
        /*Bonus(bonusY,bonusX,grid,bonusTravelPathY,bonusTravelPathX,bonus,pathReplace1,pathReplace2,
        followPath1,followPath2,followPath3,followPath4,followPath5,followPath6,followPath7,followPath8);*/
        /*
        ghostRetreat(ghostPos1,ghostPos2,grid,ghostTravelPathY,ghostTravelPathX,ghost,pathReplace1,
        pathReplace2,ghostPath1,ghostPath2,ghostPath3,ghostPath4,ghostPath5,
        ghostPath6,ghostPath7,ghostPath8,boostOn);*/
        // The ghostIncrementForSpeed will increment
        ghostIncrementForSpeed++;        

        cout << endl << "PacMan Pos: " << pacManVerticalPos << " " << pacManHorizontalPos;
        cout << endl << "Ghost Pos: " << ghostPos1 << " " << ghostPos2;
        cout << endl << "Player Score " << score; // Will display the score's value, 
                                       // 'score' being the value being displayed

        loopRepeats++;//FYI this 'loopRepeats' is needed to keep the timer running!

        //The ovrall time gets displayed right here.
        cout << endl << "Time is: " << clockTicker;        
        
        //This conditional is here to prevent the ghost's timer to display the first time,
        // that way it doesn't confuse the user.
        if((m==0)||(clik>0)){
			ghostDeath(CountDownTimeForGhostKilling, m);//This will display the time to the user
            clik++;                                    // on how much time the ghost will have before pac-man dies.
		}
         //If you need to see the time of the ghosts you can block my function, and
         // use the cout statement you had before cout << endl << m; //It works fine!
         
        //cout << endl << exitGame;			
		
		/** This function will make sure if the pacman or the ghost come in contact with each other **/
		pacManAndGhostContact(pacManVerticalPos, pacManHorizontalPos, 
            ghostPos1, ghostPos2, lives, pathReplace1, pathReplace2, grid);
		
		// The local score value will be passed down to the global value of the scores
		scoreDisplay = score;

				/*I don't know what exactly is this
                if(grid[pathReplace1][pathReplace2] == ghost || grid[pathReplace1][pathReplace2] == ' ' || grid[pathReplace1][pathReplace2] == path){
                    grid[pathReplace1][pathReplace2] = packDude;   
                }
         
                if(grid[ghostPos1][ghostPos2] == packDude || grid[ghostPos1][ghostPos2] == ' ' || grid[ghostPos1][ghostPos2] == path){
                    grid[pathReplace1][pathReplace2] = ghost;   
                }  
                if(grid[ghostPos1][ghostPos2] == grid[pathReplace1][pathReplace2] && boostOn == true){
                    run = true;
					ghost = 34;
                    grid[pathReplace1][pathReplace2] = packDude;
                    grid[ghostPos1][ghostPos2] = ghost;
                }                  
                else if(grid[ghostPos1][ghostPos2] == grid[pathReplace1][pathReplace2] && boostOn == false){
					run = false;
                    Beep(290,99);Beep(290,99);Beep(290,99);Beep(290,99);Beep(290,99);
                }
				*/

        Sleep(200);
        system("CLS");
    }

    setColorOnGrid(characterForColorCheck,amountAllowed); 
    
	int b = 0;
	int c = 0;  
//consoleResize(200,200);
coolColors = true;

/*ipnt_logo >> noskipws;  
    while(ipnt_logo >> logo){

    Vector.push_back(logo);
    b++;

}*/
/*
while(b != 0){
   cout << noskipws << Vector[c++];
   b--;
}
cout << "                                                                                                  GAME OVER" << endl; 
system("pause");
system("CLS");

cout << "Do YoU WiSh To TrY AgAiN? y/n ";

string game;

cin >> game ;
if(game == "y"){
        reset = false;
}
else if(game == "n"){
     reset == true; 
}*/
}

// This function will allow color to be displayed on the console window
void setcolor(unsigned short color){                //The function that you'll use to
                                                    //set the colour
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

//==========================Edgar's project========================================================

// This function will take charge of the ghost's movement
// This function will take charge of the ghost's movement
void ghostRetreat(int &ghostPos1, int &ghostPos2,char grid[17][17],int &ghostTravelPathY,
int &ghostTravelPathX,char ghost,int pathReplace1,int pathReplace2,
bool &ghostPath1,bool &ghostPath2,bool &ghostPath3,bool &ghostPath4,bool 
&ghostPath5,bool &ghostPath6,bool &ghostPath7,bool &ghostPath8,char boostOn){
  char wall = 219;
  char tempTwo = ' ';
    if(boostOn == true)
    {
       if(ghostPos1 < ghostTravelPathY && grid[ghostPos1+1][ghostPos2] != wall)
       {
                pathReplace1 = ghostPos1+1;
                pathReplace2 = ghostPos2;
                 tempTwo = grid[pathReplace1][pathReplace2];
                 grid[pathReplace1][pathReplace2] = ghost;
                 grid[ghostPos1][ghostPos2] = tempTwo;
                 ghostPos1++;          
       }                   
       if(ghostPos1 > ghostTravelPathY && grid[ghostPos1-1][ghostPos2] != wall)
       {
             pathReplace1 = ghostPos1-1;
             pathReplace2 = ghostPos2;
             tempTwo = grid[pathReplace1][pathReplace2];
             grid[pathReplace1][pathReplace2] = ghost;
             grid[ghostPos1][ghostPos2] = tempTwo;
             ghostPos1--;
       }   
       if (grid[ghostPos1+1][ghostPos2] == wall)
       {
                if (grid[ghostPos1][ghostPos2-1] != wall){
                pathReplace2 = ghostPos2-1;
                pathReplace1 = ghostPos1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = ghost;
                grid[ghostPos1][ghostPos2] = tempTwo;
                ghostPos2--;}
                if (grid[ghostPos1][ghostPos2+1] != wall){
                pathReplace2 = ghostPos2+1;
                pathReplace1 = ghostPos1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = ghost;
                grid[ghostPos1][ghostPos2] = tempTwo;
                ghostPos2++;}         
       }
        else if (grid[ghostPos1-1][ghostPos2] == wall)
        {//Starts first else if loop
       
	        if (grid[ghostPos1][ghostPos2-1] != wall)
	        {
					pathReplace2 = ghostPos2-1;
	                pathReplace1 = ghostPos1;
	                tempTwo = grid[pathReplace1][pathReplace2];
	                grid[pathReplace1][pathReplace2] = ghost;
	                grid[ghostPos1][ghostPos2] = tempTwo;
	                ghostPos2--;
			}
	        if (grid[ghostPos1][ghostPos2+1] != wall)
			{
	                pathReplace2 = ghostPos2+1;
	                pathReplace1 = ghostPos1;
	                tempTwo = grid[pathReplace1][pathReplace2];
	                grid[pathReplace1][pathReplace2] = ghost;
	                grid[ghostPos1][ghostPos2] = tempTwo;
	                ghostPos2++;
			}
		}         
                
        if(ghostPos2 < ghostTravelPathX && grid[ghostPos1][ghostPos2+1] != wall)
		{
	            pathReplace2 = ghostPos2+1;
	            pathReplace1 = ghostPos1;
	            tempTwo = grid[pathReplace1][pathReplace2];
	            grid[pathReplace1][pathReplace2] = ghost;
	            grid[ghostPos1][ghostPos2] = tempTwo;
	            ghostPos2++;
		}	
       else if(ghostPos2 > ghostTravelPathX && grid[ghostPos1][ghostPos2-1] != wall )
	    {
                pathReplace2 = ghostPos2-1;
                pathReplace1 = ghostPos1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = ghost;
                grid[ghostPos1][ghostPos2] = tempTwo;
                ghostPos2--;
        }
                
                
        if (grid[ghostPos1][ghostPos2-1] == wall)
        {
			if (grid[ghostPos1-1][ghostPos2] != wall)
			{
                pathReplace2 = ghostPos2;
                pathReplace1 = ghostPos1-1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = ghost;
                grid[ghostPos1][ghostPos2] = tempTwo;
                ghostPos1--;
			}         
			if (grid[ghostPos1+1][ghostPos2] != wall)
			{
                pathReplace2 = ghostPos2;
                pathReplace1 = ghostPos1+1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = ghost;
                grid[ghostPos1][ghostPos2] = tempTwo;
                ghostPos1++;
			}         
        }
                
	    else if (grid[ghostPos1][ghostPos2-1] == wall)
	    {
	        if (grid[ghostPos1-1][ghostPos2] != wall)
	        {
	                pathReplace2 = ghostPos2;
	                pathReplace1 = ghostPos1-1;
	                tempTwo = grid[pathReplace1][pathReplace2];
	                grid[pathReplace1][pathReplace2] = ghost;
	                grid[ghostPos1][ghostPos2] = tempTwo;
	                ghostPos1--;
	        }
	        if (grid[ghostPos1+1][ghostPos2] != wall)
	        {
	                pathReplace2 = ghostPos2;
	                pathReplace1 = ghostPos1+1;
	                tempTwo = grid[pathReplace1][pathReplace2];
	                grid[pathReplace1][pathReplace2] = ghost;
	                grid[ghostPos1][ghostPos2] = tempTwo;
	                ghostPos1++;
			}        
	    } 
                                           
        if (grid[ghostPos1][ghostPos2] == grid[8][1] && ghostPath1 == true)
        {
                ghostTravelPathY = 15;
                ghostTravelPathX = 15;
                ghostPath1 = false;
                ghostPath2 = false;
        }
        if (grid[ghostPos1][ghostPos2] == grid[8][15] && ghostPath1 == true)
        {
                ghostTravelPathY = 15;
                ghostTravelPathX = 15;
                ghostPath1 = false;
                ghostPath2 = false;
        }
        if (grid[ghostPos1][ghostPos2] == grid[2][1] && ghostPath1 == true)
        {
                ghostTravelPathY = 15;
                ghostTravelPathX = 15;
                ghostPath1 = false;
                ghostPath2 = false;
        }
        else if(grid[ghostPos1][ghostPos2] == grid[15][15] && ghostPath2 == false)
        {
                ghostTravelPathY = 1;
                ghostTravelPathX = 15;
                ghostPath2 = true;
                ghostPath3 = false;
        }
     
        else if (grid[ghostPos1][ghostPos2] == grid[1][15] && ghostPath3 == false)
        {
                ghostTravelPathY = 15;
                ghostTravelPathX = 1;
                ghostPath3 = true;
                ghostPath4 = false;
        }
        if (grid[ghostPos1][ghostPos2] == grid[1][8] && ghostPath4 == false)
        {
                ghostTravelPathY = 8;
                ghostTravelPathX = 1;
                ghostPath4 = true;
                ghostPath5 = false;
        }
        if (grid[ghostPos1][ghostPos2] == grid[15][8] && ghostPath4 == false)
        {
                ghostTravelPathY = 8;
                ghostTravelPathX = 1;
                ghostPath4 = true;
                ghostPath5 = false;
        }
        if (grid[ghostPos1][ghostPos2] == grid[15][1] && ghostPath4 == false)
        {
                ghostTravelPathY = 8;
                ghostTravelPathX = 1;
                ghostPath4 = true;
                ghostPath5 = false;
        }
        else if (grid[ghostPos1][ghostPos2] == grid[8][1] && ghostPath5 == false)
        {
                ghostTravelPathY = 8;
                ghostTravelPathX = 8;
                ghostPath5 = true;
                ghostPath6 = false;
        }
        else if (grid[ghostPos1][ghostPos2] == grid[8][8] && ghostPath6 == false)
        {
                ghostTravelPathY = 2;
                ghostTravelPathX = 1;
                ghostPath1 = true;
                ghostPath2 = true;
                ghostPath3 = true;
                ghostPath4 = true;
                ghostPath5 = true;
                ghostPath6 = true;
       }
    }
}

/* This is Trino's ghost function.
   The objective of my ghost function is to simply get the ghosts to chase pacman.
   For no other reason did I choose to call my function 'ghostDudeChasing'.
*/
void ghostDudeChasing(int &ghostPos1, int &ghostPos2, int pacManPos1, int pacManPos2, char grid[17][17],
	int &pathReplace1, int &pathReplace2){
    
    // The character values are named and given values
    char temp = ' ';
    char wall = 219;
    
    /* 'ghostPos1' is the ghost's vertical value in the grid. 'pacManPos1' is the 
       vertical pacman value in the grid. 
       If pacman's vertical position on the grid has a lower value than the ghost's
       vertical position, and there is no wall to where the ghost will move, 
       this conditional statement will run, making the ghost move an 
       UPWARD direction in the grid.*/
    if((ghostPos1 > pacManPos1) && (validateGhostMove(grid[ghostPos1 - 1][ghostPos2]) == true)){
		
		pathReplace1 = ghostPos1 - 1;
		pathReplace2 = ghostPos2;
        
		if(grid[pathReplace1][pathReplace2] != packDude){
			// The character to where the ghost will move ahead to will get passed down to a temporary value
			temp = grid[pathReplace1][pathReplace2];
			
			// The ghost character and the character to where the ghost will move ahead of will be switched
			grid[pathReplace1][pathReplace2] = grid[ghostPos1][ghostPos2];
			
			// The temporary value will get passed to where the the ghost's character used to be at
			grid[ghostPos1][ghostPos2] = temp;
			
			// After all the operations have taken place, the ghost position value will finally decrement
			ghostPos1--;
		}
		replaceCharsAfterSwap(pathReplace1, pathReplace2, pacManPos1, pacManPos2, ghostPos1, ghostPos2, grid);
    }
    /* 'ghostPos1' is the ghost's vertical value in the grid. 'pacManPos1' is the 
       vertical pacman value in the grid. 
       If pacman's vertical position on the grid has a higher value than the ghost's
       vertical position, and there is no wall to where the ghost will move,
       this conditional statement will run, making the ghost move a DOWNWARD
       direction in the grid.*/    
    else if((ghostPos1 < pacManPos1) && (validateGhostMove(grid[ghostPos1 + 1][ghostPos2]) == true)){

		pathReplace1 = ghostPos1 + 1;
		pathReplace2 = ghostPos2;
		
		if(grid[pathReplace1][pathReplace2] != packDude){
			// The character to where the ghost will move ahead to will get passed down to a temporary value
			temp = grid[pathReplace1][pathReplace2];
	        
			// The ghost character and the character to where the ghost will move ahead of will be switched
			grid[pathReplace1][pathReplace2] = grid[ghostPos1][ghostPos2];
			
			// The temporary value will get passed to where the the ghost's character used to be at
			grid[ghostPos1][ghostPos2] = temp;
			
			// After all the operations have taken place, the ghost position value will finally increment
			ghostPos1++;
		}
		replaceCharsAfterSwap(pathReplace1, pathReplace2, pacManPos1, pacManPos2, ghostPos1, ghostPos2, grid);
	}
    /* 'ghostPos2' is the ghost's horizonal value in the grid. 'pacManPos2' is the
       horizontal pacman value in the grid.
       If pacman's horizontal position on the grid has a lower value than the ghost's
       horizontal position, and there is no wall to where the ghost will move,
       this conditional statement will run, making the ghost move LEFT in the grid.*/
    else if((ghostPos2 > pacManPos2) && (validateGhostMove(grid[ghostPos1][ghostPos2 - 1]) == true)){

		pathReplace1 = ghostPos1;
		pathReplace2 = ghostPos2 - 1;
		
		if(grid[pathReplace1][pathReplace2] != packDude){
			// The character to where the ghost will move ahead to will get passed down to a temporary value
			temp = grid[pathReplace1][pathReplace2];
	        
			// The ghost character and the character to where the ghost will move ahead of will be switched
			grid[pathReplace1][pathReplace2] = grid[ghostPos1][ghostPos2];
		
			// The temporary value will get passed to where the the ghost's character used to be at
			grid[ghostPos1][ghostPos2] = temp;
			
			// After all the operations have taken place, the ghost position value will finally decrement
			ghostPos2--;
		}
		replaceCharsAfterSwap(pathReplace1, pathReplace2, pacManPos1, pacManPos2, ghostPos1, ghostPos2, grid);
    }
    /* 'ghostPos2' is the ghost's horizontal value in the grid. 'pacManPos2' is the
       horizontal pacman value in the grid.
       If pacman's horizontal position on the grid has a higher value that the ghost's
       horizontal position, and there is no wall to where the ghost will move,
       this conditional statement will run, making the ghost move RIGHT in the grid.*/
    else if((ghostPos2 < pacManPos2) && (validateGhostMove(grid[ghostPos1][ghostPos2 + 1]) == true)){
		
		pathReplace1 = ghostPos1;
		pathReplace2 = ghostPos2 + 1;
		
		if(grid[pathReplace1][pathReplace2] != packDude){
			// The character to where the ghost will move ahead to will get passed down to a temporary value
			temp = grid[pathReplace1][pathReplace2];
	        
			// The ghost character and the character to where the ghost will move ahead of will be switched
			grid[pathReplace1][pathReplace2] = grid[ghostPos1][ghostPos2];
	        
			// The temporary value will get passed to where the the ghost's character used to be at
			grid[ghostPos1][ghostPos2] = temp;
			
			// After all the operations have taken place, the ghost position value will finally increment
			ghostPos2++;
		}
		replaceCharsAfterSwap(pathReplace1, pathReplace2, pacManPos1, pacManPos2, ghostPos1, ghostPos2, grid);
	}
}/* The end of my ghost chasing pacman function */

// This function will replace characters on the grid, when the ghost comes in contac with the pacman
void replaceCharsAfterSwap(int pathReplace1, int pathReplace2, 
	int pacManPos1, int pacManPos2, int ghostPos1, int ghostPos2, 
	char grid[17][17]){
	
	// If the space ahead to where the ghost will move, equals a pacman character,
	// then the replacement of characters will occur.
	if(grid[pathReplace1][pathReplace2] == packDude){
		grid[pacManPos1][pacManPos2] = ' ';
		grid[ghostPos1][ghostPos2] = grid[pathReplace1][pathReplace2];
	}
}

//==========================================================================ends

// This function will move the pacman - Trino E.
void movePacMan(int &pacManVerticalPos, int &pacManHorizontalPos, char grid[17][17], int &score, int &m, bool &boostOn, bool &run){
	
	// The variables will be declared
	char userInput = ' ';
	const char escape = 27;
	int moveVerticalPos = 0;
	int moveHorizontalPos = 0;
	
	// This function will grab the user's input
	grabUserInputForPac(userInput);
	
	// If the user presses the up arrow key, this loop will run
	if(userInput == 'H')
    {
		
		// The values to which the pacman will move ahead of, will be transfered
		moveVerticalPos = pacManVerticalPos - 1;
		moveHorizontalPos = pacManHorizontalPos;
		
		// This function will be called to swap the grid's values
		pacManSwap(pacManVerticalPos, pacManHorizontalPos, moveVerticalPos, moveHorizontalPos, grid, userInput,
			score, m, boostOn);
	}
	// Else if the user presses the down arrow key, this loop will run
	else if(userInput == 'P')
    {
		
		// The values to which the pacman will move ahead of, will be transfered
		moveVerticalPos = pacManVerticalPos + 1;
		moveHorizontalPos = pacManHorizontalPos;
		
		// This function will be called to swap the grid's values
		pacManSwap(pacManVerticalPos, pacManHorizontalPos, moveVerticalPos, moveHorizontalPos, grid, userInput,
			score, m, boostOn);
	}
	// Else if the user presses the left arrow key, this loop will run
	else if(userInput == 'K')
    {
	
		// The values to which the pacman will move ahead of, will be transfered
		moveVerticalPos = pacManVerticalPos;
		moveHorizontalPos = pacManHorizontalPos - 1;
		
		// This function will be called to swap the grid's values
		pacManSwap(pacManVerticalPos, pacManHorizontalPos, moveVerticalPos, moveHorizontalPos, grid, userInput,
			score, m, boostOn);
	}
	// Else if the user presses the right arrow key, this loop will run
	else if(userInput == 'M')
    {
	
		// The values to which the pacman will move ahead of, will be transfered
		moveVerticalPos = pacManVerticalPos;
		moveHorizontalPos = pacManHorizontalPos + 1;
		
		// This function will be called to swap the grid's values
		pacManSwap(pacManVerticalPos, pacManHorizontalPos, moveVerticalPos, moveHorizontalPos, grid, userInput,
			score, m, boostOn);
	}
	// Else if the user presses the escape key, this loop will run
	else if(userInput == escape)
    {
		
		// This function will be called to prompt for user's input
		toQuitTheGame(run);		
	}
	
	// This function will clear flush out the user's input after this whole funcion takes place
	clearBuffer(userInput);
}

// This function will grab the user's input made for the pacman - Trino E.
void grabUserInputForPac(char &userInput){
	
	// The user's input will be grabbed in this loop
	if(kbhit()){
	
		// The grabbed value will be passed down to 'userInput'
		userInput = getch();
	}
}

// This function will swap the pacman and the space it will move into - Trino E.
void pacManSwap(int &pacManVerticalPos, int &pacManHorizontalPos, int moveVerticalPos, int moveHorizontalPos, char grid[17][17], char userInput, 
	int &score, int &m, bool &boostOn){
	
	// The characters will be declared
	char temp = ' ';
	const char emptyPath = ' ';
	const char wall = 219;
	
	// If the position the pacman will move ahead of does not equal a wall, this loop will execute
	if(validatePacManMove(grid[moveVerticalPos][moveHorizontalPos]) == true)
    {
		
		// This function will capture the scores
		scores(moveVerticalPos, moveHorizontalPos, grid, score, m, boostOn);
		
		// The pacman character will get stored in a temporary value
		temp = grid[pacManVerticalPos][pacManHorizontalPos];
		
		// The pacman character will be replaced by an empty path
		// With this, the pacman makes the pellets dissappear from the path it moves into
		grid[pacManVerticalPos][pacManHorizontalPos] = emptyPath;
		
		// The pacman character will get swapped to the space ahead
		grid[moveVerticalPos][moveHorizontalPos] = temp;
		
		// This function will be called to change the integer values of the pacman's position
		pacManChangePosValue(pacManVerticalPos, pacManHorizontalPos, userInput);
	}
	
	shortCutAcrossGrid(pacManVerticalPos,pacManHorizontalPos, grid);
	
}

/* This function will increment the score values

	A large part of these variables originally are not mine. So if there's any ambiguity as to what they do,
	don't ask me. I found them in my pacman code in my attempt to switch everything into a prototype. 
	So in order for I not to sabotage anyone else's work, I decided to put them as they were in the mother loop
	inside of this prototype, because I figured they must have some form of importance to the program. 
		-Trino E.
*/
void scores(int moveVerticalPos, int moveHorizontalPos, char grid[17][17], int &score, int &m, bool &boostOn){
	
	// The constant characters will be changes
	const char path = 249;
	const char boost = 15;
	
	// Will calculate the score for every pellet that the pacman eats
    if(grid[moveVerticalPos][moveHorizontalPos] == path){
		score++;
    }
	// For every boost eaten, 50 points will be added
	if(grid[moveVerticalPos][moveHorizontalPos] == boost){
		score += 50;
        m = 0;
        boostOn = true;
	}
}

// This function will increment the pacman's position integer values in respect to the user's input value made for the 
// pacman movement - Trino E.
void pacManChangePosValue(int &pacManVerticalPos, int &pacManHorizontalPos, char userInput){
	
	// If the user pressed the up arrow key, the vertical position integer value of the pacman will decrease
	if(userInput == 'H'){
		pacManVerticalPos--;
	}
	// Else if the user pressed the down arrow key, the vertical position integer value of the pacman will increase
	else if(userInput == 'P'){
		pacManVerticalPos++;
	}
	// Else if the user pressed the left arrow key, the horizontal position  integer value of the pacman will decrease
	else if(userInput == 'K'){
		pacManHorizontalPos--;
	}
	// Else if the user pressed the right arrow key, the horizontal position  integer value of the pacman will increase
	else if(userInput == 'M'){
		pacManHorizontalPos++;
	}
}

// This will make the shortcuts on the grid to work
void shortCutAcrossGrid(int &verticalPos, int &horizontalPos, char grid[17][17]){
	
	if(verticalPos == 4 && horizontalPos == 0){
		grid[verticalPos][horizontalPos] = ' ';
		verticalPos = 4;
		horizontalPos = 16;
	}
	else if(verticalPos  == 4 && horizontalPos == 16){
		grid[verticalPos][horizontalPos] = ' ';
		verticalPos = 4;
		horizontalPos = 0;		
	}
	else if(verticalPos == 12 && horizontalPos == 0){
		grid[verticalPos][horizontalPos] = ' ';
		verticalPos = 12;
		horizontalPos = 16;
	}
	else if(verticalPos == 12 && horizontalPos == 16){
		grid[verticalPos][horizontalPos] = ' ';
		verticalPos = 12;
		horizontalPos = 0;
	}
}

bool validateGhostMove(char test){
	
	bool toMove = true;
	
	// If there is a wall, the statement will become false
	if(test == wall){
		toMove = false;
	}
	// else the statement will be true
	else
    {
		toMove = true;
	}
	
	return toMove;
}

bool validatePacManMove(char test){
	
	bool toMove = true;
	
	// If there is a wall, the value will become false
	if(test == wall){
		toMove = false;
	}
	// If there is a ghost ahead of pacman, value will become false
	else if(test == ghost){
		toMove = false;
	}
	// else the statement will be true
	else{
		toMove = true;
	}
	
	return toMove;
}

// This function's purpose is to make the color changes in the game
void setColorOnGrid(char grabbedChar, int amountAllowed){
	// These are the characters that will be detected
	char pacDude = 2;
	char wall = 219;
    char path = 249;
	char ghost = 1;
	char boost = 15;
	char  crystal = 3;
    char bonus = 36;
    char wallLeftTrasport = 174;
    char wallRightTrasport = 175;
    
    //char gameOver1 = 'GAME';
    //char gameOver2 = 'OVER';
    // This will set the color for the game, 
 
    // depending on the character detected
    if(grabbedChar == pacDude){        
        setcolor(14);   
    }
	if(grabbedChar == wall){
        setcolor(2);
    }  
	else if(grabbedChar == path) {
        setcolor(14);
    }
    else if(grabbedChar == ghost){
		setcolor(12);
    }
    else if(grabbedChar == boost){
        setcolor(14);
    }
	else if (grabbedChar == crystal){
		setcolor(7);
	}
		else if (grabbedChar == bonus){
  setcolor(9);

  }
  else if (grabbedChar ==  wallLeftTrasport){
  setcolor(11);

  }
  else if (grabbedChar == wallRightTrasport){
  setcolor(11);

  }

//else if (grabbedChar == gameOver2){
//setcolor(14);
//}    
}

void boostColor(char grabbedChar, int amountAllowed,bool boostOn) {
	// These are the characters that will be detected
	char pacDude = 2; 
    char ghost = 1;
    char crystal = 3;
    // depending on the character detected
        if(boostOn == true && grabbedChar == pacDude){
                  setcolor(amountAllowed);     
                }
        else if(boostOn == false && grabbedChar == pacDude){        
        setcolor(14);
        }
       if(boostOn == true && grabbedChar == ghost){
        setcolor(11);   
}
	if (grabbedChar == crystal ){
		setcolor(amountAllowed);
	}
}

// This function's purpose is to exit the game if the user presses 'ESC' on the
// keyboard while the game runs. 
void toQuitTheGame(bool &run){

	// The variables are named
	string userInput = " ";
	bool repeat = true;
	
	// While the statement remains true, this loop will run.
	while(repeat == true) {
        clearScreen();
        setcolor(15);
		cout << "Are you sure you want" << endl;
        cout << "to quit the game," << endl;
        cout << "y/n?";
		cin >> userInput;
	    
	    // If the user inputs a "y" or a "Y" for yes, this loop will run
		if(userInput == "Y" || userInput == "y") 
		{
            main();
			
			// 'repeat' will be false, meaning that the user won't be reasked 
			// for input after this loop taked 
			repeat = false;		
		}
		
		// If the user inputs a "N" or"n" for no, this loop will run
        else if(userInput == "N" || userInput == "n") {
			
			// 'repeat' will be false, meaning that the user won't be reasked 
			// for input after this loop taked place
			repeat =  false;
		}
		
		// else if the user makes incorrect input, the this loop will run
        else {
             
            /* 'repeat' will remain true, which will make the while loop in 
               this program to repeat, meaning that the user will be reasked
               for input */
			repeat = true;
		}
	}
	clearScreen();
}

/* This function's purpose is to clear out the buffer from user's input, that 
   way if the user make multiple keystrokes on the keyboard while the game plays,
   they get cleared out, that way the pacman makes not extra moves. */ 
void clearBuffer(char &movingDirection){
    
    // The character value will be resetted to an empty value
    movingDirection = ' ';
}

void consoleResize() {
	
	HANDLE hOut;
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    SMALL_RECT DisplayArea = {0, 0, 4, 4};

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hOut,
                               &SBInfo);

        DisplayArea.Right = 20;
        SetConsoleWindowInfo(hOut,
                             TRUE,
                             &DisplayArea);
 
        DisplayArea.Bottom = 23;
        SetConsoleWindowInfo(hOut,
                             TRUE,
                             &DisplayArea);
	
}

void clearScreen() {
     system("CLS");     
}//End of clear screen

//Sound Function
void sound(void *P)
{//Starts sound funtion
     
     //Loop sound
     for(int i = 0; i < 1000; ++i)
      {
             //Slows The pace of the beeps
             //Sleep(55);
          
             {//Starts beep funtion
                        Beep(150,250);
                        Beep(100,500);
                        Beep(150,250);
                        Beep(200,200);
                        Beep(150,500);
                        Sleep(100);

                        Beep(250,250);
                        Beep(200,500);
                        Beep(150,250);
                        Beep(100,200);
                        Beep(150,250);
                        Sleep(100);

              
             }//End of void sound

      }//End of last for loop

      return;
}//End of return

//********************************//Nohemi's Project***********************************************
//Pacman's High Scores Funtion
void HighScores(int score){//Here starts the funtion of the high scores
      
     //Variables and constants
     int FirstPlace = 0;
     int SecondPlace = 0;
     int ThirdPlace = 0;
     int ArrayPosition = 0;
     string PlayersName = " ";
     
     //Open the input and output files
    ifstream fin("F:\\PacDude_working\\source\\PacmanTotalScores.txt");//This statement is for the high scores section
    ofstream sout ("F:\\PacDude_working\\source\\PacmanHighScores.txt");//This statement is for the high scores section

     //Prompt a user to type a name    
     cout<<"please type your name"<<endl;
     cin>>PlayersName;
     
     //This statement is to let you know that the player's score is belongs to the score that the player got 
     //during the game
    // PlayerScore = score;
    
    cout <<"type any number"<<endl;
    cin>>score;
    //This is an array statement to finds the position that the player got from the scores 
     int ScoresArray[]={FirstPlace, SecondPlace, ThirdPlace, score};
     
     //Those are the text file's scores
     sout<<left << setw(5) <<"Player's Name";        
     sout <<right << setw(20) <<"Player's Scores" << endl;        
    
    // sout <<score <<"   " <<endl;            
    
    
    //This is a for loop statement and it's part of the extraction of the contents of files.
     for(int LoopCounter = 0; LoopCounter < 3;LoopCounter++){
     
     //This statement is to extract the contents of files
         fin>>ScoresArray[ArrayPosition];                 
              ArrayPosition++;
              }//End of loop    
         
         
       //This statement is to see if the player got 1st place or qualify for the top 3.
     if(score > FirstPlace){//Starts first if statement
         cout<<endl<<"Congratulations, You're in First Place!"<<endl;
         }//End of first if statement
         
   //This statement is to see if the player got 1st place 
    if(score > SecondPlace){//This is the second if statement
         cout<<endl<<"Congratulations, You're in Second Place!"<<endl;  
         }//End of second if statement  
         
    if(score < ThirdPlace){//This is the third if statement
         cout <<endl<<"Congratulation, You're in Third Place!"<<endl;
         }//End of third if statement  
          
     //Those are the outputs for the hig score statement. 
     //One is to print it on the console and the other one is to print it on the text file                                                  
          cout<< PlayersName <<"  "<< score<<endl;          
          sout <<right <<setw(8)<< PlayersName <<right << setw(20) <<score<<endl;    
              
system("Pause");
return;
}//End of return

//Bubblesort Function for the continuation of the high scores

//Bubblesort Function for the continuation of the high scores
void Bubblesort(int FirstPlace, int SecondPlace, int ThirdPlace){
     
     //Function variables and constants
     const int NumberOfHighScores = 3;
     
     
     if(FirstPlace < SecondPlace){//Starts first if loop
        int tmp = FirstPlace;
        FirstPlace = SecondPlace;
        SecondPlace = tmp;
        }//End first if loop
       
       
     if(FirstPlace < ThirdPlace){//Starts Second if loop
        int tmp = FirstPlace;
        FirstPlace = ThirdPlace;
        ThirdPlace = tmp;
        }//End second if loop    
        
         
     if(SecondPlace < ThirdPlace){//Starts last if loop
        int tmp = SecondPlace;
        SecondPlace = ThirdPlace;
        ThirdPlace = tmp;
        }return; 
        }//End of the last if loop      

//********************************//End of Nohemi's project***************************************

void pacManAndGhostContact(int &pacManVerticalPos, int &pacManHorizontalPos, 
	int &ghostVerticalPos, int &ghostHorizontalPos, int &lives, int pathReplace1, 
	int pathReplace2, char grid[17][17]){
	
	// If the pacman's and the ghost's position values are the same, this 
    // loop will run
	// if(grid[pathReplace1][pathReplace2] == grid[pacManVerticalPos][pacManHorizontalPos]){
	if((pacManVerticalPos == pathReplace1) && (pacManHorizontalPos == pathReplace2)){
	
		// This function will be called to decrement the lives of pacman
		lifeDecrementation(lives);
		
		// The values will be reset
		resetValues(pacManVerticalPos, pacManHorizontalPos, ghostVerticalPos, ghostHorizontalPos);
	}
}

// The values for the ghost and the pacman will be resetted by calling the 
// global scope values.
void resetValues(int &pacManVerticalPos, int &pacManHorizontalPos, 
	int &ghostVerticalPos, int &ghostHorizontalPos){
	
	// The global scope values will be passed down to the values
	// being used in the program
	pacManVerticalPos = pacManDefaultVerticalPos;
	pacManHorizontalPos = pacManDefaultHorizontalPos;	
    ghostVerticalPos = ghostDefaultVerticalPos;
    ghostHorizontalPos = ghostDefaultHorizontal;
}

// This function is called out in the Game prototype.
// Purpose: To display to the user the time pacman has to kill the ghosts!
void ghostDeath(int &ghostExterminator, int &ghostTimeOff){

     int m = ghostTimeOff;
     int CountDownTimeForGhostKilling = ghostExterminator;

        // This conditionals tells' the user how much time pacman has to exterminate
        // the ghosts.
        if(m  <= 18){
        --CountDownTimeForGhostKilling;
        cout << endl << "KILL THE GHOST " << CountDownTimeForGhostKilling;
             if(CountDownTimeForGhostKilling == 0){
             CountDownTimeForGhostKilling = 18;
             }
        }

        else if((19<m)&&(m<30)){
             cout << endl <<"The Ghost Have Gain Their Power" << endl;
             }

            ghostTimeOff = m;
            ghostExterminator = CountDownTimeForGhostKilling;

}

// This is the timer protype
void clickTime(int &time, int loops, const int Time){

     // This tells the program after the loop repeats 7 times, to decrement a second!
     if((loops % 8) == 7){
        time--;
        }
     
     // This tells the user when its time is up!
     if(time==-1){
     cout << endl <<"Your Time is UP!!!" << endl;
     time = Time;
     }

}

// This program is called by the pacManLives prototype.
// Purpose: Displays game over, will reset the game, and also will call the high score functions!
void gameOverLink(){
     
    // This value is made false that way it can reset the gameboard, when calling
    // the gameMenu function.
    bool newGameQuestion = false;
	int counter = 100;
	int displayCount = 0;
     
    clearScreen();
	setcolor(15);
	
	// This while loop is a counter for the amount of time 'Game Over' will appear on the window
	while(counter >= 0){
		
		// The user's score will be outputted by the global value 'scoreDisplay'
		cout << "Your Score: " << scoreDisplay << endl << endl;
		
	    // This is self explanatory. ('U') << Happy face.
	    cout << "GAME OVER" << endl << endl << endl;
	     
		// For every time the remainder of the counter is zero, the value of the counter displayed will change
		if(counter % 10 == 0){
			
			// The counter displayed will be divided by 10
			displayCount = counter / 10;   
		}
		
		// If the value of 'counter' is not equal to 0, this conditional will take effect
		if(counter != 0){
  		
  			// This will output the time counted
     		cout << ' ' << ' ' << ' ' << displayCount << endl;		
        }
		// once the counter has reached 100, a system pause will occur
		else if(counter == 0){
			system("pause");
		}
		
	    clearScreen();// This clear screen will clear everything out so things will not get messy when displayed
		
		// The counter will update
		counter--;
	}
	
    //...the high scores will be called right here.
    void HighScore(int score);// This is the high score funtion
    
	
    clearScreen();// The screen will clear right here and display the following:
	// will set the color back to normal
	
    /*just in case the user wants to play again*/
    GameMenu(newGameQuestion);//This function should reset the game, if the user selects yes.
}

// This function will be called by the PROGRAMMERS!
// Purpose: To Subtract a Life.
void lifeDecrementation(int &numberOfLives){
                            
    // A life is lost.
    numberOfLives--;
                            
    //While the lifes are greater than zero the program
    // will let the user play again!
    if(numberOfLives >= 0){
	
		clearScreen();
		
		// Gives an f***ed up sound to let the user know they've been screwed
		Beep(290,99);Beep(290,99);Beep(290,99);Beep(290,99);Beep(290,99);
		
		if(numberOfLives > 1){
			cout << "You Have "<< numberOfLives << " lives Left";
		}
		else if(numberOfLives == 1){
			cout << "You Have "<< numberOfLives << "LIFE Left" ;
		}
		else{
			cout << "LAST LIFE";
		}
		
		cout << endl << endl;
		system("pause"); // I think this should be controlled
		// by a timer rather than a system pause, for this reason:
		// If the user is messing with the keys
		// while they lost a life then will not see
		// that they lost a life, because they 
		// were pressing the keys!
		// Don't understand me? PLAY THE GAME,
		// and observe if your life was lost!?
	}
                            
	// The game over function will be call here if the user
	// has no more lives to waste!
	else if (numberOfLives < 0){
        Beep(290,99);Beep(290,99);Beep(290,99);Beep(290,99);Beep(290,99);
		gameOverLink();
	}
}

// This program is called by the GameMenu prototype above.
// Purpose: To display the lives of pacman!
void pacmansLives(int numberOfLives, char packDude){
     cout << "Lives Left: ";

    for(int x = numberOfLives; x>0;x--){
		cout << packDude;
    }
}

int getOption(){
    
    //Function variables and constants 
    int number_Entered = 0;
    
    //Prompt input from the user
    cout << "Please enter one of the following numbers. \n";
    
    //Display the menu to user to choose from
    cout << left << setw(4) << " (1) " << left << setw(20) 
         << "PLAY GAME" << endl;
    cout << left << setw(4) << " (2) " << left << setw(20) << "QUIT" << endl;   
    
    //Store user input
    cin >> number_Entered;

    //Return to main
    return number_Entered;
    }
//End of function    

void Bonus(int &bonusY, int &bonusX,char grid[17][17],int &bonusTravelPathY,
int &bonusTravelPathX,char bonus,int pathReplace1,int pathReplace2,
bool &followPath1,bool &followPath2,bool &followPath3,bool &followPath4,bool 
&followPath5,bool &followPath6,bool &followPath7,bool &followPath8){
    char wall = 219;
    char tempTwo = ' ';
     
     if(bonusY < bonusTravelPathY && grid[bonusY+1][bonusX] != wall){
                pathReplace1 = bonusY+1;
                pathReplace2 = bonusX;
                 tempTwo = grid[pathReplace1][pathReplace2];
                 grid[pathReplace1][pathReplace2] = bonus;
                 grid[bonusY][bonusX] = tempTwo;
                 bonusY++;
                 
                }                   
                if(bonusY > bonusTravelPathY && grid[bonusY-1][bonusX] != wall){
             pathReplace1 = bonusY-1;
             pathReplace2 = bonusX;
             tempTwo = grid[pathReplace1][pathReplace2];
             grid[pathReplace1][pathReplace2] = bonus;
             grid[bonusY][bonusX] = tempTwo;
             bonusY--;
                     }   
             if (grid[bonusY+1][bonusX] == wall){
                if (grid[bonusY][bonusX-1] != wall){
                pathReplace2 = bonusX-1;
                pathReplace1 = bonusY;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusX--;}
                if (grid[bonusY][bonusX+1] != wall){
                pathReplace2 = bonusX+1;
                pathReplace1 = bonusY;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusX++;}         
                }
                     
     
     
                else if (grid[bonusY-1][bonusX] == wall){
                if (grid[bonusY][bonusX-1] != wall){
                pathReplace2 = bonusX-1;
                pathReplace1 = bonusY;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusX--;}
                if (grid[bonusY][bonusX+1] != wall){
                pathReplace2 = bonusX+1;
                pathReplace1 = bonusY;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusX++;}}         
                
                if(bonusX < bonusTravelPathX && grid[bonusY][bonusX+1] != wall){
                pathReplace2 = bonusX+1;
                pathReplace1 = bonusY;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusX++;
                }
                else if(bonusX > bonusTravelPathX && grid[bonusY][bonusX-1] != wall ){
                pathReplace2 = bonusX-1;
                pathReplace1 = bonusY;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusX--;
                }
                
                
                if (grid[bonusY][bonusX-1] == wall){
                if (grid[bonusY-1][bonusX] != wall){
                pathReplace2 = bonusX;
                pathReplace1 = bonusY-1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusY--;}
                
                if (grid[bonusY+1][bonusX] != wall){
                pathReplace2 = bonusX;
                pathReplace1 = bonusY+1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusY++;}         
                                           }
                                           

                
                else if (grid[bonusY][bonusX-1] == wall){
                if (grid[bonusY-1][bonusX] != wall){
                pathReplace2 = bonusX;
                pathReplace1 = bonusY-1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusY--;}
                if (grid[bonusY+1][bonusX] != wall){
                pathReplace2 = bonusX;
                pathReplace1 = bonusY+1;
                tempTwo = grid[pathReplace1][pathReplace2];
                grid[pathReplace1][pathReplace2] = bonus;
                grid[bonusY][bonusX] = tempTwo;
                bonusY++;}        } 
                                           
                

     if (grid[bonusY][bonusX] == grid[1][15] && followPath1 == true){
         bonusTravelPathY = 8;
         bonusTravelPathX = 8;
     followPath1 = false;
     followPath2 = false;
     }
     else if(grid[bonusY][bonusX] == grid[8][8] && followPath2 == false){
     bonusTravelPathY = 15;
     bonusTravelPathX = 1;
     followPath2 = true;
     followPath3 = false;
     }
     
     else if (grid[bonusY][bonusX] == grid[15][1] && followPath3 == false){
     bonusTravelPathY = 2;
     bonusTravelPathX = 1;
     followPath3 = true;
     followPath4 = false;
     }
     else if (grid[bonusY][bonusX] == grid[2][1] && followPath4 == false){
     bonusTravelPathY = 15;
     bonusTravelPathX = 15;
     followPath4 = true;
     followPath5 = false;
     }
     else if (grid[bonusY][bonusX] == grid[15][15] && followPath5 == false){
     bonusTravelPathY = 1; // actually wanted it to go to 8
     bonusTravelPathX = 15; // wanted a 1
     followPath5 = true;
     followPath6 = false;}
     else if (grid[bonusY][bonusX] == grid[1][15] && followPath6 == false){
     bonusTravelPathY = 1;
     bonusTravelPathX = 4;
     followPath6 = true;
     followPath7 = false;
     }
     else if (grid[bonusY][bonusX] == grid[1][4] && followPath7 == false){
     bonusTravelPathY = 9;
     bonusTravelPathX = 1;
     followPath7 = true;
     followPath8 = false;
     }
     else if (grid[bonusY][bonusX] == grid[9][1] && followPath8 == false){
     bonusTravelPathY = 1;
     bonusTravelPathX = 15;
     followPath1 = true;
     followPath2 = true;
     followPath3 = true;
     followPath4 = true;
     followPath5 = true;
     followPath6 = true;
     followPath7 = true;
     followPath8 = true;
     }
     
     }
