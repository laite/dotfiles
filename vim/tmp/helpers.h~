// helpers for exercises

#ifndef HELPERS_H
#define HELPERS_H

// various streams
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>

// various containers
#include <vector>
#include <list>
#include <deque>

// container adaptors
#include <stack>
#include <queue>

// associative containers
#include <map>
#include <set>

// pair
#include <utility> 

// other
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>

// algorithms (ch. 11)
#include <algorithm>
#include <numeric>

// debug helpers
#include <cassert>
#include <exception>
#include <stdexcept>

#define Max(a,b) (((a) > (b)) ? (a) : (b))
#define Min(a,b) (((a) < (b)) ? (a) : (b))

// dangerous! not for real work
using namespace std;

// c++ primer's open_file function (from chapter 8.4.3)
std::ifstream& open_file(std::ifstream &in, const string &file);

// my own helper functions, implemented in helpers.cpp
extern void PrintVector(vector<string> &stringVector, bool multiLine = false, string separator = ", ");
extern void PrintVector(vector<int> &intVector, bool multiLine = false, string separator = ", ");
extern void PrintList(list<int> &intList, bool multiLine = false, string separator = ", ");
extern void PrintList(list<string> &stringList, bool multiLine = false, string separator = " ");
extern void PopulateIntVector(vector<int> &intVector, unsigned amount, unsigned max);
extern void PopulateIntVector(vector<int> &intVector, int *begin, int *end);

//#define NDEBUG // this must be before <cassert> !

#endif
