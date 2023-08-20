import matplotlib.pyplot as plt
import numpy as np
import math
import sys

fileName = sys.argv[1]

with open(fileName, "r") as f:
    numbers = [int(line.strip()) for line in f]


loggedNumbers = [math.log(num) for num in numbers if num > 0]

plt.figure(figsize=(10, 6))
plt.plot(numbers if (input("Would you like to log the y axis (y/n): ") in ["n", "N"]) else loggedNumbers, linestyle='-')
plt.title("Collatz sequence for: " + str(numbers[0]))
plt.xlabel("Step")
plt.ylabel("Number")
plt.grid(True)
plt.show()



