#include <iostream>
#include <string>
#include <fstream> 
using namespace std;

long long int check_p(string& given, string& p)  //KMP algorithm
{
    int len_string = given.length();
    int len_sub = p.length();
    long long int counter = 0;
    bool exist;
    for (int i = 0; i < len_string; i++) 
	{
        exist = true;
        for (int j = 0; j < len_sub; j++)    
        {                                    
            if (given[i+j] != p[j]) 
			{
                exist = false;
                break;
            }
        }
        if (exist == true)
            counter++;
    }
    return counter;
}

void findOccurance(int n, long long int base_0, long long int base_1, long long int times_mid_1, long long int times_mid_2)
{
    int appearances = 0;
    while(appearances < n) 
	{
        if ((appearances % 2) == 1)           //using findOccurance to calculate the number of occurences
            base_0 += base_1 + times_mid_1; 
        else
            base_1 += base_0 + times_mid_2; 
            
        appearances++;
    }
    if ((appearances % 2) == 1)
        cout<< base_1<< endl;
    else
        cout<< base_0<< endl;
}

void solution(int n, string p)
{
	string base_0 = "0";
    string base_1 = "1";
    int len_p = p.length();
        
        
        if (n == 0)       //base case, when n = 0
		{
            cout<< check_p(base_0, p)<< endl;
            return;
        }
        else if (n == 1)  //base case, when n = 1
		{
            cout<< check_p(base_1, p)<< endl;
            return;
        }
        
        int appearances = 2;
        
        while ((base_0.length() < len_p || base_1.length() < len_p) && appearances <= n) 
		{
            if ((appearances % 2) == 1)
                base_1 = base_0 + base_1;
			else 
                base_0 = base_1 + base_0;
                
            appearances++;
        }
        appearances--;
        if (appearances == n)
		{
            if ((appearances % 2) == 0)
                cout<< check_p(base_0, p)<< endl;
            else
                cout<< check_p(base_1, p)<< endl;
            return;
        }
        
        
        
        long long int times_1 = 0;
		long long int times_2 = 0;
        long long int times_mid1 = 0;
		long long int times_mid2 = 0;
        string tempstr1 = "";
		string tempstr2 = "";
		
        tempstr1 = base_0 + base_1;
        tempstr2 = base_1 + base_0;
        times_1 = times_2 = times_mid1 = times_mid2 = -1;
        times_1 = check_p(base_0, p);
        times_2 = check_p(base_1, p);
        times_mid1 = check_p(tempstr1, p) - times_1 - times_2; //find G(n) by using the way mentioned in documentation
        times_mid2 = check_p(tempstr2, p) - times_1 - times_2; //find G(n) by using the way mentioned in documentation
        
        if ((appearances % 2) == 1)
        	findOccurance(n-appearances, times_2, times_1, times_mid1, times_mid2);
        else
            findOccurance(n-appearances, times_1, times_2, times_mid2, times_mid1);
            
        return;
}

int main(int argc, char* argv[])
{
    int n = 0;
    int number = 1; //number of times the program has executed
    string p;
    fstream fin(argv[1]);
    while(fin>> n>> p) 
	{
		cout << "Case " << number << ": ";
        number++;
        solution(n, p);
	}
    return 0;
}
