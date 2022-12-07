/**
 * This will deal with all global parameters.
 */

const MIN_SIZE = 3;
const MAX_SIZE = 48;
const PREFERRED_SIZE = 12;

var widthInput = document.getElementById("width");
var heightInput = document.getElementById("height");
var mazeWidth = PREFERRED_SIZE;
var mazeHeight = PREFERRED_SIZE;

var randomBut = document.getElementById("random");

var wallColorInput = document.getElementById("wall-color");
var floorColorInput = document.getElementById("floor-color");
var pathColorInput = document.getElementById("path-color");
var deadColorInput = document.getElementById("dead-color");
var srcColorInput = document.getElementById("src-color");
var destColorInput = document.getElementById("dest-color");
var wallColor = wallColorInput.value;
var floorColor = floorColorInput.value;
var pathColor = pathColorInput.value;
var deadColor = deadColorInput.value;
var srcColor = srcColorInput.value;
var destColor = destColorInput.value;

var generatorInput = document.getElementById("generator");
var genSpeedInput = document.getElementById("gen-speed")
var generator = generatorInput.value;
var genSpeed = parseFloat(genSpeedInput.value);

var solverInput = document.getElementById("solver");
var solSpeedInput = document.getElementById("sol-speed");
var solver = solverInput.value;
var solSpeed = parseFloat(solSpeedInput.value)

function onChangeWidth(w) {
    if (isNaN(w) || (w < MIN_SIZE || w > MAX_SIZE)) {
        w = PREFERRED_SIZE;
        widthInput.value = w;
    }
    mazeWidth = w;
}

function onChangeHeight(h) {
    if (isNaN(h) || (h < MIN_SIZE || h > MAX_SIZE)) {
        h = PREFERRED_SIZE;
        heightInput.value = h;
    }
    mazeHeight = h;
}

function onRandomSize() {
    onChangeWidth(MIN_SIZE + Math.floor(Math.random() * (MAX_SIZE - MIN_SIZE + 1)));
    onChangeHeight(MIN_SIZE + Math.floor(Math.random() * (MAX_SIZE - MIN_SIZE + 1)));
    widthInput.value = mazeWidth;
    heightInput.value = mazeHeight;
}

function onChangeGenSpeed(s) {
    genSpeed = s;
    console.log("Generate Speed: " + genSpeed)
}

function onChangeSolSpeed(s) {
    solSpeed = s;
    console.log("Solve Speed: " + solSpeed)
}

(function () {
    widthInput.onchange = function() {
        onChangeWidth(parseInt(widthInput.value));
    }
    widthInput.value = PREFERRED_SIZE;
    heightInput.onchange = function() {
        onChangeHeight(parseInt(heightInput.value));
    }
    heightInput.value = PREFERRED_SIZE;
    randomBut.onclick = function() {
        onRandomSize();
    }

    wallColorInput.onchange = function() {
        wallColor = wallColorInput.value;
    }
    floorColorInput.onchange = function() {
        floorColor = floorColorInput.value;
    }
    pathColorInput.onchange = function() {
        pathColor = pathColorInput.value;
    }
    deadColorInput.onchange = function() {
        deadColor = deadColorInput.value;
    }
    srcColorInput.onchange = function() {
        srcColor = srcColorInput.value;
    }
    destColorInput.onchange = function() {
        destColor = destColorInput.value;
    }

    generatorInput.onchange = function() {
        generator = generatorInput.value;
    }
    genSpeedInput.onchange = function() {
        onChangeGenSpeed(parseInt(genSpeedInput.value));
    }
    solverInput.onchange = function() {
        solver = solverInput.value;
    }
    solSpeedInput.onchange = function() {
        onChangeSolSpeed(parseInt(solSpeedInput.value));
    }
})();
