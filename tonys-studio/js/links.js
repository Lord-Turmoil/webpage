var linkList = [
    '<li><a href="http://www.tonys-studio.top:81" target="_blank">Logic Calculator</a></li>',
    '<li><a href="http://www.tonys-studio.top:83" target="_blank">Metronome</a></li>'
];

// '<li><a href="http://www.tonys-studio.top:90/" target="_blank">Genesis</a></li>'

(function addLinks() {
    var ul = document.getElementsByClassName("links")[0].getElementsByTagName("ul")[0];

    for (var i = 0; i < linkList.length; i++) {
        ul.innerHTML += linkList[i];
    }
})()