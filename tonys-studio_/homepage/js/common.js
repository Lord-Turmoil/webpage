function getTime() {
    var time = new Date();
    var year = time.getFullYear();
    var month = time.getMonth();
    var date = time.getDate();
    var hour = time.getHours();
    var minute = time.getMinutes();
    var second = time.getSeconds();

    hour = check(hour);
    minute = check(minute);
    second = check(second);

    var msg = "";
    msg += year + "/" + month + "/" + date + " ";
    msg += hour + ":" + minute + ":" + second;
    // console.log(msg);
    document.getElementById("time").innerHTML = msg;
    setTimeout(getTime, 1000);
}

function check(num) {
    if (num < 10) {
        num = '0' + num;
    }

    return num;
}

getTime();

// import background.js
function addScript(url) {
    var script = document.createElement('script');
    script.setAttribute('src', url);
    document.getElementsByTagName('body')[0].appendChild(script);
}
addScript("js/background.js");