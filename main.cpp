#include <iostream>
using namespace std;

const double PI = 3.14159;
const double EPSILON_0 = 8.854e-12;
const double MU_0 = 4 * PI * 1e-7;

// field class
class Field {
private:
    double x;
    double y;
    double z;

public:
    Field () {
        
        x  = 0;
        y = 0;
        z = 0;
    }

    Field ( double X_val, double Y_val, double Z_val ) {
        x = X_val;
        y = Y_val;
        z = Z_val;
    }

    Field( const Field& f ) 
    {
        x = f.x;
        
        y = f.y;
        z = f.z;
    }

    void setX(double val) { 
        x = val; 
    }
    void setY(double val) {
     y = val; 
  }
    void setZ(double val) { 
        z = val; 
     }

    double getX() { 
        return x; 
    }
    double getY() { 
        return y; 
    }
    double getZ() { 
        return z; 
    }

    void printMagnitude() {
        cout << "Vector: ("; 
        cout << x << ", " ;
        cout << y << ", "; 
        cout << z << ")" << endl;
    }

protected:
    void setValues(double a, double b, double c) 
    {
        x = a;
        y = b;
        z = c;
    }
};

// Electric field class
class ElectricField : public Field {
private:
    double e;

public:
    ElectricField( ) : Field()  {
        e = 0;
    }

    ElectricField ( double X_val, double  Y_val, double Z_val ) : Field(X_val, Y_val, Z_val) 
    {
        e = 0;
    }

    ElectricField(const ElectricField& ef) : Field(ef) {
        e = ef.e;
    }

    void calculateElectric(double Q, double r) {
        e = Q / ( 4  * PI * EPSILON_0 *  r  *  r );
    }

    ElectricField operator+(ElectricField ef) {
        ElectricField result;
       double newX = getX() + ef.getX();
       double newY = getY() + ef.getY();
       double newZ = getZ() + ef.getZ();
          result.setValues(newX, newY, newZ);

        return result;
    }

    friend ostream& operator<<(ostream& out, ElectricField ef) {
    out << "E-Field: (" ;
    out << ef.getX() << ", "; 
    out << ef.getY() << ", " ;
    out << ef.getZ() << ")";
    out << " | Magnitude: " << ef.e;
    return out;
}

};

// Magnetic field class
class MagneticField : public Field {
private:
    double b ;

public:
    MagneticField() : Field() {
        b =  0;
    }

    MagneticField (double X_val, double Y_val, double Z_val ) : Field(X_val, Y_val, Z_val) {
        b = 0;
    }

    MagneticField(const MagneticField& mf) : Field(mf) {
        b = mf.b;
    }

    void calculateMagnetic(double I, double r) {
        b = ( MU_0 *  I ) / ( 2 * PI * r );
    }

    MagneticField operator+(MagneticField mf) {
         
        double newX = getX () + mf.getX ( );
         double newY = getY() + mf.getY ();
        double newZ = getZ() + mf.getZ () ;

        MagneticField result(newX, newY, newZ);
 

        return result;
    }

    friend ostream& operator<<(ostream& out, MagneticField mf) {
        out << "Magnetic Field = (" ;
        out << mf.getX() << ", ";
         out   << mf.getY() << ", ";
            out << mf.getZ();
           out << "), Magnitude B = " << mf.b;
        return out;
    }
};


int main() {
    ElectricField ef1(0, 100000, 1000);
    ef1.calculateElectric(1e-6, 0.05);  

    MagneticField mf1(2, 4, 6);
    mf1.calculateMagnetic(10, 0.05);  

    ef1.printMagnitude();
    mf1.printMagnitude();

    ElectricField ef2(1, 2, 3);
    MagneticField mf2(1, 1, 1);

    ElectricField ef3 = ef1 + ef2;
    ef3.calculateElectric(1e-6, 0.05); 

    MagneticField mf3 = mf1 + mf2;
    mf3.calculateMagnetic(10, 0.05);    

    cout << ef3 << endl;
    cout << mf3 << endl;

    return 0;
}
