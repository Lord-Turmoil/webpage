//   Filename: days.js
// Programmer: Tony
// Start Date: May 23, 2022
//   Overview: Calculate days elapsed.

(function()
{
    var text = document.getElementById("days");

    var startTime = new Date('2023-2-10');
    var endTime = new Date();
    text.innerText = Math.floor((endTime - startTime) / 1000 / 60 / 60 / 24);
})()