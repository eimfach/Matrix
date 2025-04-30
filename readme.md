# Matrix

A toy matrix implementation using modern C++.

## Motivation / Learning Goals

This project serves as a personal exercise to learn and deepen my understanding of key C++ concepts. The primary focus was on:

* Object-Oriented Programming (OOP) principles in C++.
* Correctly implementing Operator Overloading for intuitive class usage.
* Utilizing Templates for generic code design.
* Exploring modern C++20 features like Concepts.
* Efficient use of `std::vector` for underlying data storage.
* Adhering to coding guidelines using the [Guidelines Support Library (GSL)](https://github.com/microsoft/GSL) (specifically for safe numeric casts like `narrow_cast`)
* (Optional: Initial experiments with performance considerations in C++.)

## Features

* Basic Matrix class storing `double` values.
* Initialization with dimensions and optional initial data (`std::vector<double>`).
* Overloaded `operator*` for:
    * Matrix-Matrix multiplication.
    * Scalar multiplication (Matrix * `double`).
* `size()` method to get the total number of elements.
* *(Note: Direct public element accessors (get/set methods or operator()) and formatted printing (`operator<<`) are not currently implemented.)*

## Tech Stack / Requirements

* **Language:** C++20
* **Libraries:**
    * [Microsoft Guidelines Support Library (GSL)](https://github.com/microsoft/GSL)
* **Development Environment:** Developed using Visual Studio.