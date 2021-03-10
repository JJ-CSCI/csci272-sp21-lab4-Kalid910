//------------------------------
//  DO NOT MODIFY NEXT LINE
//------------------------------
#include <iostream>
#include <string>
#include "catch.hpp"
using Catch::Matchers::Equals;
//------------------------------

using namespace std;

// Fix the following class
class Complex
{
private:
    int coeffOne;
    int coeffTwo;

public:
    Complex() {
        this->coeffOne = 0;
        this->coeffTwo = 0;
    }

    Complex(int one) {
        this->coeffOne = one;
        this->coeffTwo = 0;
    }

    Complex(int one, int two) {
        this->coeffOne = one;
        this->coeffTwo = two;
    }

    int re() const {
        return this->coeffOne;
    }

    int im() const {
        return this->coeffTwo;
    }
    
    void operator>>(std::string &s) const {
        if (this->im() < 0) { 
         s.append(to_string(this->re()) + to_string(this->im()) + "i");
        }
        else {
          s.append(to_string(this->re()) + "+" + to_string(this->im()) + "i");  
        }
    }
    //        c << "1+1i";
    void operator<<(const std::string &s) {
        bool flag = true;
        for (unsigned int i = 0; i < s.length() - 1; i++) {
            if (s.at(i) == '-' && flag){
                string num = "";
                num += s.at(i+1);
                this->coeffOne = stoi(num) * -1;
                i++;

                flag = false;
            }
            else if (flag){
                string num = "";
                num += s.at(i);
                this->coeffOne = stoi(num);
                flag = false;
            }

            if (s.at(i) == '-' && !flag) {
                string num = "";
                num += s.at(i+1);
                this->coeffTwo = stoi(num) * -1;
                break;
            }
            else if (s.at(i) == '+' && !flag) {
                string num = "";
                num += s.at(i+1);
                this->coeffTwo = stoi(num);
                break;
            }
        }
    }
 
};
//------------------------------
//   DO NOT MODIFY TEST CASES
//------------------------------
TEST_CASE( "Assignment" ) {
    SECTION( "c1" ) {
        Complex c;
        REQUIRE( c.re() == 0 );
        REQUIRE( c.im() == 0 );
    }
    SECTION( "c2" ) {
        Complex c{1};
        REQUIRE( c.re() == 1 );
        REQUIRE( c.im() == 0 );
    }
    SECTION( "c3" ) {
        Complex c{1,1};
        REQUIRE( c.re() == 1 );
        REQUIRE( c.im() == 1 );
    }
    SECTION( "o1" ) {
        Complex c; std::string s{""};
        c >> s;
        REQUIRE_THAT( s, Equals("0+0i") );
    }
    SECTION( "o2" ) {
        Complex c{1, 2}; std::string s{""};
        c >> s;
        REQUIRE_THAT( s, Equals("1+2i") );
    }
    SECTION( "o3" ) {
        Complex c{2, -2}; std::string s{""};
        c >> s;
        REQUIRE_THAT( s, Equals("2-2i") );
    }
    SECTION( "o4" ) {
        Complex c{-2, 2}; std::string s{""};
        c >> s;
        REQUIRE_THAT( s, Equals("-2+2i") );
    }
    SECTION( "p1" ) {
        Complex c;
        c << "1+1i";
        REQUIRE( c.re() == 1 );
        REQUIRE( c.im() == 1 );
    }
    SECTION( "p2" ) {
        Complex c;
        c << "1-1i";
        REQUIRE( c.re() == 1 );
        REQUIRE( c.im() == -1 );
    }
    SECTION( "p3" ) {
        Complex c;
        c << "-1+0i";
        REQUIRE( c.re() == -1 );
        REQUIRE( c.im() == 0 );
    }
    SECTION( "p4" ) {
        Complex c;
        c << "-1-2i";
        REQUIRE( c.re() == -1 );
        REQUIRE( c.im() == -2 );
    }
}
//------------------------------
