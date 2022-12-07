/**
 * Handle all interaction logic here.
 */

var genBut = document.getElementById("generate");
var solBut = document.getElementById("solve");

function onGenerate() {
    unhookGenerateEvent();
    
    maze = new Graph(mazeWidth, mazeHeight);
    maze.generate();
    renderer.init(maze);

    if (generator == "prim") {
        prim();
    } else if (generator == "kruskal") {
        kruskal();
    } else if (generator == "dfs") {
        dfs_generate();
    }
}

function hookGenerateEvent() {
    genBut.onclick = function () {
        onGenerate();
    };
}

function unhookGenerateEvent() {
    genBut.onclick = null;
}

function onSlove() {
    unhookSolveEvent();

    if (solver == "dfs") {
        dfs_solve();
    } else if (solver == "dfs-star") {
        dfs_star_solve();
    } else if (solver == "bfs") {
        bfs_solve();
    } else if (solver == "astar") {
        astar_solve(dist_manhattan);
    } else if (solver == "greedy") {
        greedy_solve();
    }
}

function hookSolveEvent() {
    solBut.onclick = function () {
        onSlove();
    };
}

function unhookSolveEvent() {
    solBut.onclick = null;
}

document.body.onload = function () {
    hookGenerateEvent();
    hookSolveEvent();
}