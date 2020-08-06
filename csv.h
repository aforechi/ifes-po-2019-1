#ifndef __CSV_H__
#define __CSV_H__

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <regex>
#include <algorithm>

// The delimiter
std::regex re{ "," };

// Proxy for the input Iterator
struct DoubleColumnProxy {    
    // Overload extractor. Read a complete line
    friend std::istream& operator>>(std::istream& is, DoubleColumnProxy& cp) {

        // Read a line
        std::string line; cp.columns.clear();
        std::getline(is, line);
        if (!line.empty()) {

            // Split values and copy into resulting vector
            std::transform(std::sregex_token_iterator(line.begin(), line.end(), re, -1),
                std::sregex_token_iterator(),
                std::back_inserter(cp.columns),
                [](const std::string& s){return std::stof(s);});
        }
        return is;
    }

    // Type cast operator overload.  Cast the type 'Columns' to std::vector<std::string>
    operator std::vector<double>() const { return columns; }
protected:
    // Temporary to hold the read vector
    std::vector<double> columns{};
};

struct StringColumnProxy {    
    // Overload extractor. Read a complete line
    friend std::istream& operator>>(std::istream& is, StringColumnProxy& cp) {

        // Read a line
        std::string line; cp.columns.clear();
        std::getline(is, line);
        if (!line.empty()) {

            // Split values and copy into resulting vector
            std::copy(std::sregex_token_iterator(line.begin(), line.end(), re, -1),
                std::sregex_token_iterator(),
                std::back_inserter(cp.columns));
        }
        return is;
    }

    // Type cast operator overload.  Cast the type 'Columns' to std::vector<std::string>
    operator std::vector<std::string>() const { return columns; }
protected:
    // Temporary to hold the read vector
    std::vector<std::string> columns{};
};

auto csv_read_string(std::istream & is, bool skip_headers = true) {
    if (skip_headers) {
        std::string line;
        std::getline(is, line);
    }
    return std::vector<std::vector<std::string>>{std::istream_iterator<StringColumnProxy>(is), std::istream_iterator<StringColumnProxy>() };
}

auto csv_read_double(std::istream & is, bool skip_headers = true) {
    if (skip_headers) {
        std::string line;
        std::getline(is, line);
    }
    return std::vector<std::vector<double>>{std::istream_iterator<DoubleColumnProxy>(is), std::istream_iterator<DoubleColumnProxy>() };
}

auto csv_test_double() {
    std::istringstream testCsv{ R"(0.0,0.1,1.5
    1.0,1.1,2.0
    2.0,2.1,2.5)" };

    // Define variable CSV with its range constructor. Read complete CSV in this statement, So, one liner
    std::vector<std::vector<double>> csv{ std::istream_iterator<DoubleColumnProxy>(testCsv), std::istream_iterator<DoubleColumnProxy>() };

    double sum{0.0};
    std::for_each(csv.begin(),csv.end(),[&sum](const std::vector<double>& c){sum += c.at(2);});
    return sum;
}
#endif