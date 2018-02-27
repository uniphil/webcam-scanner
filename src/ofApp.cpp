#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofBackground(0,0,0);
	
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
	
	vidGrabber.setVerbose(true);
	vidGrabber.setup(camWidth,camHeight);
	
    ofEnableAlphaBlending();
    
    videoRow.assign(512, 0.0);
    soundStream.printDeviceList();
    
    //if you want to set the device id to be different than the default
    //soundStream.setDeviceID(1);     //note some devices are input only and some are output only
    
    soundStream.setup(this, 2, 0, 44100, 512, 4);
    
    frameWidth = 512;
    lineSkipFactor = 2;
    lastRemainder = 0;
}


//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ofSetColor(0, 255, 0);
    // draw the raw video frame with the alpha value generated above
    vidGrabber.draw(0,0);

	ofPixelsRef pixelsRef = vidGrabber.getPixels();
    
    ofSetColor(255, 0, 255);
    ofDrawLine(320 - frameWidth / 2, line, 320 + frameWidth / 2, line);

    for (int i = 0; i < 512; i += 1) {
        float lightness = pixelsRef.getColor(i, line).getLightness();
        videoRow[i] = lightness;
    }
    
    line += lineSkipFactor;
    line %= 480;
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    int i;
    for (i = 0; i < bufferSize; i++){
        int x = (lastRemainder + i) % frameWidth;
        int audioI = 320 - frameWidth / 2 + x;
        output[i*nChannels] = videoRow[audioI];
        output[i*nChannels+1] = videoRow[audioI];
    }
    lastRemainder = (lastRemainder + i) & frameWidth;
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    frameWidth = abs(320 - x) + 1;
    lineSkipFactor = y / 4;
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
