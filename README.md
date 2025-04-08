# C++ planning algorithm
This is the implementation of the RRT and RRT* algorithms.
Currently, it supports RRT and RRT* with circular obstacles. Further expansion is planned.

```
g++ main.cpp RRT/rrt.cpp RRT/rrt_star.cpp geometry/geometry.cpp -I . -o planner -std=c++17
\\
./planner
```

For visual, run the ```path_visual.py``` in the RRT file.
