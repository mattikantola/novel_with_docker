#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<regex>
#include<chrono>
#include<omp.h>

using std::string;

string longest_common_substring(string& first, string& second){

    string longest = "";
    int match_length = 1;

    #pragma omp parallel for
    for (int start = 0; start < first.length()-match_length; start++){

        for (int stop = start + match_length; stop<first.length(); stop++){
            string candidate = first.substr(start, stop-start);
            if (second.find(candidate)!=std::string::npos){
                if(stop-start>longest.length()){
                    longest = candidate;
                    match_length = stop - start;
                }
            }
            else{
                break;
            }
        }
    }
    return longest;
}

string read_book(string filename){

    std::ifstream file(filename);

    string result;

    if (file){
        std::ostringstream ss;
        ss << file.rdbuf();
        result = ss.str();
    }

    std::regex pattern("\n\t");
    std::string book = std::regex_replace(result, pattern, " ");
    return book;

}

int main(void){

    string first_book = read_book("pride.txt");
    string second_book = read_book("wonderland.txt");

    std::cout << first_book.length() << " and " << second_book.length() << std::endl;

    string first_test = "Matti is a good guy";
    string second_test = "Nothing beats a good book";
    std::cout << longest_common_substring(first_test, second_test) << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << longest_common_substring(first_book, second_book) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop-start);
    std::cout << duration.count() << " s" << std::endl;

    return 0;
}