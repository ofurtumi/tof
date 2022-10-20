long sum10(long *a) {
    int i;
    long sum = 0;

    for(i=0; i<35; i++) {
        sum += a[i];
    }
    return sum;
}