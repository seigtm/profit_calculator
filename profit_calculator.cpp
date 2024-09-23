/**
 * @file profit_calculator.cpp
 * @brief Profit calculation and reporting based on orders and demand.
 */

#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <vector>

namespace setm {

/**
 * @brief Calculates profit based on orders and demand.
 *
 * The profit is calculated using defined sale prices and costs.
 *
 * @param orders The number of orders.
 * @param demand The demand for the product.
 * @return The calculated profit.
 */
double calculate_profit(int orders, int demand) {
    constexpr static auto sale_price_first_half{ 49'000.00 };
    constexpr static auto sale_price_second_half{ 15'000.00 };
    constexpr static auto cost_per_unit{ 25'000.00 };

    const auto revenue{ sale_price_first_half * std::min(orders, demand) +
                        sale_price_second_half * std::max(0, orders - demand) };
    const auto total_cost{ cost_per_unit * orders };

    return revenue - total_cost;
}

/**
 * @brief Creates a profit matrix for various order and demand combinations.
 *
 * This function calculates the profit for each combination of orders and demands.
 *
 * @param orders A vector of integers representing different order quantities.
 * @param demands A vector of integers representing different demand levels.
 * @return A 2D vector containing the profit for each combination of orders and demands.
 */
std::vector<std::vector<double>> create_profit_matrix(const std::vector<int>& orders,
                                                      const std::vector<int>& demands) {
    std::vector<std::vector<double>> profit_matrix(orders.size(), std::vector<double>(demands.size()));

    for(auto i{ 0uz }; i < orders.size(); ++i)
        std::ranges::transform(
            demands,
            profit_matrix[i].begin(),
            [i, &orders](int demand) {
                return calculate_profit(orders[i], demand);
            });

    return profit_matrix;
}

/**
 * @brief Calculates expected values based on the profit matrix and probabilities.
 *
 * The expected values are computed by multiplying each profit by its associated probability.
 *
 * @param profit_matrix A 2D vector containing profits.
 * @param probabilities A vector containing probabilities corresponding to demands.
 * @return A 2D vector containing expected values.
 */
std::vector<std::vector<double>> calculate_expected_values(const std::vector<std::vector<double>>& profit_matrix,
                                                           const std::vector<double>& probabilities) {
    std::vector<std::vector<double>> expected_values(
        profit_matrix.size(),
        std::vector<double>(profit_matrix[0].size()));

    for(auto i{ 0uz }; i < profit_matrix.size(); ++i)
        std::ranges::transform(
            profit_matrix[i],
            expected_values[i].begin(),
            [&probabilities, j = 0](double profit) mutable {
                return profit * probabilities[j++];
            });

    return expected_values;
}

/**
 * @brief Calculates expected profits from the expected values.
 *
 * This function accumulates the expected values for each order to calculate total expected profits.
 *
 * @param expected_values A 2D vector containing expected values.
 * @return A vector containing the expected profits for each order.
 */
std::vector<double> calculate_expected_profits(const std::vector<std::vector<double>>& expected_values) {
    std::vector expected_profits(expected_values.size(), 0.0);

    std::transform(
        expected_values.begin(),
        expected_values.end(),
        expected_profits.begin(),
        [](const auto& row) {
            return std::accumulate(row.begin(), row.end(), 0.0);
        });

    return expected_profits;
}

/**
 * @brief Prints a formatted table of orders, demands, and corresponding values.
 *
 * This function displays the provided matrix in a user-friendly table format.
 *
 * @param orders A vector of integers representing order quantities.
 * @param demands A vector of integers representing demand levels.
 * @param matrix A 2D vector containing the values to display.
 * @param title A string representing the title of the table.
 */
void print_table(const std::vector<int>& orders,
                 const std::vector<int>& demands,
                 const std::vector<std::vector<double>>& matrix,
                 const std::string& title) {
    std::cout << title << "\n";
    std::cout << std::format("{:<12}", "Order\\Demand");

    for(auto demand : demands)
        std::cout << std::format("{:>11}", demand);
    std::cout << "\n";

    for(auto i{ 0uz }; i < matrix.size(); ++i) {
        std::cout << std::format("{:<12}", std::format("Order {}", orders[i]));

        for(auto value : matrix[i])
            std::cout << std::format("{:>11.2f}", value);
        std::cout << "\n";
    }
}

}  // namespace setm


/**
 * @brief Main function for calculating and displaying profits.
 *
 * This function initializes order and demand vectors, computes the profit matrix,
 * expected values, and expected profits, and then displays the results.
 */
int main() {
    std::vector demands{ 100, 150, 200, 250, 300 };
    std::vector probabilities{ 0.1, 0.15, 0.25, 0.3, 0.2 };
    std::vector orders{ 100, 150, 200, 250, 300 };

    const auto profit_matrix{ setm::create_profit_matrix(orders, demands) };
    setm::print_table(orders, demands, profit_matrix, "Profit Matrix");

    const auto expected_values{ setm::calculate_expected_values(profit_matrix, probabilities) };
    setm::print_table(orders, demands, expected_values, "\nExpected Values (eij*qj)");

    const auto expected_profits{ setm::calculate_expected_profits(expected_values) };

    auto max_profit{ std::numeric_limits<double>::lowest() };
    auto optimal_order{ 0 };

    std::cout << "\nExpected Profits:\n";
    for(auto i{ 0uz }; i < expected_profits.size(); ++i) {
        std::cout << std::format("For Order {}: Expected Profit = {:.2f} dollars\n", orders[i], expected_profits[i]);

        if(expected_profits[i] > max_profit) {
            max_profit = expected_profits[i];
            optimal_order = orders[i];
        }
    }

    std::cout << std::format("\nOptimal order quantity: {}\nOptimal expected profit: {:.2f} dollars\n", optimal_order, max_profit);
}
