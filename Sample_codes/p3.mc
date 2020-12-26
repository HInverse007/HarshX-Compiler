int N;
int a[10];
int i,ans,j;
ans=0;
scan(N);
for(i=2;i<N;i+=1) {
    a[i] = 1;
}
for(i=2;i<N;i+=1) {
    if(a[i]!=0) {
        ans += i;
        for(j=(2)*(i);j<N;j+=i) {
            a[j] = 0;
        }
    }
}
print(ans);
return 0;