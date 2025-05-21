import pandas as pd
import requests
import sys


def getTrueRandom(n_samples: int = 10000) -> list:
    result = []

    try:
        url = f"https://www.random.org/decimal-fractions/?num={n_samples}&dec=20&col=1&format=plain&rnd=new"
        response = requests.get(url)

        if response.status_code == 200:
            result = response.text.split()
        else:
            print(f"Error: Failed to fetch true random numbers. HTTP {response.status_code}")
    except Exception as e:
        print(f"Exception occurred: {e}")

    return result


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python true_random.py {n_samples}")
        sys.exit(1)

    n_samples = int(sys.argv[1])
    true_random_numbers = getTrueRandom(n_samples)

    df = pd.DataFrame(true_random_numbers, columns=["True Random Numbers"])
    df.to_csv("data/true_random.csv", index=False)
