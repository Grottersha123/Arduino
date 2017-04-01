LAT_1 = 54.922011
LON_1 = 34.999696
a = [1000,1000,1000,1000]
b = [1000,1000,1000,1000]
first, second = 54.922011, 34.999696
third,fourth = 54.925957,35.004588
del1 = abs((first - third))/100
del2 = abs((second - fourth))/100
a_1 = del1/abs(a[0]-LAT_1)
a_2 = del2/abs(b[0]-LON_1)
print(LAT_1+a_1*abs(a[0]-LAT_1))
print(LON_1+a_2*abs(b[0]-LON_1))

print(del1,del2)
print()
for i in range(0,100):
    a_1 = del1 / abs(1000 - LAT_1)
    a_2 = del2 / abs(1000 - LON_1)
    LAT_1+= a_1*abs(1000-LAT_1)
    LON_1+= a_2 * abs(1000-LON_1)
    print(a_1)
    print(LAT_1,LON_1)

print()
lon = 1000
lat = 1000
for i in range(0,100):
    first +=del1
    second += del2
    print(first,second)

