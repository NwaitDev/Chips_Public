"""
Analyse du filtre passe-bas (LowPassFilter).

Lit le CSV genere par test_Filter_Analysis.cpp (colonnes: t, raw, filtered)
et produit les graphiques suivants:
    1. Signal temporel : brut vs filtre
    2. Spectre frequentiel (FFT) : brut vs filtre
    3. Diagramme de Bode (gain) du filtre passe-bas theorique

Usage:
    python analyze_filter.py tests/results/filter_analysis.csv
"""

import csv
import sys
import numpy as np
import matplotlib.pyplot as plt


# ----------------------------------------------------------------------
# Parametres du filtre (doivent correspondre a ceux utilises en C++)
# ----------------------------------------------------------------------
TAU = 35.0  # constante de temps du LowPassFilter [s]


def load_data(csv_path):
    required = {"t", "raw", "filtered"}

    columns = {name: [] for name in required}

    with open(csv_path, newline="") as f:
        reader = csv.DictReader(f)
        if reader.fieldnames is None:
            raise ValueError("CSV vide ou sans en-tete")

        missing = required - set(reader.fieldnames)
        if missing:
            raise ValueError(f"Colonnes manquantes dans le CSV: {missing}")

        for row in reader:
            for name in required:
                columns[name].append(float(row[name]))

    return {name: np.array(values) for name, values in columns.items()}


def sampling_frequency(t):
    dt = np.median(np.diff(t))
    return 1.0 / dt, dt


def compute_spectrum(signal, fs):
    """Spectre d'amplitude one-sided, normalise par 2/N (1/N pour DC)."""
    n = len(signal)
    nfft = 1 << (n - 1).bit_length()  # prochaine puissance de 2
    spec = np.fft.rfft(signal, n=nfft)
    freqs = np.fft.rfftfreq(nfft, d=1.0 / fs)

    mag = np.abs(spec)
    mag = mag * (2.0 / n)
    mag[0] = mag[0] / 2.0  # correction composante DC (1/N au lieu de 2/N)

    return freqs, mag


def compute_psd_welch(signal, fs, nperseg=None):
    """Densite spectrale de puissance via la methode de Welch.

    Decoupe le signal en segments superposes (fenetre de Hann, 50%
    d'overlap), calcule la FFT de chaque segment et moyenne les
    periodogrammes -> estimation plus stable et moins bruitee que
    la FFT brute, au prix d'une resolution frequentielle plus faible.
    """
    n = len(signal)
    if nperseg is None:
        nperseg = min(256, n)
    nperseg = min(nperseg, n)

    window = np.hanning(nperseg)
    win_scale = np.sum(window ** 2)

    step = nperseg // 2  # 50% overlap
    if step == 0:
        step = 1

    segments = []
    start = 0
    while start + nperseg <= n:
        segments.append(signal[start:start + nperseg])
        start += step

    if not segments:
        segments = [signal]
        window = np.hanning(len(signal))
        win_scale = np.sum(window ** 2)
        nperseg = len(signal)

    psd_acc = None
    for seg in segments:
        seg_windowed = seg * window
        spec = np.fft.rfft(seg_windowed, n=nperseg)
        psd = (np.abs(spec) ** 2) / (fs * win_scale)
        psd[1:-1] *= 2  # one-sided: double non-DC, non-Nyquist bins
        psd_acc = psd if psd_acc is None else psd_acc + psd

    psd_avg = psd_acc / len(segments)
    freqs = np.fft.rfftfreq(nperseg, d=1.0 / fs)

    return freqs, psd_avg


def bode_gain(tau, fs):
    """Gain theorique (dB) du filtre passe-bas du 1er ordre, axe log."""
    fmin, fmax = 0.01, fs / 2.0
    freqs = np.logspace(np.log10(fmin), np.log10(fmax), 200)
    wc = 1.0 / tau
    w = 2 * np.pi * freqs
    gain = wc / np.sqrt(w**2 + wc**2)
    gain_db = 20 * np.log10(gain)
    return freqs, gain_db


def plot_time_domain(data, filter):
    plt.figure(figsize=(10, 6))

    plt.plot(data["t"], data["raw"], color="tab:gray", linewidth=0.8, label="Signal brut")
    plt.plot(data["t"], data["filtered"], color="tab:green", linewidth=1.6, label="Signal filtre")
    plt.xlabel("Temps [s]")
    plt.ylabel("Amplitude")
    plt.title(f"Signal temporel : brut vs filtre ({filter})")
    plt.legend()
    plt.grid(True, alpha=0.3)

def plot_fft(data, fs, filter, is_logarithm = False):
    if is_logarithm:
        plot_fft_logarithm(data, fs, filter)
    else:
        plot_fft_normal(data, fs, filter)


