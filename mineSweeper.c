//ID:212307128
//Name: MOEEN ABU KATISH
#include "mineSweeper.h"
#include "colorPrint.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TILE_HIDDEN 		BG_Cyan
#define TILE_VISIBLE		BG_White
#define TILE_MINE			BG_Red
#define TILE_FLAGGED		BG_Red
#define TILE_CURSOR			BG_Magenta
#define TILE_STRING		"  "




bool initBoard(GameBoard *g, int rows, int cols, int level){
    
    if(rows > MAX_BOARD_DIM  || cols> MAX_BOARD_DIM ){
        return FALSE;//not sure if this is the correct thing to do here but I went with it
        
    }
else{    
    
    g->cols=cols;
    g->rows=rows;
    
    Tile** playBoard=(Tile**)malloc(rows* sizeof(Tile*));//memory allocation of rows
    
    if(playBoard==NULL){//check if memory allocation failed
        printf("Memory Allocation Failed!");
        return FALSE;
    }
    for(int i=0;i<rows;i++ ){
        
        playBoard[i]=(Tile*)malloc(cols* sizeof(Tile));//memory allocation of columns
        if(playBoard[i]==NULL){//check if memory allocation failed
            printf("Memory Allocation Failed!");
            return FALSE;
        }
        g->board=playBoard;
    }
    
    int i=0;
    
    while(i<(g->rows)){//initiallizing all of the properties to FALSE and 0
        for(int j=0;j<(g->cols);j++){
            
            
            g->board[i][j].isMine=FALSE;
            g->board[i][j].isFlagged=FALSE;
            g->board[i][j].isVisible=FALSE;
            g->board[i][j].numOfMines=0;
            
            
        }
        i+=1;
    }
    
    g->hiddenTiles=rows*cols;//total number of mines
    g->isMineClicked=FALSE;
    g->totalMines=0;
    
    populateMines(g,level);
    markNumbers(g);

    return TRUE;//successfully created a gameboard
    
}
}


void populateMines(GameBoard *g, int level){
   
    srand(time(NULL));//I used the time-random method for the random coordinates in the board
   
   int  boardRows=g->rows;
   int boardCols=g->cols;
   int difficultyPercentage=0;
   
    if(level==EASY){
        difficultyPercentage=EASY_LEVEL_PERCENT;
    }
    else if(level==MEDIUM){
        difficultyPercentage=MEDIUM_LEVEL_PERCENT;
        
    }
    else if (level==HARD){
        difficultyPercentage=HARD_LEVEL_PERCENT;
    }
    
    int totalTiles=boardRows*boardCols;
    g->totalMines=(totalTiles*difficultyPercentage)/100;//total number of mines
    
    for(int i=0; i<(g->totalMines);i++){//randomely scatter mines in the board using the time "library"
        //random method to find random coordinate in the board
        int randMineCol=rand()%(boardCols);
        int randMineRow=rand()%(boardRows);
       
        if(g->board[randMineRow][randMineCol].isMine==FALSE){
       
            g->board[randMineRow][randMineCol].isMine=TRUE;
        
    }

        else if(g->board[randMineRow][randMineCol].isMine==TRUE){//makes sure there are no lost mines in the proccess of populating the board with them
       
        i--;//go back 1 step to make sure there are not lost mines
        
    }
    }        
    
    
    
}

void markNumbers(GameBoard *g){
    
    int boardRows=g->rows;
    int boardCols=g->cols;
    
    for(int i=0 ;i<boardRows;i++){
        for(int j=0;j<boardCols;j++){
            
            if(g->board[i][j].isMine==FALSE){
                if(i>0){//not first row
                    
                    if(g->board[i-1][j].isMine==TRUE){//first possibility(check the previous in the same column)
                        g->board[i][j].numOfMines++;
                    
                        
                    }
                    if(j>0){
                        
                        if(g->board[i-1][j-1].isMine==TRUE){//second possibility(check back diagonally)
                            g->board[i][j].numOfMines++;
                        
                        }
                    }
            
                    if(j<boardCols-1){
            
                        if(g->board[i-1][j+1].isMine==TRUE){//third possibility(check next column in previous row)
                            g->board[i][j].numOfMines++;
            
                        }
                    }
                    
                }
                
                if(i<boardRows-1){//not last row
                    
                    if(g->board[i+1][j].isMine==TRUE){//fourth possibility(check the next row on the same column)
                        g->board[i][j].numOfMines++;
                        
                    }
                    
                    if(j>0){
                        
                        if(g->board[i+1][j-1].isMine==TRUE){//fifth possibility(check next row and previous column)
                            g->board[i][j].numOfMines++;
                            
                        }
                    }
                    
                    if(j<boardCols-1){
                        
                        if(g->board[i+1][j+1].isMine==TRUE){//sixth possibility(check next diagonally)
                            g->board[i][j].numOfMines++;
                        
                        }
                    }
                }
                if(j>0){//not the first column
                    
                    if(g->board[i][j-1].isMine==TRUE){//seventh possibility(check previous column in same row)
                        g->board[i][j].numOfMines++;
                    
                            }
                }
                
                if(j<boardCols-1){//not the last column
                    
                    if(g->board[i][j+1].isMine==TRUE){//eighth possibily(check next column in same row)
                        g->board[i][j].numOfMines++;
                    
                        
                    }
                }
                
            }
            
        }    
    }
}

