// Filename: restrict.js
// Function: restrict user's behavior
// Programmer: Tony

(function restrict() {
    var blackList = document.getElementsByClassName("no-select");
    var length = blackList.length;

    for (var i = 0; i < length; i++) {
        blackList[i].addEventListener('selectstart', function(e) {
            e.preventDefault();
        });
    }
})()