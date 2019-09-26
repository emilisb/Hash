//
//  Hash.h
//  Blockchain1
//
//  Created by Emilis Baliukonis on 26/09/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef Hash_h
#define Hash_h

#define NUM_BLOCKS 5
#define BASE_KEY "a3271bf53177d25638d34e853171262d"

#include <string>
#include <algorithm>
#include <cmath>

#define CHARACTER_TABLE_SIZE 62
const char CHARACTER_TABLE[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
};

class Hash {
public:
    Hash(std::string seed = BASE_KEY) {
        numericSeed = textToAscii(seed);
    }
    
    std::string getHash(std::string inputText) {
        std::string result = numericSeed;
        const std::string numericInput = textToAscii(inputText);
        
        const size_t inputLength = numericInput.length();
        
        int offset = 0;
        size_t size = std::min(numericSeed.length(), numericSeed.length());
        
        do {
            result = hashBlock(result, numericInput.substr(offset, size));
            offset += size;
        } while (offset + size < inputLength);

        std::string reverseHash = result;
        std::reverse(reverseHash.begin(), reverseHash.end());
        
        result = hashBlock(reverseHash, result);
        
        return numericToText(result);
    }
    
private:
    std::string numericSeed;
    
    int getStringSum(std::string text) {
        int sum = 0;
        for (const auto &digit : text) {
            sum += digit;
        }
        
        return sum;
    }
    
    std::string hashBlock(std::string base, std::string block) {
        std::string longerString = base.length() > block.length() ? base : block;
        const std::string shorterString = longerString == base ? block : base;
        
        const int baseSum = getStringSum(base);
        const int blockSum = getStringSum(block);
        
        int blockDigit = 0;
        for (int i = 0; i < longerString.length(); i++) {
            const int extraLonger = i > 0 ? longerString[i - 1] : longerString[1];
            const int extraShorter = blockDigit > 0 ? shorterString[blockDigit - 1] : shorterString[1];
            
            const std::string key = std::to_string(std::tan(longerString[i] * (shorterString[blockDigit] + 87) + extraLonger + extraShorter) * (101 + extraLonger * extraShorter + baseSum - blockSum));
            
            longerString[i] = key[key.length() - 1];
            if (blockDigit + 1 < shorterString.length()) {
                blockDigit++;
            } else {
                blockDigit = 0;
            }
        }
        
        return longerString;
    }
    
    std::string textToAscii(std::string text) {
        std::string result;
        for (const auto &character : text) {
            result += std::to_string(character);
        }
        
        return result;
    }
    
    std::string numericToText(std::string numericValue) {
        std::string result;
        for (int i = 0; i < numericValue.length() / 2; i++) {
            int index = stoi(numericValue.substr(i, 2)) % CHARACTER_TABLE_SIZE;
            result += CHARACTER_TABLE[index];
        }
        
        return result;
    }
};

#endif /* Hash_h */
