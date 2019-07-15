class Tube {
    constructor(x, y, z, rotarySections, linearSections, length, radius) {
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
                vertices.push(radius * Math.cos(angle), radius * Math.sin(angle), heightIndex * length / linearSections);
                normals.push(Math.cos(angle), Math.sin(angle), 1.0);
                colors.push(1.0,1.0,1.0)
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
        this.mesh.position.set( x, y, z );
    }

    setLEDValue(i, r, g, b) {
        this.mesh.geometry.attributes.color.set([r], i*3);
        this.mesh.geometry.attributes.color.set([g], i*3 + 1);
        this.mesh.geometry.attributes.color.set([b], i*3 + 2);
        this.mesh.geometry.attributes.color.needsUpdate = true;
    }
}