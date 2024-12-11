import re

pattern = r"mul\((\d+),(\d+)\)"             # match mul(int,int) and add them to a list

with open("data.txt", 'r') as file:
    content = file.read()

matches = re.findall(pattern, content)

sum = 0

for expression in matches:                  # convert to int and sum up the multiplication
    sum += int(expression[0]) * int(expression[1])

print(sum)

