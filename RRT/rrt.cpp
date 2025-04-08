#include "rrt.h"
#include <iostream>
#include <random>
#include <fstream> 


RRT::RRT(Point start, Point goal, Point minRange, Point maxRange, 
ftype stepSize, ftype goalSampleRate, 
int maxIter, std::vector<Circle> circles, 
std::vector<Rectangle> rectangles,ftype search_radius) :
    startPoint(start), goalPoint(goal), minRange(minRange), maxRange(maxRange),
    stepSize(stepSize), goalSampleRate(goalSampleRate), maxIter(maxIter), 
    rectangles(rectangles), circles(circles), search_radius(search_radius) {
        if (circles.size() > 0){
            std::ofstream obsFile("../output/circle_obstacles.csv");
            for (const auto& c : circles) {
                obsFile << c.center.x << "," << c.center.y << "," << c.radius << "\n";
            }
            obsFile.close();
        }

        if (rectangles.size() > 0){
            std::ofstream obsFile("../output/rectangle_obstacles.csv");
            for (const auto& r : rectangles) {
                obsFile << r.center.x << "," << r.center.y << "," << r.yaw << "," << r.length << "," << r.width << "\n";
            }
            obsFile.close();
        }
        std::srand(std::time(nullptr));
        startNode = new Node(start);
        nodes.push_back(startNode);        
    }

void RRT::setStart(Point start){
    startPoint = start;
    startNode = new Node(start);
    nodes.clear();
    nodes.push_back(startNode);
}

void RRT::setGoal(Point goal){
    goalPoint = goal;
    goalNode = new Node(goal);
}

// Generate a random number within the range
ftype RRT::randomCoordinate(ftype low, ftype high){
    static std::random_device rd;
    static std::mt19937 engine(rd());
    std::uniform_real_distribution<ftype> dist(low, high);
    return dist(engine);
}

Point RRT::getRandomPoint(){
    // Randomly select a point in the goal area
    ftype proToGoal = randomCoordinate(0.0, 1.0);
    if(proToGoal < goalSampleRate){
        return goalPoint;
    }
    // Randomly select a point in the entire area
    return Point(randomCoordinate(minRange.x, maxRange.x), randomCoordinate(minRange.y, maxRange.y));
}

Node* RRT::getNearestNode(const Point& point){
    Node* nearersNode = nodes[0];
    ftype minDistance = distance(nearersNode->pos, point);
    for (int i = 1; i < nodes.size(); i++){
        if(distance(nodes[i]->pos, point) < minDistance){
            nearersNode = nodes[i];
            minDistance = distance(nodes[i]->pos, point);
        }
    }
    return nearersNode;
}

bool RRT::isCollisionFree(const Point& from, const Point& to){
    for (const auto& c : circles){
        if(isSegmentIntersectCircle(from, to, c)){
            return false;
        }
    }
    return true;
}

Point RRT::stepFromTo(const Point& from, const Point& to, ftype stepSize){
    Point vectorFromTo = to - from;
    ftype distanceFromTo = distance(from, to);
    if(distanceFromTo < stepSize){
        return to;
    }
    return from + vectorFromTo / distanceFromTo * stepSize;
}


std::vector<Point> RRT::planning(){

    for(int i = 0; i < maxIter; i++){
        // Randomly select a point
        Point newRandomPoint = getRandomPoint();
        // Find the nearest node
        Node* nearestNode = getNearestNode(newRandomPoint);
        // Find the new point base on step size
        Point newPoint = stepFromTo(nearestNode->pos, newRandomPoint, stepSize);
        if(isCollisionFree(nearestNode->pos, newPoint)){
            Node* newNode = new Node(newPoint);
            newNode->parent = nearestNode;
            nodes.push_back(newNode);
        }
        //Check the distance between the new node and the goal, small then break
        if(distance(nodes.back()->pos, goalPoint) < stepSize){
            Node* goalNode = new Node(goalPoint);
            goalNode->parent = nodes.back();
            nodes.push_back(goalNode);
            break;
        }
    }

    std::vector<Point> path;
    Node* currentNode = nodes.back();
    // If path not found
    if (!(currentNode->pos == goalPoint)){
        std::cout << "No path found" << std::endl;
        return path;
    }
    while(currentNode != NULL){
        path.push_back(currentNode->pos);
        currentNode = currentNode->parent;
    }

    if (path.size() > 1){
        std::reverse(path.begin(), path.end());
    }

    std::ofstream outFile("../output/rrt_path.csv");
    for (const auto& p : path) {
        outFile << p.x << "," << p.y << "\n";
    }
    outFile.close();
    return path;
}









