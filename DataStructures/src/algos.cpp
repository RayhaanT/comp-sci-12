#include "main.h"
#include "algos.h"
#include <algorithm>

int computeRecursiveMirrordrome(string str);
int computeRecursivePalindrome(string str);

/**
 * Uses an iterative algorithm to calculate the sum of all
 * digits in a non-zero integer
 * 
 * @param num - the number to be summed
 * @return the sum of the digits, -1 if num < 0
*/
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

/**
 * Uses a recursive algorithm to calculate the sum of all
 * digits in a non-zero integer
 * 
 * @param num - the number to be summed
 * @return the sum of the digits
*/
int recursiveSum(int num) {
    if(num < 0) {
        return -1;
    }

    if(num < 10) {
        return num;
    }

    return recursiveSum(num / 10) + num % 10;
}

/**
 * Compares 2 characters to see if they qualify as mirror images
 * in a mirrordrome
 * 
 * @param a - the first character to compare
 * @param b - the second character to compare
 * @return whether the characters are mirrors
*/
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

/**
 * Check if a character belongs to the family of single 
 * characters that are considered mirrors (i, l, m, n, o, t, u, v, w, x) 
 * 
 * @param c - the character to evaluate
 * @return whether the character is a mirror
*/
bool checkSingleMirrorChar(char c) {
    if(c == 'i') {
        return true;
    }

    int ci = c - 'a';
    
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

/**
 * Checks if a given string is a mirrordrome
 * 
 * @param str - the string to evaluate
*/
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
        if(str[i] == str[lastIndex - i] && checkSingleMirrorChar(str[i])) {
            continue;
        }
        if (!compareMirrorChars(str[i], str[lastIndex - i])) {
            return false;
        }
    }

    return true;
}

/**
 * Counts how many mirrordromes exist within a given
 * string's set of substrings using an iterative algorithm.
 * 
 * @param str - the string to evaluate
 * @return the number of mirrordromes found
*/
int iterativeMirrordromes(string str) {
    transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return tolower(c); });
    int count = 0;

    // Check all substrings
    for(int i = 0; i < str.size(); i++) {
        string sub = "";
        // Have to check all chars because mirrordromes can be 1 char
        for(int x = i; x < str.size(); x++) {
            sub += str[x];
            if(checkMirrordrome(sub)) {
                count++;
            }
        }
    }

    return count;
}

/**
 * Counts how many mirrordromes exist within a given
 * string's set of substrings using a recursive algorithm.
 * 
 * @param str - the string to evaluate
 * @param subString - the current current substring being evaluated
 * @return the number of mirrordromes found
*/
int computeRecursiveMirrordrome(string str, string subString) {
    if(str.empty()) {
        return 0;
    }
    if(subString.empty()) {
        return computeRecursiveMirrordrome(str.substr(1, str.size() - 1));
    }

    int returnVal = checkMirrordrome(subString) ? 1 : 0;
    return returnVal + computeRecursiveMirrordrome(str, subString.substr(0, subString.size() - 1));
}

/**
 * An overload for computeRecursiveMirrordrome that sends the same
 * value for both parameters in the primary function. C++ does not allow
 * default params to be set based on other params so this is a workaround.
 * 
 * @param str - the string to evaluate
 * @return the number of mirrordromes found
*/
int computeRecursiveMirrordrome(string str) { return computeRecursiveMirrordrome(str, str); }

/**
 * A wrapper function for computeRecursiveMirrordrome that
 * sets the string to lowercase before evaluating it so that
 * it doesn't have to be done on every recursive call
 * 
 * @param str - the string to evaluate
 * @return the number of mirrordromes found by computeRecursiveMirrordrome
*/
int recursiveMirrordromes(string str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c) { return tolower(c); });
    return computeRecursiveMirrordrome(str);
}



/**
 * The following code is unused now that mirrordromes are functional
*/

/**
 * Checks if a string is a palindrome
 * 
 * @param str- the string to evaluate
 * @return whether the input is a palindrome
*/
bool checkPalindrome(string str) {
    int lastIndex = str.size() - 1;

    // Palindromes must be >1 char
    if(lastIndex == 0) {
        return false;
    }

    for(int i = 0; i < str.size() / 2; i++) {
        if(str[i] != str[lastIndex - i]) {
            return false;
        }
    }

    return true;
}

/**
 * Counts how many palindromes exist within a given
 * string's set of substrings using an iterative algorithm.
 * 
 * @param str - the string to evaluate
 * @return the number of palindromes found
*/
int iterativePalindromes(string str) {
    transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return tolower(c); });
    int count = 0;

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

/**
 * Counts how many palindromes exist within a given
 * string's set of substrings using a recursive algorithm.
 * 
 * @param str - the string to evaluate
 * @param subString - the current substring being evaluated
 * @return the number of palindromes found
*/
int computeRecursivePalindrome(string str, string subString) {
    if(str.empty()) {
        return 0;
    }
    if(subString.empty()) {
        return computeRecursivePalindrome(str.substr(1, str.size() - 1));
    }

    int returnVal = checkPalindrome(subString) ? 1 : 0;
    return returnVal + computeRecursivePalindrome(str, subString.substr(0, subString.size() - 1));
}

/**
 * An overload for computeRecursivePalindrome that sends the same
 * value for both parameters in the primary function. C++ does not allow
 * default params to be set based on other params so this is a workaround.
 * 
 * @param str - the string to evaluate
 * @return the number of palindromes found
*/
int computeRecursivePalindrome(string str) { return computeRecursivePalindrome(str, str); }

/**
 * A wrapper function for computeRecursivePalindrome that
 * sets the string to lowercase before evaluating it so that
 * it doesn't have to be done on every recursive call
 * 
 * @param str - the string to evaluate
 * @return the number of palindromes found by computeRecursivePalindrome
*/
int recursivePalindromes(string str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c) { return tolower(c); });
    return computeRecursivePalindrome(str);
}