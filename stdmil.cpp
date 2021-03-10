// Standard to military time converter
#include <iostream>
#include <string>

std::string change_format(const std::string& time);

int main(int argc, char *argv[])
{
    if(argc != 2){
        std::cout <<"Usage: stdmil TIME\nTIME: [hh:mm:ss]{AM|PM}\n"
               <<"Convert standard time to military time.\n"
               <<"Example: stdmil 07:54:30AM\n";
        return -1;
    }

    std::cout << change_format(argv[1]) << std::endl;
}

std::string change_format(const std::string& time)
{
    std::string result = time;
    if(result[8] == 'A') {
        result.pop_back();
        result.pop_back();

        if (result[0] == '1') {
            std::string temp;
            temp.append(1,result[0]);
            temp.append(1,result[1]);

            result.erase(0,2);
            
            if(temp == "12"){
                result.insert(0,"00");
                return result;
            }
            return result;
        }
        return result;
    }

    result.pop_back();
    result.pop_back();
    
    //    std::string temp = "" + result[0] + result[1];
    std::string temp;
    temp.append(1,result[0]);
    temp.append(1,result[1]);

    if(temp == "00")
        return result;

    if(temp == "12")
        return result;

    int hours = std::stoi(temp) + 12 ;

    result.erase(0,2);

    result.insert(0,std::to_string(hours));

    return result;
}
