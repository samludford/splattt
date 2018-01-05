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
    
    
//    samp.load(ofToDataPath("chen_loop_4.wav"));
    s1.load(ofToDataPath("s_1.wav"));
    s2.load(ofToDataPath("s_2.wav"));
    s3.load(ofToDataPath("s_3.wav"));
    s4.load(ofToDataPath("s_4.wav"));
    s5.load(ofToDataPath("s_5.wav"));
    s6.load(ofToDataPath("s_6.wav"));
    s7.load(ofToDataPath("s_7.wav"));
    s8.load(ofToDataPath("s_8.wav"));
    s9.load(ofToDataPath("s_9.wav"));
    s10.load(ofToDataPath("dub_2.wav"));
    
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
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
    fft.setup(1024, 512, 256);
    oct.setup(44100, 1024, 7);
    
    ofSetSphereResolution(3);
    
    // GUI
    
    params.add(s1_speed.set("s1 speed", 1.0, 0.01, 2));
    params.add(s2_speed.set("s2 speed", 1.0, 0.01, 2));
    params.add(s3_speed.set("s3 speed", 1.0, 0.01, 2));
    params.add(s4_speed.set("s4 speed", 1.0, 0.01, 2));
    params.add(s5_speed.set("s5 speed", 1.0, 0.01, 2));
    params.add(s6_speed.set("s6 speed", 1.0, 0.01, 2));
    params.add(s7_speed.set("s7 speed", 1.0, 0.01, 2));
    params.add(s8_speed.set("s8 speed", 1.0, 0.01, 2));
    params.add(s9_speed.set("s9 speed", 1.0, 0.01, 2));
    params.add(s10_speed.set("s10 speed", 0.7, 0.01, 2));
    
    gui.setup(params);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    if(saving) {
        ofBeginSaveScreenAsPDF(ofToString(ofGetFrameNum()) + ".pdf");
    }
    
    if (mode == 1) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//        ofRotate(ofGetFrameNum());
        
        
        float scale = 100.0;
        
        for ( int i = 0 ; i < bufferSize ; i++) {
            
            ofPolyline line;
            
            float val = display_buffer[i];
            float rad = 0.0;
            float theta = 0.0;
//            line.curveTo(sin(0.0) * rad * scale, cos(0.0) * rad * scale);
            while(theta <= 360.0) {
                
                float r = ofDegToRad(theta);
                
//                rad = sf(theta, oct.averages[0] * val * 10, oct.averages[1],oct.averages[2] * val,oct.averages[3],oct.averages[4], oct.averages[5] * val, oct.averages[6] * val);
                
                rad = sf(r, oct.averages[0] * val * 10, oct.averages[1],oct.averages[2] * val,oct.averages[3],oct.averages[4], oct.averages[5] * val, oct.averages[6] * val);
                
                
                line.curveTo(sin(r) * rad * scale, cos(r) * rad * scale);
                
                theta+=3.0;
            }
            

            
            line.close();
            line.draw();
        }
        
//        line.curveTo(0.0, 0.0);
//
//        line.close();
        
        ofPopMatrix();
    }


    if(saving) {
        ofEndSaveScreenAsPDF();
        saving = false;
    }
    
//    gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
//        double speed =  ofMap(mouseX, 0, ofGetWidth(), 0.1, 1);
//        double mix = samp.play(speed );
//        double m1 = s1.play(s1_speed);
//        double m2 = s2.play(s2_speed);
//        double m3 = s3.play(s3_speed);
//        double m4 = s4.play(s4_speed);
//        double m5 = s5.play(s5_speed);
//        double m6 = s6.play(s6_speed);
//        double m7 = s7.play(s7_speed);
//        double m8 = s8.play(s8_speed);
//        double m9 = s9.play(s9_speed);
        double m10 = s10.play(s10_speed);
        
//        double mix = (m1 + m2 + m3 + m4 + m5 + m6 + m7 + m8 + m9 + m10);
        
//        double mix = m9 * 1.4;
        
        double mix = m10;
        
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
    
    if(key == ' ') {
        saving = true;
    } else if(key == '1') {
        mode = 1;
    } else if(key == '2') {
        mode = 2;
//        ofBackground(30);
    } else if(key == '3') {
        mode = 3;
    } else if (key == '4') {
        mode = 4;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
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

