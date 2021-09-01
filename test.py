import random
f1 = open('ip_test.txt', 'w+')
N = 1000000
ip_list = []
f1.write(str(N) + " " + str(int(random.random()*(N-1))) + "\n")
for ip4 in range(255):
	for ip3 in range(255):
		if (random.random()<0.5):
			continue
		for ip2 in range(10):
			for ip1 in range(20):
				ip =str(ip4)+'.'+str(ip3)+'.'+str(ip2)+'.'+str(ip1)+"\n"
				ip_list.append(ip)
				if len(ip_list) == N:
					random.shuffle(ip_list)
					f1.writelines(ip_list)
					exit()
	
