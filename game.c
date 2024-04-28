//Name: MOEEN ABU KATISH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"mineSweeper.h"
#include"getch.h"
#include"colorPrint.h"


int main(){
    int rows,columns,difficulty;
    GameBoard mSweeper;
    char button='0';
    
    
    printf("Please enter the number of rows: ");
    scanf("%d",&rows);
    printf("\nPlease enter the number of columns: ");
    scanf("%d",&columns);
    printf("How hard do you like it to be: (1) EASY, (2) MEDIUM, (3) HARD ?\n");
    while(difficulty>3 || difficulty<1){//keep trying to take a valid difficulty if the input is invalid
        scanf("%d",&difficulty);
    }
    
    
    button=getche()-50;//make sure that the first click even if it is wrong, it it is not taken into account
    
    initBoard(&mSweeper,rows,columns,difficulty);//initiallizing the board
    int coordinates[2]={0,0};//default cursor initiallized
    printBoard(&mSweeper,coordinates);//print the first state of the board before any clicks
    
    
    void freeBoard(GameBoard g){//method that frees the board
        for(int i=0;i<g.rows;i++){//freeing the board
                  free(g.board[i]);
                  g.board[i]==NULL;//extra step of making sure it is null after freeing
            }
                free(g.board);
                g.board=NULL;//extra step of making sure it is null after freeing
    }
	   
	   
	    printf("Controls:-\nMovement:\n");
		printf("Up : %c\nDown : %c,\nLeft : %c,\nRight : %c\nInteractions:\n",UP, DOWN, LEFT, RIGHT);
		printf("Click - Enter, Flag - Space\n");
		printf("Press %c to quit.\n",QUIT);
   
    while(1){//only quit when either the game is finished or when the q button is pressed
        
        button=getch();//take button input
        if(button== QUIT){//quit when q is pressed
            printf("You quit!");
            freeBoard(mSweeper);
                exit(0);
            break;
        }
        clearScreen();
        if(button==UP){//move up a tile in the board
            if(coordinates[0]>0){
                coordinates[0]--;
            }
        }
        else if(button==DOWN){//move down a tile in the board
            if(coordinates[0]<rows-1){
                coordinates[0]++;
            }
        }
        else if(button==RIGHT){//move right a tile in the board
            if(coordinates[1]<columns-1){
                coordinates[1]++;
            }
        }
       else if(button==LEFT){//move left a tile in the board
            if(coordinates[1]>0){
                coordinates[1]--;
            }
        }
        else if(button==FLAG_TILE){//flag the tile or remove the flag if it already is flagged 
            flagTile(&mSweeper,coordinates[0],coordinates[1]);
        }
        else if(button==CLICK_TILE){//click on the tile 
          clickTile(&mSweeper,coordinates[0],coordinates[1]);
          if(mSweeper.isMineClicked==TRUE||mSweeper.hiddenTiles==mSweeper.totalMines){//exit the loop when the game is either won or lost
                if(mSweeper.isMineClicked==TRUE){//game is lost
                printBoard(&mSweeper,coordinates);//print the final state of the board when ypu won/lost before freeing the memory allocation
                printf("\nYOU HIT A MINE!\nYOU LOSE, GAME OVER!!!\n");
            }
                 if(mSweeper.hiddenTiles==mSweeper.totalMines){//game is won
                printBoard(&mSweeper,coordinates);//print the final state of the board when ypu won/lost before freeing the memory allocation
                printf("YOU FINISHED THE GAME WITHOUT HITTING A MINE!\nGOOD JOB, YOU WIN!!!\n");
            }
                
               freeBoard(mSweeper);
                exit(0);
        }
            
        }
        
        printf("\n\n\n");
		printBoard(&mSweeper,coordinates);//keep printing the gameboard	
	    printf("Controls:-\nMovement:\n");
		printf("Up : %c\nDown : %c,\nLeft : %c,\nRight : %c\nInteractions:\n",UP, DOWN, LEFT, RIGHT);
		printf("Click - Enter, Flag - Space\n");
		printf("Press %c to quit.\n",QUIT);
       }
        
         return 1;
    }
    
   
