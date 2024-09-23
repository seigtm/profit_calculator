# Profit Calculator

A C++ implementation for calculating profits based on orders and demand levels.

This project includes methods for evaluating profits using defined sale prices and costs to create a profit matrix, expected values, and optimal order quantities.

## Table of Contents

- [Profit Calculator](#profit-calculator)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Functionality](#functionality)
  - [Installation](#installation)
  - [Usage](#usage)
  - [License](#license)

## Introduction

This project aims to provide an efficient way to evaluate profit scenarios based on varying order quantities and demand levels. The implemented methods help in determining optimal ordering strategies to maximize profits.

## Functionality

1. **Profit Calculation**: Computes the profit based on the number of orders and demand, taking into account sale prices and costs.
2. **Profit Matrix Creation**: Generates a matrix showing profits for all combinations of orders and demands.
3. **Expected Values Calculation**: Calculates expected profits based on probabilities associated with different demand levels.
4. **Optimal Order Determination**: Identifies the order quantity that maximizes expected profit.

## Installation

To build and run this project, you need a C++ compiler that supports **C++23**.

You can clone the repository and compile it using the following commands:

```bash
git clone https://github.com/seigtm/profit_calculator.git
cd ./profit_calculator
# Compile the code (adjust command based on your setup)
clang++ ./profit_calculator.cpp -o ./profit_calculator.o -std=c++23
```

## Usage

After compiling, you can run the executable:

```bash
./profit_calculator.o
```

The program will output the profit matrix, expected values, and optimal order quantity based on the predefined order and demand scenarios.

## License

This project is licensed under the **MIT License** - see the [LICENSE](https://github.com/seigtm/profit_calculator/tree/master/LICENSE) file for details.

Feel free to modify the content to fit your specific needs and preferences!
