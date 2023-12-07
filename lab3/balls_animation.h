#ifndef BALLS
#define BALLS

#include <iostream>
#include <vector>

using namespace std;

extern float coeff_loss;
extern vector<float> acc;
extern float dt;

// define the struct for the balls
struct Ball {
    int id;
    vector<float> position;
    vector<float> velocity;
    float radius;
    float mass;
};

// the function to initialize the balls, and store them in vectors
void init_balls(vector <vector<float>> balls_positions, vector <vector<float>> balls_velocity, float ball_radius, float ball_mass);

// the function to get the matrix of the ball with positions and flatten it
vector<float> get_ball_matrix(Ball ball);

// the function to check if ball collides with the walls, if it is multiply the velocity with the loss of energy
void check_wall_collision(Ball& ball);

// the function to update the velocities if there is a collision between balls
void check_balls_collision(Ball& ball);

// helper function to calculate velocity difference
vector<float> calc_vel_difference(Ball& ball_1, Ball& ball_2);

// helper function to calculate position difference
vector<float> calc_pos_difference(Ball& ball_1, Ball& ball_2);

// helper function to calculate the square of the magnitude of a vector
float calc_mag_sq(vector<float> vec);

// the boolean function to see if there is a collision between 2 balls
bool if_collision(const Ball& ball_1, const Ball& ball_2);

// the function to animate the balls
void animate_balls();

#endif