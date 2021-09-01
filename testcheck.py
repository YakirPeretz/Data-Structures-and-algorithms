
# Task1 check
for i in range(0, 200):
    testpass = "Task 1 test %d correct" % i
    testfail = "Task 1 test %d fail" % i
    filename1 = "D:/Algo/myoutput/test1/q1myOutput%d.txt" % i
    filename2 = "D:/Algo/progoutput/test1/q1Output%d.txt" % i
    with open(filename1) as f1:
        line1 = f1.readlines()
    with open(filename2) as f2:
        line2 = f2.readlines()
    if line1 != line2:
        print(testfail)
    else:
        print(testpass)

# Task2 check
for i in range(50):
    testpass = "Task 2 test %d correct" % i
    testfail = "Task 2 test %d fail" % i
    filename1 = "D:/Algo/myoutput/test2/q2myOutput%d.txt" % i
    filename2 = "D:/Algo/progoutput/test2/q2Output%d.txt" % i
    with open(filename1) as f1:
        line1 = f1.readlines()
    with open(filename2) as f2:
        line2 = f2.readlines()
    if line1 != line2:
        print(testfail)
        print("my out:", line1)
        print("there output:", line2)
    else:
        print(testpass)

# Task3 check
for i in range(150):
    testpass = "Task 3 test %d correct" % i
    testfail = "Task 3 test %d fail" % i
    filename1 = "D:/Algo/myoutput/test3/q3myOutput%d.txt" % i
    filename2 = "D:/Algo/progoutput/test3/q3Output%d.txt" % i
    with open(filename1) as f1:
        line1 = f1.readlines()
    with open(filename2) as f2:
        line2 = f2.readlines()
    if line1 != line2:
        print(testfail)
        print("my out:", line1)
        print("there output:", line2)
    else:
        print(testpass)

