
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_java_util_regex_RETokenNamedProperty$POSIXHandler__
#define __gnu_java_util_regex_RETokenNamedProperty$POSIXHandler__

#pragma interface

#include <gnu/java/util/regex/RETokenNamedProperty$Handler.h>
extern "Java"
{
  namespace gnu
  {
    namespace java
    {
      namespace util
      {
        namespace regex
        {
            class RETokenNamedProperty$POSIXHandler;
            class RETokenPOSIX;
        }
      }
    }
  }
}

class gnu::java::util::regex::RETokenNamedProperty$POSIXHandler : public ::gnu::java::util::regex::RETokenNamedProperty$Handler
{

public:
  RETokenNamedProperty$POSIXHandler(::java::lang::String *);
  virtual jboolean includes(jchar);
private:
  ::gnu::java::util::regex::RETokenPOSIX * __attribute__((aligned(__alignof__( ::gnu::java::util::regex::RETokenNamedProperty$Handler)))) retoken;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_java_util_regex_RETokenNamedProperty$POSIXHandler__
