var tbgm = document.getElementById("lzy-bgm");
var tbut = document.getElementById("lzy-but");
var cbgm = document.getElementById("ckm-bgm");
var cbut = document.getElementById("ckm-but");

const CKM = 1;
const LZY = 2;
var curBgm = 0;

function stopTony() {
    tbut.className = "stop";
    tbgm.pause();
    curBgm = 0;
}

function playTony() {
    if (curBgm == LZY) {
        stopTony();
        return;
    }

    if (curBgm == CKM) {
        stopCKM();
    }

    tbgm.play();
    tbut.className = "rotate";
    curBgm = LZY;
}

function stopCKM() {
    cbut.className = "stop";
    cbgm.pause();
    curBgm = 0;
}

function playCKM() {
    if (curBgm == CKM) {
        stopCKM();
        return;
    }

    if (curBgm == LZY) {
        stopTony();
    }

    cbgm.play();
    cbut.className = "rotate";
    curBgm = CKM;
}

(function() {
    cbut.onclick = playCKM;
    tbut.onclick = playTony;
})()