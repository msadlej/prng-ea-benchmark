import pandas as pd
import random
import sys


def getDecimalFractions(n_samples: int) -> list:
    return [random.random() for _ in range(n_samples)]


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python mersenne_twister.py {n_samples}")
        sys.exit(1)

    n_samples = int(sys.argv[1])
    mersenne_twister = getDecimalFractions(n_samples)

    df = pd.DataFrame(mersenne_twister, columns=["Mersenne-Twister Numbers"])
    df.to_csv("data/mersenne_twister.csv", index=False)
