#pragma once
#include <sstream>

#define Trace(x) {stringstream s; s<<x;  fprintf(stdout, s.str().c_str() ); fprintf(stdout, "\n");}
#define Error(x) {stringstream s; s<<x;  fprintf(stderr, s.str().c_str() ); fprintf(stderr, "\n");}
#define Warning(x) {stringstream s; s<<x;  fprintf(stderr, s.str().c_str() ); fprintf(stderr, "\n");}
