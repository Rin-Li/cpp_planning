#include "rrt_star.h"
#include <iostream>
#include <fstream> 


std::vector<Point> RRTStar::planning(){
    for(int i = 0; i < maxIter; i++){
        // Randomly select a point
        Point newRandomPoint = getRandomPoint();
        // Find the nearest node
        Node* nearestNode = getNearestNode(newRandomPoint);
        // Find the new point base on step size
        Point newPoint = stepFromTo(nearestNode->pos, newRandomPoint, stepSize);
        if(isCollisionFree(nearestNode->pos, newPoint)){
            // Create a new node
            Node* newNode = new Node(newPoint);
            newNode->parent = nearestNode;
            
            newNode->cost = nearestNode->cost + distance(nearestNode->pos, newPoint);
            //Get near nodes
            std::vector<Node*> nearNodes = getNearNodes(newNode);
            //Rewire the tree
            rewire(newNode, nearNodes);
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

    std::ofstream outFile("rrt_path.csv");
    for (const auto& p : path) {
        outFile << p.x << "," << p.y << "\n";
    }
    outFile.close();
    return path;
}

std::vector<Node*> RRT::getNearNodes(Node* newNode){
    std::vector<Node*> nearNodes;
    for (const auto& node : nodes){
        if(distance(node->pos, newNode->pos) < search_radius){
            nearNodes.push_back(node);
        }
    }
    return nearNodes;
}

void RRTStar::rewire(Node* newNode, std::vector<Node*>& nearNodes){
    for (const auto& node : nearNodes){
        if(node->cost > newNode->cost + distance(node->pos, newNode->pos)){
            if (isCollisionFree(node->pos, newNode->pos)){
                node->cost = newNode->cost + distance(node->pos, newNode->pos);
                node->parent = newNode;
            }
        }
    }
}