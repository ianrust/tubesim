var Module = {
    onRuntimeInitialized: () => {
        Module.initializeTrigTables();

        var container, stats;

        var scene = new THREE.Scene();

        var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
        var goals = new GoalController(scene, song);

        initializeButtons(goals);

        camera.rotation.x = Math.PI / 4.0;
        camera.position.y = -13;
        camera.position.z = 13;

        var renderer = new THREE.WebGLRenderer();
        var controls = new THREE.OrbitControls( camera, renderer.domElement );

        renderer.setSize(window.innerWidth, window.innerHeight);
        document.body.appendChild(renderer.domElement);
        container = document.getElementById('container');
        container.appendChild(renderer.domElement);
        stats = new Stats();
        container.appendChild(stats.dom);

        function animate() {
            goals.update();

            requestAnimationFrame( animate );
            renderer.render( scene, camera );
            stats.update();
        }
        animate();
    }
};

function hexToRgb(hex) {
    const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null;
}

let currentPattern = '';
let currentColor = {r: 255, g: 255, b: 255};

const initializeButtons = function(goals) {
    const left = document.getElementById("left");
    const right = document.getElementById("right");
    const music = document.getElementById("music");
    const clear = document.getElementById("clear");
    const timeOfDay = document.getElementById("timeOfDay");
    const patternInput = document.getElementById("patternInput");
    const colorPicker = document.getElementById("colorPicker");

    left.addEventListener('click', (e) => {
        goals.state.updateEvent(true, false);
    });

    right.addEventListener('click', (e) => {
        goals.state.updateEvent(false, true);
    });

    music.addEventListener('click', (e) => {
        goals.state.music_on = !goals.state.music_on;
    });

    clear.addEventListener('click', (e) => {
        goals.state.goal_left = false;
        goals.state.goal_right = false;
        goals.state.music_on = false;
    });

    timeOfDay.addEventListener('input', function() {
        goals.state.now_stored = Module.timeFromDaySeconds(parseInt(timeOfDay.value));
    });

    patternInput.addEventListener('input', function(e) {
        currentPattern = e.data;

        const {r, g, b} = currentColor;
        goals.state.updatePattern(currentPattern, true, r, g, b);
    });

    colorPicker.addEventListener('input', function(e) {
        const newColor = hexToRgb(e.target.value);
        if (!newColor) {
            return;
        }

        currentColor = newColor;

        const {r, g, b} = currentColor;
        goals.state.updatePattern(currentPattern, false, r, g, b);
    });
}
