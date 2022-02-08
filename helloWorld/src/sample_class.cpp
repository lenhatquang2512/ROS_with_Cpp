#include<iostream>
#include<helloWorld/SampleClass.h>

SampleClass::SampleClass(){
    std::cout << "hello" << std::endl;
}

SampleClass::~SampleClass(){
    std::cout <<"This is destructor " << std::endl;
}