function addAttribute() {
    var canvasList = document.getElementsByTagName("canvas");

    for (var i = 0; i < canvasList.length; i++) {
        var canvas = canvasList[i];

        if (!canvas.hasAttribute("id")) {
            canvas.setAttribute("class", "refraction");
        }
    }
}

addAttribute();