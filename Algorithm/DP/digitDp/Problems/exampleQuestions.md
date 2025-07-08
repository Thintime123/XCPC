## 例题题解代码

### 1.度的数量

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 100000 + 5;
const int mod = 1e9+7;

int l,r,k,b;
int f[35][35];
//首先我们先预处理f数组。其中f[i][j]表示剩下还有i个没填，需要填写j个1的方案数。
void init(){
    for(int i=0;i<35;i++){
        for(int j=0;j<=i;j++){
            if(!j)f[i][j]=1;
            else{
                f[i][j]=f[i-1][j]+f[i-1][j-1];
            }
        }
    }
}
int dp(int n){
    //求解f(n)。我们需要避免n为0的情况，这里需要特判。
    if(!n)return 0;
    vector<int> nums;//将n分割，存储位数。
    while(n){
        nums.push_back(n%b);
        n/=b;
    }
    int ans=0;//答案。
    int last=0;//前面的信息，这里代表的是前面分支选取了多少个1.
    for(int i=nums.size()-1;i>=0;i--){
        int x=nums[i];
        if(x){
            //说明x>0，我们可以选择左边分支填0.
            ans+=f[i][k-last];
            if(x>1){
                //当x>1我们才可以枚举左边分支填1.
                if(k-last-1>=0){
                    //如果还可以填1的话。
                    ans+=f[i][k-last-1];
                }
                break;//因为右边分支只能为0或1，所以不符合条件。break。
            }
            else{
                //当x=1就可以进入右边的分支继续讨论。
                last++;
                if(last>k)break;
            }
        }
        //考虑到最后一位，如果符合条件那么末位填0也算一种方案。
        if(!i&&last==k)ans++;
    }
    return ans;
}
void solve(){
}
int main(){
    cin>>l>>r>>k>>b;
    init();
    cout<<dp(r)-dp(l-1)<<endl;
    solve();
    return 0;
}
```



### 2.数字游戏

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 100000 + 5;
const int mod = 1e9+7;

int l,r;
int f[11][11];//预处理f数组。其中f[i][j]表示i位数，且最高位为j的不降数方案数。
void init(){
    for(int i=1;i<10;i++)f[1][i]=1;
    for(int i=2;i<11;i++){
        for(int j=0;j<10;j++){
            for(int k=j;k<10;k++){
                f[i][j]+=f[i-1][k];
            }
        }
    }
}
int dp(int n){
    //1~n，这里我们需要特判n=0。
    if(!n)return 0;
    vector<int> nums;//存储分割位数。
    while(n)nums.push_back(n%10),n/=10;
    int last=0;//last存储上一位的最大值。
    int ans=0;//答案。
    for(int i=nums.size()-1;i>=0;i--){
        int x=nums[i];
        //走左边的分支。因为要保持不降序，所以我们j>=last。
        for(int j=last;j<x;j++){
            ans+=f[i+1][j];//注意是i+1位。
        }
        if(last>x)break;//说明上一位比x大，不能构成降序了，直接退出。
        last=x;//走右分支了，更新last。
        if(!i)ans++;//全部枚举完了，自身也同样构成了一种方案。
    }
    return ans;
}
int main(){
    init();
    while(cin>>l>>r){
        cout<<dp(r)-dp(l-1)<<endl;
    }
    return 0;
}
```



