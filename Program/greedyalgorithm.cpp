#include <iostream> 
using namespace std; 

int main()
{
    float wt_pig = 4.5;
    float wt_sheep= 3.0;
    float total_wt= 36;

    for (int num_pigs =0;num_pigs *wt_pig <= total_wt; num_pigs++)
    {
        float remain_wt = total_wt - num_pigs * wt_pig;
        int num_sheeps = remain_wt / wt_sheep;
        remain_wt -= num_sheeps * wt_sheep;

        if (remain_wt ==0) // remaining  number is 0, then do this , compare float and float
            cout << num_pigs << " * " << wt_pig << " + "
            << num_sheeps << " * " << wt_sheep << " = "
            << total_wt << endl;
// if compare with  integer and float, then integer will change to float
int a=1;
float b=2.5;
a=b // fractional part of real value will throw away, all round down
    }
    return 0;
}