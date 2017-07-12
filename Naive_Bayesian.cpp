#include<iostream>
#include"Naive_Bayesian.hpp"

#define NUM 14
#define Dim 4

int main(int argc,char **argv)
{
    //age,income,student,credit_rating
    int dataList[NUM*Dim] = 
    {
        20,3,0,0,  
        20,3,0,1,  
        30,3,0,0,  
        40,2,0,0,  
        40,1,1,0,  
        40,1,1,1,  
        30,1,1,1,  
        20,2,0,0,  
        20,1,1,0,  
        40,2,1,0,  
        20,2,1,1,  
        30,2,0,1,  
        30,3,1,0,  
        40,2,0,1};

    int classList[NUM] = {0,0,1,1,1,0,1,0,1,1,1,1,1,0}; 
    NaiveBayesianClassifier NBClassifier(NUM,classList);
    

    //Train
    NBClassifier.Train(dataList);

    //Test
    int testList[Dim];
    std::cout<<"Please enter 4 number ! age:20,30,40   income:low,1 medium,2 high,3  student:no,0 yes,1   credit_rating:fair,0 excellent,1"<<std::endl;
    std::cin>>testList[0]>>testList[1]>>testList[2]>>testList[3];
    NBClassifier.Test(testList);
}