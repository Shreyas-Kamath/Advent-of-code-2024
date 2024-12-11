import re

with open('data.txt', 'r') as file:
    content = file.read()

# pattern = r"mul\((\d+),(\d+)\)"
pattern = r"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))"

enable_multiplication = True
 
sum = 0

data = re.findall(pattern, content)
for pair in data:
    match pair[0]:
        case "do()":
            enable_multiplication = True
        case "don't()":
            enable_multiplication = False
        case _ if enable_multiplication:
            sum += int(pair[1]) * int(pair[2])

print(sum)