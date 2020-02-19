#pragma once

#include "ofMain.h"
#include "wiggle.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	//Custom
	void setupWiggles(int index);
	void resetWiggles();

	//ofxGui
	void initGUI();
	void setupApp();
	void onSliderEvent(ofxDatGuiSliderEvent e);	
	void onToggleEvent(ofxDatGuiToggleEvent e);

	
	//Variables
	vector<wiggle> wiggleGroup;

	int lineSegmentLength;
	int amountOfNewLines;
	int lineSegments;
	int offset, currentOffset;
	int randomStart;
	int degreesOfRotation;


	bool newLines = false;
	bool canClear = false;
	bool autoMode = false;
	bool fillState = false;
	bool spacePressed = false;
	bool canDrawNewAuto = false;

	ofImage screenCapture;


	//time
	float startTime;
	float endTime;
	bool timerEnd;


	//ofxDatGui
	ofxDatGui* gui;
	ofxDatGuiSlider* sl_iterations;
	ofxDatGuiSlider* sl_numOfLines;
	ofxDatGuiSlider* sl_degrees;	

	ofxDatGuiToggle* tog_Automode;
	ofxDatGuiToggle* tog_FillState;
	ofxDatGuiSlider* sl_autoDelay;


	
};
