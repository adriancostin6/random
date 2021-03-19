#include <vector>
#include <math.h>
#include <iostream>

int binary_to_integer(const std::string& in);

int main(int argc, char* argv[])
{
    if(argc !=2 ){
        std::cout <<"Usage: bin-int BIN\nBIN: binary number\n"
               <<"Convert binary numbers to integers.\n"
               <<"Example: bin-int 1101\n";
        return -1;
    }

    std::cout << binary_to_integer(argv[1]) << std::endl;
}

int binary_to_integer(const std::string& in)
{
    int size = in.length();
    int result = 0;
    for(int i = 0; i < size; ++i) {
        //get ascii value of each character in the input argument
        int b = in[i] - '0';

        //if it is not 0 or 1, it is not a bit
        if(b != 0 && b != 1) {
            std::cerr << "Input parameter is not a binary number\n";
            std::exit(EXIT_FAILURE);
        }

        //if bit value is 1, add power of two to result 
        if(b == 1)
            result += pow(2, size-(i+1));
    }
    return result;
}
