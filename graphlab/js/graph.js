/**
 * Provide basic structure to represent graph.
 * This should be included before all the other js files
 * that use graph.
 */

const EDGE_NONE = 0;
const EDGE_FLOOR = 1;
const EDGE_PATH = 2;
const EDGE_DEAD = 4;
const EDGE_SRC = 8
const EDGE_DST = 16;

const INVALID_VERTEX = 0;

class Edge {
    constructor(u, v, w, id) {
        this.u = u;
        this.v = v;
        this.w = w;
        this.id = id;
        this.tag = EDGE_NONE;
    }
}

class Graph {
    constructor(w, h) {
        this.width = w;
        this.height = h;
        this.size = w * h;
        this.matrix = null;     // For algorithm.
        this.edgeList = null;   // For rendering.
        this.ready = false;
    }

    addEdge(u, v, id) {
        var w = Math.random() * 1000;
        this.matrix[u].push(new Edge(u, v, w, id));
        this.matrix[v].push(new Edge(v, u, w, id));
        if (u != INVALID_VERTEX && v != INVALID_VERTEX) {
            this.edgeList.push(new Edge(u, v, w, id));
        }
    }

    generate() {
        var id = 0;
    
        this.matrix = [[]];
        this.edgeList = [];

        for (var i = 0; i < this.size; i++) {
            this.matrix.push([]);
        }

        for (var i = 1; i <= this.size; i++) {
            // Add left edge.
            id++;
            if (i % this.width == 1) {
                this.addEdge(i, INVALID_VERTEX, id)
            } else {
                this.addEdge(i, i - 1, id);
            }
            // Add top edge.
            id++;
            if (i <= this.width) {
                this.addEdge(i, INVALID_VERTEX, id);
            } else {
                this.addEdge(i, i - this.width, id);
            }
        }
    }

    // This is a bad one. :(
    modifyEdge(id, tag) {
        for (var i = 0; i < this.edgeList.length; i++) {
            if (this.edgeList[i].id == id) {
                this.edgeList[i].tag = tag;
            }
        }
    }

    getEdgeTag(id) {
        for (var i = 0; i < this.edgeList.length; i++) {
            if (this.edgeList[i].id == id) {
                return this.edgeList[i].tag;
            }
        }
        return EDGE_NONE;
    }

    reset() {
        for (var i = 0; i < this.edgeList.length; i++) {
            if (this.edgeList[i].tag != EDGE_NONE) {
                this.edgeList[i].tag = EDGE_FLOOR;
            }
        }
    }

    print() {
        console.log("----- Graph ------");
        console.log(" width: " + this.width);
        console.log("height: " + this.height)
        console.log(this.matrix);
        console.log(this.edgeList);
        console.log("------------------");
    }
}

// Global graph.
var maze = null;
