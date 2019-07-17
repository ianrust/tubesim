class GoalController {
    constructor(scene, getColor) {
        this.numStrips = 6;
        this.ledsPerStrip = 150;
        this.goalPosts = [
            new Tube(-10, -2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.4),
            new Tube(-10, 2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.4),
            new Tube(10, 2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.4),
            new Tube(10, -2.5, 0.0, this.numStrips, this.ledsPerStrip, 5.0, 0.4)
        ];
        this.goalPosts.forEach((item, index) => {
            scene.add(item.mesh);
        });
        this.totalLeds = this.numStrips * this.ledsPerStrip * this.goalPosts.length;
        this.getColor = getColor;
    }

    // Calls the getColor function from the goal posts for each pixel and then updates it
    update(tick) {
        for (let i = 0; i < this.totalLeds; i++) {
            // let color = this.getColor(i, tick,  freq0,
            //                                     freq1,
            //                                     freq2,
            //                                     freq3,
            //                                     freq4,
            //                                     freq5,
            //                                     freq6);
            let color = this.getColor(i, tick,  0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0);
            this.setLED(i, color);
        }
    }

    // i is the OctoWS811 index of the LED
    // This assumes the goals have 900 addresses each, split in 2 groups
    setLED(i, color) {
        let postIndex = Math.floor(i/(this.numStrips * this.ledsPerStrip));
        let tubeIndex = i % (this.numStrips * this.ledsPerStrip);
        this.goalPosts[postIndex].setLEDValueMapped(tubeIndex, color[0], color[1], color[2])
    }
}