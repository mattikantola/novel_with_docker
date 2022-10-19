#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<regex>
#include<chrono>
#include<omp.h>

using std::string;

string longest_common_substring(string& first, string& second){

    /* The purpose of this procedure is to find the longest common substring of two strings. It is done by checking all the substrings of 
        the first string. If a substring is found in the second string, its length is increased by one and a new check is performed. 
        When a substring is found, its length is checked against the length of the current longest substring. If the new match is longer than
        its predecessor, its length is saved. The saved value is used as a new starting length of the substring check, because the algorithm is no longer
        interested in shorter substrings than the longest found substring.    
     */

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

    /* This procedure reads a file and joins it into a string, replacing all tabs and newlines with a single whitespace. */

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

    string first_book = read_book("dracula.txt.utf-8");
    string second_book = read_book("musketeers.txt.utf-8");

    std::cout << first_book.length() << " and " << second_book.length() << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << longest_common_substring(first_book, second_book) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop-start);
    std::cout << duration.count() << " s" << std::endl;

    return 0;
}