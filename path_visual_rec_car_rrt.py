import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.patches import Rectangle
import numpy as np


CAR_LENGTH = 4.0
CAR_WIDTH = 2.0


path = pd.read_csv('output/rrt_path.csv', header=None, names=["x", "y"])
obstacles = pd.read_csv('output/rectangle_obstacles.csv', header=None, names=["x", "y", "yaw", "length", "width"])


fig, ax = plt.subplots(figsize=(8, 6))
ax.plot(path["x"], path["y"], 'r-', label='RRT Path')
ax.scatter(path["x"][0], path["y"][0], c='green', label='Start')
ax.scatter(path["x"].iloc[-1], path["y"].iloc[-1], c='red', label='Goal')


for _, row in obstacles.iterrows():
    cx, cy = row["x"], row["y"]
    yaw = row["yaw"]
    length = row["length"]
    width = row["width"]

    dx = -length / 2
    dy = -width / 2

    rect = Rectangle((dx, dy), length, width,
                     angle=np.degrees(yaw),
                     color='black', alpha=0.5)

    t = plt.matplotlib.transforms.Affine2D() \
        .rotate_around(0, 0, yaw) \
        .translate(cx, cy) + ax.transData
    rect.set_transform(t)
    ax.add_patch(rect)


for i in range(len(path) - 1):
    x1, y1 = path.iloc[i]["x"], path.iloc[i]["y"]
    x2, y2 = path.iloc[i + 1]["x"], path.iloc[i + 1]["y"]
    yaw = np.arctan2(y2 - y1, x2 - x1)

    dx = -CAR_LENGTH / 2
    dy = -CAR_WIDTH / 2

    car = Rectangle((dx, dy), CAR_LENGTH, CAR_WIDTH,
                    color='blue', alpha=0.3)

    t = plt.matplotlib.transforms.Affine2D() \
        .rotate_around(0, 0, yaw) \
        .translate(x1, y1) + ax.transData
    car.set_transform(t)
    ax.add_patch(car)


ax.set_aspect('equal')
ax.grid(True)
ax.legend()
ax.set_title("RRT Path with Rectangle Obstacles and Simple Cars")
plt.show()
