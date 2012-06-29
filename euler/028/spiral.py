

#MAX_SIZE = 1001
MAX_SIZE = 100000001;
sum = 1
counter = 1
for i in xrange(2, MAX_SIZE, 2) :
    for j in xrange(0,4) :
        counter += i
        sum += counter

print sum
