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

#define CHARACTER_TABLE "0123456789abcdefghijklmnopqrstuvwxyz"
#define CHARACTER_TABLE_SIZE 36

class Hash {
public:
    Hash(std::string seed = BASE_KEY) {
        baseKey = seed;
    }
    
    std::string getHash(std::string inputText) {
        char *result = new char[baseKey.length()];
        strcpy(result, baseKey.c_str());
        
        const size_t inputLength = inputText.length();
        
        size_t offset = 0;
        size_t size = std::min(baseKey.length(), inputLength);
        
        do {
            const std::string newBlock = inputText.substr(offset, std::min(size, inputLength - offset));
            result = hashBlock(result, newBlock.c_str(), newBlock.length());
            offset += size;
        } while (offset < inputLength);

        return numericToText(result, baseKey.length());
    }
    
private:
    std::string baseKey;
    
    inline unsigned int getStringSum(const char *text, size_t length) {
        unsigned int sum = 0;
        for (size_t i = 0; i < length; i++) {
            sum += text[i];
        }
        
        return sum;
    }
    
    inline char *hashBlock(char *base, const char *block, size_t blockSize) {
#if __PROFILE__
        std::cout << "Hashing " << base << " with " << block << std::endl;
#endif
        const unsigned int baseSum = getStringSum(base, baseKey.length());
        const unsigned int blockSum = getStringSum(block, blockSize);
        
        char *result = base;
        unsigned int blockDigit = 0;
        for (int i = 0; i < baseKey.length(); i++) {
            const unsigned int extraLonger = i > 0 ? base[i - 1] : base[1];
            const unsigned int extraShorter = blockDigit > 0 ? block[blockDigit - 1] : block[1];
            
            const int key = std::tan(base[i] * (block[blockDigit] + 87) + extraLonger + extraShorter) * (101 + extraLonger * extraShorter + baseSum - blockSum) + i;
            
            result[i] = std::abs(key) % CHAR_MAX;
            if (blockDigit + 1 < blockSize) {
                blockDigit++;
            } else {
                blockDigit = 0;
            }
        }
        
        return result;
    }
    
    inline std::string numericToText(char *numericValue, size_t length) {
        std::string result;
        for (size_t i = 0; i < length; i++) {
            result += CHARACTER_TABLE[numericValue[i] % CHARACTER_TABLE_SIZE];
        }
        
        return result;
    }
};

#endif /* Hash_h */
