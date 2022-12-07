/**
 * Generate maze.
 * Methods provided:
 *      Prim
 *      Kruskal
 *      DFS
 */


/********** Prim **********/
class PrimToken {
    constructor(f, s, i) {
        this.first = f;
        this.second = s;
        this.id = i;
    }
}

const prim = async () => {
    var n = maze.size;
    var heap = [];
    var flag = [];
    for (var i = 0; i <= n; i++) {
        flag.push(false);
    }
    heap.push(new PrimToken(0, 1, 0));
    while (heap.length > 0) {
        var u = heap[0].second;
        var w = heap[0].first;
        var id = heap[0].id;
        var k = 0;
        for (var i = 1; i < heap.length; i++) {
            if (heap[i].first < w) {
                u = heap[i].second;
                w = heap[i].first;
                id = heap[i].id;
                k = i;
            }
        }
        heap[k] = heap[heap.length - 1];
        heap.length--;

        if (flag[u]) {
            continue;
        }
        flag[u] = true;

        // Render to the maze.
        await sleep(genSpeed);
        renderer.draw();

        if (id != 0) {
            maze.modifyEdge(id, EDGE_FLOOR);
        }

        for (var i = 0; i < maze.matrix[u].length; i++) {
            var edge = maze.matrix[u][i];
            var v = edge.v;
            if (v != INVALID_VERTEX) {
                w = edge.w;
                id = edge.id;
                heap.push(new PrimToken(w, v, id));
            }
        }
    }

    renderer.draw();
    hookGenerateEvent();
    maze.ready = true;
}

/********** Kruskal **********/
var father = [];
function getFather(u) {
    if (u != father[u]) {
        father[u] = getFather(father[u]);
    }

    return father[u];
}

const kruskal = async () => {
    var n = maze.size;
    var list = maze.edgeList;
    var eflag = [];
    var vflag = [];
    var cnt = 0;

    father = [];
    for (var i = 0; i <= n; i++) {
        vflag.push(false);
        father.push(i);
    }
    for (var i = 0; i < list.length; i++) {
        eflag.push(false);
    }

    list.sort(function (e1, e2) { return e1.w - e2.w; });
    for (var i = 0; i < list.length; i++) {
        var fu = getFather(list[i].u);
        var fv = getFather(list[i].v);
        if (fu == fv) {
            continue;
        }

        await sleep(genSpeed);
        renderer.draw();

        list[i].tag = EDGE_FLOOR;
        father[fu] = fv;

        cnt++;
        if (cnt >= n - 1) {
            break;
        }
    }

    renderer.draw();
    hookGenerateEvent();
    maze.ready = true;
}

/********** DFS **********/
const dfs_gen = async(u, flag) => {
    var candidate = [];
    var list = maze.matrix[u];

    flag[u] = true;

    for (var i = 0; i < list.length; i++) {
        candidate.push(i);
    }
    shuffle(candidate);
    for (var i = 0; i < list.length; i++) {
        var e = list[candidate[i]];
        if (flag[e.v]) {
            continue;
        }
        flag[e.v] = true;

        await sleep(genSpeed);
        renderer.draw();

        maze.modifyEdge(e.id, EDGE_FLOOR);

        await dfs_gen(e.v, flag);
    }
}

const dfs_generate = async () => {
    var n = maze.size;
    var flag = [true];

    for (var i = 1; i <= n; i++) {
        flag.push(false);
    }

    await dfs_gen(1, flag);

    renderer.draw();
    hookGenerateEvent();
    maze.ready = true;
}