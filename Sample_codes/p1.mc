int N,k;
scan(N);
scan(k);
int i,j;
int ans;
ans=0;
for(i=1;i<=N;i+=1) {
    int tp;
    tp = 1;
    for(j=0;j<k;j+=1) {
        tp *= i;
    }
    ans += tp;
}
print(ans);
return 0;