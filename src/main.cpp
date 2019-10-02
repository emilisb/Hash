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
#include "Timer/Timer.h"
#include "Hash.h"

#define __PROFILE__ false

void printUsage() {
    std::cout <<
    "Bad usage!" << std::endl << std::endl <<
    "Usage with string:" << std::endl <<
    "<program> <value>" << std::endl << std::endl <<
    "Usage with file:" << std::endl <<
    "<program> file <filename>" << std::endl;
}

int main(int argc, const char * argv[]) {
    if (argc == 1) {
        printUsage();
        return 0;
    }
    
    const std::vector<std::string> allArgs(argv, argv + argc);
    
    std::string input;
    
    if (argc == 2) {
        input = allArgs.at(1);
    } else if (allArgs.at(1) == "file") {
        std::ifstream infile { allArgs.at(2) };
        input = { std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
        
        if (input.empty()) {
            std::cout << "Could not read file!" << std::endl;
            return 0;
        }
    } else {
        printUsage();
        return 0;
    }
    
#if __PROFILE__
    Timer t;
    t.start();
#endif
    
    Hash hasher;
    std::cout << hasher.getHash(input) << std::endl;
    
#if __PROFILE__
    std::cout << "Took: " << t.duration() << " us" << std::endl;
#endif
    
    return 0;
}
