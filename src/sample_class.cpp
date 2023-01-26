#include<iostream>
#include<ros_with_cpp/SampleClass.h>

SampleClass::SampleClass(){
    std::cout << "hello" << std::endl;
}

SampleClass::~SampleClass(){
    std::cout <<"This is destructor " << std::endl;
}