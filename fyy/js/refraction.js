var camera, scene, renderer, mesh;
var mouseX = 0,
    mouseY = 0;

var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;

// var colors = ["#D98E04", "#F2E205", "#7F25D9", "#5C12A6", "#2F0459"];
var colors = ["#D98E04", "#EEE5DE", "#FF4500", "#F2E205", "#7F25D9", "#FF83FA", "#00BFFF", "#7CFC00"];

var TEXT = "祝FYY小朋友18岁生日快乐!";

function init() {
    camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 1, 10000);
    camera.position.z = -100;
    camera.position.y = -100;
    // 
    var imgs = textToTexture(TEXT);
    var texture = new THREE.CubeTextureLoader().load(imgs);
    texture.mapping = THREE.CubeRefractionMapping;

    scene = new THREE.Scene();
    //scene.background = texture;

    var ambient = new THREE.AmbientLight(0xffffff);
    scene.add(ambient);

    var geometry = new THREE.IcosahedronGeometry(50, 1);
    var material = new THREE.MeshPhongMaterial({
        envMap: texture,
        refractionRatio: 0.85
    });

    mesh = new THREE.Mesh(geometry, material);
    scene.add(mesh);

    renderer = new THREE.WebGLRenderer({
        antialias: true,
        alpha: true
    });
    renderer.setPixelRatio(window.devicePixelRatio);

    var ratio = 1.0;
    renderer.setSize(window.innerWidth * ratio, window.innerHeight * ratio);
    document.body.appendChild(renderer.domElement);

    document.addEventListener('mousemove', onDocumentMouseMove, false);
    document.addEventListener('touchmove', onDocumentMouseMove, false);
    window.addEventListener('resize', onWindowResize, false);

    // document.getElementById("text-trigger").onclick = onChange;
}

function onChange() {
    var imgs = textToTexture(TEXT);
    var texture = new THREE.CubeTextureLoader().load(imgs);
    texture.mapping = THREE.CubeRefractionMapping;
    mesh.material.envMap = texture;
}

function onWindowResize() {
    windowHalfX = window.innerWidth / 2;
    windowHalfY = window.innerHeight / 2;
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

function onDocumentMouseMove(event) {
    if (event.touches) event = event.touches[0];
    mouseX = (event.clientX - windowHalfX) / 4;
    mouseY = (event.clientY - windowHalfY) / 4;
}

function animate() {
    requestAnimationFrame(animate);
    render();
}

function render() {
    camera.position.x += (mouseX - camera.position.x) * 0.05;
    camera.position.y += (-mouseY - camera.position.y) * 0.05;
    camera.lookAt(mesh.position);
    renderer.render(scene, camera);
}

function textToTexture(text) {
    if (text === undefined) text = "Hello World";
    var canvas = document.createElement('canvas');
    // var canvas = document.getElementById("refraction-canvas");
    var tile_size = 1024;
    var fontSize = 50;
    // 
    canvas.width = tile_size * 4;
    canvas.height = tile_size;
    // 
    var ctx = canvas.getContext('2d');
    // ctx.font = fontSize + "px Rubik Mono One, Helvetica";
    ctx.font = fontSize + "px 华文新魏, Helvetica";
    var fillColor = colors[Math.floor(Math.random() * colors.length)];
    // document.body.style.backgroundColor = fillColor;
    // ctx.fillStyle = fillColor;
    ctx.fillStyle = "transparent";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    var text_width = ctx.measureText(text).width;
    var text_height = fontSize * 0.8;
    var repetitions_x = Math.ceil(canvas.width / text_width);
    var repetitions_y = Math.ceil(canvas.height / text_height);
    var index = 0;
    for (var y = 0; y < canvas.height; y += text_height) {
        for (var x = 0; x < canvas.width; x += text_width) {
            ctx.fillStyle = colors[Math.floor(Math.random() * colors.length)];
            var _x = index % 2 == 0 ? x : x - (text_width / 2);
            ctx.fillText(text, _x, y);
        }
        index += 1;
    }
    var tileFromCanvas = function(index) {
        var img_canvas = document.createElement('canvas');
        img_canvas.width = tile_size;
        img_canvas.height = tile_size;
        var context = img_canvas.getContext("2d");
        context.drawImage(canvas, -tile_size * index, 0);
        return img_canvas.toDataURL();
    }
    var imgs = [];
    imgs.push(tileFromCanvas(0));
    imgs.push(tileFromCanvas(1));
    imgs.push(tileFromCanvas(4)); // blank_space
    imgs.push(tileFromCanvas(4)); // blank_space
    imgs.push(tileFromCanvas(2));
    imgs.push(tileFromCanvas(3));
    return imgs;
}

init();
animate();