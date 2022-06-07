#include <iostream>

constexpr int pow(int value, int degree) {
    return degree == 0 ? 1 : value * pow(value, degree - 1);
}

template<bool isDef, int A, int B, int power, int coefficient, int ...data>
class Integral
{
public:


    static constexpr double definiteIntegral  = coefficient * ((double(pow(B, power + 1)) / (power + 1)) - (double(pow(A, power + 1)) / (power + 1)))
                                                + Integral<isDef, A, B, data...>::definiteIntegral;

    friend std::ostream& operator << (std::ostream& out, const Integral& P){
        if(isDef == 1) {
            if (coefficient == 0) {
                out << Integral<isDef, A, B, data...>();
            } else if (coefficient == 1) {
                out << "((" << pow(B, power + 1) << "/" << power + 1 << ") - (" << pow(A, power + 1) << "/" << power + 1
                    << ")) + "
                    << Integral<isDef, A, B, data...>();
            } else {
                out << coefficient << " * ((" << pow(B, power + 1) << "/" << power + 1 << ") - (" << pow(A, power + 1)
                    << "/" << power + 1 << ")) + "
                    << Integral<isDef, A, B, data...>();
            }
            return out;
        }
        else
        {
            if (coefficient == 0) {
                out << Integral<isDef, A, B, data...>();
            } else if (coefficient == 1) {
                out << "(x";

            } else {
                out << "(" << coefficient << "x";
            }
            out << "^" << power + 1 << ")/" << power + 1 << " + " << Integral<isDef, A, B, data...>();

            return out;
        }
    }
};

template<bool isDef, int A, int B, int power, int coefficient>
class Integral<isDef, A, B, power, coefficient>
{
public:

    static constexpr double definiteIntegral = coefficient * ((double(pow(B, power + 1)) / (power + 1)) - (double(pow(A, power + 1)) / (power + 1)));

    friend std::ostream& operator << (std::ostream& out, const Integral& P){
        if(isDef == 1) {
            if (coefficient == 0) {
                return out;
            } else if (coefficient == 1) {
                out << "((" << pow(B, power + 1) << "/" << power + 1 << ") - (" << pow(A, power + 1) << "/" << power + 1
                    << "))";
            } else {
                out << coefficient << " * ((" << pow(B, power + 1) << "/" << power + 1 << ") - (" << pow(A, power + 1)
                    << "/" << power + 1 << "))";
            }
            return out;
        }
        else
        {
            if (coefficient == 0) {
                return out;
            } else if (coefficient == 1) {
                out << "(x";

            } else {
                out << "(" << coefficient << "x";
            }
            out << "^" << power + 1 << ")/" << power + 1 << "|(from " << A << " to " << B << ")";

            return out;
        }
    }

};

template<bool isDef, int Point, int power, int coefficient, int ...data>
class Derivative
{
public:
    static constexpr int derivative = power == 0 ? 0 : coefficient * power * pow(Point, power - 1) + Derivative<isDef, Point, data...>::derivative;

    friend std::ostream& operator << (std::ostream& out, const Derivative& P){
        if(isDef)
        {
            if (power == 0) {
                out << 0 << " + " << Derivative<isDef, Point, data...>();
                return out;
            }

            if(power == 1)
            {
                out << coefficient << " + " << Derivative<isDef, Point, data...>();
                return out;
            }

            if(power != 1)
            {
                out << power << "*";
            }

            if (coefficient == 1) { out << ""; }
            else if (coefficient == -1) { out << "-"; }
            else out << coefficient << "*";
            if (power - 1 == 1) { out << Point << " + " << Derivative<isDef, Point, data...>(); }
            else { out << pow(Point, power - 1) << " + " << Derivative<isDef, Point, data...>(); }
            return out;
        }
        else {
            if (power == 0) {
                out << 0 << " + " << Derivative<isDef, Point, data...>();
                return out;
            }

            if(power == 1)
            {
                out << coefficient << " + " << Derivative<isDef, Point, data...>();
                return out;
            }

            if(power != 1)
            {
                out << power << "*";
            }

            if (coefficient == 1) { out << "x"; }
            else if (coefficient == -1) { out << "-x"; }
            else out << coefficient << "x";
            if (power - 1 == 1) { out << " + " << Derivative<isDef, Point, data...>(); }
            else { out << "^" << power - 1 << " + " << Derivative<isDef, Point, data...>(); }
            return out;
        }
    }

};

