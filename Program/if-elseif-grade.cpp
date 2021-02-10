#include <iostream>     /* File: if-elseif-grade.cpp */
using namespace std;	

int main()             /* To determine your grade (fictitious) */
{
    char grade;            // Letter grade
    // int mark; cin >> mark; // Numerical mark between 0 and 100
    
    // if (mark >= 90) 
    //     grade = 'A';    // mark >= 90
    // else if (mark >= 60) 
    //     grade = 'B';    // 90 > mark >= 60
    // else if (mark >= 20) 
    //     grade = 'C';    // 60 > mark >= 20
    // else if (mark >= 10) 
    //     grade = 'D';    // 20 > mark >= 10
    // else 
    //     grade = 'F';    // 10 > mark 
    int percentile;
    cin >> percentile;
    grade = (percentile >= 85)?'A' //variable = condition ? if statement '' true outcome : if false outcome () condition ?if statement '' true outcome
                                : (percentile >= 70)?'B'
                                : (percentile >=60)?'C'
                                : (percentile >=40)?'D':'F';
         
    cout << "Your letter grade is " << grade << endl;
    return 0;
}
