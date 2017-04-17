LAT_1 = 55.826090
LON_1 = 37.387760
a = [1000,1000,1000,1000]
b = [1000,1000,1000,1000]
first, second = 55.826090, 37.387760
third,fourth = 55.825867,  37.389916
n  = 10
del1 = (third -first)/n
del2 = (fourth - second)/n
#a_1 = del1/abs(a[0]-LAT_1)
#a_2 = del2/abs(b[0]-LON_1)
#print(LAT_1+a_1*abs(a[0]-LAT_1))
#print(LON_1+a_2*abs(b[0]-LON_1))

print(del1,del2)
print()
"""for i in range(0,10):
    a_1 = del1 / abs(1000 - LAT_1)
    a_2 = del2 / abs(1000 - LON_1)
    LAT_1+= a_1*abs(1000-LAT_1)
    LON_1+= a_2 * abs(1000-LON_1)
    print(a_1)
    print(LAT_1,LON_1)
"""
print()


def coordinates(first,second,third,fourth,n):
    del1 = (third - first) / n
    del2 = (fourth - second) / n
    for i in range(0,n):
        first +=del1
        second += del2
        print(first,second)
coordinates(first,second,third,fourth,n)
        #return ()

