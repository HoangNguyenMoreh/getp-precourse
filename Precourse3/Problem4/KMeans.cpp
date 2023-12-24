// KMeans.cpp
#include "KMeans.h"
#include "Point.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

// TODO: Fix the random seed to ensure consistent results across different program executions.
const int MAX_CORRDINATE = 50;
const unsigned int RANDOM_INIT_SEED = 123456;
bool isSeedInitialized = false;

float randFloat() {
    if (!isSeedInitialized) {
        std::srand(RANDOM_INIT_SEED);
        isSeedInitialized = true;
    }
    float random_ratio = static_cast<float>(rand()) / RAND_MAX;
    return random_ratio * MAX_CORRDINATE;
}

KMeans::KMeans(int num_points, int k) : k(k) {
    cluster_assignment.clear();
    generateRandomDataPoints(num_points);
    initializeCentroids();
}

void KMeans::initializeCentroids() {
     // TODO: Implement this function
    // Initialize the centroids of clusters randomly.
    centroids.clear();
    for (int i=1 ; i<=k ; ++i)
    {
        centroids.push_back(Point(randFloat(), randFloat()));
    }
}

void KMeans::generateRandomDataPoints(int num_points) {
    // TODO: Implement this function
    // Generate a given number of random data points within a specified range ( 0< x, y<50)
    data_points.clear();
    for (int i=1 ; i <= num_points ; ++i)
    {
        data_points.push_back(Point(randFloat(), randFloat()));
    }
}

void KMeans::assignToClusters() {
    // TODO: Implement this function
    // Assign each point to a cluster of the nearest centroid
    cluster_assignment.clear();
    for(size_t i=0 ; i<data_points.size() ; ++i)
    {
        Point point = data_points[i];
        double min_distance = calculateDistance(point, centroids[0]);
        int closest_centroid = 0;
        for(int i=1 ; i<k ; ++i)
        {
            double cur_distance = calculateDistance(point, centroids[i]);
            if (min_distance > cur_distance)
            {
                min_distance = cur_distance;
                closest_centroid = i;
            }
        }
        cluster_assignment.push_back(closest_centroid);
    }
}

void KMeans::updateCentroids() {
    // TODO: Implement this function
    // Update the centroids of clusters based on the current assignment of data points.
    std::vector<Point> new_centroids(k, Point(0, 0));
    std::vector<int> cluster_size(k, 0);
    for(size_t i=0 ; i<data_points.size() ; ++i)
    {
        int cluster_id = cluster_assignment[i];
        cluster_size[cluster_id]++;
        new_centroids[cluster_id].x += data_points[i].x;
        new_centroids[cluster_id].y += data_points[i].y;
    }
    for(int i=0 ; i<k ; i++)
        if (cluster_size[i] > 0)
        {
            new_centroids[i].x /= (float)cluster_size[i];
            new_centroids[i].y /= (float)cluster_size[i];
        }
    centroids = new_centroids;
}

double KMeans::calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

void KMeans::run(int max_iterations) {
    // TODO: Implement K-means algorithm and print the coordinates of each cluster centroid After the maximum number of iterations
    for (int i=0 ; i<max_iterations ; ++i)
    {
        assignToClusters();
        updateCentroids();
    }

    for(Point centroid: centroids)
    {
        std::cout<<"("<<centroid.x<<", "<<centroid.y<<")\n";
    }

}
