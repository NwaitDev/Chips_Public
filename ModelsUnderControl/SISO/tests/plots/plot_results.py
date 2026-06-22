import os
import matplotlib.pyplot as plt
import base_plot

if __name__ == "__main__":
    print("Affichage des courbes")

    base_plot.BASE_DIR = os.path.dirname(__file__)
    base_plot.RESULTS_DIR = os.path.join(base_plot.BASE_DIR, "..", "results")

    base_plot.FILES = {
        "P Controller": "p_controller.csv",
        "PI Controller": "pi_controller.csv",
        "PID Controller": "pid_controller.csv",
    }

    base_plot.plot_response("Réponse à échelon - comparaison P / PI / PID", "")
    base_plot.plot_command("Commande générée par les contrôleurs", "Temps (s)", "Commande")
    plt.show()
