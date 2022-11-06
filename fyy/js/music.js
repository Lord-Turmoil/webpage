var musicTrigger = document.getElementById("music-trigger");

function play() {
    var audio = document.getElementById("bgm");
    audio.play();
    musicTrigger.onclick = null;
    musicTrigger.style.display = "none";
}

(function initAudio() {
    musicTrigger.onclick = play;
})()