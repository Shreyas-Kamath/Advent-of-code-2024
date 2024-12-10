l1=[]
l2=[]

sum=0

# two lists

with open("data.txt", 'r') as file:
    for line in file:
        n1, n2 = map(int, line.split())
        l1.append(n1)
        l2.append(n2)

counts = {}
sum = 0

for num in l2:
    counts[num] = counts.get(num, 0) + 1

for num in l1:
    sum += num * counts.get(num, 0)

print(sum)


