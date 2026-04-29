#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>
#include "../controllers/LQRController.hpp"

int main() {
    const int n = 4;
    const int m = 2;
    const int p = 2;
    const float dt = 0.1f;
    const int steps = 200;

    std::vector<float> A = {
        1, 0, dt, 0,
        0, 1, 0, dt,
        0, 0, 1,  0,
        0, 0, 0,  1
    };

    std::vector<float> B = {
        0, 0,
        0, 0,
        dt, 0,
        0, dt
    };

    // No C needed in LQR-only

    std::vector<float> Q = {
        10, 0, 0, 0,
        0, 10, 0, 0,
        0, 0,  1, 0,
        0, 0,  0, 1
    };

    std::vector<float> R = {
        0.1f, 0,
        0, 0.1f
    };

    LQRController lqr(n, m, p);
    lqr.setSystemMatrices(A, B);
    lqr.setCostMatrices(Q, R);

    std::vector<float> r = {1, 1};
    lqr.setTarget(r); // stored only, not used by LQR

    std::vector<float> state = {1, 0, 0, 0};
    std::vector<float> targetState = {-1, 2, 0, 0};

    // wind = constant + sin + gusts
    const float windAx_const = 0.05f;
    const float windAy_const = -0.03f;

    std::mt19937 rng(42);
    std::normal_distribution<float> gustNoise(0.0f, 0.02f);

    const float windAx_sin_amp = 0.03f;
    const float windAy_sin_amp = 0.02f;
    const float windFreq = 0.15f;

    std::ofstream file("lqr_drone_2d_wind.csv");
    file << "t,posX,posY,velX,velY,ux,uy,windAx,windAy\n";

    for (int k = 0; k < steps; ++k) {
        float t = k * dt;

        float windAx = windAx_const
                     + windAx_sin_amp * std::sin(2.0f * 3.1415926f * windFreq * t)
                     + gustNoise(rng);

        float windAy = windAy_const
                     + windAy_sin_amp * std::cos(2.0f * 3.1415926f * windFreq * t)
                     + gustNoise(rng);

        std::vector<float> output = {state[0], state[1]}; // optional, not used by LQR

        std::vector<float> stateError(n);
        for (int i = 0; i < n; ++i) stateError[i] = state[i] - targetState[i];

        lqr.setCurrentState(stateError);
        lqr.setCurrentOutput(output); // stored only, not used by LQR

        std::vector<float> control = lqr.compute(dt);

        std::vector<float> nextState(n, 0.0f);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                nextState[i] += A[i*n + j] * state[j];
            for (int j = 0; j < m; ++j)
                nextState[i] += B[i*m + j] * control[j];
        }

        // affect velocity
        nextState[2] += dt * windAx * 10;
        nextState[3] += dt * windAy * 10;

        state = nextState;

        file << t << ","
             << state[0] << "," << state[1] << ","
             << state[2] << "," << state[3] << ","
             << control[0] << "," << control[1] << ","
             << windAx << "," << windAy << "\n";
    }

    file.close();
    std::cout << "CSV generated: lqr_drone_2d_wind.csv\n";
    return 0;
}