var Module = {
    onRuntimeInitialized: () => {
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
            // goals.update();

            requestAnimationFrame( animate );
            renderer.render( scene, camera );
            stats.update();
        }
        animate();
    }
};

var initializeButtons = function(goals) {
  const left = document.getElementById("left");
  const right = document.getElementById("right");
  const music = document.getElementById("music");
  const clear = document.getElementById("clear");

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
}