def plot_fft_normal(data, fs, filter):

    plt.figure(figsize=(10, 6))

    f_raw, mag_raw = compute_spectrum(data["raw"], fs)
    f_filt, mag_filt = compute_spectrum(data["filtered"], fs)

    plt.plot(f_raw, mag_raw, color="tab:gray", linewidth=0.8, label="Spectre brut")
    plt.plot(f_filt, mag_filt, color="tab:green", linewidth=1.6, label="Spectre filtre")
    plt.xlabel("Frequence [Hz]")
    plt.ylabel("Amplitude")
    plt.title(f"Spectre frequentiel (FFT) ({filter})")
    plt.legend()
    plt.grid(True, alpha=0.3)

def plot_fft_logarithm(data, fs, filter):

    plt.figure(figsize=(10, 6))

    f_raw, mag_raw = compute_spectrum(data["raw"], fs)
    f_filt, mag_filt = compute_spectrum(data["filtered"], fs)

    # éviter f=0 sur un axe log
    mask_raw = f_raw > 0
    mask_filt = f_filt > 0

    plt.semilogx(
        f_raw[mask_raw],
        mag_raw[mask_raw],
        color="tab:gray",
        linewidth=0.8,
        label="Spectre brut"
    )

    plt.semilogx(
        f_filt[mask_filt],
        mag_filt[mask_filt],
        color="tab:green",
        linewidth=1.6,
        label="Spectre filtre"
    )

    plt.xlabel("Frequence [Hz] (log)")
    plt.ylabel("Amplitude")
    plt.title(f"Spectre frequentiel (FFT) ({filter})")
    plt.legend()
    plt.grid(True, which="both", alpha=0.3)


def plot_psd(data, fs, filter):
    plt.figure(figsize=(10, 6))

    f_raw, psd_raw = compute_psd_welch(data["raw"], fs)
    f_filt, psd_filt = compute_psd_welch(data["filtered"], fs)

    plt.semilogy(f_raw, psd_raw, color="tab:gray", linewidth=0.8, label="PSD brut")
    plt.semilogy(f_filt, psd_filt, color="tab:green", linewidth=1.6, label="PSD filtre")
    plt.xlabel("Frequence [Hz]")
    plt.ylabel("PSD [unite^2/Hz]")
    plt.title(f"Densite spectrale de puissance (Welch) ({filter})")
    plt.legend()
    plt.grid(True, which="both", alpha=0.3)
    plt.xlim(0, fs / 2)


def plot_bode(tau, fs, ax):
    freqs, gain_db = bode_gain(tau, fs)
    fc = 1.0 / (2 * np.pi * tau)

    ax.semilogx(freqs, gain_db, color="tab:blue", linewidth=1.6, label="Gain")
    ax.axvline(fc, color="tab:red", linestyle="--", linewidth=1,
               label=f"fc = {fc:.4f} Hz (-3dB)")
    ax.axhline(-3, color="tab:red", linestyle=":", linewidth=0.8)
    ax.set_xlabel("Frequence [Hz] (log)")
    ax.set_ylabel("Gain [dB]")
    ax.set_title("Diagramme de Bode (gain) du filtre passe-bas")
    ax.legend()
    ax.grid(True, which="both", alpha=0.3)


def print_summary(data, fs, dt, tau):
    alpha = tau / (tau + dt)
    fc = 1.0 / (2 * np.pi * tau)
    rms_raw = np.sqrt(np.mean(data["raw"]**2))
    rms_filt = np.sqrt(np.mean(data["filtered"]**2))

    print("--- Resume ---")
    print(f"fs           = {fs:.4f} Hz")
    print(f"dt           = {dt:.6f} s")
    print(f"tau          = {tau:.2f} s")
    print(f"alpha        = {alpha:.4f}")
    print(f"fc (-3dB)    = {fc:.4f} Hz")
    print(f"RMS brut     = {rms_raw:.4f}")
    print(f"RMS filtre   = {rms_filt:.4f}")


def plot_filter(csv_path, filter, is_logarithm = False):

    data = load_data(csv_path)
    fs, dt = sampling_frequency(data["t"])

    print_summary(data, fs, dt, TAU)

    plot_time_domain(data, filter)
    plot_fft(data, fs, filter, is_logarithm=is_logarithm)
    plot_psd(data, fs, filter)

if __name__ == "__main__":
    import base_plot

    plot_filter("tests/results/low_pass.csv", "passe-bas (ordre 1)")
    plot_filter("tests/results/low_pass_2.csv", "passe-bas (ordre 2)")
    plot_filter("tests/results/low_pass_4.csv", "passe-bas (ordre 4)")
    plot_filter("tests/results/high_pass.csv", "passe-haut")
    plot_filter("tests/results/high_low_pass.csv", "passe-haut puis bas", True)

    plot_filter("tests/results/median.csv", "median")

    plt.show()