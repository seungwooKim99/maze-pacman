#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    printf("%d\n", ofGetWidth());
    printf("%d\n", ofGetHeight());
    playerX = ofGetWidth()/2;
    playerY = ofGetHeight()/2;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0,100,1024,2);
    ofSetLineWidth(5);
    //ofGetWidth();
    ofSetColor(33,127,31);
    ofDrawCircle(playerX, playerY, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP){
        playerY -= 10;
    }
    if(key == OF_KEY_RIGHT){
        playerX += 10;
    }
    if(key == OF_KEY_DOWN){
        playerY += 10;
    }
    if(key == OF_KEY_LEFT){
        playerX -= 10;
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
