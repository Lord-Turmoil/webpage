// Filename: index.js
// Function: initialize all properties
// Programmer: Tony

// in bubble.js
const WINDOW_WIDTH = document.body.clientWidth;
const WINDOW_HEIGHT = document.body.clientHeight;
const CENTER_X = WINDOW_WIDTH / 2;
const CENTER_Y = WINDOW_HEIGHT / 2;

var margin;
var text = document.getElementsByClassName("text")[0].getElementsByTagName("img");
var button = document.getElementById("button");

function init() {
    if (WINDOW_HEIGHT < WINDOW_WIDTH) {
        document.body.innerHTML = "<h1>Only on Mobile!</h1>";
        document.body.style.backgroundColor = "#efefef";
        return;
    }

    if (WINDOW_HEIGHT * 9 > WINDOW_WIDTH * 16) {
        var height = WINDOW_WIDTH * 16.0 / 9.0;
        margin = ((WINDOW_HEIGHT - height) / 2.0) / WINDOW_HEIGHT * 100;
    } else {
        margin = 0;
    }

    button.style.fontSize = WINDOW_WIDTH * 0.05 + "px";

    text[0].style.width = WINDOW_WIDTH * 0.7 + "px";
    text[0].style.left = "5%";
    text[0].style.top = margin + 10 + "%";
    text[0].style.transformOrigin = "top left";

    text[1].style.width = WINDOW_WIDTH * 0.9 + "px";
    text[1].style.right = "5%";
    text[1].style.bottom = margin + 10 + "%";
    text[1].style.transformOrigin = "bottom right";

    document.getElementsByClassName("footer")[0].style.fontSize = WINDOW_WIDTH * 0.05 + "px";
}

function start() {
    button.style.display = "none";
    var video = document.getElementById("video");
    video.style.transition = "opacity 2s";
    video.style.opacity = "100%";

    var textDiv = document.getElementsByClassName("text")[0];
    textDiv.style.transition = "opacity 2.5s 1s";
    textDiv.style.opacity = "100%";


    var footer = document.getElementsByClassName("footer")[0];
    console.log(footer.style);
}

init();

document.body.onload = function() {
    button.onclick = function() {
        document.getElementById("bgm").play();
        start();
    }
}