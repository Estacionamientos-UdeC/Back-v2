#ifndef TYPES_H
#define TYPES_H

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <array>
#include <vector>
#include <string>

#include <memory>
#include <functional>

using sInt8 = int8_t;
using sInt16 = int16_t;
using sInt32 = int32_t;
using sInt64 = int64_t;

using uInt8 = uint8_t;
using uInt16 = uint16_t;
using uInt32 = uint32_t;
using uInt64 = uint64_t;

using string = std::string;

template<typename T> using set = std::set<T>;
template<typename T> using queue = std::queue<T>;
template<typename T> using stack = std::stack<T>;
template<typename T> using vector = std::vector<T>;

template<typename T, uInt64 S> using array = std::array<T, S>;

template<typename T1, typename T2> using map = std::map<T1, T2>;

template<typename T> using uPointer = std::unique_ptr<T>;
template<typename T> using sPointer = std::shared_ptr<T>;

template<typename T> using reference = std::reference_wrapper<T>;

#endif