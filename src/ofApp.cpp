#include "ofApp.h"

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

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP){
        if(playerMazeX != 0){
            if(playerY > topLy && maze[playerMazeX-1][playerMazeY].horizontal == 0){
                playerY -= 62;
                playerMazeX--;
                visited[playerMazeX][playerMazeY] = 1;
            }
        }
    }
    if(key == OF_KEY_RIGHT){
        if(playerX < topRx && maze[playerMazeX][playerMazeY].vertical == 0){
            playerX += 62;
            playerMazeY++;
            visited[playerMazeX][playerMazeY] = 1;
            //printf("visited[2][2]: %d, (x,y)=(%d,%d)\n", visited[2][2],playerMazeX,playerMazeY);
        }
    }
    if(key == OF_KEY_DOWN){
        if(playerY < downLy && maze[playerMazeX][playerMazeY].horizontal == 0){
            playerY += 62;
            playerMazeX++;
            visited[playerMazeX][playerMazeY] = 1;
        }
    }
    if(key == OF_KEY_LEFT){
        if(playerMazeY != 0){
            if(playerX > downLx && maze[playerMazeX][playerMazeY-1].vertical == 0){
                playerX -= 62;
                playerMazeY--;
                visited[playerMazeX][playerMazeY] = 1;
            }
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
    //상단 테두리
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
