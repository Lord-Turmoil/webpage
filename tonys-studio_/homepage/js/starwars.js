const SLIDE_WIDTH = 200;
const SLIDE_DELAY = 2000;
const SLIDE_SPEED = 5;

var slideshow = slideshow = document.getElementsByClassName("slideshow")[0];
var imgList = document.getElementsByClassName("imgList")[0];
var slide_num = imgList.getElementsByTagName("img").length;
var curSlide = 0;

function init() {
    imgList.style.left = 0 + "px";
}

var autoChange = setInterval(function() {
    curSlide++;
    console.log(curSlide);
    if (curSlide == slide_num) {
        curSlide = 0;
        switchTo(curSlide);
        console.log(curSlide);
        curSlide++;
        changeTo(curSlide);
    } else {
        changeTo(curSlide);
    }
}, SLIDE_DELAY);

function changeTo(id) {
    var targetLeft = -id * SLIDE_WIDTH;
    var left = parseInt(imgList.style.left);
    var dist = left - targetLeft;

    for (var i = 1; i <= dist; i++) {
        (function(_i) {
            // console.log("_i = " + _i);
            setTimeout(function() {
                imgList.style.left = left - _i + "px";
            }, _i * SLIDE_SPEED);
        })(i);
    }
}

function switchTo(id) {
    imgList.style.left = -id * SLIDE_WIDTH + "px";
}