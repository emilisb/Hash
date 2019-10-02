//
//  Hash.h
//  Blockchain1
//
//  Created by Emilis Baliukonis on 26/09/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef Hash_h
#define Hash_h

#define BASE_KEY "a3271bf53178d25638d34e853171262d"

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
#if __PROFILE__
        std::cout << "Input text: " << inputText << std::endl;
#endif
        std::string result = numericSeed;
        const std::string numericInput = textToAscii(inputText);
#if __PROFILE__
        std::cout << "Ascii value: " << numericInput << std::endl;
#endif
        
        const size_t inputLength = numericInput.length();
        
        size_t offset = 0;
        size_t size = std::min(numericSeed.length(), inputLength);
        
        do {
            result = hashBlock(result, numericInput.substr(offset, std::min(size, inputLength - offset)));
            offset += size;
        } while (offset < inputLength);

        std::string reverseHash = result;
        std::reverse(reverseHash.begin(), reverseHash.end());
        
        result = hashBlock(reverseHash, result);
        
        return numericToText(result);
    }
    
private:
    std::string numericSeed;
    
    inline unsigned int getStringSum(const char *text, size_t length) {
        unsigned int sum = 0;
        for (size_t i = 0; i < length; i++) {
            sum += text[i];
        }
        
        return sum;
    }
    
    inline std::string hashBlock(std::string base, std::string block) {
#if __PROFILE__
        std::cout << "Hashing " << base << " with " << block << std::endl;
#endif
        std::string longerString = base.length() > block.length() ? base : block;
        const std::string shorterString = longerString == base ? block : base;
        
        const unsigned int baseSum = getStringSum(base.c_str(), base.length());
        const unsigned int blockSum = getStringSum(block.c_str(), block.length());
        
        const auto longerStringLength = longerString.length();
        const auto shorterStringLength = shorterString.length();
        
        unsigned int blockDigit = 0;
        for (int i = 0; i < longerStringLength; i++) {
            const unsigned int extraLonger = i > 0 ? longerString[i - 1] : longerString[1];
            const unsigned int extraShorter = blockDigit > 0 ? shorterString[blockDigit - 1] : shorterString[1];
            
            const std::string key = std::to_string(std::tan(longerString[i] * (shorterString[blockDigit] + 87) + extraLonger + extraShorter) * (101 + extraLonger * extraShorter + baseSum - blockSum));
            
            longerString[i] = key.back();
            if (blockDigit + 1 < shorterStringLength) {
                blockDigit++;
            } else {
                blockDigit = 0;
            }
        }
        
        return longerString;
    }
    
    inline std::string textToAscii(std::string text) {
        std::string result;
        for (const auto &character : text) {
            result += std::to_string(character);
        }
        
        return result;
    }
    
    inline std::string numericToText(std::string numericValue) {
        std::string result;
        const auto numericValueLength = numericValue.length();
        for (size_t i = 0; i < numericValueLength / 2; i++) {
            unsigned int index = stoi(numericValue.substr(i, 2)) % CHARACTER_TABLE_SIZE;
            result += CHARACTER_TABLE[index];
        }
        
        return result;
    }
};

#endif /* Hash_h */
