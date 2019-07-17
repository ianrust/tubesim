bool isClapping(int16_t* freq) {
    return freq[6] > 200;
}

// TODO make these interpretations available
// dominant_bass = (lpf_output[0] * Bands[0] + lpf_output[1] * Bands[1]) / (lpf_output[0] + lpf_output[1]);
// dominant_vocal = (lpf_output[2] * Bands[2] + lpf_output[3] * Bands[3]) / (lpf_output[2] + lpf_output[3]);
// active_snare = lpf_output[6] > 600 || lpf_output[5] > 600;
// bin_centroid = Compute_Bin_Centroid();