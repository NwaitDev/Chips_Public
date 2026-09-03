import csv
import numpy as np
import matplotlib.pyplot as plt


def load_data(csv_path, channel=0):
    required = {"t", "channel", "original", "mixed", "filtered"}

    data = {name: [] for name in required}

    with open(csv_path, newline="") as f:
        reader = csv.DictReader(f)

        if reader.fieldnames is None:
            raise ValueError("CSV vide ou sans en-tête")

        missing = required - set(reader.fieldnames)
        if missing:
            raise ValueError(f"Colonnes manquantes : {missing}")

        for row in reader:
            if int(row["channel"]) == channel:
                for name in required:
                    data[name].append(float(row[name]))

    return {name: np.array(values) for name, values in data.items()}


def sampling_frequency(t):
    dt = np.median(np.diff(t))
    fs = 1.0 / dt
    return fs, dt


def compute_fft(signal, fs):
    n = len(signal)
    window = np.hanning(n)
    signal_windowed = signal * window

    fft_values = np.fft.rfft(signal_windowed)
    freqs = np.fft.rfftfreq(n, d=1.0 / fs)

    magnitude = np.abs(fft_values) * 2.0 / n

    return freqs, magnitude


def compute_psd_welch(signal, fs, nperseg=8192):
    n = len(signal)
    nperseg = min(nperseg, n)

    window = np.hanning(nperseg)
    win_scale = np.sum(window ** 2)
    step = nperseg // 2

    psd_acc = None
    count = 0

    for start in range(0, n - nperseg + 1, step):
        segment = signal[start:start + nperseg]
        segment_windowed = segment * window

        spectrum = np.fft.rfft(segment_windowed)
        psd = (np.abs(spectrum) ** 2) / (fs * win_scale)
        psd[1:-1] *= 2.0

        if psd_acc is None:
            psd_acc = psd
        else:
            psd_acc += psd

        count += 1

    psd_avg = psd_acc / count
    freqs = np.fft.rfftfreq(nperseg, d=1.0 / fs)

    return freqs, psd_avg


def rms(signal):
    return np.sqrt(np.mean(signal ** 2))


def band_energy(freqs, values, fmin, fmax):
    mask = (freqs >= fmin) & (freqs <= fmax)
    return np.sum(values[mask])


def plot_time(data, title, max_time=0.1):
    mask = data["t"] <= max_time

    plt.figure(figsize=(12, 5))
    plt.plot(data["t"][mask], data["original"][mask], label="Instrument seul original", linewidth=1.2)
    plt.plot(data["t"][mask], data["mixed"][mask], label="Mix complet", linewidth=0.8)
    plt.plot(data["t"][mask], data["filtered"][mask], label="Mix filtré", linewidth=1.2)

    plt.xlabel("Temps [s]")
    plt.ylabel("Amplitude")
    plt.title(f"Signal temporel - {title}")
    plt.legend()
    plt.grid(True, alpha=0.3)

def plot_fft(data, fs, title, fmin, fmax, max_freq=6000):
    f_original, fft_original = compute_fft(data["original"], fs)
    f_mixed, fft_mixed = compute_fft(data["mixed"], fs)
    f_filtered, fft_filtered = compute_fft(data["filtered"], fs)

    max_amp = max(
        np.max(fft_original),
        np.max(fft_mixed),
        np.max(fft_filtered)
    )

    fig, axes = plt.subplots(2, 1, figsize=(12, 8), sharex=True, sharey=True)

    axes[0].plot(f_original, fft_original, label="Instrument seul original", linewidth=1.2)
    axes[0].axvline(fmin, linestyle="--", linewidth=1)
    axes[0].axvline(fmax, linestyle="--", linewidth=1)
    axes[0].set_ylabel("Amplitude")
    axes[0].set_title(f"FFT - Instrument seul - {title}")
    axes[0].legend()
    axes[0].grid(True, alpha=0.3)

    axes[1].plot(f_mixed, fft_mixed, label="Mix complet", color="green", linewidth=0.8)
    axes[1].plot(f_filtered, fft_filtered, label="Mix filtré", color="orange", linewidth=1.2)
    axes[1].axvline(fmin, linestyle="--", linewidth=1)
    axes[1].axvline(fmax, linestyle="--", linewidth=1)
    axes[1].set_xlabel("Fréquence [Hz]")
    axes[1].set_ylabel("Amplitude")
    axes[1].set_title(f"FFT - Mix complet vs mix filtré - {title}")
    axes[1].legend()
    axes[1].grid(True, alpha=0.3)

    axes[1].set_xlim(0, max_freq)
    axes[0].set_ylim(0, max_amp * 1.05)

    fig.tight_layout()

