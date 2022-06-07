#include <iostream>
#include <fstream>

int main()
{

    std::ofstream out("L");
    out << "hello\n";
    out.close();


    return 0;
}

