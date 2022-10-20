void sumv(long *a, int len, long *s) {
    int i;

    *s = 0;
    for (i = 0; i < len; i++)
    {
        *s += a[i];
    }
    
}