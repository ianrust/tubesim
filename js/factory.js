 class Tube {
    constructor(position, mapping_config) {
        let rotarySections = mapping_config.addresses_per_goal / mapping_config.goal_led_strip_length;
        let linearSections = mapping_config.goal_led_strip_length;
        this.numLeds = rotarySections*linearSections;
        let geometry = new THREE.BufferGeometry();

        let indices = [];
        let vertices = [];
        let normals = [];
        let colors = [];

        let rotarySectionsAdjusted = rotarySections;
        for ( var heightIndex = 0; heightIndex <= linearSections; heightIndex ++ ) {
            for ( var rotaryIndex = 0; rotaryIndex < rotarySectionsAdjusted; rotaryIndex ++ ) {
                let angle = rotaryIndex * Math.PI * 2 / rotarySectionsAdjusted;
                vertices.push(
                    mapping_config.radius * Math.cos(angle),
                    mapping_config.radius * Math.sin(angle),
                    heightIndex * mapping_config.pixel_height
                );
                normals.push(Math.cos(angle), Math.sin(angle), 1.0);
                colors.push(0.1,0.1,0.1)
            }
        }

        
        for ( var heightIndex = 0; heightIndex < linearSections; heightIndex ++ ) {
            for ( var rotaryIndex = 0; rotaryIndex < rotarySectionsAdjusted; rotaryIndex ++ ) {
                let bottomLeftIndex = rotaryIndex + (heightIndex*rotarySections);
                let rightModifier = (rotaryIndex !== rotarySectionsAdjusted-1) ? 1 : (1-rotarySectionsAdjusted);
                let bottomRightIndex = (rotaryIndex + rightModifier)  + (heightIndex*rotarySections)
                let topLeftIndex = rotaryIndex + ((heightIndex+1)*rotarySections);
                let topRightIndex = (rotaryIndex + rightModifier) + ((heightIndex+1)*rotarySections);
                indices.push(bottomLeftIndex, bottomRightIndex, topLeftIndex);
                indices.push(bottomRightIndex, topRightIndex, topLeftIndex);
            }
        }

        // map where the vertex index is saved in a map in the location of it's Octo address
        // always starts at 0. if more than 1 tube is used please apply an offset from this
        // TODO this is not very general and would probaly break in a lot of cases
        this.twoGroupMap = []
        for (let i = 0; i < (linearSections * rotarySections); i++) {
            let rotaryIndex = Math.floor(i / linearSections);
            let up = (rotaryIndex % 2 === 0 && rotaryIndex < rotarySectionsAdjusted/2) ||
                        (rotaryIndex % 2 !== 0 && rotaryIndex >= rotarySectionsAdjusted/2);
            let heightIndex = up ? i % linearSections : ((linearSections-1) - i % linearSections) ;
            this.twoGroupMap.push(heightIndex*rotarySections + rotaryIndex)
        }

        // map for octo address when all strips are chained togethe for a single tube
        this.oneGroupMap = []
        for (let i = 0; i < (linearSections * rotarySections); i++) {
            let rotaryIndex = Math.floor(i / linearSections);
            let up = rotaryIndex % 2 === 0;
            let heightIndex = up ? i % linearSections : ((linearSections-1) - i % linearSections) ;
            this.oneGroupMap.push(heightIndex*rotarySections + rotaryIndex)
        }

        geometry.setIndex( indices );
        geometry.addAttribute( 'position', new THREE.Float32BufferAttribute( vertices, 3 ) );
        geometry.addAttribute( 'normal', new THREE.Float32BufferAttribute( normals, 3 ) );
        let colorAttribute = new THREE.Float32BufferAttribute( colors, 3 );
        colorAttribute.setDynamic(true);
        geometry.addAttribute( 'color', colorAttribute);

        let material = new THREE.ShaderMaterial({
            vertexShader: `
                attribute vec3 color;
                varying vec3 colorShader;
                varying vec3 pos;

                void main() {
                    colorShader = color;
                    pos = position;
                    gl_Position = projectionMatrix * modelViewMatrix * vec4(position,1.0);
                }
            `,
            fragmentShader: `
                varying vec3 colorShader;
                varying vec3 pos;
                
                void main() {
                    gl_FragColor = vec4(colorShader, 1.0);
                }
            `,    
        });
        this.mesh = new THREE.Mesh( geometry, material );
        this.mesh.position.set( position.x, position.y, position.z );
    }

    setLEDValueMapped(i, r, g, b) {
        this.setLEDValue(this.oneGroupMap[i], r, g, b);
    }

    setLEDValue(i, r, g, b) {
        this.mesh.geometry.attributes.color.set([r], i*3);
        this.mesh.geometry.attributes.color.set([g], i*3 + 1);
        this.mesh.geometry.attributes.color.set([b], i*3 + 2);
        this.mesh.geometry.attributes.color.needsUpdate = true;
    }
}

