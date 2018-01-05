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
     
     
    
        int		bufferSize;
        int		sampleRate;
    
        ofxPanel gui;
    
        ofParameterGroup params;

        maxiSample samp;
    
        float speed {1.0};
    
        maxiSample s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
    
        ofxMaxiFFT fft;
        ofxMaxiFFTOctaveAnalyzer oct;
    

};
