from scipy.stats import wilcoxon
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np
import matplotlib
import warnings


matplotlib.rcParams["pdf.fonttype"] = 42
matplotlib.rcParams["ps.fonttype"] = 42


N = 28
FUNCTIONS = (
    ["Empty"]
    + 5 * ["Unimodal Function"]
    + 15 * ["Basic Function"]
    + 8 * ["Composition Function"]
)


def read_results(
    file_path: str, method: str, buffer_size: int | str = "Unlimited"
) -> pd.DataFrame:
    df = pd.read_csv(file_path)
    df["Method"] = method
    df["Buffer Size"] = buffer_size

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
    summary["Mean Function Evaluations"] = (
        df.groupby(["Function", "Dimension"])["Evals"].mean().values
    )
    summary["Mean Execution Time"] = (
        df.groupby(["Function", "Dimension"])["Time"].mean().values
    )

    summary["Function"] = "F" + summary["Function"].astype(str)
    summary["CV"] = summary["Std Error"] / summary["Mean Error"]
    summary = summary[
        [
            "Function",
            "Mean Error",
            "Std Error",
            "Minimum",
            "Maximum",
            "CV",
            "Mean Function Evaluations",
            "Mean Execution Time",
        ]
    ]

    return summary


def plot_results(df: pd.DataFrame, path: str) -> None:
    plt.figure(figsize=(18, 60))

    for function in range(1, N + 1):
        plt.subplot(10, 3, function)
        data = df[df["Function"] == function]
        sns.boxplot(
            data=data,
            x="Buffer Size",
            y="Error",
            hue="Method",
            hue_order=["Unlimited", "Shuffle", "Offset", "Restart"],
            palette={
                "Unlimited": "black",
                "Shuffle": "red",
                "Offset": "green",
                "Restart": "blue",
            },
            fill=False,
        )

        plt.title(f"F{function} - {FUNCTIONS[function]}")
        plt.xlabel("Buffer Size")
        plt.ylabel("Error Value")
        plt.legend(title="Method", loc="upper left")
        plt.grid(axis="y", alpha=0.3)

        ax = plt.gca()
        labels = [label.get_text() for label in ax.get_xticklabels()]
        formatted_labels = format_labels(labels)
        ax.set_xticks(ax.get_xticks())
        ax.set_xticklabels(formatted_labels, rotation=45, ha="right")

    plt.tight_layout()
    plt.savefig(path, dpi=300, bbox_inches="tight")
    plt.show()


def plot_by_method(df: pd.DataFrame, path: str) -> None:
    plt.figure(figsize=(18, 60))

    for function in range(1, N + 1):
        plt.subplot(10, 3, function)
        data = df[df["Function"] == function]
        sns.boxplot(data=data, x="Method", y="Error", color="black", fill=False)

        plt.title(f"F{function} - {FUNCTIONS[function]}")
        plt.xlabel("Method")
        plt.ylabel("Error Value")
        plt.xticks(rotation=45, ha="right")
        plt.grid(axis="y", alpha=0.3)

    plt.tight_layout()
    plt.savefig(path, dpi=300, bbox_inches="tight")
    plt.show()


def plot_by_buffer_size(df: pd.DataFrame, path: str) -> None:
    plt.figure(figsize=(18, 60))

    for function in range(1, N + 1):
        plt.subplot(10, 3, function)
        data = df[df["Function"] == function]
        sns.boxplot(data=data, x="Buffer Size", y="Error", color="black", fill=False)

        plt.title(f"F{function} - {FUNCTIONS[function]}")
        plt.xlabel("Buffer Size")
        plt.ylabel("Error Value")
        plt.grid(axis="y", alpha=0.3)

        ax = plt.gca()
        labels = [label.get_text() for label in ax.get_xticklabels()]
        formatted_labels = format_labels(labels)
        ax.set_xticks(ax.get_xticks())
        ax.set_xticklabels(formatted_labels, rotation=45, ha="right")

    plt.tight_layout()
    plt.savefig(path, dpi=300, bbox_inches="tight")
    plt.show()


def combine_errors(df: pd.DataFrame) -> list:
    return [
        np.array(df[df["Function"] == i]["Error"].tolist()) for i in range(1, N + 1)
    ]


def colour_pvalue(val: int) -> str:
    if pd.isna(val):
        return "color: orange"
    elif val < 0.01:
        return "color: green"
    return ""


def calculate_wilcoxon(
    base_errors: list, compare_errors: list, buffer_size: int | str = "Unlimited"
) -> pd.DataFrame:
    result = []

    for i in range(N):
        row = {"Function": f"F{i+1}"}

        with warnings.catch_warnings():
            warnings.simplefilter("ignore", RuntimeWarning)
            res = wilcoxon(base_errors[i], compare_errors[i])

        row["Statistic"] = res.statistic
        row["p-value"] = res.pvalue
        row["Buffer Size"] = buffer_size
        result.append(row)

    df = pd.DataFrame(result)
    return df


def format_labels(labels: list) -> list:
    formatted_labels = []
    for label in labels:
        if label:
            try:
                value = float(label)
                exponent = int(np.floor(np.log10(abs(value))))
                mantissa = value / (10**exponent)
                if abs(mantissa - 1.0) < 0.01:
                    formatted_labels.append(f"$10^{{{exponent}}}$")
                else:
                    formatted_labels.append(
                        f"${mantissa:.1f} \\times 10^{{{exponent}}}$"
                    )
            except (ValueError, TypeError):
                formatted_labels.append(label)
        else:
            formatted_labels.append(label)
    return formatted_labels


def plot_pvalues(pvalue_data: pd.DataFrame, path: str) -> None:
    pvalue_plot_df = pvalue_data.copy()
    pvalue_plot_df["Method"] = pvalue_plot_df.index.get_level_values(0)
    pvalue_plot_df.reset_index(drop=True, inplace=True)

    plt.figure(figsize=(18, 8))
    sns.boxplot(
        data=pvalue_plot_df,
        x="Buffer Size",
        y="p-value",
        hue="Method",
        hue_order=["Shuffle", "Offset", "Restart"],
        palette={"Shuffle": "red", "Offset": "green", "Restart": "blue"},
        fill=False,
    )

    plt.axhline(y=0.01, color="black", linestyle="--", linewidth=1, label="α = 0.01")
    plt.xlabel("Buffer Size", fontsize=16)
    plt.ylabel("P-value", fontsize=16)
    plt.tick_params(axis="both", labelsize=14)
    plt.legend(title="Method", loc="upper right", fontsize=12)
    plt.grid(axis="y", alpha=0.3)

    ax = plt.gca()
    labels = [label.get_text() for label in ax.get_xticklabels()]
    formatted_labels = format_labels(labels)
    ax.set_xticks(ax.get_xticks())
    ax.set_xticklabels(formatted_labels)
    ax.invert_xaxis()

    plt.tight_layout()
    plt.savefig(path, dpi=300, bbox_inches="tight")
    plt.show()
