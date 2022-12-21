#include <iostream>
using namespace std;

#define Lock_Code "";

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
protected:
    bool isLocked = false;

public:
    Plane() : fuelLevel(0), distance(0), planeName("not_plane") {}

    Plane(const int fuelLevel, const int distance, const string &planeName);

    Plane(const Plane &plane) : fuelLevel(new int(*plane.fuelLevel)),
                                distance(distance),
                                planeName(planeName)
    {
    }

    Plane &operator=(const Plane &object)
    {
        int *originalCopy = fuelLevel;
        fuelLevel = new int(*object.fuelLevel);
        delete originalCopy;

        if (this == &object)
            return *this;

        fuelLevel = object.fuelLevel;
        distance = object.distance;
        planeName = object.planeName;

        return *this;
    }

    string planeInfo()
    {
        if (isLocked)
        {
            return "Lock_Code";
        }
        else
        {
            cout << "The plane " << planeName << " traveled " << distance << " km and has " << *fuelLevel << " litres of kerosen left.\n";
        }
    }

    ~Plane()
    {
        cout << "The Plane does not exist in the memory.\n";
    }

    void lock()
    {
        this->isLocked = true;
    }

    void unLock()
    {
        this->isLocked = false;
    }
    // pt custom copy asignment
    //  Plane& operator=(const Plane& Plane){
    //    this->fuelLevel=Plane.fuelLevel;
    //    this->distance=Plane.distance;
    //    this->planeName=Plane.planeName;
    //    return *this;
    //  }

private:
    int *fuelLevel, distance;
    string planeName;
};

Plane::Plane(const int fuelLevel, const int distance, const string &planeName) : fuelLevel(new int(fuelLevel)), distance(distance), planeName(planeName)
{
}

class Boeing : public Plane
{
public:
    Boeing() : Plane(), seats(0) {}

    Boeing(const int fuelLevel, const int distance, const string &planeName, const int seats) :

                                                                                                Plane(fuelLevel, distance, planeName),
                                                                                                seats(seats)
    {
    }

    Boeing(const Boeing &plane) :

                                  Plane(plane),
                                  seats(plane.seats)
    {
    }

    Boeing &operator=(const Boeing &object)
    {
        if (this == &object)
        {
            cout << "The Plane does not exist in the memory.\n";
            return *this;
        }

        Plane::operator=(object);
        seats = object.seats;
        return *this;
    }

    int getNumberOfSeats()
    {
        return this->seats;
    }

private:
    int seats;
};

class LockPlane
{
private:
    Plane &lockedPlane;

public:
    explicit LockPlane(Plane &value) : lockedPlane(value)
    {
        lock();
    }

    ~LockPlane()
    {
        unlock();
    }
};

Plane *createPlaneInstance(int fuelLevel, int distance, string planeName)
{
    return (new Plane(fuelLevel, distance, planeName));
}

void doSomething()
{
    Plane *p = createPlaneInstance(123, 451, "Boeing X");
    return;
    delete p;
    unique_ptr<Plane> newPlane(createPlaneInstance(123, 455, "Boeing Y"));
    newPlane->planeInfo();

    unique_ptr<Plane> newPlane2 = move(newPlane);

    shared_ptr<Plane> p2(createPlaneInstance(1255, 4212, "Boeing Z"));
    shared_ptr<Plane> p3(p2);
    p2->planeInfo();
    p3->planeInfo();
    p2.use_count();

    shared_ptr<Plane> p4 = move(p2);
    p4->planeInfo();
}

int main()
{
    Plane Plane1(99, 1001, "Boeing 747");
    Plane1.planeInfo();
    // Plane Plane2(Plane1);
    // Plane2.planeInfo();
    // Plane Plane3(22, 100, "Boeing 757");
    // Plane Plane4;
    // Plane4 = Plane3;
    Boeing boeing(55, 129, "Boeing 737", 180);
    boeing.planeInfo();
    cout << "Latest boeing has " << boeing.getNumberOfSeats() << " number of seats.\n";

    doSomething();

    Plane Plane5(555, 421, "Boeing A");
    LockPlane *lockedPlane = new LockPlane(Plane5);

    Plane5.planeInfo();

    delete lockedPlane;
    Plane5.planeInfo();

    return 0;
}
