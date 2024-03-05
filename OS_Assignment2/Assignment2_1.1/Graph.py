import matplotlib.pyplot as plt

arr = [[0,19.27,10,13.23,10,6.94],[0,19.39,99,13.30,99,7.008],[0,19.11,30,12.90,60,6.99],[0,19.47,60,7.30,30,14.17],[0,18.53,15,12.43,75,6.87],[0,19.64,75,7.83,15,14.78]]

plt.bar(0,8.6,color="b",width=1,label="OTHER")
plt.bar(30,8.2,color="g",width=1,label="RR")
plt.bar(60,7.9,color="r",width=1,label="FIFO")

plt.legend()
plt.show()