template<bool isDef, int Point, int power, int coefficient>
class Derivative<isDef, Point, power, coefficient>
{
public:
    static constexpr int derivative = power == 0 ? 0 : coefficient * power * pow(Point, power - 1);

    friend std::ostream& operator << (std::ostream& out, const Derivative& P){
        if(isDef)
        {
            if (power == 0) {
                out << 0;
                return out;
            }

            if(power == 1)
            {
                out << coefficient;
                return out;
            }

            if(power != 1)
            {
                out << power << "*";
            }

            if (coefficient == 1) { out << ""; }
            else if (coefficient == -1) { out << "-"; }
            else out << coefficient << "*";
            if (power - 1 == 1) { out << Point; }
            else { out << pow(Point, power - 1); }
            return out;
        }
        else {
            if (power == 0) {
                out << 0 ;
                return out;
            }

            if(power == 1)
            {
                out << coefficient;
                return out;
            }

            if(power != 1)
            {
                out << power << "*";
            }

            if (coefficient == 1) { out << "x"; }
            else if (coefficient == -1) { out << "-x"; }
            else out << coefficient << "x";
            if (power - 1 == 1) { return out;}
            else { out << "^" << power - 1; }
            return out;
        }
    }


};


template<int Point, int power, int coefficient, int ...data>
class Polynomial {
public:

    static constexpr int value = pow(Point, power) * coefficient + Polynomial<Point, data...>::value;

    friend std::ostream& operator << (std::ostream& out, const Polynomial& P){
        if(power == 0)
        {
            if(coefficient != 0)
            {
                out << coefficient << " + " << Polynomial<Point, data...>();
            }
            else
            {
                out << Polynomial<Point, data...>();
            }

            return out;
        }

        if (coefficient == 1) {out << "x";}
        else if(coefficient == -1){out << "-x";}
        else out << coefficient << "x";
        if (power == 1) {out << " + " << Polynomial<Point, data...>();}
        else {out << "^" << power << " + " << Polynomial<Point, data...>();}
        return out;
    }
};

template<int Point, int power, int coefficient>
class Polynomial<Point, power, coefficient>{
public:

    static constexpr int value = pow(Point, power) * coefficient;

    friend std::ostream& operator << (std::ostream& out, const Polynomial& P){
        if(power == 0)
        {
            if(coefficient != 0)
            {
                out << coefficient;
            }

            return out;
        }

        if (coefficient == 1) {out << "x";}
        else if(coefficient == -1){out << "-x";}
        else out << coefficient << "x";
        if (power != 1 && power != 0) {out << "^" << power;}

        return out;
    }
};

int main()
{
    Polynomial<2, 1, 1, 2, 1> p;
    Integral<1, 0, 2,  1, 5,  2, 17> i;
    Derivative<1, 2, 5, 3, 8, 17, 1, 12> d;
    std::cout << "Polynomial is " << Polynomial<2, 5, 3, 8, 17, 1, 12>() << std::endl
              << "Polynomial's derivative in point " << 2 << " is " << Derivative<0, 2, 5, 3, 8, 17, 1, 12>() << " = " << Derivative<1, 2, 5, 3, 8, 17, 1, 12>()
              << " = " << Derivative<1, 2, 5, 3, 8, 17, 1, 12>::derivative << std::endl;
    std::cout << "Polynomial's integral is " << Integral<0, 0, 2, 5, 3, 8, 17, 1, 12>() << " = "
              << Integral<1, 0, 2, 5, 3, 8, 17, 1, 12>() << " = " << Integral<0, 0, 2, 5, 3, 8, 17, 1, 12>::definiteIntegral << std::endl;
    static_assert(Polynomial<2, 1, 1, 2, 1>::value == 6);
    static_assert(Derivative<1, 2, 1, 1, 2, 1>::derivative == 5);
    static_assert(Integral<0, 0, 2,  1, 56,  2, 12>::definiteIntegral - 144 < 0.0001);
    static_assert(Integral<0, 0, 2,  1, 5,  2, 17>::definiteIntegral - 55.3333 < 0.0001);
    return 0;
}