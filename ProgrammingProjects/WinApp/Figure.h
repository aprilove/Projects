#include <string>
class Figure
{
    private:
        float Area;
        float Length;
        float Angle;
    public:
        Figure();
        Figure(float myArea, float myLength, float myAngle);
        void setArea(float myArea);
        void setLength(float myLength);
        void setAngle(float myAngle);
        std::string getArea();
        std::string getLength();
        std::string getAngle();
};