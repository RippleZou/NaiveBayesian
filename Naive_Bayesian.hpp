#include<iostream>

class NaiveBayesianClassifier
{
public:
    NaiveBayesianClassifier(int num,int* classlist)
    {
        positive=0.0;
        negative=0.0;
        class_list=new int[num];
        std::cout<<"Compute priori probability..."<<std::endl;
        num_train=num;
        for(int i=0;i<num;i++)
        {
            if(classlist[i]==0)
            {
                negative++;

            }
            else
            {
                positive++;
            }
            class_list[i]=classlist[i];
        }
        positive=positive/num;
        negative=negative/num;
        std::cout<<"The priori probability of buying computer is "<<positive<<std::endl;
        std::cout<<"The priori probability of not buying computer is "<<negative<<std::endl;
    }

    void Train(int *data)
    {
        std::cout<<"Training...."<<std::endl;

        //age
        P20_0=P20_1=P30_0=P30_1=P40_0=P40_1=0.0;
        for(int i=0;i<num_train*4;i=i+4)
        {
            //std::cout<<class_list[i/4]<<std::endl;
            if(data[i]==20 && class_list[i/4]==0)
                P20_0++;
            if(data[i]==20 && class_list[i/4]==1)
                P20_1++;
            if(data[i]==30 && class_list[i/4]==0)
                P30_0++;
            if(data[i]==30 && class_list[i/4]==1)
                P30_1++;
            if(data[i]==40 && class_list[i/4]==0)
                P40_0++;
            if(data[i]==40 && class_list[i/4]==1)
                P40_1++;
        }
        //std::cout<<P40_0<<std::endl;
        P20_0=P20_0/num_train;
        P20_1=P20_1/num_train;
        P30_0=P30_0/num_train;
        P30_1=P30_1/num_train;
        P40_0=P40_0/num_train;
        P40_1=P40_1/num_train;

        P20_0=P20_0/negative;
        P20_1=P20_1/positive;
        P30_0=P30_0/negative;
        P30_1=P30_1/positive;
        P40_0=P40_0/negative;
        P40_1=P40_1/positive;

        std::cout<<"P(20years old|no buy) = "<<P20_0<<std::endl;
        std::cout<<"P(30years old|no buy) = "<<P30_0<<std::endl;
        std::cout<<"P(40years old|no buy) = "<<P40_0<<std::endl;
        std::cout<<"P(20years old|buy) = "<<P20_1<<std::endl;
        std::cout<<"P(30years old|buy) = "<<P30_1<<std::endl;
        std::cout<<"P(40years old|buy) = "<<P40_1<<std::endl;


        //income  1,low  2,medium  3,high
        P_income_1_0=P_income_1_1=P_income_2_0=P_income_2_1=P_income_3_0=P_income_3_1=0.0;
        for(int i=1;i<num_train*4;i=i+4)
        {
            if(data[i]==1 && class_list[i/4]==0)
                P_income_1_0++;
            if(data[i]==1 && class_list[i/4]==1)
                P_income_1_1++;
            if(data[i]==2 && class_list[i/4]==0)
                P_income_2_0++;
            if(data[i]==2 && class_list[i/4]==1)
                P_income_2_1++;
            if(data[i]==3 && class_list[i/4]==0)
                P_income_3_0++;
            if(data[i]==3 && class_list[i/4]==1)
                P_income_3_1++;
        }
        P_income_1_0=P_income_1_0/num_train;
        P_income_1_1=P_income_1_1/num_train;
        P_income_2_0=P_income_2_0/num_train;
        P_income_2_1=P_income_2_1/num_train;
        P_income_3_0=P_income_3_0/num_train;
        P_income_3_1=P_income_3_1/num_train;

        P_income_1_0=P_income_1_0/negative;
        P_income_1_1=P_income_1_1/positive;
        P_income_2_0=P_income_2_0/negative;
        P_income_2_1=P_income_2_1/positive;
        P_income_3_0=P_income_3_0/negative;
        P_income_3_1=P_income_3_1/positive;


        //student
        P_student_0_0=P_student_0_1=P_student_1_0=P_student_1_1=0.0;
        for(int i=2;i<num_train*4;i=i+4)
        {
            if(data[i]==0 && class_list[i/4]==0)
                P_student_0_0++;
            if(data[i]==0 && class_list[i/4]==1)
                P_student_0_1++;
            if(data[i]==1 && class_list[i/4]==0)
                P_student_1_0++;
            if(data[i]==1 && class_list[i/4]==1)
                P_student_1_1++;
        }
        P_student_0_0=P_student_0_0/num_train;
        P_student_0_1=P_student_0_1/num_train;
        P_student_1_0=P_student_1_0/num_train;
        P_student_1_1=P_student_1_1/num_train;

        P_student_0_0=P_student_0_0/negative;
        P_student_0_1=P_student_0_1/positive;
        P_student_1_0=P_student_1_0/negative;
        P_student_1_1=P_student_1_1/positive;

        //credit_rating
        P_cr_0_0=P_cr_0_1=P_cr_1_0=P_cr_1_1=0.0;
        for(int i=3;i<num_train*4;i=i+4)
        {
            if(data[i]==0 && class_list[i/4]==0)
                P_cr_0_0++;
            if(data[i]==0 && class_list[i/4]==1)
                P_cr_0_1++;
            if(data[i]==1 && class_list[i/4]==0)
                P_cr_1_0++;
            if(data[i]==1 && class_list[i/4]==1)
                P_cr_1_1++;
        }
        P_cr_0_0=P_cr_0_0/num_train;
        P_cr_0_1=P_cr_0_1/num_train;
        P_cr_1_0=P_cr_1_0/num_train;
        P_cr_1_1=P_cr_1_1/num_train;

        P_cr_0_0=P_cr_0_0/negative;
        P_cr_0_1=P_cr_0_1/positive;
        P_cr_1_0=P_cr_1_0/negative;
        P_cr_1_1=P_cr_1_1/positive;
    }

