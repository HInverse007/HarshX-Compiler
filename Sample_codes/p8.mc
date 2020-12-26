int arr[1000000],i,n,temp,m,l,r; 

scan(n);

for(i=0;i<n;i+=1) {
    scan(arr[i]);
}

int merge(int arr[], int l, int m, int r) { 
    int i,j,k; 
    int n1;
    n1 = ((m) - (l)) + (1); 
    int n2;
    n2 = (r) - (m); 
    int L[1000000], R[1000000]; 
  
    for (i = 0; i < n1; i+=1) {
        L[i] = arr[(l) + (i)];
    } 
    for (j = 0; j < n2; j+=1) {
        R[j] = arr[((m) + (1)) + (j)]; 
    }
  
    i = 0; 
    j = 0; 
    k = l; 
    while ((i < n1) and (j < n2)) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i+=1; 
        } else { 
            arr[k] = R[j]; 
            j+=1; 
        } 
        k+=1; 
    } 
  
    while (i < n1) { 
        arr[k] = L[i]; 
        i+=1; 
        k+=1; 
    } 
  
    while (j < n2) { 
        arr[k] = R[j]; 
        j+=1; 
        k+=1; 
    } 
    return 0;
} 

int mergeSort(int arr[], int l, int r) 
{ 
    int t;
    if (l < r) { 
        m = ((r)+(l))/(2); 
  
        // Sort first and second halves 
        t = mergeSort(arr, l, m); 
        t = mergeSort(arr, (m)+(1), r); 
  
        t = merge(arr, l, m, r); 
    } 
    return 0;
} 

temp = mergeSort(arr, 0, (n)-(1)); 

for(i=0;i<n;i+=1) {
    print(arr[i]);
}
return 0;