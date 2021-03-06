#include "ofApp.h"
#include <time.h>

//--------------------------------------------------------------
void ofApp::setup(){
    int N = 10, M = 10;
    int i, j,idx=0;
    //set Background Color Black
    ofSetBackgroundColor(0,0,0);

    cellSize = 60;
    mWidth = mHeight = 10;
    lineWidth = 2;
    boxStartX = ofGetWidth()/2 - (cellSize * 10 + lineWidth * 11)/2;
    boxStartY = ofGetHeight()/2 - (cellSize * 10 + lineWidth * 11)/2;
    
    playerX = boxStartX + lineWidth;
    playerY = boxStartY + lineWidth;
    playerMazeX = 0;
    playerMazeY = 0;
    
    //set the coordinate of the corner cells
    topLx = playerX;
    topLy = playerY;
    
    topRx = topLx + cellSize*9 + lineWidth*9;
    topRy = topLy;
    
    downLx = topLx;
    downLy = topLy + cellSize*9 + lineWidth*9;
    
    downRx = topLx + cellSize*9 + lineWidth*9;
    downRy = topLy + cellSize*9 + lineWidth*9;
    
    //memory allocate maze
    maze = (CELL**)malloc(sizeof(CELL*)*N);
    for(i=0;i<N;i++){
        maze[i] = (CELL*)malloc(sizeof(CELL)*M);
    }

    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            maze[i][j].horizontal = maze[i][j].vertical = 1;
            maze[i][j].set = ++idx;
        }
    }
    
    //init maze
    createMaze(maze, N, M);
    //printMaze(maze, N, M);
    drawMaze(maze, 10, 10);
    
    //init visited
    visited = (int **)malloc(sizeof(int*)*N);
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            visited[i] = (int*)malloc(sizeof(int*)*M);
        }
    }
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            visited[i][j] = 0;
        }
    }
    visited[0][0] = 1;
    visited[N-1][M-1] = 1;
    
    //init coin number
    totalCoin = 0;
    
    //init obstacle
    obstacleX = ofGetWidth()/2;
    obstacleY = ofGetHeight()/2;
    
    reverseFlagX = 0;
    reverseFlagY = 0;
    
    gameover = 0;
    gameclear = 0;
    
    srand(time(NULL));

}

