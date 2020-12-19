#include "Figure.h"

Figure::Figure(float myArea, float myLength, float myAngle){Area = myArea; Length = myLength; Angle = myAngle;};
void Figure::setArea(float myArea){Area = myArea;};
void Figure::setLength(float myLength){Length = myLength;};
void Figure::setAngle(float myAngle){Angle = myAngle;};
std::string Figure::getArea(){return std::to_string(Area);};
std::string Figure::getLength(){return std::to_string(Length);};
std::string Figure::getAngle(){return std::to_string(Angle);};