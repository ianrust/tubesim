class GoalController {
    constructor(scene, getGoalsColor, getLinesColor, song, stateClass) {
        this.numStrips = 12;
        this.ledsPerStrip = 50;
        this.maxPerWire = 700
        this.goalPosts = [
            new Tube(-10, -2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            new Tube(-10, 2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            new Tube(10, 2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            new Tube(10, -2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            new Line(true, this.maxPerWire, 0.05),
            new Line(false, this.maxPerWire, 0.05)
        ];
        this.goalPosts.forEach((item, index) => {
            scene.add(item.mesh);
        });
        this.totalLeds = this.maxPerWire * this.goalPosts.length;
        this.getGoalsColor = getGoalsColor;
        this.getLinesColor = getLinesColor;
        this.song = song;
        this.state = new stateClass();
    }

    // Calls the getColor function from the goal posts for each pixel and then updates it
    // Should match what is happening inside the loop in controller.h
    update() {
        let freq = this.song[this.state.tick % song.length];
        this.state.updateOutputState();
        for (let i = 0; i < this.totalLeds; i++) {
            let color;
            if (Math.floor(i/(this.maxPerWire)) < 4) {
                color = this.getGoalsColor(i, this.state, freq[0],
                                                            freq[1],
                                                            freq[2],
                                                            freq[3],
                                                            freq[4],
                                                            freq[5],
                                                            freq[6]);
            } else {
                color = this.getLinesColor(i, this.state, freq[0],
                                                            freq[1],
                                                            freq[2],
                                                            freq[3],
                                                            freq[4],
                                                            freq[5],
                                                            freq[6]);
            }
            this.setLED(i, color);
        }
    }

    // i is the OctoWS811 index of the LED
    setLED(i, color) {
        let postIndex = Math.floor(i/(this.maxPerWire));
        let tubeIndex = i % this.maxPerWire;
        this.goalPosts[postIndex].setLEDValueMapped(tubeIndex, color[0], color[1], color[2])
    }
}