//--------------------------------------------------------------
void ofApp::update(){
    //check game over
    if(obstacleX-15 <= playerX && playerX <= obstacleX+15 && obstacleY-15 <= playerY && playerY <= obstacleY+15){
        gameover = 1;
        printf("GAME OVER!!\n");
    }
    //check game clear
    if(playerMazeX == 9 && playerMazeY == 9 && totalCoin == 98){
        gameclear = 1;
        printf("GAME CLEAR!!\n");
    }
    
    if(!gameover && !gameclear){
        //set reverseFlag if the condition is true
        if(obstacleX == topRx)
            reverseFlagX = 1;
        if(obstacleX == topLx)
            reverseFlagX = 0;
        if(obstacleY == downLy)
            reverseFlagY = 1;
        if(obstacleY == topLy)
            reverseFlagY = 0;
        
        //change X coordinate if changeX is 1
        int changeX = rand()%2;
        int randomNumber = rand()%10;
        if(changeX){
            if(topLx <= obstacleX && obstacleX <= topRx){
                if(!reverseFlagX){
                    if(obstacleX + randomNumber >= topRx)
                        obstacleX = topRx;
                    else
                        obstacleX += randomNumber;
                }
                else{
                    if(obstacleX - randomNumber <= topLx)
                        obstacleX = topLx;
                    else
                        obstacleX -= randomNumber;
                }
            }
        }
        else{
            if(topLy <= obstacleY && obstacleY <= downLy){
                if(!reverseFlagY){
                    if(obstacleY + randomNumber >= downLy)
                        obstacleY = downLy;
                    else
                        obstacleY += randomNumber;
                }
                else{
                    if(obstacleY - randomNumber <= topLy)
                        obstacleY = topLy;
                    else
                        obstacleY -= randomNumber;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //set the title
    string title = "MAZE PACMAN";
    ofSetColor(255,255,255);
    ofDrawBitmapString(title, ofGetWidth()/2 - 40, 50);
    
    string madeBy = "  made by Seungwoo Kim\nSogang Univ CSE 20181610";
    ofDrawBitmapString(madeBy, ofGetWidth()/2 - 90, ofGetHeight() - 50);
    
    //Draw Out line of the Box
    ofSetColor(14,37,179);
    ofSetLineWidth(lineWidth);
    int lineLegth = cellSize*10 + lineWidth*11;
    ofDrawLine(boxStartX, boxStartY, boxStartX + lineLegth, boxStartY);
    ofDrawLine(boxStartX, boxStartY, boxStartX, boxStartY + lineLegth);
    ofDrawLine(boxStartX + lineLegth, boxStartY, boxStartX + lineLegth, boxStartY + lineLegth);
    ofDrawLine(boxStartX, boxStartY + lineLegth, boxStartX + lineLegth, boxStartY + lineLegth);

    //Draw Coin
    drawCoin(maze, 10, 10);
    
    //Draw player
    ofSetColor(247,233,3);
    //ofDrawRectangle(playerX, playerY, 60, 60);
    ofDrawCircle(playerX+30, playerY+30, 20);
    ofSetColor(0, 0, 0);
    ofDrawLine(playerX+30-8, playerY+30-3, playerX+30-8, playerY+30-13);
    ofDrawLine(playerX+30+8, playerY+30-3, playerX+30+8, playerY+30-13);
    ofSetColor(247,233,3);

    
    //Draw Maze
    drawMaze(maze, 10, 10);
    
    //Draw obstacle
    ofSetColor(255, 49, 0);
    ofDrawCircle(obstacleX+30, obstacleY+30, 20);
    ofSetColor(0, 0, 0);
    ofDrawLine(obstacleX+30-4, obstacleY+30-3, obstacleX+30-8, obstacleY+30-13);
    ofDrawLine(obstacleX+30+4, obstacleY+30-3, obstacleX+30+8, obstacleY+30-13);
    
    //Draw Game Over
    if(gameover){
        int centerY = ofGetHeight()/2;
        int centerX = ofGetWidth()/2;
        ofSetColor(255, 255, 255);
        ofDrawRectangle(centerX-80, centerY-30, 160, 60);
        ofSetColor(0, 0, 0);
        ofDrawRectangle(centerX-79, centerY-29, 158, 58);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("   GAME OVER\nPress q to quit", centerX - 60, centerY);
    }
    if(gameclear){
        int centerY = ofGetHeight()/2;
        int centerX = ofGetWidth()/2;
        ofSetColor(255, 255, 255);
        ofDrawRectangle(centerX-80, centerY-30, 160, 60);
        ofSetColor(0, 0, 0);
        ofDrawRectangle(centerX-79, centerY-29, 158, 58);
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("  GAME CLEAR!\nPress q to quit", centerX - 60, centerY);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(!gameover){
        if(key == OF_KEY_UP){
            if(playerMazeX != 0){
                if(playerY > topLy && maze[playerMazeX-1][playerMazeY].horizontal == 0){
                    playerY -= 62;
                    playerMazeX--;
                    if (!visited[playerMazeX][playerMazeY]){
                        visited[playerMazeX][playerMazeY] = 1;
                        totalCoin++;
                    }
                }
            }
        }
        if(key == OF_KEY_RIGHT){
            if(playerX < topRx && maze[playerMazeX][playerMazeY].vertical == 0){
                playerX += 62;
                playerMazeY++;
                if (!visited[playerMazeX][playerMazeY]){
                    visited[playerMazeX][playerMazeY] = 1;
                    totalCoin++;
                }
                if(playerMazeX == 9 && playerMazeY == 9 && totalCoin == 98){
                    printf("Clear!\n");
                }
            }
        }
        if(key == OF_KEY_DOWN){
            if(playerY < downLy && maze[playerMazeX][playerMazeY].horizontal == 0){
                playerY += 62;
                playerMazeX++;
                if (!visited[playerMazeX][playerMazeY]){
                    visited[playerMazeX][playerMazeY] = 1;
                    totalCoin++;
                }
                if(playerMazeX == 9 && playerMazeY == 9 && totalCoin == 98){
                    printf("Clear!\n");
                }
            }
        }
        if(key == OF_KEY_LEFT){
            if(playerMazeY != 0){
                if(playerX > downLx && maze[playerMazeX][playerMazeY-1].vertical == 0){
                    playerX -= 62;
                    playerMazeY--;
                    if (!visited[playerMazeX][playerMazeY]){
                        visited[playerMazeX][playerMazeY] = 1;
                        totalCoin++;
                    }
                }
            }
        }
    }
    if(gameover || gameclear){
        if(key == 'q'){
            printf("Press q to quit");
            //free memory
            
            _Exit(0);
            
        }
    }
    if(key == 'd'){
        drawMazeFlag = 1;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

// user defined!
void ofApp::createMaze(CELL **maze, int N, int M){
    int i,j,k,l;
    int del = 0;
    int setNumber = 1;
    int verticalPathExists = 0;
    int temp;
    for(i=0;i<N;i++){
        //Step1 : set the cell number same with the upper one if the upper horizontal wall absents
        for(j=0;j<M;j++){
            if(i != 0){
                if(!maze[i-1][j].horizontal){
                    maze[i][j].set = maze[i-1][j].set;
                }
            }
        }

        //Step2 : Remove vertical wall
        for(j=0;j<M;j++){
            del = rand()%2;
            if(i == N-1 && j == M-1){
                break;
            }
            else if(i == N-1){
                setNumber = maze[i][j].set;
                if(maze[i][j+1].set != setNumber){
                    temp = maze[i][j+1].set;
                    maze[i][j+1].set = setNumber;
                    maze[i][j].vertical = 0;
                    for(k=0;k<N;k++){
                        for(l=0;l<M;l++){
                            if(maze[k][l].set == temp)
                                maze[k][l].set = setNumber;
                        }
                    }
                }
            }
            else if(j == M-1){
                //
                continue;
            }
            else{
                setNumber = maze[i][j].set;
                if(del && (maze[i][j+1].set != setNumber)){
                    temp = maze[i][j+1].set;
                    maze[i][j+1].set = setNumber;
                    maze[i][j].vertical = 0;
                    for(k=0;k<N;k++){
                        for(l=0;l<M;l++){
                            if(maze[k][l].set == temp)
                                maze[k][l].set = setNumber;
                        }
                    }
                }
            }
        }

        //Step3 : Remove horizontal wall
        verticalPathExists = 0;
        for(j=0;j<M;j++){
            del = rand()%2;
            if(j == M-1 && i == N-1){
                //
                break;
            }
            else if (i == N-1){
                //
                continue;
            }
            else {
                if(del){
                    temp = maze[i+1][j].set;
                    maze[i][j].horizontal = 0;
                    maze[i+1][j].set = maze[i][j].set;
                    for(k=0;k<N;k++){
                        for(l=0;l<M;l++){
                            if(maze[k][l].set == temp)
                                maze[k][l].set = setNumber;
                        }
                    }
                    verticalPathExists = 1;
                }
                else if (maze[i][j].vertical == 1){
                    if(!verticalPathExists){
                        temp = maze[i+1][j].set;
                        maze[i][j].horizontal = 0;
                        maze[i+1][j].set = maze[i][j].set;
                        for(k=0;k<N;k++){
                            for(l=0;l<M;l++){
                                if(maze[k][l].set == temp)
                                    maze[k][l].set = setNumber;
                            }
                        }
                    }
                }
                if (maze[i][j].vertical == 1){
                    verticalPathExists = 0;
                }
            }
        }
    }
    return;
}
void ofApp::printMaze(CELL **maze, int N, int M){
    int i,j;
    //print
    //?????? ?????????
    for(j=0;j<M;j++){
        printf("+-");
    }
    printf("+\n|");

    for(i=0;i<N-1;i++){
        for(j=0;j<M;j++){
            if(maze[i][j].vertical){
                printf(" |");
            }
            else{
                printf("  ");
            }
        }
        printf("\n+");

        for(j=0;j<M;j++){
            if(maze[i][j].horizontal){
                printf("-+");
            }
            else{
                printf(" +");
            }
        }
        printf("\n|");
    }

    for(j=0;j<M;j++){
        if(maze[i][j].vertical){
            printf(" |");
        }
        else{
            printf("  ");
        }
    }
    printf("\n+");
    for(j=0;j<M;j++){
        printf("-+");
    }
    return;
}

void ofApp::drawMaze(CELL **maze, int N, int M){
    int i,j;
    ofSetColor(14,37,179);
    ofSetLineWidth(lineWidth);
    int verX = boxStartX + cellSize + lineWidth;
    int verY = boxStartY + lineWidth;
    
    int horX = boxStartX + lineWidth;
    int horY = boxStartY + lineWidth + cellSize;
    //print
    for(i=0;i<N;i++){
        for(j=0;j<M-1;j++){
            if(maze[i][j].vertical){
                ofDrawLine(verX, verY, verX, verY + cellSize);
                //printf(" |");
            }
            verX += (cellSize + lineWidth);
        }
        //printf("\n+");
        //verX = boxStartX + lineWidth;

        for(j=0;j<M;j++){
            if(maze[i][j].horizontal){
                ofDrawLine(horX, horY, horX+cellSize+lineWidth, horY);
                //printf("-+");
            }
            else{
                ofDrawLine(horX+cellSize, horY, horX+cellSize+lineWidth, horY);
                //printf(" +");
            }
            horX += (cellSize + lineWidth);
        }
        verY += (cellSize + lineWidth);
        horY += (cellSize + lineWidth);
        verX = boxStartX + cellSize + lineWidth;
        horX = boxStartX + lineWidth;
        //printf("\n|");
    }

    //for(j=0;j<M;j++){
    //    if(maze[i][j].vertical){
    //        printf(" |");
    //    }
     //   else{
    //        printf("  ");
    //    }
    //}
    //printf("\n+");
    //for(j=0;j<M;j++){
    //    printf("-+");
    //}
    return;
}

void ofApp::drawCoin(CELL **maze, int N, int M){
    ofSetColor(151, 124, 104);
    int i,j;
    int X = boxStartX + lineWidth;
    int Y = boxStartY + lineWidth;
    
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            if(visited[i][j] == 0){
                ofDrawCircle(X+30, Y+30, 3);
            }
            X += (lineWidth + cellSize);
        }
        X = boxStartX + lineWidth;
        Y += (lineWidth + cellSize);
    }
}
