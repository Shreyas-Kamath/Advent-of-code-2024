l1=[]
l2=[]

sum=0

# two lists

with open("data.txt", 'r') as file:
    for line in file:
        n1, n2 = map(int, line.split())
        l1.append(n1)
        l2.append(n2)

# sort them both

l1.sort()
l2.sort()

# iterate through both using zip()

for num1,num2 in zip(l1,l2):
    sum += abs(num1-num2)

print(sum)


