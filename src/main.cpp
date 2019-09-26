//
//  main.cpp
//  Blockchain1
//
//  Created by Emilis Baliukonis on 23/09/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "timer/Timer.h"
#include "Hash.h"

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cout <<
        "Bad usage!" << std::endl << std::endl <<
        "Usage with string:" << std::endl <<
        "<program> string <value>" << std::endl << std::endl <<
        "Usage with file:" << std::endl <<
        "<program> file <filename>" << std::endl;
        return 0;
    }
    
    const std::vector<std::string> allArgs(argv, argv + argc);
    const std::string type = allArgs.at(1);
    
    std::string input;
    
    if (type == "string") {
        input = allArgs.at(2);
    } else if (type == "file") {
        std::ifstream infile { allArgs.at(2) };
        input = { std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
        
        if (input.empty()) {
            std::cout << "Could not read file!" << std::endl;
            return 0;
        }
    } else {
        std::cout << "Unknown argument!" << std::endl;
        return 0;
    }
    
    Timer t;
    t.start();

    Hash hasher;
    std::cout << "Result: " << hasher.getHash(input) << std::endl;
    
    std::cout << "Took: " << t.duration() << " us" << std::endl;
    
    return 0;
}
