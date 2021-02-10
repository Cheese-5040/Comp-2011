#include<iostream>
using namespace std;

 
int main (){
    float pig = 4.5;
    float sheep =3;
    float total = 36;

    for (int numpig =0; pig *numpig <=total; numpig ++){
        float remain = total - numpig*pig;
        int numsheep = remain / sheep;
        remain -= numsheep * sheep;

        if  (remain ==0){
            cout << numpig<< " * "<< pig << " + " <<
             numsheep <<" * " << sheep << " + " << total << endl;
        }
    }

    return 0;
}