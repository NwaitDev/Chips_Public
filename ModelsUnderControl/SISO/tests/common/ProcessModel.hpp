#ifndef PROCESS_MODEL_HPP
#define PROCESS_MODEL_HPP

#include <random>

class FirstOrderProcess {
public:
    FirstOrderProcess(float a, float b, float dt)
        : m_a(a), m_b(b), m_dt(dt), m_y(0.0f),
          m_disturbance(0.0f),
          m_noiseAmplitude(0.0f),
          m_generator(m_rd()),
          m_noiseDist(-1.0f, 1.0f) {}

    void reset(float y0 = 0.0f) {
        m_y = y0;
    }

    void setDisturbance(float d) {
        m_disturbance = d;
    }

    void setNoiseAmplitude(float amp) {
        m_noiseAmplitude = amp;
    }

    float update(float u) {
        m_y += m_dt * (-m_a * m_y + m_b * u + m_disturbance);
        return m_y;
    }

    float output() const {
        return m_y;
    }

    float measuredOutput() {
        float noise = m_noiseAmplitude * m_noiseDist(m_generator);
        return m_y + noise;
    }

private:
    float m_a; // Constante de dissipation
    float m_b; // Gain du système
    float m_dt; // Pas de simulation
    float m_y; // État interne du système

    float m_disturbance;
    float m_noiseAmplitude;

    std::random_device m_rd;
    std::mt19937 m_generator;
    std::uniform_real_distribution<float> m_noiseDist;
};

#endif
