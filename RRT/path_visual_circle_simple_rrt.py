import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.patches import Circle


path = pd.read_csv('rrt_path.csv', header=None, names=["x", "y"])
obstacles = pd.read_csv('obstacles.csv', header=None, names=["x", "y", "r"])


fig, ax = plt.subplots(figsize=(8, 6))


ax.plot(path["x"], path["y"], 'r-', label='RRT Path')
ax.scatter(path["x"][0], path["y"][0], c='green', label='Start')
ax.scatter(path["x"].iloc[-1], path["y"].iloc[-1], c='red', label='Goal')


for _, row in obstacles.iterrows():
    circle = Circle((row["x"], row["y"]), row["r"], color='black', alpha=0.5)
    ax.add_patch(circle)


ax.set_aspect('equal')
ax.grid(True)
ax.legend()
ax.set_title("RRT Path with Obstacles")
plt.show()

