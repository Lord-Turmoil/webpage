// Intro
var introDiv = document.getElementById("intro");
var letterDiv = document.getElementById("letter");
var trickDiv = document.getElementById("trick");
var jumpDiv = document.getElementById("jump");

// Letter
const SCROLL_DELAY = 3000;
const MARGIN = 50;
const BEGIN_ID = 2;
var itemBox = letterDiv.getElementsByClassName("box")[0];
var itemList = itemBox.getElementsByClassName("item");
var itemNum = itemList.length;
var totalOffset = 0;
var curId = BEGIN_ID;
var scrollInterval = null;

// Trick
var noButton = document.getElementById("no");
var yesButton = document.getElementById("yes");
var yesOriginX = yesButton.offsetLeft;
var yesOriginY = yesButton.offsetTop;
var buttonOriginX = noButton.offsetLeft;
var buttonOriginY = noButton.offsetTop;
var buttonWidth = noButton.offsetWidth;
var buttonHeight = noButton.offsetHeight;
var maxWidth = document.body.clientWidth - buttonWidth;
var maxHeight = document.body.clientHeight - buttonHeight * 1.5;
var buttonSize = _distance(0, 0, buttonWidth, buttonHeight);
var curX = buttonOriginX;
var curY = buttonOriginY;

/****************************************/

// Intro
introDiv.onclick = function () {
    playBGM();
    showLetter();
}

// Letter
function showLetter() {
    introDiv.style.display = "none";
    introDiv.onclick = null;
    // letterDiv.style.display = "block";
    letterDiv.classList.remove("deactive");
    letterDiv.classList.add("active");

    scrollInterval = setInterval(() => {
        scroll();
    }, SCROLL_DELAY);
}

function setHighlight(i) {
    if (i >= 2) {
        itemList[i - 2].classList.remove("highlight");
        itemList[i - 2].classList.add("lowlight");
    }
    itemList[i].classList.remove("lowlight");
    itemList[i].classList.add("highlight");
}

function shift(i) {
    totalOffset += (itemList[i - 1].offsetHeight + itemList[i].offsetHeight) / 2 + MARGIN;
    itemBox.style.transform = "translate(0px,-" + totalOffset + "px)";
}

function scroll() {
    if (curId < itemNum - 1) {
        curId++;
        setHighlight(curId);
        shift(curId);
    } else {
        clearInterval(scrollInterval);
        showConfirm();
    }
}

letterDiv.onclick = function () {
    clearInterval(scrollInterval);
    scroll();
    scrollInterval = setInterval(() => {
        scroll();
    }, SCROLL_DELAY);
}

// Confirm
function showConfirm() {
    letterDiv.onclick = null;
    trickDiv.classList.remove("deactive");
    trickDiv.classList.add("active");
    noButton.onmouseenter = function () {
        jump();
    }
    noButton.onclick = function () {
        jump();
    }
    yesButton.onclick = function () {
        confirm();
    }
}

function _distance(x1, y1, x2, y2) {
    return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

function jump() {
    var nx, ny;

    do {
        nx = Math.random() * maxWidth;
        ny = Math.random() * maxHeight;
    } while ((_distance(nx, ny, curX, curY) < buttonSize) || (_distance(nx, ny, yesOriginX, yesOriginY) < buttonSize));

    curX = nx;
    curY = ny;
    var x = curX - buttonOriginX;
    var y = curY - buttonOriginY;

    noButton.style.transform = "translate(" + x + "px," + y + "px)"
}


function confirm() {
    hurray();
    var delay = 0;
    for (var i = 0; i < 10; i++) {
        delay += 100 + Math.random() * 600;
        setTimeout(() => {
            hurray();
        }, delay);
    }

    yesButton.onclick = null;

    showJump();
}

function hurray() {
    fire(0.25, {
        spread: 26,
        startVelocity: 55,
    });
    fire(0.2, {
        spread: 60,
    });
    fire(0.35, {
        spread: 100,
        decay: 0.91,
        scalar: 0.8
    });
    fire(0.1, {
        spread: 120,
        startVelocity: 25,
        decay: 0.92,
        scalar: 1.2
    });
    fire(0.1, {
        spread: 120,
        startVelocity: 45,
    });
}

var count = 150;
var defaults = {
    origin: { y: 0.7 }
};

function fire(particleRatio, opts) {
    confetti(Object.assign({}, defaults, opts, {
        particleCount: Math.floor(count * particleRatio)
    }));
}

// Jump
function showJump() {
    trickDiv.classList.remove("active");
    trickDiv.classList.add("deactive");
    letterDiv.classList.remove("active");
    letterDiv.classList.add("deactive");
    jumpDiv.classList.remove("deactive");
    jumpDiv.classList.add("active");
    countdown();
}

var curCount = 5;
var timeDiv = document.getElementById("count");
function countdown() {
    timeDiv.innerHTML = curCount;
    if (curCount > 0) {
        curCount--;
        setTimeout(countdown, 1000);
    } else {
        setTimeout(redirect, 1000);
    }
}

function redirect() {
    window.location.href = "http://www.tonys-studio.top";
}

var bgm = document.getElementById("bgm");
function playBGM() {
    bgm.play();
    document.getElementById("track").getElementsByTagName("img")[0].classList.add("rotate");
}