/**
 * Solve maze without delay.
 * Methods provided:
 *      DFS
 *      BFS
 *      AStar
 */

/*********** DFS **********/
function dfs_sol_b(u, dest, flag) {
    if (u == dest) {
        success = true;
        return;
    }

    var list = maze.matrix[u];

    steps++;
    dfsOutput.innerHTML = steps;

    flag[u] = true;

    for (var i = 0; (i < list.length) && !success; i++) {
        var e = list[i];
        if (maze.getEdgeTag(e.id) == EDGE_NONE) {
            continue;
        }
        if (flag[e.v]) {
            continue;
        }

        maze.modifyEdge(e.id, EDGE_PATH);
        dfs_sol_b(e.v, dest, flag);
        if (!success) {
            maze.modifyEdge(e.id, EDGE_DEAD);
        }
    }

    flag[u] = false;
}

function dfs_solve_b() {
    if (maze === null) {
        console.log("Maze is null.");
        hookSolveEvent();
        return;
    }

    if (!maze.ready) {
        console.log("Maze not ready.");
        hookSolveEvent();
        return;
    }

    maze.reset();
    success = false;
    steps = 0;
    dfsOutput.innerHTML = steps;

    var n = maze.size;
    var flag = [true];

    for (var i = 1; i <= n; i++) {
        flag.push(false);
    }

    dfs_sol_b(1, n, flag);

    renderer.draw();

    hookSolveEvent();
}

/*********** DFS* **********/
function dfs_star_sol_b(u, dest, flag) {
    if (u == dest) {
        success = true;
        return;
    }

    var list = maze.matrix[u];
    var order;
    steps++;
    dfsStarOutput.innerHTML = steps;

    flag[u] = true;

    if (list.length == 4) {
        order = [2, 3, 0, 1];
    } else {
        order = [2, 0, 1];
    }

    for (var i = 0; (i < list.length) && !success; i++) {
        var e = list[order[i]];
        if (maze.getEdgeTag(e.id) == EDGE_NONE) {
            continue;
        }
        if (flag[e.v]) {
            continue;
        }

        maze.modifyEdge(e.id, EDGE_PATH);

        dfs_star_sol_b(e.v, dest, flag);
        if (!success) {
            maze.modifyEdge(e.id, EDGE_DEAD);
        }
    }

    flag[u] = false;
}

function dfs_star_solve_b() {
    if (maze === null) {
        console.log("Maze is null.");
        hookSolveEvent();
        return;
    }

    if (!maze.ready) {
        console.log("Maze not ready.");
        hookSolveEvent();
        return;
    }

    maze.reset();
    success = false;
    steps = 0;
    dfsStarOutput.innerHTML = steps;

    var n = maze.size;
    var flag = [true];

    for (var i = 1; i <= n; i++) {
        flag.push(false);
    }

    dfs_star_sol_b(1, n, flag);

    renderer.draw();

    hookSolveEvent();
}


/********** BFS ***********/
function bfs_solve_b() {
    if (maze === null) {
        console.log("Maze is null.");
        hookSolveEvent();
        return;
    }

    if (!maze.ready) {
        console.log("Maze not ready.");
        hookSolveEvent();
        return;
    }

    maze.reset();
    success = false;
    steps = 0;
    bfsOutput.innerHTML = steps;

    var n = maze.size;
    var flag = [true];
    var candidates = [];
    var parent = [0];

    for (var i = 1; i <= n; i++) {
        flag.push(false);
        parent.push(0);
    }

    candidates.push(1);
    flag[1] = true;
    while (candidates.length > 0 && !success) {
        steps++;
        bfsOutput.innerHTML = steps;

        var u = candidates[0];

        candidates.shift();
        var list = maze.matrix[u];
        for (var i = 0; (i < list.length) && !success; i++) {
            var e = list[i];
            if (maze.getEdgeTag(e.id) == EDGE_NONE) {
                continue;
            }
            if (flag[e.v]) {
                continue;
            }

            maze.modifyEdge(e.id, EDGE_DEAD);
            candidates.push(e.v);
            flag[e.v] = true;
            parent[e.v] = u;
            if (e.v == n) {
                success = true;
            }
        }
    }

    renderer.draw();

    var u = n;
    while (u != 0) {
        var list = maze.matrix[u];
        for (var i = 0; i < list.length; i++) {
            var e = list[i];
            if (e.v == parent[u] || e.u == parent[u]) {
                maze.modifyEdge(e.id, EDGE_PATH);
                break;
            }
        }
        u = parent[u];
    }
    
    renderer.draw();

    hookSolveEvent();
}

