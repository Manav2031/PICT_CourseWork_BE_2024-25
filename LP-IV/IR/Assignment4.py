from collections import defaultdict
import re

# Sample dataset (you can replace this with your actual data)
data = ["Hello World!", "MapReduce in Python", "Counting characters like a pro."]

# Map function: Emits (key, value) pairs where key is a lowercase letter and value is 1
def map_function(dataset):
    intermediate = []
    for line in dataset:
        # Remove non-alphabetic characters and convert to lowercase
        letters = re.findall(r'[a-zA-Z]', line.lower())
        for letter in letters:
            intermediate.append((letter, 1))
    return intermediate

# Reduce function: Sums the counts for each letter
def reduce_function(intermediate_data):
    result = defaultdict(int)
    for key, value in intermediate_data:
        result[key] += value
    return result

# Map step
intermediate_data = map_function(data)

# Reduce step
result = reduce_function(intermediate_data)

# Output the result
for letter, count in result.items():
    print(f"{letter}: {count}")