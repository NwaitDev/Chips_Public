import csv
import os
import matplotlib.pyplot as plt

BASE_DIR = os.path.dirname(__file__)
RESULTS_DIR = os.path.join(BASE_DIR, "..", "results")

FILES = {
    # "P Controller": "p_controller.csv",
    # "PI Controller": "pi_controller.csv",
    # "PID Controller": "pid_controller.csv",
}

def load_csv(filepath):
    time = []
    target = []
    measure = []
    command = []
    proportional = []
    integral = []
    derivative = []

    with open(filepath, newline="") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            time.append(float(row["time"]))
            target.append(float(row["target"]))
            measure.append(float(row["measure"]))
            command.append(float(row["command"]))
            proportional.append(float(row["proportional"]))
            integral.append(float(row["integral"]))
            derivative.append(float(row["derivative"]))

    return time, target, measure, command, proportional, integral, derivative


def plot_response(title, unit):
    plt.figure(figsize=(10, 6))

    for label, filename in FILES.items():
        path = os.path.join(RESULTS_DIR, filename)
        t, target, measure, _, _, _, _ = load_csv(path)
        if "Sans" in label:
            plt.plot(t, measure, '--', color='yellow', label=f"{label} - mesure")
        else:
            plt.plot(t, measure, label=f"{label} - mesure")

    t, target, _, _, _, _, _ = load_csv(os.path.join(RESULTS_DIR, list(FILES.values())[0]))
    plt.plot(t, target, "--", label="Consigne")

    plt.xlabel("Temps (s)")
    plt.ylabel(f"Sortie du système ({unit})")
    plt.title(title)
    plt.legend()
    plt.grid(True)

def plot_proportional():
    plt.figure(figsize=(10, 6))

    for label, filename in FILES.items():
        path = os.path.join(RESULTS_DIR, filename)
        t, _, _, _, proportional, _, _ = load_csv(path)
        if "Sans" in label:
            plt.plot(t, proportional, '--', color='yellow', label=label)
        else:
            plt.plot(t, proportional, label=label)

    plt.xlabel("Temps (s)")
    plt.ylabel("Proportional")
    plt.title("Proportionnel des contrôleurs")
    plt.legend()
    plt.grid(True)

def plot_integral():
    plt.figure(figsize=(10, 6))

    for label, filename in FILES.items():
        path = os.path.join(RESULTS_DIR, filename)
        t, _, _, _, _, integral, _ = load_csv(path)
        if "Sans" in label:
            plt.plot(t, integral, '--', color='yellow', label=label)
        else:
            plt.plot(t, integral, label=label)

    plt.xlabel("Temps (s)")
    plt.ylabel("Integral")
    plt.title("Intégral des contrôleurs")
    plt.legend()
    plt.grid(True)

def plot_derivative():
    plt.figure(figsize=(10, 6))

    for label, filename in FILES.items():
        path = os.path.join(RESULTS_DIR, filename)
        t, _, _, _, _, _, derivative = load_csv(path)
        if "Sans" in label:
            plt.plot(t, derivative, '--', color='yellow', label=label)
        else:
            plt.plot(t, derivative, label=label)

    plt.xlabel("Temps (s)")
    plt.ylabel("Derivative")
    plt.title("Dérivée des contrôleurs")
    plt.legend()
    plt.grid(True)
    


def plot_command(title, xlabel, ylabel):
    plt.figure(figsize=(10, 6))

    for label, filename in FILES.items():
        path = os.path.join(RESULTS_DIR, filename)
        t, _, _, command, _, _, _ = load_csv(path)
        if "Sans" in label:
            plt.plot(t, command, '--', color='yellow', label=label)
        else:
            plt.plot(t, command, label=label)

    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend()
    plt.grid(True)

def plot_filter(title, xlabel, ylabel):
    plt.figure(figsize=(10, 6))

    for label, filename in FILES.items():
        path = os.path.join(RESULTS_DIR, filename)
        t, _, _, command, _, _, _ = load_csv(path)
        print(label)
        # if "without" in label:
        #     label = "sans filtre"
        # else:
        #     label = "avec filtre"
        plt.plot(t, command, label=label)

    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend()
    plt.grid(True)