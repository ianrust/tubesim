class GoalController {
    constructor(scene, getColor, song, stateClass) {
        this.numStrips = 6;
        this.ledsPerStrip = 50;
        this.goalPosts = [
            new Tube(-10, -2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            new Tube(-10, 2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            new Tube(10, 2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08),
            new Tube(10, -2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.08)
        ];
        this.goalPosts.forEach((item, index) => {
            scene.add(item.mesh);
        });
        this.totalLeds = this.numStrips * this.ledsPerStrip * this.goalPosts.length;
        this.getColor = getColor;
        this.song = song;
        this.state = new stateClass();
    }

    // Calls the getColor function from the goal posts for each pixel and then updates it
    // Should match what is happening inside the loop in controller.h
    update() {
        let freq = this.song[this.state.tick % song.length];
        this.state.updateOutputState();
        for (let i = 0; i < this.totalLeds; i++) {
            let color = this.getColor(i, this.state, freq[0],
                                                     freq[1],
                                                     freq[2],
                                                     freq[3],
                                                     freq[4],
                                                     freq[5],
                                                     freq[6]);
            this.setLED(i, color);
        }
    }

    // i is the OctoWS811 index of the LED
    setLED(i, color) {
        let postIndex = Math.floor(i/(this.numStrips * this.ledsPerStrip));
        let tubeIndex = i % (this.numStrips * this.ledsPerStrip);
        this.goalPosts[postIndex].setLEDValueMapped(tubeIndex, color[0], color[1], color[2])
    }
}
