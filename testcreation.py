import numpy as np
import random as rd
import math

# test create for question 2:
for i in range(20):

    filename = "D:/Algo/tests/test2/test2_%d.txt" % i
    N = rd.randint(1, 2000)
    M = rd.randint(1, 2000)
    arr = np.zeros((N, M))
    for j in range(N):
        for k in range(M):
            arr[j][k] = rd.randint(0, 1)
    with open(filename, 'w') as f:
        f.write('2\n')
        dimensions = "%d %d\n" % (N, M)
        f.write(dimensions)
        np.savetxt(f, arr, fmt='%d')
for i in range(20, 30):
    filename = "D:/Algo/tests/test2/test2_%d.txt" % i
    N = 2000
    M = 2000
    arr = np.zeros((N, M))
    for j in range(N):
        for k in range(M):
            arr[j][k] = rd.randint(0, 1)
    with open(filename, 'w') as f:
        f.write('2\n')
        dimensions = "%d %d\n" % (N, M)
        f.write(dimensions)
        np.savetxt(f, arr, fmt='%d')

for i in range(30, 50):
    filename = "D:/Algo/tests/test2/test2_%d.txt" % i
    N = 2000
    M = 2000
    arr = np.zeros((N, M))
    H = rd.randint(0, 4000000)
    for j in range(H):
        arr[rd.randint(0, N-1)][rd.randint(0, M-1)] = 1
    with open(filename, 'w') as f:
        f.write('2\n')
        dimensions = "%d %d\n" % (N, M)
        f.write(dimensions)
        np.savetxt(f, arr, fmt='%d')

# test create for question 3
for i in range(50):
    filename = "D:/Algo/tests/test3/test3_%d.txt" % i
    N = rd.randint(3, 200)
    M = rd.randint(3, 200)
    K = rd.randint(1, 100)
    with open(filename, 'w') as f:
        f.write('3\n')
        dimensions = "%d %d\n" % (N, M)
        circle_num = "%d\n" % K
        f.write(dimensions)
        f.write(circle_num)
        for j in range(K):
            x = rd.randint(0, N-1)
            y = rd.randint(0, M-1)
            rad = rd.randint(1, int(math.sqrt(N*N+M*M)))
            circle = "%d %d %d\n" % (rad, x, y)
            f.write(circle)

for i in range(50, 70):
    filename = "D:/Algo/tests/test3/test3_%d.txt" % i
    N = rd.randint(3, 200)
    M = rd.randint(3, 200)
    K = rd.randint(1, 100)
    with open(filename, 'w') as f:
        f.write('3\n')
        dimensions = "%d %d\n" % (N, M)
        circle_num = "%d\n" % K
        f.write(dimensions)
        f.write(circle_num)
        for j in range(K):
            x = rd.randint(0, N-1)
            y = rd.randint(0, M-1)
            rad = rd.randint(1, 5)
            circle = "%d %d %d\n" % (rad, x, y)
            f.write(circle)

for i in range(70, 100):
    filename = "D:/Algo/tests/test3/test3_%d.txt" % i
    N = 200
    M = 200
    K = rd.randint(1, 100)
    with open(filename, 'w') as f:
        f.write('3\n')
        dimensions = "%d %d\n" % (N, M)
        circle_num = "%d\n" % K
        f.write(dimensions)
        f.write(circle_num)
        for j in range(K):
            x = rd.randint(0, N-1)
            y = rd.randint(0, M-1)
            rad = rd.randint(1, 5)
            circle = "%d %d %d\n" % (rad, x, y)
            f.write(circle)

for i in range(100, 150):
    filename = "D:/Algo/tests/test3/test3_%d.txt" % i
    N = 200
    M = 200
    K = rd.randint(1, 100)
    with open(filename, 'w') as f:
        f.write('3\n')
        dimensions = "%d %d\n" % (N, M)
        circle_num = "%d\n" % K
        f.write(dimensions)
        f.write(circle_num)
        for j in range(K):
            x = rd.randint(0, N-1)
            y = rd.randint(0, M-1)
            rad = rd.randint(1, 3)
            circle = "%d %d %d\n" % (rad, x, y)
            f.write(circle)

# test create for Question 1:
for i in range(100):

    filename = "D:/Algo/tests/test1/test1_%d.txt" % i
    N = rd.randint(1, 50000)
    F = rd.randint(1, 1000000)
    T = rd.randint(0, F)
    L = rd.randint(1, 1000000001)
    Gas = np.zeros((N, 2))
    for j in range(N):
        Gas[j][0] = rd.randint(0, L)
        Gas[j][1] = rd.randint(1, 1000000)
    with open(filename, 'w') as f:
        f.write('1\n')
        parameters = "%d %d %d %d\n" % (N, F, T, L)
        f.write(parameters)
        np.savetxt(f, Gas, fmt='%d')
for i in range(100, 150):
    filename = "D:/Algo/tests/test1/test1_%d.txt" % i
    N = 50000
    F = rd.randint(1, 1000000)
    T = rd.randint(1, F)
    L = rd.randint(1, 1000000001)
    Gas = np.zeros((N, 2))
    for j in range(N):
        Gas[j][0] = rd.randint(0, L)
        Gas[j][1] = rd.randint(1, 1000000)
    with open(filename, 'w') as f:
        f.write('1\n')
        parameters = "%d %d %d %d\n" % (N, F, T, L)
        f.write(parameters)
        np.savetxt(f, Gas, fmt='%d')

for i in range(150, 200):
    filename = "D:/Algo/tests/test1/test1_%d.txt" % i
    N = rd.randint(1, 10000)
    F = rd.randint(1, 10000)
    T = rd.randint(1, F)
    L = rd.randint(1, 1000001)
    Gas = np.zeros((N, 2))
    for j in range(N):
        Gas[j][0] = rd.randint(0, L)
        Gas[j][1] = rd.randint(1, 1000000)
    with open(filename, 'w') as f:
        f.write('1\n')
        parameters = "%d %d %d %d\n" % (N, F, T, L)
        f.write(parameters)
        np.savetxt(f, Gas, fmt='%d')
print("All the tests has been created successfully. Great Job!")