void flagTile(GameBoard *g, int row, int col){//flagging tiles and removing flags if it already is flagged
   
   
    if(g->board[row][col].isVisible==TRUE){
   
    return;
   
    }
   
    else if(g->board[row][col].isVisible==FALSE && g->board[row][col].isFlagged==TRUE){
   
        g->board[row][col].isFlagged=FALSE;
   
    }
   
    else if((g->board[row][col].isVisible==FALSE) && (g->board[row][col].isFlagged==FALSE)){
   
        g->board[row][col].isFlagged=TRUE;
   
    }
    
}

void clickTile(GameBoard *g, int row, int col){
    
    int tempRows=g->rows;
    int tempCols=g->cols;
    
    
    if(g->board[row][col].isVisible==TRUE){//do nothing if tile is already visible
        return;
    }
    
    if(g->board[row][col].isVisible==FALSE && g->board[row][col].isFlagged==TRUE){//do nothing if tile is flagged
        return;
    }
    
    if(g->board[row][col].isVisible==FALSE && g->board[row][col].isFlagged==FALSE){
        //reduce the hidden tiles number by 1 when clicking on a hidden tile and make it visible
        g->board[row][col].isVisible=TRUE;
        g->hiddenTiles--;
        
        if(g->board[row][col].isMine==TRUE){
           
            g->isMineClicked=TRUE;
            
        }
        
        else if(g->board[row][col].numOfMines>0){
            g->board[row][col].isVisible=TRUE;
           
        }
        else if(g->board[row][col].numOfMines==0){//this is done using recursion with the same procedure used in the previous markNumbers method
        
            if(row>0){//not on the first row
                
                clickTile(g,row-1,col);//first possibility(previous row in the same column)
                
                if(col>0){
                    clickTile(g,row-1,col-1);//second possibility(check back diagonally)
                }
                if(col<tempCols-1){
                    clickTile(g,row-1,col+1);//third possibility(check next column in the previous row)
                }
            
            }
            
            if(row<tempRows-1){//not on the last row
                
                clickTile(g,row+1,col);//fourth possibility(next row in the same column)
                
                if(col>0){//fifth possibility(next row and previous column)
                    clickTile(g,row+1,col-1);
                }
                if(col<tempCols-1){//sixth possibility(check next diagonally)
                    clickTile(g,row+1,col+1);
                }
            }
            
            if(col>0){//seventh possibility(check previous column in the same row)
                clickTile(g,row,col-1);
            }
            if(col<tempCols-1){//eighth possibility(check next column in the same row)
                clickTile(g,row,col+1);
            }
            
            
       
        }
    }
    
}




void printBoard(GameBoard *g, int cursorCoords[2]){
    int tempRows=g->rows;
    int tempCols=g->cols;
    
    for(int i=0;i<tempRows;i++){
        
        for(int j=0;j<tempCols;j++){
            if(cursorCoords[0]==i && cursorCoords[1]==j){
             if(g->board[i][j].isVisible==TRUE && g->board[i][j].numOfMines>0){
                    if(g->board[i][j].isMine==FALSE){
                        colorPrint(FG_Def,TILE_CURSOR,ATT_Def,"%2d",g->board[i][j].numOfMines);
                }
            }
                else{
                    colorPrint(FG_Def,TILE_CURSOR,ATT_Def,TILE_STRING);
            }
            }
           
            else if(g->board[i][j].isFlagged==TRUE){//color if flagged
                colorPrint(FG_Def,TILE_FLAGGED,ATT_Def,TILE_STRING);
            }
            else if(g->board[i][j].isVisible==TRUE){
                if(g->board[i][j].numOfMines==0){//color visible tile if it is not a mine
                    colorPrint(FG_Def,TILE_VISIBLE,ATT_Def,TILE_STRING);
                }
                //color all eight possible numbers of mines
                else if(g->board[i][j].numOfMines<4){
                    colorPrint(FG_Black,TILE_VISIBLE,ATT_Def,"%2d",g->board[i][j].numOfMines);
                }
                
                else if(g->board[i][j].numOfMines>=4){
                    colorPrint(FG_Red,TILE_VISIBLE,ATT_Def,"%2d",g->board[i][j].numOfMines);
                }
                
            }
        	else
			{
				colorPrint(FG_Def,TILE_HIDDEN ,ATT_Def,TILE_STRING);// coloring the hidden tiles
			}
		}
		printf("\n");
	}
}
        
    


