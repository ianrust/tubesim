class GoalController {
    constructor(scene) {
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
    }

    // Calls the getColor function from the goal posts for each pixel and then updates it
    update(tick) {
        for (let i = 0; i < this.totalLeds; i++) {
            if (i < tick % this.totalLeds) {
                this.setLED(i, 0.0, 1.0, 0.0);
            } else {
                this.setLED(i, 0.0, 0.0, 0.0);
            }
        }
    }

    // i is the OctoWS811 index of the LED
    // This assumes the goals have 900 addresses each, split in 2 groups
    setLED(i, r, g, b) {
        let postIndex = Math.floor(i/(this.numStrips * this.ledsPerStrip));
        let tubeIndex = i % (this.numStrips * this.ledsPerStrip);
        this.goalPosts[postIndex].setLEDValueMapped(tubeIndex, r, g, b)
    }
}