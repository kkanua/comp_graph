#include "function.h"

Function::Function(){

}

double Function::f(double x, double y){
    return x*x*cos(x) + y*y;
}

double Function::leg(double x, double y){
    return y;
}
