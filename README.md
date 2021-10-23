# *SE<sup>2</sup>*: A *S*imple *E*xpression *E*valuator for Very Large Integers
# Part 1: Integers of Unlimited Size

**❗️ NOTE: A (prettier) web version of this file can be found [here](https://cisc2200.github.io/fa21-proj-part1/).**

This is the first part of the semester-long project.
The ultimate goal of the project is to create an evaluator for simple arithmetic expressions of arbitrarily large integers.
The evaluator will support [addition](https://en.wikipedia.org/wiki/Addition) and [subtraction for absolute difference](https://en.wikipedia.org/wiki/Absolute_difference), and also definition of variables.
(Technically, it will support a subset of the Python grammar.)
Given a compound expression, for example, `a = 2349587938475 + (123489709845 - 1234789832417098); b = a + 1; b;`, the evaluator should recognize each operator and operands,
build an internal representation (IR) of the expression, evaluate the expression based on the IR, and output the result, which is `1237015930645729` for the example.

The project contains **3** parts. Part 1 is to build the `BigInt` class that can hold integers of unlimited size, as long as they fit in the physical memory. In part 2, we will implement the transformation of an expression in [infix notation](https://en.wikipedia.org/wiki/Infix_notation) to its [postfix form](https://en.wikipedia.org/wiki/Reverse_Polish_notation). We will also create a calculator for only arithmetic expressions. In the 3rd part, we will add the support for variables and finish the construction of IR and the actual evaluation.

📖 **Information:** You can find the overview of the project [here](https://docs.google.com/presentation/d/1NO2ZKEVu3IZ07Oy-QNxdAell_FThC6RylEWDEGRim6U/edit?usp=sharing).

## 1. Background

There are infinite number of integers. It is impossible to represent all of them in a computer.
In C++, the fundamental type `int` is used to store *signed* integers.
If no length modifiers are present (e.g., `short`, `long`), it's guaranteed to have a width of [at least 16 bits](https://en.cppreference.com/w/cpp/language/types).
In 64-bit systems, it is almost exclusively guaranteed to have width of at least 32 bits.
Suppose on our machine an `int` is 32 bits wide.
This means in memory the Operating System (OS) will use a memory box of *32 bits* (= 4 bytes) to store an integer of type `int`.
The maximum and minimum value of such an integer are `2^31-1` and `-2^31`. (The `31` here is due to the dedicated sign bit.)
You can read these values using functions defined in [`std::numeric_limits`](http://www.cplusplus.com/reference/limits/numeric_limits/).
Any integer that is greater than the `2^31-1` or less than `-2^31` cannot be correctly stored and represented by `int` in C++.

To store integers of any size, we can design our own variable-length representations of integers as types using classes. In our project, we define class `BigInt` for **unsigned integers only**.

**❗️ Note:** For simplicity, we only consider **unsigned integers** in the project.

## 2. The `BigInt` class

### 2.1. Data members

In the `BigInt` class, an integer is stored in a `VList`, as shown below (and in [BigInt.h](BigInt.h#L12)) . **Each item in the list stores one digit of the integer**.

```cpp
VList<int> digits;
```

The `VList` class is a list implementation based on `std::vector` from the standard C++ library. Its definition can be found in [VList.h](VList.h).
**The class supports all functions discussed in class, including `addFirst`, `addLast`, `removeFirst`, `removeLast`, and so on.**
As a user of the class, you can assume it is correctly implemented.

### 2.2. Methods

You will implement two arithmetic operations for `BigInt`: [addition](https://en.wikipedia.org/wiki/Addition) and [subtraction for absolute difference](https://en.wikipedia.org/wiki/Absolute_difference).

In [BigInt.h](BigInt.h), you should finish [`operator+`](BigInt.h#L42) and [`operator-`](BigInt.h#L49). 
They utilize the [operator overloading](https://en.cppreference.com/w/cpp/language/operators) feature of C++.
The return value should be **a new `BigInt` object**, i.e., the two operands should not be modified.
There should be no leading `0`s for the results except for `0` itself.

For example, if we have two `BigInt` objects that store integer `456` and `1123`, the results of the two operations are as follows:

```cpp
ds::BigInt a("456");
ds::BigInt b("1123");

ds::BigInt sum = a + b; // sum = 1579
ds::BigInt dif = a - b; // dif = 667
```

**❗️ NOTE:** You should **NEVER** change the declaration of the two methods (`operator+` and `operator-`). The content of the two operands should also **NOT** be changed, as there are decorated with `const`. Otherwise, there will be compilation errors during autograding.

**🦄 Challenge:** Can you implement the multiplication operator (i.e., `BigInt operator*(const BigInt &other) const`) that returns the [product](https://en.wikipedia.org/wiki/Multiplication) of two `BigInt`s, for example `456 * 1123 = 512088`?

## 3. Test your implementation

A sample [doctest](https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md) test case is given in [main.cpp](main.cpp). You can modify its content to create your own tests (and use the [online big number calculator](https://www.calculator.net/big-number-calculator.html) for validation). But they will not be used for grading.
To run the given test, simple execute in terminal `make clean test`.

## 4. Submitting the code

After testing the program locally, you should submit `BigInt.h` to the [autograding system](https://storm.cis.fordham.edu:8443/web/project/129).
There will be **10** test cases (**30** points in total) to evaluate your implementation. For each passing test case, you will get **3** points if there is no memory error and **2** points if there are memory errors.
We will also manually look at your code to evaluate the quality of your code (**50** points), including coding style, comments, indentation, and so on.

**✨ Extra Credit:** There are **5** test cases that test the multiplication operator, each of which is **1** point.
