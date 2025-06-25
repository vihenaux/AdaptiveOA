## 📋 `TODO.md`

```markdown
# AdaptiveOA – Project TODO

This document tracks the progress and design decisions of the AdaptiveOA framework, along with planned implementation steps.

---

## ✅ Completed

- [x] Designed `SolutionBase` as a CRTP base class
- [x] Defined `SolutionLike` concept for compile-time validation

---

## 🧠 Design Principles

- Prefer CRTP over runtime polymorphism to enable compile-time resolution and avoid heap allocations
- Use `concepts` for interface enforcement where possible
- Minimize use of virtuals, dynamic memory, and pointer indirection
- Ensure extensibility with clean separation of concerns (e.g., solutions, algorithms, mutations, functions)

---

## 🔧 In Progress / Planned

### 📦 Core Components

- [x] **Define Mutation Interface**
  - [x] Assess whether an interface is needed
  - [x] Options: CRTP base, simple base class, concept-only
  - [x] Design pattern for reversible mutations (e.g. `apply()` / `undo()`)

- [ ] **Define `NeighborhoodBase`**
  - [ ] CRTP base class for generating neighbors
  - [ ] Should operate over a specific `SolutionLike`
  - [ ] Possibly templated on the `Mutation` type

- [ ] **Define `AlgorithmBase`**
  - [ ] CRTP base class for local search (and eventually other optimization algorithms)
  - [ ] Should support pluggable mutation + neighborhood + evaluation function
  - [ ] Design unified interface: `run(Solution&)` or similar

- [ ] **Define `FunctionBase`**
  - [ ] CRTP base for fitness/evaluation functions
  - [ ] Ensure compatibility with solution types
  - [ ] May include normalization/scaling

- [ ] **Implement `BitstringSolution`**
  - [ ] Inherits from `SolutionBase<BitstringSolution>`
  - [ ] Stores a `std::vector<bool>` or bitset
  - [ ] Implements required `do_*` methods
  - [ ] Add example mutation (bit flip)

---

## 🧪 Testing & Utilities

- [ ] Add unit tests for `SolutionBase` and `BitstringSolution`
- [ ] Add a deterministic `Random` singleton utility
- [ ] CLI interface for running experiments with parameterized configurations

---

## 📘 Documentation

- [ ] Add `README.md` (once core components are established)
- [ ] Document extension points: how to add new algorithms, solutions, etc.
- [ ] Usage examples for each module (`BitstringSolution`, `LocalSearch`, etc.)

---

## 🌱 Future Work

- [ ] Add support for multi-objective optimization
- [ ] Add benchmark problems (e.g. MAXSAT, TSP, etc.)
- [ ] Add performance profiling hooks
- [ ] Add serialization for saving solutions/functions
- [ ] Parallel/local-distributed execution model

---
```

Would you like me to save this as a file named `TODO.md` and attach it to this project?
