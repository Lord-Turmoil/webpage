/**
 * Provide some utility functions. 
 */

const sleep = (delay) => new Promise((resolve) => setTimeout(resolve, delay))

function shuffle(array) {
    var index = -1;
    var length = array.length;

    while (++index < length) {
        var rand = index + Math.floor(Math.random() * (length - index))
        
        var temp = array[rand];
        array[rand] = array[index];
        array[index] = temp;
    }

    return array;
}

function dist_manhattan(x1, y1, x2, y2) {
    return Math.abs(x1 - x2) + Math.abs(y1 - y2);
}