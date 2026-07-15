#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <unistd.h>

#include "../../Filters/StatefulFilter/LowPass/LowPassFilterOrder2.hpp"
#include "../../Filters/StatefulFilter/HighPass/HighPassFilterOrder2.hpp"

class BandPassFilter {
private:
    HighPassFilterOrder2 highPass;
    LowPassFilterOrder2 lowPass;
    float sampleRate;

public:
    BandPassFilter(float lowCutoff, float highCutoff, float sampleRate)
        : highPass(lowCutoff),
          lowPass(highCutoff),
          sampleRate(sampleRate)
    {}

    float process(float input) {
        float dt = 1.0f / sampleRate;
        float x = highPass.apply(input, dt);
        x = lowPass.apply(x, dt);
        return x;
    }
};

struct WavData {
    std::vector<float> samples;
    uint64_t frameCount = 0;
    uint32_t channels = 0;
    uint32_t sampleRate = 0;
};

bool readWavFile(const std::string& filePath, WavData& data) {
    drwav wav;

    if (!drwav_init_file(&wav, filePath.c_str(), nullptr)) {
        std::cerr << "Erreur : impossible d'ouvrir " << filePath << std::endl;
        return false;
    }

    data.frameCount = wav.totalPCMFrameCount;
    data.channels = wav.channels;
    data.sampleRate = wav.sampleRate;
    data.samples.resize(data.frameCount * data.channels);

    uint64_t framesRead = drwav_read_pcm_frames_f32(
        &wav,
        data.frameCount,
        data.samples.data()
    );

    drwav_uninit(&wav);

    if (framesRead != data.frameCount) {
        std::cerr << "Attention : lecture incomplete pour " << filePath << std::endl;
    }

    return true;
}

bool exportBandPassAnalysisCsv(
    const std::string& originalFile,
    const std::string& mixedFile,
    const std::string& outputCsv,
    float lowCutoff,
    float highCutoff
) {
    WavData original;
    WavData mixed;

    if (!readWavFile(originalFile, original)) return false;
    if (!readWavFile(mixedFile, mixed)) return false;

    if (original.sampleRate != mixed.sampleRate) {
        std::cerr << "Erreur : frequences d'echantillonnage differentes." << std::endl;
        return false;
    }

    if (original.channels != mixed.channels) {
        std::cerr << "Erreur : nombres de canaux differents." << std::endl;
        return false;
    }

    uint64_t frameCount = std::min(original.frameCount, mixed.frameCount);
    uint32_t channels = mixed.channels;
    uint32_t sampleRate = mixed.sampleRate;

    std::ofstream csv(outputCsv);

    if (!csv.is_open()) {
        std::cerr << "Erreur : impossible de creer " << outputCsv << std::endl;
        return false;
    }

    csv << std::fixed << std::setprecision(10);
    csv << "t,channel,original,mixed,filtered\n";

    std::vector<BandPassFilter> filters;
    for (uint32_t c = 0; c < channels; ++c) {
        filters.emplace_back(lowCutoff, highCutoff, static_cast<float>(sampleRate));
    }

    float maxOriginal = 0.0f;
    float maxMixed = 0.0f;
    float maxFiltered = 0.0f;

    for (uint64_t frame = 0; frame < frameCount; ++frame) {
        double t = static_cast<double>(frame) / sampleRate;

        for (uint32_t channel = 0; channel < channels; ++channel) {
            uint64_t index = frame * channels + channel;

            float originalSample = original.samples[index];
            float mixedSample = mixed.samples[index];
            float filteredSample = filters[channel].process(mixedSample);

            maxOriginal = std::max(maxOriginal, std::abs(originalSample));
            maxMixed = std::max(maxMixed, std::abs(mixedSample));
            maxFiltered = std::max(maxFiltered, std::abs(filteredSample));

            csv << t << ","
                << channel << ","
                << originalSample << ","
                << mixedSample << ","
                << filteredSample << "\n";
        }
    }

    csv.close();

    std::cout << "\nCSV cree : " << outputCsv << std::endl;
    std::cout << "Instrument original : " << originalFile << std::endl;
    std::cout << "Mix analyse         : " << mixedFile << std::endl;
    std::cout << "Bande filtree       : " << lowCutoff << " Hz -> " << highCutoff << " Hz" << std::endl;
    std::cout << "Amplitude max original : " << maxOriginal << std::endl;
    std::cout << "Amplitude max mix      : " << maxMixed << std::endl;
    std::cout << "Amplitude max filtre   : " << maxFiltered << std::endl;

    if (maxFiltered < 1e-8f) {
        std::cerr << "Attention : signal filtre presque nul." << std::endl;
    }

    return true;
}

int main() {
    std::string current_dir = get_current_dir_name();

    std::string mixedFile = current_dir + "/tests/mixed.wav";

    exportBandPassAnalysisCsv(
        current_dir + "/tests/11_Bass.wav",
        mixedFile,
        "tests/results/bass.csv",
        30.0f,
        250.0f
    );

    exportBandPassAnalysisCsv(
        current_dir + "/tests/14_ElecGtr2.wav",
        mixedFile,
        "tests/results/guitar.csv",
        280.0f,
        900.0f
    );

    exportBandPassAnalysisCsv(
        current_dir + "/tests/16_Flute.wav",
        mixedFile,
        "tests/results/flute.csv",
        1000.0f,
        1400.0f
    );

    return 0;
}