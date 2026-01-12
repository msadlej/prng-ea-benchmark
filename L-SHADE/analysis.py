from scipy.stats import wilcoxon
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np
import warnings


FUNCTIONS = {
    1: {"Description": "Unimodal Function", "Optimum": 100},
    2: {"Description": "Basic Function", "Optimum": 1100},
    3: {"Description": "Basic Function", "Optimum": 700},
    4: {"Description": "Basic Function", "Optimum": 1900},
    5: {"Description": "Hybrid Function", "Optimum": 1700},
    6: {"Description": "Hybrid Function", "Optimum": 1600},
    7: {"Description": "Hybrid Function", "Optimum": 2100},
    8: {"Description": "Composition Function", "Optimum": 2200},
    9: {"Description": "Composition Function", "Optimum": 2400},
    10: {"Description": "Composition Function", "Optimum": 2500},
}


def read_results(file_path: str, method: str, buffer_size: int) -> pd.DataFrame:
    df = pd.read_csv(file_path)
    df["Method"] = method
    df["Buffer Size"] = buffer_size
    df["Error"] = df.apply(
        lambda row: row["ErrorValue"] - FUNCTIONS[row["Function"]]["Optimum"], axis=1
    )

    return df


def summarize_results(df: pd.DataFrame) -> pd.DataFrame:
    summary = (
        df.groupby(["Function", "Dimension"])["Error"]
        .agg(
            [
                ("Mean Error", "mean"),
                ("Std Error", "std"),
                ("Minimum", "min"),
                ("Maximum", "max"),
            ]
        )
        .reset_index()
    )

    summary["Function"] = "F" + summary["Function"].astype(str)
    summary["CV"] = summary["Std Error"] / summary["Mean Error"]
    summary = summary[
        ["Function", "Mean Error", "Std Error", "Minimum", "Maximum", "CV"]
    ]

    return summary


def plot_by_method(df: pd.DataFrame, path: str) -> None:
    plt.figure(figsize=(12, 30))

    for i, function in enumerate(FUNCTIONS.keys()):
        plt.subplot(5, 2, i + 1)
        data = df[df["Function"] == function]
        sns.boxplot(data=data, x="Method", y="Error", fill=False)

        plt.title(f'F{function} - {FUNCTIONS[function]["Description"]}')
        plt.xlabel("Method")
        plt.ylabel("Error Value")
        plt.xticks(rotation=45, ha="right")

    plt.tight_layout()
    plt.savefig(path, dpi=300, bbox_inches="tight")
    plt.show()


def plot_by_buffer_size(df: pd.DataFrame, path: str) -> None:
    plt.figure(figsize=(12, 30))

    for i, function in enumerate(FUNCTIONS.keys()):
        plt.subplot(5, 2, i + 1)
        data = df[df["Function"] == function]
        sns.boxplot(data=data, x="Buffer Size", y="Error", fill=False)

        plt.title(f'F{function} - {FUNCTIONS[function]["Description"]}')
        plt.xlabel("Buffer Size")
        plt.ylabel("Error Value")
        plt.xticks(rotation=45, ha="right")

    plt.tight_layout()
    plt.savefig(path, dpi=300, bbox_inches="tight")
    plt.show()


def combine_errors(df: pd.DataFrame) -> list:
    return [np.array(df[df["Function"] == i]["Error"].tolist()) for i in range(1, 11)]


def color_pvalue(val):
    if pd.isna(val):
        return "color: orange"
    elif val < 0.05:
        return "color: green"
    return ""


def calculate_wilcoxon(base_errors: list, compare_errors: list, styled: bool = False):
    result = []

    for i in range(10):
        row = {"Function": f"F{i+1}"}

        with warnings.catch_warnings():
            warnings.simplefilter("ignore", RuntimeWarning)
            res = wilcoxon(base_errors[i], compare_errors[i])

        row["Statistic"] = res.statistic
        row["p-value"] = res.pvalue
        result.append(row)

    df = pd.DataFrame(result)

    if styled:
        return df.style.map(color_pvalue, subset=["p-value"]).format(precision=2)

    return df
