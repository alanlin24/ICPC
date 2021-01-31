#include <iostream>

using namespace std;

#define MAX 256
#define ll long long

const ll inf=9e18;
int color_code[MAX + 12];
ll cost[MAX +12][MAX + 12];
ll f[MAX + 12][MAX + 12];

inline ll min(ll a,ll b)
{
    if(a < b) 
        return a;
    else
        return b;
}

int main()
{
    int d = 0;
    int k = 0;
    ll ans;
    
    //input processing
    cin>> d>> k;
    if(k >= d){
        cout<< "0";
        return 0;
    }
    for(int i = 1; i <= d; i++){ 
        int temp;
        cin>> temp;
        cin>> color_code[temp + 1];
    }

	//l for left bound and r for right bound
	//p for traversing the color code
    for(int l = 1; l <= MAX; l++){
        for(int r = l + 1; r <= MAX; r++){
            for(int p = l + 1; p < r; p++)
                if(r - p <= p - l) 
                    cost[l][r] += (ll)(r - p) * (r - p) * color_code[p];
                else 
                    cost[l][r] += (ll)(p - l) * (p - l) * color_code[p];
        }
    }
    
    for(int i = 1; i <= MAX; i++)
        for(int j = 1; j < i; j++) 
            f[i][1] += (ll)(i - j) * (i - j) * color_code[j];
            
    for(int i = 2; i <= MAX; i++)
        for(int j = 2; j <= min(k, i); j++){
            f[i][j] = inf;
            for(int p = j - 1; p < i; p++) 
                f[i][j] = min(f[p][j - 1] + cost[p][i], f[i][j]);
        }

    ans = f[MAX][k];
    for(int i = MAX - 1; i >= k; i--){
        ll temp = 0;
        for(int j = MAX; j > i; j--) 
            temp += (ll)(j - i) * (j - i) * color_code[j];
        ans = min(ans, f[i][k] + temp);
    }
    cout<< ans;
    return 0;
}
