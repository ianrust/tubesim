using namespace std;

void normalize255(int16_t* freq) {
    uint16_t total = 0;
    for (int i = 0; i < 7; i++) {
        total += freq[i];
    }
    for (int i = 0; i < 7; i++) {
        freq[i] = max(0, min(255, (255 * freq[i]) / total));
    }
}

bool isClapping(int16_t* freq) {
    for (int i = 0; i < 7; i++) {
        if (freq[i] > freq[6]) {
            return false;
        }
    }
    return true;
}

int16_t sum(int16_t* freq) {
    int16_t sum = 0;
    for (int i = 0; i < 7; i++) {
        sum += freq[i];
    }
    return sum;
}

// TODO make these interpretations available
// dominant_bass = (lpf_output[0] * Bands[0] + lpf_output[1] * Bands[1]) / (lpf_output[0] + lpf_output[1]);
// dominant_vocal = (lpf_output[2] * Bands[2] + lpf_output[3] * Bands[3]) / (lpf_output[2] + lpf_output[3]);
// active_snare = lpf_output[6] > 600 || lpf_output[5] > 600;
// bin_centroid = Compute_Bin_Centroid();