/********** AStar **********/
function astar_solve_b(heuristic) {
    if (maze === null) {
        console.log("Maze is null.");
        hookSolveEvent();
        return;
    }

    if (!maze.ready) {
        console.log("Maze not ready.");
        hookSolveEvent();
        return;
    }

    maze.reset();
    success = false;
    steps = 0;
    astarOutput.innerHTML = steps;

    var n = maze.size;
    var width = maze.width;
    var frontier = [];
    var cost = [];
    var parent = [0];

    for (var i = 1; i <= n; i++) {
        parent.push(0);
    }
    for (var i = 0; i < maze.height; i++) {
        var list = new Array();
        for (var j = 0; j < maze.width; j++) {
            list.push(MAX_SIZE * MAX_SIZE * MAX_SIZE);
        }
        cost.push(list);
    }

    frontier.push(new Pair(1, 0));
    cost[0][0] = 0;
    while (frontier.length > 0 && !success) {
        steps++;
        astarOutput.innerHTML = steps;

        var k = 0;
        var current = frontier[0];

        for (var i = 1; i < frontier.length; i++) {
            if (frontier[i].w < current.w) {
                k = i;
                current = frontier[i];
            }
        }
        frontier[k] = frontier[frontier.length - 1];
        frontier.length--;

        var u = current.u;
        var list = maze.matrix[u];
        var x1 = Math.floor((u - 1) % width);
        var y1 = Math.floor((u - 1) / width);

        for (var i = 0; i < list.length; i++) {
            var e = list[i];
            if (maze.getEdgeTag(e.id) == EDGE_NONE) {
                continue;
            }
            var v = e.v;
            if (v == n) {
                success = true;
                parent[v] = u;
                maze.modifyEdge(e.id, EDGE_DEAD);
                break;
            }

            var x2 = Math.floor((v - 1) % width);
            var y2 = Math.floor((v - 1) / width);
            if (cost[y1][x1] + 1 < cost[y2][x2]) {
                cost[y2][x2] = cost[y1][x1] + 1;
                maze.modifyEdge(e.id, EDGE_DEAD);
                frontier.push(new Pair(v, cost[y2][x2] + heuristic(x1, y1, maze.width, maze.height)));
                parent[v] = u;
            }
        }
    }

    var u = n;
    while (u != 0) {
        var list = maze.matrix[u];
        for (var i = 0; i < list.length; i++) {
            var e = list[i];
            if (e.v == parent[u] || e.u == parent[u]) {
                maze.modifyEdge(e.id, EDGE_PATH);
                break;
            }
        }
        u = parent[u];
    }

    renderer.draw();

    hookSolveEvent();
}

/********** Greedy **********/
function greedy_solve_b() {
    if (maze === null) {
        console.log("Maze is null.");
        hookSolveEvent();
        return;
    }

    if (!maze.ready) {
        console.log("Maze not ready.");
        hookSolveEvent();
        return;
    }

    maze.reset();
    success = false;
    steps = 0;
    greedyOutput.innerHTML = steps;

    var n = maze.size;
    var width = maze.width;
    var frontier = [];
    var flag = [true]
    var parent = [0];

    for (var i = 1; i <= n; i++) {
        parent.push(0);
        flag.push(false);
    }

    frontier.push(new Pair(1, 0));
    flag[1] = true;
    while (frontier.length > 0 && !success) {
        var k = 0;
        var current = frontier[0];

        for (var i = 1; i < frontier.length; i++) {
            if (frontier[i].w < current.w) {
                k = i;
                current = frontier[i];
            }
        }
        frontier[k] = frontier[frontier.length - 1];
        frontier.length--;

        var u = current.u;
        var list = maze.matrix[u];
        var x1 = Math.floor((u - 1) % width);
        var y1 = Math.floor((u - 1) / width);

        steps++;
        greedyOutput.innerHTML = steps;

        for (var i = 0; i < list.length; i++) {
            var e = list[i];
            if (maze.getEdgeTag(e.id) == EDGE_NONE) {
                continue;
            }
            var v = e.v;
            if (v == n) {
                success = true;
                parent[v] = u;
                maze.modifyEdge(e.id, EDGE_DEAD);
                break;
            }
            if (flag[v]) {
                continue;
            }
            flag[v] = true;

            var x2 = Math.floor((v - 1) % width);
            var y2 = Math.floor((v - 1) / width);
            var cost = dist_manhattan(x2, y2, maze.width, maze.height);
            maze.modifyEdge(e.id, EDGE_DEAD);
            frontier.push(new Pair(v, cost));
            parent[v] = u;
        }
    }

    var u = n;
    while (u != 0) {
        var list = maze.matrix[u];
        for (var i = 0; i < list.length; i++) {
            var e = list[i];
            if (e.v == parent[u] || e.u == parent[u]) {
                maze.modifyEdge(e.id, EDGE_PATH);
                break;
            }
        }
        u = parent[u];
    }

    renderer.draw();

    hookSolveEvent();
}