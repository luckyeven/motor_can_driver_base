import matplotlib.pyplot as plt
import re


data_file = 'data.txt'
data = {}
with open(data_file, 'r') as file:
    for line in file:
        match = re.match(r'Joint (\d+) degree ([\d.-]+)', line)
        if match:
            joint_num = int(match.group(1))
            degree_value = float(match.group(2))
            if joint_num not in data:
                data[joint_num] = []
            data[joint_num].append(degree_value)


plt.figure(figsize=(10, 6))
for joint, values in data.items():
    plt.plot(values, label=f'Joint {joint}')

plt.xlabel('Time (arbitrary units)')
plt.ylabel('Degree')
plt.title('Joint Angle Data Over Time')
plt.legend()
plt.grid(True)
plt.show()
