#pragma once

#include "ofMain.h"
#include "maze.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //about maze method
        void createMaze(CELL **maze, int N, int M);
        void printMaze(CELL **maze, int N, int M);
        void drawMaze(CELL **maze, int N, int M);
        void drawCoin(CELL **maze, int N, int M);
		
    //user defined variables
    int playerX, playerY;
    int playerMazeX, playerMazeY;
    int mWidth, mHeight;
    int cellSize;
    int boxStartX, boxStartY;
    int lineWidth;
    int topLx, topRx, downLx, downRx;
    int topLy, topRy, downLy, downRy;
    int drawMazeFlag = 0;
    
    int **visited;
    
    CELL **maze;
};
