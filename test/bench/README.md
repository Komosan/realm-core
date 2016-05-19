# Core Benchmarking Infrastructure

A benchmark is a subclass of the `Benchmark` base class.

## Getting Started

Include `util` in your project. Include `benchmark.hpp`.

## FAQ

### How do I force exactly one repetition?

Override the `max_warmup_reps` and `max_reps` methods of the `Benchmark` base
class. For instance, to do one, measured repetition:

~~~~
// Subclass of Benchmark
    size_t max_reps()
    {
        return 1;
    }
    size_t max_warmup_reps()
    {
        return 0;
    }
~~~~