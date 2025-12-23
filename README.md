# AdaptiveOA

AdaptiveOA is a high-performance C++ framework for designing, composing, and experimenting with **optimization algorithms** using **compile-time composition**.

The framework is built around a strict CRTP-based architecture that prioritizes:
- Zero or near-zero runtime overhead
- Deterministic behavior
- Strong compile-time guarantees
- Algorithmic self-composition and meta-optimization

AdaptiveOA is intended as a **research-oriented framework** for exploring local search, population-based methods, and ultimately **algorithm generation**.

## Motivation

Most optimization frameworks focus on flexibility through runtime polymorphism and configuration layers.  
AdaptiveOA takes the opposite approach.

The core idea is that **algorithms, solutions, neighborhoods, and evaluation functions are all types**, and that composing them at compile time enables:
- Better optimization by the compiler
- Clearer expression of algorithmic intent
- Safer experimentation with complex algorithmic structures
- Recursive algorithm composition

## High-Level Organization

AdaptiveOA is structured around a small number of **core abstractions**, each enforced through CRTP base classes and concepts.

At a high level, the framework is composed of:
- Solutions: representations of candidate answers
- Functions: evaluation functions of (combinatorial) optimization problems
- Neighborhoods: mutation generators
- Mutations: atomic solution transformations
- Algorithms: orchestration logic

Each component is designed to be **independently replaceable** and **statically verified**.

## Core Architecture and CRTP

### What is CRTP?

The Curiously Recurring Template Pattern (CRTP) is a C++ technique where a class derives from a template instantiated with itself.

In AdaptiveOA, CRTP is used to:
- Enforce interfaces at compile time
- Avoid virtual functions
- Allow the base class to call derived implementations
- Enable aggressive inlining and optimization

This pattern is used consistently across all core modules.

## Core Modules

### SolutionBase

A solution represents a candidate point in the search space.

Responsibilities include:
- Storing the representation
- Managing an optional cached score
- Supporting mutation application and rollback
- Providing random initialization

Concrete solution types derive from SolutionBase and implement solution-specific behavior.

### FunctionBase

A function represents an optimization problem.

Its role is to:
- Evaluate a solution
- Track evaluation counts
- Optionally support incremental evaluation

Functions are stateless or minimally stateful and operate on solutions provided by algorithms.

### NeighborhoodBase

A neighborhood defines how mutations are generated.

It is responsible for:
- Enumerating or sampling mutations

Neighborhoods do not apply mutations themselves — they only generate them.

### MutationBase

A mutation represents an atomic modification to a solution.

It encapsulates:
- The mutation parameters

Mutations are passed between neighborhoods, algorithms, and solutions.

### AlgorithmBase

AlgorithmBase provides:
- Lifecycle management
- Best-solution tracking
- A unified execution entry point

Concrete algorithms implement their logic in a do_run method.

## Extending the Framework

AdaptiveOA is designed to be extended by **adding new types**.

### Adding a New Solution Type

To add a new solution:
- Derive from SolutionBase using CRTP
- Implement a do_randomize method
- Implement a do_to_string method
- Implement a do_mutation method
- Implement a do_reverse_mutation method

Examples already included:
- BitString

### Adding a New Function (Problem)

To add a new problem:
- Derive from FunctionBase
- Implement an evaluation method to evaluate a solution
- Optionally implement an evaluation method to evaluate a mutation of a solution

Examples already included:
- OneMax
- NK
- MaxSat

### Adding a New Neighborhood

To add a neighborhood:
- Derive from NeighborhoodBase
- Implement a do_mutation_available method
- Implement a do_next_mutation method
- Implement a do_accept_mutation method
- Implement a do_reset method

Examples already included:
- BitFlipNeighborhood
- PopulationMutationNeighborhood
- SeedNeighborhood
- SpecificSeedNeighborhood

### Adding a New Mutation

To add a mutation:
- Derive from MutationBase
- Implement a do_to_string method

Examples already included:
- BitFlip
- PopulationMutation
- SeedMutation
- SpecificSeedMutation

### Adding a New Algorithm

To add a new algorithm:
- Derive from AlgorithmBase
- Implement a do_run method

Examples include:
- Local Search
- Iterated Local Search

## Documentation Status

This project is under active development.

Planned documentation additions:
- Detailed extension guides
- Examples per module
- Design rationale documents
- Experimental reports
