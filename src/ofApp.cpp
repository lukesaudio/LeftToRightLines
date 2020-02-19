#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	initGUI(); //GUI intialisation
	setupApp(); //Project and Wiggles Initialisation
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (autoMode)
	{
		float timer = ofGetElapsedTimeMillis() - startTime;

		if (timer >= endTime)
		{
			timerEnd = true;

			resetWiggles();

			for (int currentLine = 0; currentLine < amountOfNewLines; currentLine++)
			{

				for (int i = 0; i < lineSegments; i++)
				{
					ofVec2f v1(offset, 0);
					ofVec2f newPoint = v1.rotate(ofRandom(-degreesOfRotation + rotModifier, degreesOfRotation + rotModifier));

					wiggleGroup[currentLine].currPoint += newPoint;
					wiggleGroup[currentLine].wigglePath.lineTo(wiggleGroup[currentLine].currPoint);


				}

				randomStart = ofRandom(0, ofGetHeight());

				
				ofResetElapsedTimeCounter();
				timerEnd = false;
				


			}
		}
			

			

		

	}
	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofPushMatrix();

	ofTranslate(0, randomStart);

	ofPolyline poly;

	for (int i = 0; i < amountOfNewLines; i++)
	{
		wiggleGroup[i].wigglePath.draw();
		wiggleGroup[i].polylines[i].draw();

		

	}


	ofPopMatrix();


	
}

	

		
	
	

	


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

	if (key == ' ') 	
	{
		resetWiggles();

		for (int currentLine = 0; currentLine < amountOfNewLines; currentLine++)
		{
			wiggleGroup[currentLine].wigglePath.setFilled(fillState);


			for (int i = 0; i < lineSegments; i++)
			{
				ofVec2f v1(offset, 0);
				ofVec2f newPoint = v1.rotate(ofRandom(-degreesOfRotation + rotModifier, degreesOfRotation + rotModifier));




				wiggleGroup[currentLine].currPoint += newPoint;
				wiggleGroup[currentLine].wigglePath.lineTo(wiggleGroup[currentLine].currPoint);

				rotModifier *= 3;

			}

			randomStart = ofRandom(0, ofGetHeight());


		}
		
	}

	if (key == 'x') 
	{
		gui->setVisible(false);
		gui->setEnabled(false);
		gui->collapse();
		gui->setOpacity(0);


		screenCapture.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenCapture.save("LeftToRight.png");

		gui->setOpacity(1);
		gui->expand();
		gui->setEnabled(true);
		gui->setVisible(true);

	}

}


//---------------------------------------------------------------Initialising App
void ofApp::setupApp()
{
	startTime = ofGetElapsedTimeMillis();
	timerEnd = false;
	endTime = 1000.0f;

	randomStart = ofRandom(0, ofGetHeight());

	amountOfNewLines = 10;
	lineSegmentLength = 20;
	lineSegments = 120;
	degreesOfRotation = 90;

	wiggleGroup.resize(1000);

	for (int i = 0; i < amountOfNewLines; i++)
	{
		setupWiggles(i);

	}


	offset = lineSegmentLength; // offset line length
	currentOffset = 0;


	//Colours
	ofBackground(ofColor::black);
}

//---------------------------------------------------------------Initialise Wiggles
void ofApp::setupWiggles(int index)
{
	for (int i = 0; i < wiggleGroup.size(); i++)
	{
		wiggleGroup[i].currPoint.set(0, ofRandom(0, ofGetHeight()));
		wiggleGroup[i].wigglePath.setStrokeWidth(10);
		wiggleGroup[i].wigglePath.setFilled(true);
		wiggleGroup[i].wigglePath.lineTo(wiggleGroup[index].currPoint);
		wiggleGroup[i].polylines.resize(1000);
		
	}
	
	
}

void ofApp::resetWiggles()
{
	wiggleGroup.resize(0);
	wiggleGroup.resize(1000);
;
}

//---------------------------------------------------------------ofxDatGui

void ofApp::initGUI()
{
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	gui->setEnabled(true);
	gui->setVisible(true);
	gui->setWidth(ofGetWidth());

	sl_iterations = gui->addSlider("Iterations", 1, 1000);
	sl_iterations->setEnabled(true);
	sl_iterations->setVisible(true);
	sl_iterations->setWidth(20, 20);

	sl_numOfLines = gui->addSlider("Number of Lines", 1, 100);
	sl_numOfLines->setEnabled(true);
	sl_numOfLines->setVisible(true);
	sl_numOfLines->setWidth(20, 20);

	sl_degrees = gui->addSlider("Degrees of Rotation", 1, 179);
	sl_degrees->setEnabled(true);
	sl_degrees->setVisible(true);
	sl_degrees->setWidth(20, 20);

	sl_rotModifier = gui->addSlider("Rotation Modifier", -30, 30);
	sl_rotModifier->setEnabled(true);
	sl_rotModifier->setVisible(true);
	sl_rotModifier->setWidth(20, 20);
	
	tog_Automode = gui->addToggle("Auto", false);
	tog_Automode->setEnabled(true);
	tog_Automode->setVisible(true);
	tog_Automode->setWidth(20, 20);

	tog_FillState = gui->addToggle("Fill/No Fill", false);
	tog_FillState->setEnabled(true);
	tog_FillState->setVisible(true);
	tog_FillState->setWidth(20, 20);

	sl_autoDelay = gui->addSlider("Auto Delay", 100, 2000);
	sl_autoDelay->setEnabled(true);
	sl_autoDelay->setVisible(true);
	sl_autoDelay->setWidth(20, 20);

	sl_iterations->onSliderEvent(this, &ofApp::onSliderEvent);
	sl_numOfLines->onSliderEvent(this, &ofApp::onSliderEvent);
	sl_degrees->onSliderEvent(this, &ofApp::onSliderEvent);
	tog_FillState->onToggleEvent(this, &ofApp::onToggleEvent);
	tog_Automode->onToggleEvent(this, &ofApp::onToggleEvent);
	sl_autoDelay->onSliderEvent(this, &ofApp::onSliderEvent);
	sl_rotModifier->onSliderEvent(this, &ofApp::onSliderEvent);



}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
	if (e.target->is("Iterations"))
	{
		lineSegments = e.value;
	}

	if (e.target->is("Number of Lines"))
	{
		wiggleGroup.resize(e.value);
		amountOfNewLines = e.value;
	}

	if (e.target->is("Degrees of Rotation"))
	{
		degreesOfRotation = e.value;
	}

	if (e.target->is("Auto Delay"))
	{
		endTime = e.value;
		ofResetElapsedTimeCounter();
	}

	if (e.target->is("Rotation Modifier"))
	{
		 degreesOfRotation += e.value;
	}
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
	if (e.target->is("Auto"))
	{
		autoMode = e.checked;
	}

	if (e.target->is("Fill/No Fill"))
	{
		fillState = e.checked;
	}

	
}

