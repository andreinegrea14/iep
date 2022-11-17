#include <iostream>
using namespace std;
// bbase
class Uncopyable
{
protected:
    Uncopyable() {}
    ~Uncopyable() {}

private:
    Uncopyable(const Uncopyable &);
    Uncopyable &operator=(const Uncopyable &);
};

// add this
//: private Uncopyable
class Plane
{
public:
    Plane() {}

    Plane(const int fuelLevel, const int distance, const string &planeName) : fuelLevel(fuelLevel),
                                                                              distance(distance),
                                                                              planeName(planeName)
    {
    }

    void planeInfo()
    {
        cout << "The plane " << planeName << "traveled " << distance << "km and has " << fuelLevel << " litres of kerosen left.\n";
    }

    ~Plane()
    {
        cout << "The Plane does not exist in the memory.\n";
    }

    // pt custom copy asignment
    //  Plane& operator=(const Plane& Plane){
    //    this->fuelLevel=Plane.fuelLevel;
    //    this->distance=Plane.distance;
    //    this->planeName=Plane.planeName;
    //    return *this;
    //  }

private:
    int fuelLevel, distance;
    string planeName;
};

int main()
{
    Plane Plane1(99, 1001, "Boeing 747");
    Plane1.planeInfo();
    Plane Plane2(Plane1);
    Plane2.planeInfo();
    Plane Plane3(22, 100, "Boeing 757");
    Plane Plane4;
    Plane4 = Plane3;
    return 0;
}
