var typer = document.getElementById("typer");
var content = typer.getElementsByTagName("p")[0].getAttribute("data-text");
var index = -1;

var counter;

function type() {
    if (index == -1) {
        typer.innerText = "";
        index++;
    } else if (index < content.length) {
        typer.innerText = typer.innerText + content.charAt(index);
        index++;
    } else {
        clearInterval(counter);
        index = -1;
        setTimeout(start_type, rand(1000, 3000));
    }
}

function start_type() {
    counter = setInterval(type, rand(100, 300));
}

start_type();

function rand(left, right) {
    return Math.floor(Math.random(right - left + 1)) + left;
}