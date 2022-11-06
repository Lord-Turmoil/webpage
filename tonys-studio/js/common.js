(function addFooter() {
    var footer = document.getElementsByClassName('footer')[0];
    var str = '<div class="links"><h4>My Links</h4><ul></ul></div>'
    footer.innerHTML += str;
    str = '<div class="copyright"><span>Copyright &copy; Tony\'s Studio 2022 </span></div><div class="record"><span><a href="https://beian.miit.gov.cn" target="_blank">晋ICP备2022002858号-1</a></span><span><a target="_blank" href="http://www.beian.gov.cn/portal/registerSystemInfo?recordcode=14080202000495"><img src="res/img/record.png">晋公网安备 14080202000495号</a></span></div>';
    footer.innerHTML += str;
    str = '<div id="time"></div>'
    footer.innerHTML += str;
})();

function check(num) {
    if (num < 10) {
        num = '0' + num;
    }

    return num;
}

(function getTime() {
    var time = new Date();
    var year = time.getFullYear();
    var month = time.getMonth() + 1;
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
})();

// import background.js
(function addScript(url) {
    var script = document.createElement('script');
    script.setAttribute('src', url);
    document.getElementsByTagName('body')[0].appendChild(script);
})("js/background.js");