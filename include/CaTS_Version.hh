#ifndef CATSVERSION_HH
#define CATSVERSION_HH 1
// Numbering rule for "CATSVERSION_NUMBER":
// - The number is consecutive (i.e. 71) as an integer.
// - The meaning of each digit is as follows;
//
//   71
//   |--> major version number
//    |--> minor version number
#ifndef CATSVERSION_NUMBER
#  define CATSVERSION_NUMBER 10
#endif
#ifndef CATSVERSION_TAG
#  define CATSVERSION_TAG "CaTS_1_0"
#endif
// as variables
#include <string>
static const std::string CaTSVersion = "CaTS_1_0";
static const std::string CaTSDate    = "(07-October-2021)";
#endif
