# Comparison of influence of various methods of (pseudo)random sequences on the efficiency of algorithms from DE and CMA-ES family
Porównanie wpływu różnych metod generacji liczb (pseudo)losowych na efektywność algorytmów z rodziny CMA-ES i DE


## Requirements

### C++ Dependencies
For building the C++ components, you need:

- **C++11 compiler** (g++ or clang++)
- **CMake** or **autotools** (autoconf, automake, libtool)
- **Eigen3** - for matrix operations
- **Google glog** - for logging (optional but recommended)
- **Google gflags** - for command line parsing (optional)

On Debian/Ubuntu systems:
```bash
sudo apt-get install autoconf automake libtool libgoogle-glog-dev libgflags-dev libeigen3-dev
```

### Python Dependencies
- **Python 3.8+**
- All Python dependencies are listed in [requirements.txt](requirements.txt)

Install Python dependencies:
```bash
pip install -r requirements.txt
```

Key Python packages include:
- `numpy` - numerical computing
- `scipy` - scientific computing
- `matplotlib`, `seaborn` - visualization
- `pandas` - data analysis
- `jupyter`, `notebook` - interactive notebooks


## Building the Project

### Quick Start
To build all C++ components at once from the root directory:

```bash
make
```

This will build:
- Random number generators (linear congruential and Mersenne Twister)
- CEC-2013 and CEC-2021 benchmark functions
- L-SHADE algorithm
- CMA-ES algorithm (including libcmaes if not already installed)

### Build Individual Components
You can also build specific components:

```bash
make generators   # Build only random number generators
make benchmarks   # Build CEC-2013 and CEC-2021
make algorithms   # Build L-SHADE and CMA-ES
```

Or build from individual directories:

```bash
cd L-SHADE && make
cd CMA-ES && make
cd CEC-2013 && make
cd CEC-2021 && make
```


## Project Structure

### Random Number Generators
- `linear_congruential.cpp` - Linear congruential generator implementation
- `mersenne_twister.cpp` - Mersenne Twister generator implementation
- `true_random.py` - True random number generator using RANDOM.ORG API
- `Random-Buffer/` - Random number buffer class implementation
- `Random-Reader/` - Random number reader class implementation
- `generators.ipynb` - Jupyter notebook for generator analysis

### Optimization Algorithms
- `/CMA-ES` - CMA-ES experiments implementation
  - `results/` - Experimental results and data
  - `notebooks/` - Jupyter notebooks for analysis
- `/L-SHADE` - L-SHADE algorithm implementation (downloaded from https://github.com/P-N-Suganthan/2021-SO-BCO/),<br>
  and experiments implementation
  - `results/` - Experimental results and data
  - `notebooks/` - Jupyter notebooks for analysis

### Benchmark Functions
- `/CEC-2021` - CEC 2021 benchmark functions (downloaded from https://github.com/P-N-Suganthan/2021-SO-BCO/)
- `/CEC-2013` - CEC 2013 benchmark functions (downloaded from https://github.com/dmolina/cec2013single)

### External Dependencies
- `/libcmaes` - CMA-ES library (cloned from https://github.com/CMA-ES/libcmaes)
- `/Random-Reader/rapidcsv.h` - CSV parser library (cloned from https://github.com/d99kris/rapidcsv)

### Data and Results
- `/data` - Generated random number data (not included in repository)
- `/imgs` - Plots and graphs


## Authors

**Michał Sadlej**
[michal.sadlej@gmail.com]


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


## Acknowledgments

We gratefully acknowledge Polish high-performance computing infrastructure PLGrid (HPC Center: CI TASK) for providing computer facilities and support within computational grant no. PLG/2025/018266.

<img src="imgs/PLGrid-logotype.png" alt="PLGrid" height="80">
