const DELAY = 50;

var navList = document.getElementsByClassName("nav")[0].getElementsByTagName("li");
var content = document.getElementsByClassName("content")[0];
var button = document.getElementsByClassName("button")[0].getElementsByTagName("span")[0];
var curId = 0;

function init() {
    content.style.top = 0 + "%";
    content.width = document.body.clientWidth;
    for (var i = 0; i < navList.length; i++) {
        (function(_i) {
            navList[_i].onclick = function() {
                changeTo(_i);
            };
        })(i);
    }

    button.onclick = function() {
        changeTo(curId + 1);
    }
}

init();

function changeTo(id) {
    if (id == navList.length) {
        return;
    }

    // console.log("Change to: " + id);
    var curTop = parseInt(content.style.top);
    var destTop = -id * 100;

    var top;
    for (var i = 0; i < 100; i++) {
        (function(_i) {
            setTimeout(function() {
                // console.log(_i)
                top = (_i * destTop + (100 - _i) * curTop) / 100;
                content.style.top = top + "%";
            }, Math.sqrt(_i) * DELAY);
        })(i);
    }
    content.style.top = destTop + "%";
    curId = id;
    if (curId == navList.length - 1) {
        button.innerHTML = "THE END";
    } else {
        button.innerHTML = "CONTINUE";
    }
}