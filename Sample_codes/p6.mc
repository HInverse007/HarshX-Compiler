int n; 
scan(n);
int i,a[100000];

for(i=0;i<n;i+=1) {
    scan(a[i]);
}

for(i=1;i<n;i+=1) {  
    int tp;
    tp = a[i];
    int j; 
    j = (i) - (1);  
    while ((j>=0) and (a[j]>tp)) {  
        a[(j)+(1)] = a[j];  
        j-=1;
    }  
    a[(j)+(1)] = tp;    
}  
 
for(i=0;i<n;i+=1) {
    print(a[i]);
}
return 0;