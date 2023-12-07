#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>
#include <algorithm>

#include "opengl_conf.h"
#include "utils.h"
#include "balls_animation.h"

using namespace std;

// global variables
float coeff_loss = 1;

vector<float> acc = {0, -9.8, 0}; //EARTH GRAVITATION

float dt = 0.03;

vector <Ball> vec_balls;

// the function to get the matrix of the ball with positions and flatten it
vector<float> get_ball_matrix(Ball ball) {
    
    vector <vector<float>> ball_matrix = {{
        {1, 0, 0, ball.position[0]},
        {0, 1, 0, ball.position[1]},
        {0, 0, 1, ball.position[2]},
        {0, 0, 0, 1}
    }};
    
    return flatten_matrix(ball_matrix);
}

// the function to check if wall collides with the walls, if it is multiply the velocity with the loss of energy
void check_wall_collision(Ball& ball){
    if (abs(ball.position[0]) + ball.radius > WALL_LENGTH)
        ball.velocity[0] *= -coeff_loss;

    if(ball.position[1] <= ball.radius)
        ball.velocity[1] *= -coeff_loss;
    
    if (abs(ball.position[2]) + ball.radius > WALL_LENGTH)
        ball.velocity[2] *= -coeff_loss;
}

// the function to update the velocities if there is a collision between balls
void check_balls_collision(Ball& curr_ball) {
    for (auto& other_ball : vec_balls) {
        // skip to next ball if there is no collision or id of the ball is less than current ball
        if (!if_collision(curr_ball, other_ball) || other_ball.id <= curr_ball.id)
            continue;

        // calculate the position and velocity differences using helper functions
        vector<float> pos_diff = calc_pos_difference(curr_ball, other_ball);
        vector<float> vel_diff = calc_vel_difference(curr_ball, other_ball);

        // calculate the impulse
        float impulse = 2 * dot_product(vel_diff, pos_diff) / (calc_mag_sq(pos_diff) * (curr_ball.mass + other_ball.mass));

        // update velocities
        for (int i = 0; i < 3; i++) {
            curr_ball.velocity[i] -= impulse * other_ball.mass * pos_diff[i];
            other_ball.velocity[i] += impulse * curr_ball.mass * pos_diff[i];
        }
    }
}

// helper function to calculate the square of the magnitude of a vector
float calc_mag_sq(vector<float> vec){
    float mag_sq = 0;

    for (float val : vec)
        mag_sq += pow(val,2);

    return mag_sq;
}

// helper function to calculate position difference
vector<float> calc_pos_difference(Ball& ball_1, Ball& ball_2){
    vector <float> pos_diff(3);

    for(int i=0;i<3;i++)
        pos_diff[i] = ball_1.position[i] - ball_2.position[i];

    return normalize_vector(pos_diff);
}

// helper function to calculate velocity difference
vector<float> calc_vel_difference(Ball& ball_1, Ball& ball_2){
    vector<float> vel_diff(3);
    
    for (int i = 0; i < 3; i++)
        vel_diff[i] = ball_1.velocity[i] - ball_2.velocity[i];
    
    return vel_diff;
}

// the boolean function to see if there is a collision between 2 balls
bool if_collision(const Ball& ball_1, const Ball& ball_2) {
    float distance = sqrt(
        pow(ball_1.position[0] - ball_2.position[0], 2) +
        pow(ball_1.position[1] - ball_2.position[1], 2) +
        pow(ball_1.position[2] - ball_2.position[2], 2)
    );

    return distance < (ball_1.radius + ball_2.radius);
}

// the function to initialize the balls, and store them in vectors
void init_balls(vector <vector<float>> balls_positions, vector <vector<float>> balls_velocity, float ball_radius, float ball_mass){
    
    vec_balls.resize(balls_positions.size());
    
    for(int ball=0;ball<vec_balls.size();ball++){
        vec_balls[ball].id = ball;
        vec_balls[ball].position = balls_positions[ball];
        vec_balls[ball].velocity = balls_velocity[ball];
        vec_balls[ball].radius = ball_radius;
        vec_balls[ball].mass = ball_mass;
    }
}

// the function to animate the balls
void animate_balls(){
    for(int ball=0;ball<vec_balls.size();ball++){
        glPushMatrix();

        // calculate the new position and velocity
        for(int i=0;i<3;i++){
            vec_balls[ball].position[i] += (vec_balls[ball].velocity[i] * dt);
            vec_balls[ball].velocity[i] += (acc[i] * dt);
        }

        // check if there is a collision with walls or between balls, if there is change the velocity
        check_wall_collision(vec_balls[ball]);
        check_balls_collision(vec_balls[ball]);

        // apply the ball's transformation matrix
        glMultMatrixf(get_ball_matrix(vec_balls[ball]).data());
        
        // change the color of the balls
        GLfloat diffColor[] = {0.0, 1.0, 0.0, 1.0};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffColor);

        // draw the ball as sphere with its radius
        glutSolidSphere(vec_balls[ball].radius, 30, 30);

        glPopMatrix();
    }
}