#include "main.h"
#include "algos.h"
#include <algorithm>

int iterativeSum(int num) {
    if(num < 0) {
        return -1;
    }
    
    int sum = 0;
    while(num > 0) {
        int lastDigit = num % 10;
        sum += lastDigit;
        num = num / 10;
    }
    return sum;
}

int recursiveSum(int num) {
    if(num < 0) {
        return -1;
    }

    if(num < 10) {
        return num;
    }

    return recursiveSum(num / 10) + num % 10;
}

bool checkPalindrome(string str) {
    int lastIndex = str.size() - 1;

    for(int i = 0; i < str.size() / 2; i++) {
        if(str[i] != str[lastIndex - i]) {
            return false;
        }
    }

    return true;
}

bool compareMirrorChars(char a, char b) {
    if((a == 'b' && b == 'd') || (a == 'd' && b == 'b')) {
        return true;
    }
    if((a == 's' && b == 'z') || (a == 'z' && b == 's')) {
        return true;
    }
    if((a == 'p' && b == 'q') || (a == 'q' && b == 'p')) {
        return true;
    }

    return false;
}

bool checkSingleMirrorChar(char c) {
    if(c == 'i') {
        return true;
    }

    int ci = c = 'a';
    
    // l, m, n, o
    if(ci > 10 && ci < 15) {
        return true;
    }
    // t, u, v, w, x
    if(ci > 18 && ci < 24) {
        return true;
    }

    return false;
}

bool checkMirrordrome(string str) {
    int lastIndex = str.size() - 1;

    // Check middle char
    if(str.size() % 2 == 1) {
        if(!checkSingleMirrorChar(str[str.size() / 2])) {
            return false;
        }
    }

    // Check the rest
    for(int i = 0; i < str.size() / 2; i++) {
        if(str[i] != str[lastIndex - i]) {
            if (!compareMirrorChars(str[i], str[lastIndex - i])) {
                return false;
            }
        }
    }

    return true;

}

int iterativePalindromes(string str) {
    transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return tolower(c); });
    int count = 0;

    cout << checkPalindrome("s") << endl;

    // Check all substrings
    for(int i = 0; i < str.size(); i++) {
        // Add first char of each substring set bc palindromes must be >1 char
        string sub(1, str[i]);

        for(int x = i + 1; x < str.size(); x++) {
            sub += str[x];
            if(checkPalindrome(sub)) {
                count++;
            }
        }
    }

    return count;
}

int computeRecursivePalindrome(string str) {
    if(str.size() == 0) {
        return 0;
    }

    string sub(1, str[0]);
    int count = 0;

    for(int i = 1; i < str.size(); i++) {
        sub += str[i];
        if(checkPalindrome(sub)) {
            count++;
        }
    }

    return count + computeRecursivePalindrome(str.substr(1, str.size() - 1));
}

int recursivePalindromes(string str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c) { return tolower(c); });
    return computeRecursivePalindrome(str);
}

int iterativeMirrordromes(string str) {
    transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return tolower(c); });
    int count = 0;

    // Check all substrings
    for(int i = 0; i < str.size(); i++) {
        string sub = "";
        // Have to check all chars because mirrordromes can be 1 char
        for(int x = 0; x < str.size(); x++) {
            sub += str[x];
            if(checkMirrordrome(sub)) {
                count++;
            }
        }
    }

    return count;
}