class Line {
    constructor(side, mapping_config) {
        this.numLeds = mapping_config.leds_per_channel;
        let geometry = new THREE.BufferGeometry();

        let indices = [];
        let vertices = [];
        let normals = [];
        let colors = [];

        let flip = side ? 1 : -1;

        for ( var sectionIndex = 0; sectionIndex <= this.numLeds; sectionIndex ++ ) {
            for ( var lateralIndex = 0; lateralIndex <= 2; lateralIndex ++) {
                if (sectionIndex < 200) {
                    vertices.push(
                        flip*sectionIndex*mapping_config.pixel_length,
                        (mapping_config.pitch_width_half + (lateralIndex - 1) * mapping_config.line_width/2),
                        0
                    );
                } else if (sectionIndex < 500) {
                    vertices.push(
                        flip*(mapping_config.pitch_length_half + (lateralIndex - 1) * mapping_config.line_width/2),
                        (mapping_config.pitch_width_half-(sectionIndex-200)*mapping_config.pixel_length),
                        0
                    );
                } else {
                    vertices.push(
                        flip*(700-sectionIndex)*mapping_config.pixel_length,
                        (-mapping_config.pitch_width_half - (lateralIndex - 1) * mapping_config.line_width/2),
                        0
                    );
                }
                normals.push(0, 0, 1.0);
                colors.push(0.5, 0.5, 0.5);
            }
        }

        for ( var sectionIndex = 0; sectionIndex < this.numLeds; sectionIndex ++ ) {
            for ( var lateralIndex = 0; lateralIndex < 2; lateralIndex ++) {
                let bottomLeftIndex = sectionIndex * 3 + lateralIndex;
                let bottomRightIndex = sectionIndex * 3 + lateralIndex + 1;
                let topLeftIndex = (sectionIndex+1) * 3 + lateralIndex;
                let topRightIndex = (sectionIndex+1) * 3 + lateralIndex + 1;
                if (side) {
                    indices.push(bottomRightIndex, bottomLeftIndex, topLeftIndex);
                    indices.push(topRightIndex, bottomRightIndex, topLeftIndex);
                } else {
                    indices.push(bottomLeftIndex, bottomRightIndex, topLeftIndex);
                    indices.push(bottomRightIndex, topRightIndex, topLeftIndex);
                }
            }
        }

        geometry.setIndex( indices );
        geometry.addAttribute( 'position', new THREE.Float32BufferAttribute( vertices, 3 ) );
        geometry.addAttribute( 'normal', new THREE.Float32BufferAttribute( normals, 3 ) );
        let colorAttribute = new THREE.Float32BufferAttribute( colors, 3 );
        colorAttribute.setDynamic(true);
        geometry.addAttribute( 'color', colorAttribute);

        let material = new THREE.ShaderMaterial({
            vertexShader: `
                attribute vec3 color;
                varying vec3 colorShader;
                varying vec3 pos;

                void main() {
                    colorShader = color;
                    pos = position;
                    gl_Position = projectionMatrix * modelViewMatrix * vec4(position,1.0);
                }
            `,
            fragmentShader: `
                varying vec3 colorShader;
                varying vec3 pos;
                
                void main() {
                    gl_FragColor = vec4(colorShader, 1.0);
                }
            `,    
        });
        this.mesh = new THREE.Mesh( geometry, material );
        this.mesh.position.set( 0, 0, 0 );
    }

    // Set all 3 in parallel
    setLEDValueMapped(i, r, g, b) {
        this.setLEDValue(i*3, r, g, b);
        this.setLEDValue(i*3+1, r, g, b);
        this.setLEDValue(i*3+2, r, g, b);
    }

    setLEDValue(i, r, g, b) {
        this.mesh.geometry.attributes.color.set([r], i*3);
        this.mesh.geometry.attributes.color.set([g], i*3 + 1);
        this.mesh.geometry.attributes.color.set([b], i*3 + 2);
        this.mesh.geometry.attributes.color.needsUpdate = true;
    }
}