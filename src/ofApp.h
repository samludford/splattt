#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    
    // Audio output and input methods
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
    
    float sf(float angle, float a, float b, float m1, float m2, float n1, float n2, float n3);
     
     
    
    int		bufferSize; /* buffer size */
    int		sampleRate;
    
    ofxPanel gui;
    
    ofParameterGroup params;
    
    ofParameter<double> s1_speed;
    ofParameter<double> s2_speed;
    ofParameter<double> s3_speed;
    ofParameter<double> s4_speed;
    ofParameter<double> s5_speed;
    ofParameter<double> s6_speed;
    ofParameter<double> s7_speed;
    ofParameter<double> s8_speed;
    ofParameter<double> s9_speed;
    ofParameter<double> s10_speed;
    
    
    
    maxiSample samp;
    
    maxiSample s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
    
    ofxMaxiFFT fft;
    ofxMaxiFFTOctaveAnalyzer oct;
    

};
