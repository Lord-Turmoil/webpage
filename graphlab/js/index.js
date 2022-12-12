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

var genBatchBut = document.getElementById("gen-batch");
var solBatchBut = document.getElementById("sol-batch");
var resetBut = document.getElementById("sol-reset");

function onGenerateBatch() {
    unhookGenerateEvent();
    maze = new Graph(mazeWidth, mazeHeight);
    maze.generate();
    renderer.init(maze);

    if (generator == "prim") {
        prim_b();
    } else if (generator == "kruskal") {
        kruskal_b();
    } else if (generator == "dfs") {
        dfs_generate_b();
    }
}

function onSolveBatch() {
    var dfsCnt = 0;
    var dfsStarCnt = 0;
    var bfsCnt = 0;
    var astarCnt = 0;
    var greedyCnt = 0;

    for (var i = 0; i < batchTime; i++) {
        // Generate
        unhookGenerateEvent();
        maze = new Graph(mazeWidth, mazeHeight);
        maze.generate();
        renderer.init(maze);

        if (generator == "prim") {
            prim_b();
        } else if (generator == "kruskal") {
            kruskal_b();
        } else if (generator == "dfs") {
            dfs_generate_b();
        }

        // Solve
        unhookSolveEvent();
        dfs_solve_b();
        dfsCnt += steps;
        unhookSolveEvent();
        dfs_star_solve_b();
        dfsStarCnt += steps;
        unhookSolveEvent();
        bfs_solve_b();
        bfsCnt += steps;
        unhookSolveEvent();
        astar_solve_b(dist_manhattan);
        astarCnt += steps;
        unhookSolveEvent();
        greedy_solve_b();
        greedyCnt += steps;
    }

    dfsCnt = Math.ceil(dfsCnt / batchTime);
    dfsStarCnt = Math.ceil(dfsStarCnt / batchTime);
    bfsCnt = Math.ceil(bfsCnt / batchTime);
    astarCnt = Math.ceil(astarCnt / batchTime);
    greedyCnt = Math.ceil(greedyCnt / batchTime);

    dfsOutput.innerHTML = "AVG: " + dfsCnt;
    dfsStarOutput.innerHTML = "AVG: " + dfsStarCnt;
    bfsOutput.innerHTML = "AVG: " + bfsCnt;
    astarOutput.innerHTML = "AVG: " + astarCnt;
    greedyOutput.innerHTML = "AVG: " + greedyCnt;
}

function onReset() {
    dfsOutput.innerHTML = 0;
    dfsStarOutput.innerHTML = 0;
    bfsOutput.innerHTML = 0;
    astarOutput.innerHTML = 0;
    greedyOutput.innerHTML = 0;
}

function hookBatchEvent() {
    genBatchBut.onclick = function () {
        onGenerateBatch();
    }
    solBatchBut.onclick = function () {
        onSolveBatch();
    }
    resetBut.onclick = function () {
        onReset();
    }
}

document.body.onload = function () {
    hookGenerateEvent();
    hookSolveEvent();
    hookBatchEvent();
}