import csv 
import os
import matplotlib.pyplot as plt
import base_plot

base_plot.BASE_DIR = os.path.dirname(__file__)
base_plot.RESULTS_DIR = os.path.join(base_plot.BASE_DIR, "..", "results")

base_plot.FILES = {
    "Anti-windup clamp": "drone_with_aw.csv",
    "Anti-windup back calculation": "back_calculation.csv",
    "Sans anti-windup": "drone.csv",
}

base_plot.plot_response("Réponse à échelon - comparaison avec / sans anti-windup", "altitude (m)")
base_plot.plot_integral()
base_plot.plot_command("Commande générée par les contrôleur", "Temps (s)", "Commande (tour/min)")

plt.show()