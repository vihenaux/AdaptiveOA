# TODO — AdaptiveOA

This document lists all planned extensions, assessments, and future developments for the AdaptiveOA framework.s

---

## ⚙️ Core Framework

### ✅ Current State
- Core CRTP-based architecture implemented (`AlgorithmBase`, `FunctionBase`, `NeighborhoodBase`, etc.).
- Consistent compile-time interfaces for neighborhood exploration and evaluation.
- Deterministic, minimal runtime overhead philosophy.

### 🧩 Planned
- **Unit tests & example suite**  
  Add small, isolated tests and simple example programs (e.g., single local search, ILS, ES).  
  Goal: ensure stability and demonstrate intended API usage patterns.

---

## 🔢 Algorithms

### ✅ Current State
- Local search and iterated local search implemented.
- Flexible mutation/pivot rule selection via CRTP.
- Mutation selection concepts established.

### 🧩 Planned
- **Evolution Strategies (μ, λ)**  
  Implement a first (μ+λ) and (μ,λ) version of `EvolutionStrategy`.  
  Use the current `PopulationMutation` and `MutationSelectionLike` concepts.  
  Serve as the foundation for future population-based algorithm exploration.

---

## 📦 Data Management & Persistence

### 🧩 Planned
- **Persistence / (De)Serialization**  
  Implement state saving and loading for algorithms, solutions, and experiments.  
  Necessary for large-scale experimentation, reproducibility, and checkpointing.

---

## 🧪 Benchmarking & Experimentation

### 🧩 Assess
- **Benchmark Class Design**  
  Investigate a plug-in `Benchmark` CRTP class, attachable to any algorithm or function.  
  Goal: transparent data collection (runtime, evaluations, mutations, improvements, etc.).  
  Compare with standard benchmarking utilities for trade-offs between flexibility and performance.

- **Standard Benchmark Harvesters**  
  Define minimal, reusable components for tracking runtime metrics without requiring inheritance.

---

## 🧩 Algorithmic Self-Evolution (Long-Term)

### 🧩 Planned
- **Algorithm Hierarchies**  
  Enable recursive composition of algorithms:  
  e.g. `LocalSearch<LocalSearch<NK, BitFlip>, AlgoNeighborhood>`  
  where an algorithm can itself be treated as a “function” to be optimized.  
  This will form the base for evolutionary optimization of algorithms.

- **Meta-Evolution Layer**  
  Add a higher-order algorithm capable of evolving or adapting optimization functions themselves.  
  Objective: experiment with meta-optimization of solvers using their own mechanisms.

---

## 🖥 Visualization & Reporting

### 🧩 Long-Term
- Add visualization and structured logging tools for:
  - Performance curves
  - Neighborhood traversal statistics
  - Population dynamics
  - Mutation diversity

Keep these separate from core logic to maintain performance purity.

---

## 📘 Documentation

- [ ] Add `README.md` (once core components are established)
- [ ] Document extension points: how to add new algorithms, solutions, etc.
- [ ] Usage examples for each module (`BitstringSolution`, `LocalSearch`, etc.)

---

## 🧭 Guiding Principles

- **Compile-time composition** over runtime flexibility.
- **Speed and determinism** take precedence over generality.
- **Incremental generalization**: extend only when measurable benefit exists.
- Maintain a **clean separation** between research-oriented abstractions and production efficiency.

---
