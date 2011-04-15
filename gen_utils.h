#ifndef _GEN_UTILS_H_
#define _GEN_UTILS_H_

#include <sstream>
#include <string>

/* A macro to disallow the copy constructor and operator= functions
 * This should be used in the private: declarations for a class
 * Taken from Google C++ coding standards
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

/* Mostly for debugging purposes */
template<class T>
inline std::string to_string(const T& obj) {
	std::ostringstream out;
	out << obj;
	return out.str();
}

#endif

