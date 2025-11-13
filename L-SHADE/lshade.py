import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import re


METHODS = ["Linear Congruential", "Mersenne Twister", "True Random"]
FUNCTIONS = {
    "F1": {"Description": "Unimodal Function", "Optimum": 100},
    "F2": {"Description": "Basic Function", "Optimum": 1100},
    "F3": {"Description": "Basic Function", "Optimum": 700},
    "F4": {"Description": "Basic Function", "Optimum": 1900},
    "F5": {"Description": "Hybrid Function", "Optimum": 1700},
    "F6": {"Description": "Hybrid Function", "Optimum": 1600},
    "F7": {"Description": "Hybrid Function", "Optimum": 2100},
    "F8": {"Description": "Composition Function", "Optimum": 2200},
    "F9": {"Description": "Composition Function", "Optimum": 2400},
    "F10": {"Description": "Composition Function", "Optimum": 2500},
}


def parse_results(filename: str) -> dict:
    results = {}

    with open(filename, "r") as file:
        content = file.read()

    function_sections = re.split(
        r"-------------------------------------------------------",
        content,
    )

    for section in function_sections:
        if "Function =" in section:
            function_match = re.search(
                r"Function = (\d+), Dimension size = (\d+)",
                section,
            )

            if function_match:
                function = int(function_match.group(1))
                dimension = int(function_match.group(2))

                error_matches = re.findall(
                    r"(\d+)th run, error value = ([\d\.e\+\-]+)",
                    section,
                )
                error_values = tuple([float(error) for _, error in error_matches])

                stats_match = re.search(
                    r"mean = ([\d\.e\+\-]+), std = ([\d\.e\+\-]+)",
                    section,
                )
                mean = float(stats_match.group(1)) if stats_match else 0
                std = float(stats_match.group(2)) if stats_match else 0

                results[function] = {
                    "dimension": dimension,
                    "error_values": error_values,
                    "mean": mean,
                    "std": std,
                    "num_runs": len(error_values),
                    "min": min(error_values) if error_values else 0,
                    "max": max(error_values) if error_values else 0,
                }

    return results


def analyze_results(results: dict) -> tuple:
    summary = []
    errors = []

    for function, data in results.items():
        summary.append(
            {
                "Function": f"F{function}",
                "Mean Error": data["mean"],
                "Std Error": data["std"],
                "Minimum": data["min"],
                "Maximum": data["max"],
                "CV": (data["std"] / data["mean"] if data["mean"] != 0 else 0),
                "Dimension": data["dimension"],
                "Num_Runs": data["num_runs"],
            }
        )

        for error in data["error_values"]:
            errors.append(
                {
                    "Function": f"F{function}",
                    "Error": error - FUNCTIONS[f"F{function}"]["Optimum"],
                }
            )

    return pd.DataFrame(summary), pd.DataFrame(errors)


def plot_results(combined_errors: pd.DataFrame, filepath: str = None) -> None:
    plt.figure(figsize=(12, 30))

    for i, function in enumerate(FUNCTIONS.keys()):
        plt.subplot(5, 2, i + 1)
        data = combined_errors[combined_errors["Function"] == function]
        sns.boxplot(data=data, x="Method", y="Error", fill=False)

        plt.title(f'{function} - {FUNCTIONS[function]["Description"]}')
        plt.xlabel("Method")
        plt.ylabel("Error Value")
        plt.tick_params(axis="x", rotation=45)
        plt.tick_params(axis="y")

    plt.tight_layout()
    if filepath:
        plt.savefig(filepath)

    plt.show()
