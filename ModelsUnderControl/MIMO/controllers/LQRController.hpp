/**
 * @file LQRController.hpp
 * 
 * @brief Discrete-time MIMO LQR controller
 *
 * This controller implements a discrete-time Linear Quadratic Regulator (LQR)
 *
 * Discrete model:
 *   x_{k+1} = A x_k + B u_k
 *
 * Control law:
 *   u_k = -K x_k
 *
 * The gain K is computed by solving the Discrete Algebraic Riccati Equation (DARE)
 * for the provided matrices A, B, Q, R
 */

#ifndef LQR_CONTROLLER_HPP
#define LQR_CONTROLLER_HPP

#include "../IControllerMIMO.hpp"
#include "../utils/LinearAlgebra.hpp"

#include <vector>

class LQRController : public IControllerMIMO {
public:
    /**
     * @brief Construct a new LQRController object
     *
     * Initializes:
     * - A: zeros (n x n)
     * - B: zeros (n x m)
     * - Q: identity (n x n)
     * - R: identity (m x m)
     * - x, y, r, u: zero vectors with correct sizes
     * - K: zeros (m x n)
     *
     * @param nStates  Number of states (n), must be > 0
     * @param nInputs  Number of inputs (m), must be > 0
     * @param nOutputs Number of outputs (p), must be > 0 
     *
     * @throws std::runtime_error if any dimension is invalid
     */
    LQRController(int nStates, int nInputs, int nOutputs);

    /**
     * @brief Destructor
     */
    ~LQRController() override = default;

    /**
     * @brief Get the state size object
     * 
     * @return int Number of states
     */
    int getStateSize() const override { return _n; }

    /**
     * @brief Get the input size object
     * 
     * @return int Number of inputs
     */
    int getInputSize() const override { return _m; }

   /**
     * @brief Get the output size object
     * 
     * @return int Number of outputs
     */
    int getOutputSize() const override { return _p; }

    /**
     * @brief Set discrete-time system matrices A and B
     *
     * Defines:
     *   x_{k+1} = A x_k + B u_k
     *
     * @param A Row-major matrix of size n x n
     * @param B Row-major matrix of size n x m
     *
     * @throws std::runtime_error if A or B size is invalid
     *
     * @note Matrix A defines the state evolution, while B defines how inputs affect the state
     */
    void setSystemMatrices(const std::vector<float>& A, const std::vector<float>& B);

    /**
     * @brief Set cost matrices Q and R
     *
     * Cost:
     *   J = sum_k ( x_k^T Q x_k + u_k^T R u_k )
     *
     * @param Q Row-major matrix of size n x n
     * @param R Row-major matrix of size m x m
     *
     * @throws std::runtime_error if Q or R size is invalid
     * 
     * @note Q penalizes state deviations, while R penalizes control effort
     * Both must be positive semi-definite for a valid LQR problem
     */
    void setCostMatrices(const std::vector<float>& Q, const std::vector<float>& R);

    /**
     * @brief Configure Riccati (DARE) solver parameters
     *
     * @param maxIterations Maximum number of iterations, must be > 0
     * @param tolerance     Convergence tolerance, must be > 0
     *
     * @throws std::runtime_error if parameters are invalid
     */
    void setRiccatiOptions(int maxIterations, double tolerance);

    // --- IControllerMIMO ---

    const std::vector<float>& getTarget() const override { return _r; }
    const std::vector<float>& getCurrentOutput() const override { return _y; }
    const std::vector<float>& getCurrentState() const override { return _x; }
    const std::vector<float>& getControl() const override { return _u; }

    void setTarget(const std::vector<float>& r) override;
    void setCurrentOutput(const std::vector<float>& y) override;
    void setCurrentState(const std::vector<float>& x) override;

    std::vector<float> compute(float dt) override;
    void reset() override;

private:
    int _n; // states
    int _m; // inputs
    int _p; // outputs

    linalg::Mat _A; // n x n
    linalg::Mat _B; // n x m

    linalg::Mat _Q; // n x n
    linalg::Mat _R; // m x m

    std::vector<float> _x; // size n
    std::vector<float> _y; // size p
    std::vector<float> _r; // size p
    std::vector<float> _u; // size m

    linalg::Mat _K; // m x n

    int _maxIter    = 200;
    double _tol     = 1e-9;
    bool _dirtyGain = true;

    /**
     * @brief Recompute the gain K if dirty
     *
     * Checks that Q is n x n and R is m x m, then:
     * - solve DARE to get P
     * - compute K = (R + B' P B)^(-1) * (B' P A)
     *
     * @throws std::runtime_error if sizes are invalid
     */
    void recomputeGainOrThrow();

    /**
     * @brief Solve the Discrete Algebraic Riccati Equation (DARE)
     *
     * The solver uses an iterative approach to obtain P such that:
     *   P = A' P A - A' P B (R + B' P B)^(-1) B' P A + Q
     *
     * (Here A' is the transpose of A)
     *
     * @param A       State transition matrix (n x n)
     * @param n       State dimension
     * @param B       Input matrix (n x m)
     * @param m       Input dimension
     * @param Q       State cost matrix (n x n)
     * @param R       Input cost matrix (m x m)
     * @param maxIter Maximum number of iterations
     * @param tol     Convergence tolerance
     * @return Riccati solution matrix P (n x n)
     */

    static linalg::Mat solveDARE(const linalg::Mat& A, int n,
                                 const linalg::Mat& B, int m,
                                 const linalg::Mat& Q, const linalg::Mat& R,
                                 int maxIter, double tol);

    /**
     * @brief Compute LQR gain K from Riccati solution P
     *
     * The gain is computed as:
     *   K = (R + B' P B)^(-1) * (B' P A)
     *
     * @param A State transition matrix (n x n)
     * @param n State dimension
     * @param B Input matrix (n x m)
     * @param m Input dimension
     * @param P Riccati solution matrix (n x n)
     * @param R Input cost matrix (m x m)
     * @return Gain matrix K (m x n)
     */
    static linalg::Mat computeK(const linalg::Mat& A, int n,
                                const linalg::Mat& B, int m,
                                const linalg::Mat& P, const linalg::Mat& R);
};

#endif