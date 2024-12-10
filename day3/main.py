import re

# Regex pattern to match mul(X, Y)
pattern = r"mul\((\d+),(\d+)\)"

# Read the file content
with open("data.txt", 'r') as file:
    content = file.read()

# Initialize variables
enabled = True  # Start with mul instructions enabled
sum_result = 0

# Iterate through the content character by character
i = 0
while i < len(content):
    if content[i:i+4] == "do()":
        enabled = True  # Enable future mul instructions
        i += 4  # Move past the "do()" instruction
    elif content[i:i+7] == "don't()":
        enabled = False  # Disable future mul instructions
        i += 7  # Move past the "don't()" instruction
    else:
        # Search for mul(X, Y) using regex if mul instructions are enabled
        match = re.match(pattern, content[i:])
        if match and enabled:
            num1 = int(match.group(1))
            num2 = int(match.group(2))
            sum_result += num1 * num2
            i += match.end()  # Move past the matched mul() instruction
        else:
            i += 1  # Move to the next character if no match

# Output the final sum result
print(sum_result)
