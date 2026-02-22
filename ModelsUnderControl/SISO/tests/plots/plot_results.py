import csv
import os
import matplotlib.pyplot as plt

BASE_DIR = os.path.dirname(__file__)
RESULTS_DIR = os.path.join(BASE_DIR, "..", "results")

FILES = {
    "P Controller": "p_controller.csv",
    "PI Controller": "pi_controller.csv",
    "PID Controller": "pid_controller.csv",
}

def load_csv(filepath):
    time = []
    target = []
    measure = []
    command = []

    with open(filepath, newline="") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            time.append(float(row["time"]))
            target.append(float(row["target"]))
            measure.append(float(row["measure"]))
            command.append(float(row["command"]))

    return time, target, measure, command


def plot_response():
    plt.figure(figsize=(10, 6))

    for label, filename in FILES.items():
        path = os.path.join(RESULTS_DIR, filename)
        t, target, measure, _ = load_csv(path)
        plt.plot(t, measure, label=f"{label} - mesure")

    t, target, _, _ = load_csv(os.path.join(RESULTS_DIR, list(FILES.values())[0]))
    plt.plot(t, target, "--", label="Consigne")

    plt.xlabel("Temps (s)")
    plt.ylabel("Sortie du système")
    plt.title("Réponse à échelon - comparaison P / PI / PID")
    plt.legend()
    plt.grid(True)


def plot_command():
    plt.figure(figsize=(10, 6))

    for label, filename in FILES.items():
        path = os.path.join(RESULTS_DIR, filename)
        t, _, _, command = load_csv(path)
        plt.plot(t, command, label=label)

    plt.xlabel("Temps (s)")
    plt.ylabel("Commande")
    plt.title("Commande générée par les contrôleurs")
    plt.legend()
    plt.grid(True)


if __name__ == "__main__":
    print("Affichage des courbes")
    plot_response()
    plot_command()
    plt.show()
