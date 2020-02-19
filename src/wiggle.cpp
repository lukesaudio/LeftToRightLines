#include "wiggle.h"

wiggle::wiggle()
{

	int r = ofRandom(0, 255);
	int g = ofRandom(0, 255);
	int b = ofRandom(0, 255);

	wiggleColor = ofColor(r, g, b);
	
	wigglePath.setColor(wiggleColor);
}