def plot_psd(data, fs, title, fmin, fmax, max_freq=6000):
    f_original, psd_original = compute_psd_welch(data["original"], fs)
    f_mixed, psd_mixed = compute_psd_welch(data["mixed"], fs)
    f_filtered, psd_filtered = compute_psd_welch(data["filtered"], fs)

    psd_values = np.concatenate([psd_original, psd_mixed, psd_filtered])
    psd_values = psd_values[psd_values > 0]

    ymin = np.min(psd_values)
    ymax = np.max(psd_values)

    fig, axes = plt.subplots(2, 1, figsize=(12, 8), sharex=True, sharey=True)

    axes[0].semilogy(f_original, psd_original, label="Instrument seul original", linewidth=1.2)
    axes[0].axvline(fmin, linestyle="--", linewidth=1)
    axes[0].axvline(fmax, linestyle="--", linewidth=1)
    axes[0].set_ylabel("PSD [amplitude²/Hz]")
    axes[0].set_title(f"PSD - Instrument seul - {title}")
    axes[0].legend()
    axes[0].grid(True, which="both", alpha=0.3)

    axes[1].semilogy(f_mixed, psd_mixed, label="Mix complet", color="green", linewidth=0.8)
    axes[1].semilogy(f_filtered, psd_filtered, label="Mix filtré", color="orange", linewidth=1.2)
    axes[1].axvline(fmin, linestyle="--", linewidth=1)
    axes[1].axvline(fmax, linestyle="--", linewidth=1)
    axes[1].set_xlabel("Fréquence [Hz]")
    axes[1].set_ylabel("PSD [amplitude²/Hz]")
    axes[1].set_title(f"PSD - Mix complet vs mix filtré - {title}")
    axes[1].legend()
    axes[1].grid(True, which="both", alpha=0.3)

    axes[1].set_xlim(0, max_freq)
    axes[0].set_ylim(ymin, ymax * 1.2)

    fig.tight_layout()

def print_summary(data, fs, title, fmin, fmax):
    f_original, psd_original = compute_psd_welch(data["original"], fs)
    f_mixed, psd_mixed = compute_psd_welch(data["mixed"], fs)
    f_filtered, psd_filtered = compute_psd_welch(data["filtered"], fs)

    energy_original = band_energy(f_original, psd_original, fmin, fmax)
    energy_mixed = band_energy(f_mixed, psd_mixed, fmin, fmax)
    energy_filtered = band_energy(f_filtered, psd_filtered, fmin, fmax)

    total_original = np.sum(psd_original)
    total_mixed = np.sum(psd_mixed)
    total_filtered = np.sum(psd_filtered)

    print(f"\n--- {title} ---")
    print(f"Fréquence d'échantillonnage : {fs:.2f} Hz")
    print(f"Bande étudiée : {fmin} Hz -> {fmax} Hz")

    print(f"RMS instrument original : {rms(data['original']):.6f}")
    print(f"RMS mix complet         : {rms(data['mixed']):.6f}")
    print(f"RMS mix filtré          : {rms(data['filtered']):.6f}")

    print(f"Energie dans la bande - original : {energy_original:.6e}")
    print(f"Energie dans la bande - mix      : {energy_mixed:.6e}")
    print(f"Energie dans la bande - filtré   : {energy_filtered:.6e}")

    print(f"Part énergie bande original : {100 * energy_original / total_original:.2f} %")
    print(f"Part énergie bande mix      : {100 * energy_mixed / total_mixed:.2f} %")
    print(f"Part énergie bande filtré   : {100 * energy_filtered / total_filtered:.2f} %")


def analyse_filter(csv_path, title, fmin, fmax, max_freq=6000):
    data = load_data(csv_path, channel=0)
    fs, dt = sampling_frequency(data["t"])

    print_summary(data, fs, title, fmin, fmax)

    # plot_time(data, title)
    plot_fft(data, fs, title, fmin, fmax, max_freq=max_freq)
    plot_psd(data, fs, title, fmin, fmax, max_freq=max_freq)


if __name__ == "__main__":
    analyse_filter(
        "tests/results/bass.csv",
        "Basse : 30-250 Hz",
        30,
        250,
        max_freq=1000
    )

    analyse_filter(
        "tests/results/guitar.csv",
        "Guitare : 280-900 Hz",
        280,
        900,
        max_freq=3000
    )

    analyse_filter(
        "tests/results/flute.csv",
        "Flûte : 1000-1400 Hz",
        1000,
        1400,
        max_freq=7000
    )

    plt.show()