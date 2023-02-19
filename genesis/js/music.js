var light_bgm = document.getElementById("light-bgm");
var light_button = document.getElementById("light-but");
var dark_bgm = document.getElementById("dark-bgm");
var dark_button = document.getElementById("dark-but");

const DARK = 1;
const LIGHT = 2;
var curBgm = 0;

function stopLight() {
    light_button.className = "stop";
    light_bgm.pause();
    curBgm = 0;
}

function playLight() {
    if (curBgm == LIGHT) {
        stopLight();
        return;
    }

    if (curBgm == DARK) {
        stopDark();
    }

    light_bgm.play();
    light_button.className = "rotate";
    curBgm = LIGHT;
}

function stopDark() {
    dark_button.className = "stop";
    dark_bgm.pause();
    curBgm = 0;
}

function playDark() {
    if (curBgm == DARK) {
        stopDark();
        return;
    }

    if (curBgm == LIGHT) {
        stopLight();
    }

    dark_bgm.play();
    dark_button.className = "rotate";
    curBgm = DARK;
}

(function() {
    dark_button.onclick = playDark;
    light_button.onclick = playLight;
})()