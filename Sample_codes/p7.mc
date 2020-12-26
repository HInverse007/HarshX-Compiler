int n;
scan(n);
int a[100];
int i,exp,tp,temp;
for(i=0;i<n;i+=1) {
    scan(a[i]);
}

int get_Max() { 
    int ii,mx;
    mx = a[0]; 
    for (ii = 1; ii < n; ii+=1) {
        if (a[ii] > mx) {
            mx = a[ii]; 
        }
    }
    return mx;
} 

int countSort() { 
    int output[100];
    int j, count[10];
    for (j=0;j<10;j+=1)
    {
        count[j]=0;
    } 
  
    for (j = 0; j < n; j+=1) {
        tp = (a[j])/(exp);
        tp %= 10;
        count[tp] += 1; 
    }
  
    for (j = 1; j < 10; j+=1) {
        count[j] += count[(j) - (1)];
    } 
  
    for (j = (n) - (1); j >= 0; j-=1) {
        tp = (a[j])/(exp);
        tp %= 10;
        output[(count[tp]) - (1)] = a[j]; 
        count[tp]-=1;
    } 

    for (j = 0; j < n; j+=1) {
        a[j] = output[j]; 
    }
    return 0;
} 

int radixsort() { 
    int t,m;
    m = get_Max(); 

    for (exp = 1; (m)/(exp) > 0; exp *= 10) {
        t = countSort();
    }
    return 0;
} 

temp = radixsort(); 

for (i=0;i<n;i+=1) {
    print(a[i]);
}
return 0;