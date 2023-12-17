#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <random>

#include "boids_animation.h"
#include "utils.h"

using namespace std;

// global variables
vector <float> leader_position(3);
vector <Boid> vec_boids;

float dt = 0.05;
float avoidance_threshold = 3;

// the function to follow the leaders for boids (rule 1)
vector<float> follow_the_leader(Boid boid){
    vector <float> vec_lf(3);

    // calculate the position difference
    for(int i=0;i<3;i++)
        vec_lf[i] = (leader_position[i] - boid.position[i]);

    // return the difference vector
    return vec_lf;
}

// the function to fetch the leader positions from the leader matrix
void assign_leader_position(vector <float> leader_matrix){
    leader_position[0] = leader_matrix[12];
    leader_position[1] = leader_matrix[13];
    leader_position[2] = leader_matrix[14]; 
}

// the function to avodicance the colission between each other (rule 2)
vector<float> collision_avoidance(Boid curr_boid) {
    vector<float> avoidance_vector(3, 0);

    for (auto& boid : vec_boids) {
        if (boid.id == curr_boid.id)
            continue;

        // calculate the distance
        float d = distance(curr_boid, boid);

        // based on the avoidance threshold calculate the avoidance vector
        if (d < avoidance_threshold)
            for (int i = 0; i < 3; i++)
                avoidance_vector[i] -= (boid.position[i] - curr_boid.position[i]);
    }

    // return avoidance vector
    return avoidance_vector;
}

// the helper function to calculate distance between each other
float distance(Boid boid_1, Boid boid_2){

    // calculate the distance between boids
    float distance = sqrt(
        pow(boid_1.position[0] - boid_2.position[0], 2) +
        pow(boid_1.position[1] - boid_2.position[1], 2) +
        pow(boid_1.position[2] - boid_2.position[2], 2)
    );

    // return the distance
    return distance;
}

// the function for velocity matching (rule 3)
vector<float> velocity_matching(Boid boid){
    // calculate average velocity
    vector <float> avg_velocity = calc_avg(boid,0);

    vector <float> vec_vm(3);
    
    // calculate difference difference between average and current velocity
    for(int i=0;i<3;i++)
        vec_vm[i] = (avg_velocity[i] - boid.velocity[i]);

    // return the velocity difference vector
    return vec_vm;
}

// the function for flock centring (rule 4)
vector<float> flock_centering(Boid boid){
    // calculate average position
    vector <float> avg_position = calc_avg(boid,1);

    vector <float> vec_fc(3);

    // calculate difference difference between average and current position
    for(int i=0;i<3;i++)
        vec_fc[i] = (avg_position[i] - boid.position[i]);

    // return the difference vector
    return vec_fc;
}

// the initialization function for boids
void init_boids(vector <vector<float>> boids_position){
    
    // resize the global boid vector
    vec_boids.resize(boids_position.size());
    
    // assign the corresponding id, position and random velocity for each boid
    for(int i=0;i<vec_boids.size();i++){
        vec_boids[i].id = i;
        vec_boids[i].position = boids_position[i];
        vec_boids[i].velocity = {
                                    static_cast<float>(rand()) / RAND_MAX * 2 - 1,
                                    static_cast<float>(rand()) / RAND_MAX * 2 - 1,
                                    static_cast<float>(rand()) / RAND_MAX * 2 - 1
                                };

    }
}

// the function to animate the boids
void animate_boids(vector <float> leader_boid){

    // assign the leader position to the local global variable
    assign_leader_position(leader_boid);

    for(auto& boid: vec_boids){
        // get the vectors from each rule
        vector <float> leader_direction = follow_the_leader(boid);
        vector <float> vec_va = collision_avoidance(boid);
        vector <float> vec_fc = flock_centering(boid);
        vector <float> vec_vm = velocity_matching(boid);

        // calculate the new velocity and position based on the rules with corresponding weighs
        for(int i=0;i<3;i++){
            boid.velocity[i] +=  1e-1 * leader_direction[i] + 1e-2 *  vec_va[i] + 1e-4 * vec_fc[i] + 1e-4 * vec_vm[i];
            boid.position[i] += boid.velocity[i] * dt;
        }

        //animate each boid as sphere
        glPushMatrix();
        glMultMatrixf(get_boid_matrix(boid).data());
        glutSolidSphere(0.2,30,30);
        glPopMatrix();
    }
}

// the function to calculate the average for position and velocity based on the argument
vector<float> calc_avg(Boid boid, bool if_position){
    vector <float> vec_average(3,0);

    // calculate the sum of velocities or positions based on the function argument
    for(int i=0;i<3;i++){
        for(int j=0;j<vec_boids.size();j++){
            if(j == boid.id)
                continue;

            if (if_position)
                vec_average[i] += vec_boids[j].position[i];
            else
                vec_average[i] += vec_boids[j].velocity[i];
        }
    }

    // calculate average
    for(auto v: vec_average)
        v = (float) v / (vec_boids.size()-1);
    
    // return the average vector
    return vec_average;
}

// the function to get the boid matrix
vector<float> get_boid_matrix(Boid boid){
    
    // assign the boid matrix
    vector <vector<float>> boid_matrix = {
        {1, 0, 0, boid.position[0]},
        {0, 1, 0, boid.position[1]},
        {0, 0, 1, boid.position[2]},
        {0, 0, 0, 1}
    };
    
    // return the flattened boid matrix
    return flatten_matrix(boid_matrix);
}

