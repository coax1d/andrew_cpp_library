/*
Demonstration of adding a serialize/deserialize
method to a class

Author: Andrew Burger
*/

#include <iostream>
#include <vector>

class Foo {

    public:

        Foo() = default;
        ~Foo() = default;
        Foo(float a, int b, std::initializer_list<int> l);
        Foo(std::istream &serialization);

        void serialize(std::ostream &buffer);
        void deserialize(std::istream &serialization);
        void print_fields();

        const float get_x();
        const int get_y();
        const std::vector<int> & get_z();

    private:
        float x = 1.0;
        int y = 3;
        std::vector<int> z{1,2,3};

};

Foo::Foo(float a, int b, std::initializer_list<int> l) :
    x{a}, y{b}, z{l} {}

Foo::Foo(std::istream & serialization) {

    serialization.read((char*)(&x), sizeof(float));
    serialization.read((char*)(&y), sizeof(int));

    int buf[z.size()];
    serialization.read((char*)(&buf), sizeof(int) * z.size());

    for (int i = 0; i < z.size(); ++i) {
        z.at(i) = buf[i];
    }
}

void Foo::serialize(std::ostream &buffer) {

    buffer.write((char*)(&x), sizeof(float));
    buffer.write((char*)(&y), sizeof(int));

    for (auto val : z) {
        buffer.write((char*)(&val), sizeof(int));
    }
}

void Foo::deserialize(std::istream &serialization) {

    serialization.read((char*)(&x), sizeof(float));
    serialization.read((char*)(&y), sizeof(int));

    int buf[z.size()];
    serialization.read((char*)(&buf), sizeof(int) * z.size());

    for (int i = 0; i < z.size(); ++i) {
        z.at(i) = buf[i];
    }
}

void Foo::print_fields() {

    std::cout << "Object fields are:" << std::endl;
    std::cout << "x: " << x
        << " y: " << y
        << " z:";

    for (int i = 0; i < z.size(); i++) {
        std::cout << ' ' << z[i];
    }
    std::cout << std::endl;
}

const float Foo::get_x() {
    return x;
}

const int Foo::get_y() {
    return y;
}

const std::vector<int> & Foo::get_z() {
    return z;
}