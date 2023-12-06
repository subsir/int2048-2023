import random
f = open ("in.in", "w")
g = open ("out.out", "w")
for i in range(100000):
  a = random.randint(-1000000000000000000000000000,1000000000000000000000000000)
  b = random.randint(-1000000000000,1000000000000)
  f.write(str(a) + " " + str(b) + "\n")
  g.write(str(a // b) + "\n")
f.close()
g.close()