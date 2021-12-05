#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //set Background Color Black
    ofSetBackgroundColor(0,0,0);

    cellSize = 60;
    mWidth = mHeight = 10;
    lineWidth = 2;
    boxStartX = ofGetWidth()/2 - (cellSize * 10 + lineWidth * 11)/2;
    boxStartY = ofGetHeight()/2 - (cellSize * 10 + lineWidth * 11)/2;
    
    playerX = boxStartX + lineWidth;
    playerY = boxStartY + lineWidth;
    
    //set the coordinate of the corner cells
    topLx = playerX;
    topLy = playerY;
    
    topRx = topLx + cellSize*9 + lineWidth*9;
    topRy = topLy;
    
    downLx = topLx;
    downLy = topLy + cellSize*9 + lineWidth*9;
    
    downRx = topLx + cellSize*9 + lineWidth*9;
    downRy = topLy + cellSize*9 + lineWidth*9;
    
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

    //Draw player
    ofSetColor(247,233,3);
    //ofDrawRectangle(playerX, playerY, 60, 60);
    ofDrawCircle(playerX+30, playerY+30, 29);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP){
        if(playerY > topLy)
            playerY -= 62;
    }
    if(key == OF_KEY_RIGHT){
        if(playerX < topRx)
            playerX += 62;
    }
    if(key == OF_KEY_DOWN){
        if(playerY < downLy)
            playerY += 62;
    }
    if(key == OF_KEY_LEFT){
        if(playerX > downLx)
            playerX -= 62;
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
