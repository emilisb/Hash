//
//  Tester.h
//  Hash
//
//  Created by Emilis Baliukonis on 03/10/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef Tester_h
#define Tester_h

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>
#include "Hash.h"
#include "sha256/sha256.hpp"

#define WORD_COLLISION_STRING_LENGTH 5
#define WORD_COLLISION_PAIR_COUNT 1000000

#define SIMILAR_COLLISION_STRING_LENGTH 5
#define SIMILAR_COLLISION_PAIR_COUNT 100000

#define SHA256_BENCHMARK_STRING_LENGTH 14
#define SHA256_BENCHMARK_WORD_COUNT 100000

class Tester {
public:
    void benchmark(std::string filename) {
        testSha256();
        testFile(filename);
        testUniqueWords();
        testSimilarWorlds();
    }
    
private:
    void testSha256() {
        Timer t;
        Hash hasher;
        
        std::cout << "Starting comparison with SHA256 with " << SHA256_BENCHMARK_WORD_COUNT << " strings of " << SHA256_BENCHMARK_STRING_LENGTH << " characters" << std::endl;
        
        t.start();
        srand(1);
        for (int i = 0; i < SHA256_BENCHMARK_WORD_COUNT; i++) {
            const std::string word = randomString(SHA256_BENCHMARK_STRING_LENGTH);
            hasher.getHash(word);
        }
        
        std::cout << "My hash took: " << t.duration() / 1000000.0 << "s" << std::endl;
        
        t.start();
        srand(1);
        for (int i = 0; i < SHA256_BENCHMARK_WORD_COUNT; i++) {
            const std::string word = randomString(SHA256_BENCHMARK_STRING_LENGTH);
            sha256(word);
        }
        
        std::cout << "SHA256 took: " << t.duration() / 1000000.0 << "s" << std::endl << std::endl;
    }
    
    void testFile(std::string filename) {
        Hash hasher;
        
        std::ifstream infile { filename };
        std::string input = { std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
        
        Timer t;
        t.start();
        
        std::string hash = hasher.getHash(input);
        
        std::cout << "File test took: " << t.duration() / 1000000.0 << "s" << std::endl << std::endl;
    }
    
    void testUniqueWords() {
        Hash hasher;
        unsigned int collisions = 0;
        
        std::cout << "Starting word collision test with " << WORD_COLLISION_PAIR_COUNT << " pairs of " << WORD_COLLISION_STRING_LENGTH << " characters" << std::endl;
        
        for (int i = 0; i < WORD_COLLISION_PAIR_COUNT; i++) {
            std::string word1 = randomString(WORD_COLLISION_STRING_LENGTH);
            std::string word2 = randomString(WORD_COLLISION_STRING_LENGTH);
            
            if (word1 == word2) { // Just in case we get 2 identical strings
                word1 = randomString(WORD_COLLISION_STRING_LENGTH);
                word2 = randomString(WORD_COLLISION_STRING_LENGTH);
            }
            
            if (hasher.getHash(word1) == hasher.getHash(word2)) {
                collisions++;
            }
        }
        
        std::cout << "Collisions found in word test: " << collisions << std::endl << std::endl;
    }
    
    void testSimilarWorlds() {
        Hash hasher;
        unsigned int collisions = 0;
        double minDifference = 1.0;
        double totalDifference = 0;
        double maxDifference = 0;
        
        std::cout << "Starting similar word collision test with " << SIMILAR_COLLISION_PAIR_COUNT << " pairs of " << SIMILAR_COLLISION_STRING_LENGTH << " characters" << std::endl;
        
        for (int i = 0; i < SIMILAR_COLLISION_PAIR_COUNT; i++) {
            const std::string word1 = randomString(SIMILAR_COLLISION_STRING_LENGTH);
            std::string word2;
            
            do { // There is a high chance for getting 2 identical strings
                const unsigned int letterToChange = rand() % SIMILAR_COLLISION_STRING_LENGTH;
                const std::string newLetter = randomString(1);
                word2 = word1;
                word2[letterToChange] = newLetter[0];
            } while (word1 == word2);
            
            const std::string hash1 = hasher.getHash(word1);
            const std::string hash2 = hasher.getHash(word2);
            
            if (hash1 == hash2) {
                collisions++;
            }
            
            const std::string binary1 = textToBinaryString(hash1);
            const std::string binary2 = textToBinaryString(hash2);
            
            const double difference = compareStrings(binary1, binary2);
            totalDifference += difference;
            
            if (difference < minDifference) {
                minDifference = difference;
            } else if (difference > maxDifference) {
                maxDifference = difference;
            }
        }
        
        std::cout << "Collisions found in similar words test: " << collisions << std::endl;
        std::cout << "Minimum difference: " << minDifference * 100 << std::endl;
        std::cout << "Maximum difference: " << maxDifference * 100 << std::endl;
        std::cout << "Average difference: " << (totalDifference / SIMILAR_COLLISION_PAIR_COUNT) * 100 << std::endl;
    }
    
    std::string textToBinaryString(std::string words) {
        std:: string binaryString = "";
        for (char& _char : words) {
            binaryString += std::bitset<8>(_char).to_string();
        }
        return binaryString;
    }
    
    std::string randomString(const int length) {
        static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        
        std::string result("", length);
        
        for (int i = 0; i < length; ++i) {
            result[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        
        return result;
    }
    
    double compareStrings(std::string input1, std::string input2) {
        const size_t length = std::min(input1.length(), input2.length());
        unsigned int identical = 0;
        
        for (int i = 0; i < length; i++) {
            if (input1[i] == input2[i]) {
                identical++;
            }
        }
        
        return 1.0 - (double)identical / length;
    }
};


#endif /* Tester_h */