    void Test(int *data)
    {
        std::cout<<"Test..."<<std::endl;
        /**********1.The probability of no buy************/
        P_no_buy=1.0;
        //age
        float P_age;
        if(data[0]==20)
            P_age=P20_0;
        else if(data[0]==30)
            P_age=P30_0;
        else if(data[0]==40)
            P_age=P40_0;
        else
            {
                std::cout<<"Please enter the age 20,30,40"<<std::endl;
                return;
            }
        //income
        float P_income;
        std::cout<<data[1]<<std::endl;
        if(data[1]==1)
            P_income=P_income_1_0;
        else if(data[1]==2)
            P_income=P_income_2_0;
        else if(data[1]==3)
            P_income=P_income_3_0;
        else
            {
                std::cout<<"Please enter the income 1,2,3"<<std::endl;
                return;
            }
        //student
        float P_student;
        if(data[2]==0)
            P_student=P_student_0_0;
        else if(data[2]==1)
            P_student=P_student_1_0;
        else
            {
                std::cout<<"Please enter the student 0,1"<<std::endl;
                return;
            }
        //credit_rating
        float P_cr;
        if(data[3]==0)
            P_cr=P_cr_0_0;
        else if(data[3]==1)
            P_cr=P_cr_1_0;
        else
            {
                std::cout<<"Please enter the credit_rating 0,1"<<std::endl;
                return;
            }
        //compute the probability of no buy
        P_no_buy=P_age*P_income*P_student*P_cr*negative;




        /**********1.The probability of buy************/
        P_buy=1.0;
        //age
        if(data[0]==20)
            P_age=P20_1;
        else if(data[0]==30)
            P_age=P30_1;
        else if(data[0]==40)
            P_age=P40_1;
        else
            {
                std::cout<<"Please enter the age 20,30,40"<<std::endl;
                return;
            }
        //income
        if(data[1]==1)
            P_income=P_income_1_1;
        else if(data[1]==2)
            P_income=P_income_2_1;
        else if(data[1]==3)
            P_income=P_income_3_1;
        else
            {
                std::cout<<"Please enter the income 1,2,3"<<std::endl;
                return;
            }
        //student
        if(data[2]==0)
            P_student=P_student_0_1;
        else if(data[2]==1)
            P_student=P_student_1_1;
        else
            {
                std::cout<<"Please enter the student 0,1"<<std::endl;
                return;
            }
        //credit_rating
        if(data[3]==0)
            P_cr=P_cr_0_1;
        else if(data[3]==1)
            P_cr=P_cr_1_1;
        else
            {
                std::cout<<"Please enter the credit_rating 0,1"<<std::endl;
                return;
            }
        //compute the probability of buy
        P_buy=P_age*P_income*P_student*P_cr*positive;

        std::cout<<"The probability of buying computer is "<<P_buy<<std::endl;
        std::cout<<"The probability of not buying computer is "<<P_no_buy<<std::endl;

        if(P_buy>P_no_buy)
        {
            std::cout<<"Buy!!!!!!!!!!!"<<std::endl;
        }
        else
        {
            std::cout<<"No Buy!!!!!!!!!!!"<<std::endl;
        }
    }

private:
    float positive;
    float negative;
    int num_train;
    int* class_list;
    //0,no   1,yes
    //age
    float P20_0,P20_1,P30_0,P30_1,P40_0,P40_1;
    //income  1,low  2,medium  3,high
    float P_income_1_0,P_income_1_1,P_income_2_0,P_income_2_1,P_income_3_0,P_income_3_1;
    //student 0,no 1,yes
    float P_student_0_0,P_student_0_1,P_student_1_0,P_student_1_1;
    //credit_rating  0,fair 1,excellent
    float P_cr_0_0,P_cr_0_1,P_cr_1_0,P_cr_1_1;

    float P_buy,P_no_buy;
};