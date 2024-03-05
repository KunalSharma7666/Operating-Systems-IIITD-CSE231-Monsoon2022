import matplotlib.pyplot as plt

arr = [[0,2407.79,80,1746.47,80,1741.94],[0,1985.34,20,1466.76,60,1470.97]]

plt.bar(0,1985.34,color="b",width=3,label="OTHER")
plt.bar(20,1466.76,color="r",width=3,label="FIFO")
plt.bar(60,1470.97,color="g",width=3,label="RR")


plt.legend()
plt.show()