#include <iostream>
#include <vector>
#include <string>
#include <nlopt.hpp> // ensure this matches your include path
#include "globals.h"
// Sample objective function: negative of a 2D Gaussian (maximized)
double objective(const std::vector<double> &x, std::vector<double> &grad, void *data) {
    return -((x[0] - 1.0)*(x[0] - 1.0) + (x[1] - 2.0)*(x[1] - 2.0));
}
int seq_num = -1;  // <-- this is the definition (not just extern)

int main(int argc, char* argv[]) {

    // You need to ensure your modified ISRES uses this output_dir internally
    // e.g., pass it via a global, static variable, or config if you edited ISRES code
    if (argc > 1)
        seq_num = atoi(argv[1]);

    const int dim = 2;
    std::vector<double> x(dim, 0.0);  // Initial guess
    double maxf;

    nlopt::opt opt(nlopt::GN_ISRES, dim);
    opt.set_max_objective(objective, nullptr);
    opt.set_lower_bounds(std::vector<double>(dim, -5.0));
    opt.set_upper_bounds(std::vector<double>(dim, 5.0));
    opt.set_maxeval(1000);
    opt.set_population(100);

    // Optionally: set seed or other params
    // opt.set_seed(...);

    nlopt::result result = opt.optimize(x, maxf);

    std::cout << "Best x found: ";
    for (double xi : x) std::cout << xi << " ";
    std::cout << "\nBest objective: " << maxf << "\n";

    return 0;
}

