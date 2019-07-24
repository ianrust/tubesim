class GoalController {
    constructor(scene, song) {
        this.mapping_config = new Module.MappingConfig();
        this.song = song;
        this.state = new Module.ControllerState();

        this.channels = []
        for (let i = 0; i < 8; i++) {
            let position = this.mapping_config.getPosition(i);
            if (this.mapping_config.getChannelType(i).value === Module.ChannelType.GOALPOST.value) {
                this.channels.push(new Tube(position, this.mapping_config));
            } else if (this.mapping_config.getChannelType(i).value === Module.ChannelType.LINES.value) {
                this.channels.push(new Line(position.x > 0, this.mapping_config));
            }
            scene.add(this.channels[this.channels.length-1].mesh)
        }
        this.totalLeds = this.maxPerWire * this.channels.length;
    }

    // Calls the getColor function from the goal posts for each pixel and then updates it
    // Should match what is happening inside the loop in controller.h
    update() {
        let freq = this.song[this.state.tick % song.length];
        this.state.updateOutputState();
        for (let i = 0; i < this.totalLeds; i++) {
            let color;
            if (Math.floor(i/(this.maxPerWire)) < 4) {
                color = Module.getGoalsColor(i, this.state, freq[0],
                                                            freq[1],
                                                            freq[2],
                                                            freq[3],
                                                            freq[4],
                                                            freq[5],
                                                            freq[6]);
            } else {
                color = Module.getLinesColor(i, this.state, freq[0],
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
