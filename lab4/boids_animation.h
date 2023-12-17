#ifndef BOIDS_ANIMATION
#define BOIDS_ANIMATION

#include <iostream>
#include <vector>

using namespace std;

struct Boid{
    int id;
    vector<float> position;
    vector<float> velocity;
};

// the function to follow the leaders for boids (rule 1)
vector<float> follow_the_leader(Boid boid);

// the function to fetch the leader positions from the leader matrix
void assign_leader_position(vector <float> leader_matrix);

// the function to avodicance the colission between each other (rule 2)
vector<float> collision_avoidance(Boid curr_boid);

// the helper function to calculate distance between each other
float distance(Boid boid_1, Boid boid_2);

// the function for velocity matching (rule 3)
vector<float> velocity_matching(Boid boid);

// the function for flock centring (rule 4)
vector<float> flock_centering(Boid boid);

// the initialization function for boids
void init_boids(vector <vector<float>> boids_position);

// the function to animate the boids
void animate_boids(vector <float> leader_boid);

// the function to calculate the average for position and velocity based on the argument
vector<float> calc_avg(Boid boid, bool if_position);

// the function to get the boid matrix
vector<float> get_boid_matrix(Boid boid);

#endif