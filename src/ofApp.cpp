/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"

vector<double> display_buffer;

bool saving = false;
int mode = 1;

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    samp.load(ofToDataPath("os_loop_1.wav"));
    
    ofBackground(230);
    ofSetColor(40);
    
    ofSetCircleResolution(100);
    ofSetVerticalSync(true);
    
    ofSetFrameRate(60);
    
    // audio setup
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    display_buffer.resize(bufferSize);
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    fft.setup(1024, 512, 256);
    oct.setup(44100, 1024, 7);
    
    ofSetSphereResolution(3);
    
    // GUI
    gui.setup(params);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (mode == 1) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        
        
        float scale = 100.0;
        
        for ( int i = 0 ; i < bufferSize ; i++) {
            
            ofPolyline line;
            
            float val = display_buffer[i];
            float rad = 0.0;
            float theta = 0.0;
            while(theta <= 360.0) {
                
                float r = ofDegToRad(theta);
                
                rad = sf(r, oct.averages[0] * val * 10, oct.averages[1],oct.averages[2] * val,oct.averages[3],oct.averages[4], oct.averages[5] * val, oct.averages[6] * val);
                
                
                line.curveTo(sin(r) * rad * scale, cos(r) * rad * scale);
                
                theta+=3.0;
            }
            

            
            line.close();
            line.draw();
        }
        
        ofPopMatrix();
    }
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        double mix = samp.play(speed);
        
        if (fft.process(mix)) {
            oct.calculate(fft.magnitudes);
        }

        output[i*nChannels    ] = mix;
        output[i*nChannels + 1] = mix;
        
        display_buffer[i] = mix;

    }
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    speed = ofMap(x, 0, ofGetWidth(), -2, 2);
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

float ofApp::sf(float angle, float a, float b, float m1, float m2, float n1, float n2, float n3) {
    return pow(pow(abs((cos( (m1 * angle) / 4.0 ))/a),n2) + pow(abs((sin( (m2 * angle)/4.0 ))/b),n2), -1.0/n1);
}

