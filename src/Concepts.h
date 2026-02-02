#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

template<typename T>
concept SChar = std::same_as<T, char>;

template<typename T>
concept UChar = std::same_as<T, unsigned char>;

template<typename T>
concept Char = UChar<T> || SChar<T>;

template<typename T>
concept SInt = 
(
    std::same_as<T, short int> ||
    std::same_as<T, int> ||
    std::same_as<T, long int> ||
    std::same_as<T, long long int>
);

template<typename T>
concept UInt = 
(
    std::same_as<T, unsigned short int> ||
    std::same_as<T, unsigned int> ||
    std::same_as<T, unsigned long int> ||
    std::same_as<T, unsigned long long int>
);

template<typename T>
concept Int = SInt<T> || UInt<T>;

template<typename T>
concept Float = 
(
    std::same_as<T, float> ||
    std::same_as<T, double> ||
    std::same_as<T, long double>
);

template<typename T>
concept SCharPtr = std::same_as<T, char*>;

template<typename T>
concept UCharPtr = std::same_as<T, unsigned char*>;

template<typename T>
concept CharPtr = SCharPtr<T> || UCharPtr<T>;

template<typename T>
concept SIntPtr = 
(
    std::same_as<T, short int*> ||
    std::same_as<T, int*> ||
    std::same_as<T, long int*> ||
    std::same_as<T, long long int*>
);

template<typename T>
concept UIntPtr = 
(
    std::same_as<T, unsigned short int*> ||
    std::same_as<T, unsigned int*> ||
    std::same_as<T, unsigned long int*> ||
    std::same_as<T, unsigned long long int*>
);

template<typename T>
concept IntPtr = SIntPtr<T> || UIntPtr<T>;

template<typename T>
concept FloatPtr = 
(
    std::same_as<T, float*> ||
    std::same_as<T, double*> ||
    std::same_as<T, long double*>
);

template<typename T>
concept Numeric = Int<T> || Float<T>;

template<typename T>
concept NumericPtr = IntPtr<T> || FloatPtr<T>;

template<typename T>
concept AlphaNumeric = Char<T> || Int<T> || Float<T>;

template<typename T>
concept AlphaNumericPtr = CharPtr<T> || IntPtr<T> || FloatPtr<T>;

template<typename T>
concept AlphaNumericComplete = AlphaNumeric<T> || AlphaNumericPtr<T>;

#endif