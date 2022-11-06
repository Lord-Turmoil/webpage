//  toggle: 70px
//      hr: 12px
//      li: 40px
const ORIGINAL_HEIGHT = 70;
const HR_HEIGHT = 12;
const ITEM_HEIGHT = 50;
const DELAY = 10;

function init() {
    var div = document.getElementsByClassName("set");
    var num = div.length;

    for (var i = 0; i < num; i++) {
        div[i].style.height = ORIGINAL_HEIGHT + "px";
    }

    initButton();
}

function transform(id) {
    // console.log("Transform begin.");
    var div = document.getElementsByClassName("btn")[id].parentNode.parentNode;
    var num = div.getElementsByTagName("li").length;

    // if height is in CSS and JS can't get it
    var height = parseInt(div.style.height);
    // console.log(height);
    if (height <= ORIGINAL_HEIGHT) {
        // console.log("Case 1:");
        expand(id, ORIGINAL_HEIGHT + HR_HEIGHT + num * ITEM_HEIGHT);
        document.getElementsByClassName("btn")[id].innerHTML = "Shrink";
    } else {
        // console.log("Case 2:");
        shrink(id, ORIGINAL_HEIGHT);
        document.getElementsByClassName("btn")[id].innerHTML = "Expand";
    }
}

function expand(id, targetHeight) {
    // console.log("Expand.");
    var div = document.getElementsByClassName("btn")[id].parentNode.parentNode;
    var dist = targetHeight - parseInt(div.style.height);

    var height = parseInt(div.style.height);
    for (var i = 1; i <= dist; i++) {
        (function (_i) {
            // console.log(_i);
            setTimeout(function () {
                div.style.height = height + _i + "px";
            }, Math.sqrt(_i) * DELAY);
        })(i);
    }
}

function shrink(id, targetHeight) {
    // console.log("Shrink");
    var div = document.getElementsByClassName("btn")[id].parentNode.parentNode;
    var dist = parseInt(div.style.height) - targetHeight;

    var height = parseInt(div.style.height);
    for (var i = 1; i <= dist; i++) {
        (function (_i) {
            // console.log(_i);
            setTimeout(function () {
                div.style.height = height - _i + "px";
            }, Math.sqrt(_i) * DELAY);
        })(i);
    }
}

function initButton() {
    var showcase = document.getElementsByClassName("showcase")[0];
    var btnList = showcase.getElementsByClassName("btn");

    for (var i = 0; i < btnList.length; i++) {
        (function (id) {
            btnList[id].onclick = function () {
                transform(id);
            };
        })(i);
    }
}